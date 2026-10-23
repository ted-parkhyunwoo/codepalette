#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <tesseract/baseapi.h>
#include <tesseract/pageiterator.h>

namespace {

constexpr double kScale = 1.5;

struct Word {
    std::string text;
    int x;
    int y;
    int height;

    double center_y() const {
        return y + height / 2.0;
    }
};

struct Line {
    double center_y;
    std::vector<Word> words;
};

struct SwimRecord {
    int lap_number;
    std::string stroke;
    double lap_seconds;
    double rest_seconds = 0.0;
};

struct ImSession {
    double total_seconds;
    std::vector<double> lap_seconds;
};

double round_like_python(double value) {
    return std::nearbyint(value);
}

std::vector<std::string> extract_lines(const std::string& image_path) {
    const cv::Mat image = cv::imread(image_path);
    if (image.empty()) {
        throw std::runtime_error("이미지를 읽을 수 없습니다: " + image_path);
    }

    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::resize(
        gray,
        gray,
        cv::Size(),
        kScale,
        kScale,
        cv::INTER_CUBIC
    );

    tesseract::TessBaseAPI api;
    if (api.Init(nullptr, "kor+eng") != 0) {
        throw std::runtime_error("Tesseract kor+eng 초기화에 실패했습니다.");
    }
    api.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    api.SetImage(
        gray.data,
        gray.cols,
        gray.rows,
        1,
        static_cast<int>(gray.step)
    );
    if (api.Recognize(nullptr) != 0) {
        throw std::runtime_error("Tesseract OCR에 실패했습니다.");
    }

    std::vector<Word> words;
    std::unique_ptr<tesseract::ResultIterator> iterator(api.GetIterator());
    if (iterator) {
        do {
            std::unique_ptr<char[]> text(iterator->GetUTF8Text(tesseract::RIL_WORD));
            if (!text) {
                continue;
            }

            std::string word_text(text.get());
            const auto first = word_text.find_first_not_of(" \t\n\r\f\v");
            if (first == std::string::npos) {
                continue;
            }
            const auto last = word_text.find_last_not_of(" \t\n\r\f\v");
            word_text = word_text.substr(first, last - first + 1);

            int left = 0;
            int top = 0;
            int right = 0;
            int bottom = 0;
            if (!iterator->BoundingBox(
                    tesseract::RIL_WORD,
                    &left,
                    &top,
                    &right,
                    &bottom
                )) {
                continue;
            }

            words.push_back({
                word_text,
                static_cast<int>(round_like_python(left / kScale)),
                static_cast<int>(round_like_python(top / kScale)),
                static_cast<int>(round_like_python((bottom - top) / kScale)),
            });
        } while (iterator->Next(tesseract::RIL_WORD));
    }

    std::stable_sort(
        words.begin(),
        words.end(),
        [](const Word& lhs, const Word& rhs) {
            return lhs.center_y() < rhs.center_y();
        }
    );

    std::vector<Line> lines;
    for (const Word& word : words) {
        const double center_y = word.center_y();
        const double threshold = std::max(8.0, word.height * 0.65);
        auto matched = lines.rend();
        for (auto line = lines.rbegin(); line != lines.rend(); ++line) {
            if (center_y - line->center_y > threshold) {
                break;
            }
            if (std::abs(center_y - line->center_y) <= threshold) {
                matched = line;
                break;
            }
        }

        if (matched == lines.rend()) {
            lines.push_back({center_y, {word}});
            continue;
        }

        matched->words.push_back(word);
        double center_sum = 0.0;
        for (const Word& line_word : matched->words) {
            center_sum += line_word.center_y();
        }
        matched->center_y = center_sum / matched->words.size();
    }

    std::vector<std::string> result;
    result.reserve(lines.size());
    for (Line& line : lines) {
        std::stable_sort(
            line.words.begin(),
            line.words.end(),
            [](const Word& lhs, const Word& rhs) {
                return lhs.x < rhs.x;
            }
        );
        std::string text;
        for (const Word& word : line.words) {
            if (!text.empty()) {
                text += ' ';
            }
            text += word.text;
        }
        result.push_back(std::move(text));
    }
    return result;
}

std::string trim(const std::string& value) {
    const auto first = value.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) {
        return {};
    }
    const auto last = value.find_last_not_of(" \t\n\r\f\v");
    return value.substr(first, last - first + 1);
}

std::string remove_whitespace(const std::string& value) {
    std::string result;
    for (unsigned char character : value) {
        if (!std::isspace(character)) {
            result.push_back(static_cast<char>(character));
        }
    }
    return result;
}

std::vector<SwimRecord> fix_swim_record_string_for_samsung_health(
    const std::vector<std::string>& ocr_lines
) {
    static const std::regex lap_pattern(R"(^([0-9]+))");
    static const std::regex time_pattern(R"(([0-9]+):([0-9]{2}(?:\.[0-9]+)?))");

    std::vector<SwimRecord> swim_records;
    std::optional<std::size_t> last_swim_record;
    bool passed_number = false;

    for (const std::string& line : ocr_lines) {
        const std::string text = trim(line);
        if (!text.empty() && std::isdigit(static_cast<unsigned char>(text[0]))) {
            passed_number = true;
        }
        if (!passed_number || text.empty()) {
            continue;
        }

        std::smatch lap_match;
        if (std::regex_search(text, lap_match, lap_pattern)) {
            const std::string after_lap = text.substr(lap_match.length());
            std::smatch time_match;
            if (!std::regex_search(after_lap, time_match, time_pattern)) {
                std::cerr << "경고: 랩 시간 OCR을 해석하지 못했습니다: "
                          << text << '\n';
                continue;
            }

            const std::size_t time_start =
                static_cast<std::size_t>(lap_match.length()) +
                static_cast<std::size_t>(time_match.position());
            std::string stroke = remove_whitespace(
                text.substr(
                    static_cast<std::size_t>(lap_match.length()),
                    time_start - static_cast<std::size_t>(lap_match.length())
                )
            );
            if (stroke.rfind("자", 0) == 0) {
                stroke = "자유";
            } else if (stroke.rfind("접", 0) == 0) {
                stroke = "접영";
            } else if (stroke.rfind("배", 0) == 0) {
                stroke = "배영";
            } else if (stroke.rfind("평", 0) == 0) {
                stroke = "평영";
            } else if (stroke.rfind("H", 0) == 0) {
                stroke = "배영";
            } else if (stroke.rfind("킥", 0) == 0) {
                stroke = "킥판";
            } else if (stroke.rfind("혼", 0) == 0) {
                stroke = "혼영";
            }

            const int minutes = std::stoi(time_match[1].str());
            const double seconds = std::stod(time_match[2].str());
            swim_records.push_back({
                std::stoi(lap_match[1].str()),
                stroke,
                minutes * 60.0 + seconds,
                0.0,
            });
            last_swim_record = swim_records.size() - 1;
            continue;
        }

        std::smatch rest_match;
        if (std::regex_search(text, rest_match, time_pattern)) {
            if (!last_swim_record) {
                std::cerr << "경고: 앞에 연결할 랩 기록이 없는 휴식 행입니다: "
                          << text << '\n';
                continue;
            }
            swim_records[*last_swim_record].rest_seconds =
                std::stoi(rest_match[1].str()) * 60.0 +
                std::stod(rest_match[2].str());
        } else {
            std::cerr << "경고: OCR 행을 랩 또는 휴식으로 해석하지 못했습니다: "
                      << text << '\n';
        }
    }
    return swim_records;
}

std::vector<ImSession> find_im_sessions(
    const std::vector<SwimRecord>& swim_records
) {
    std::vector<std::size_t> starts;
    for (std::size_t i = 0; i + 3 < swim_records.size(); ++i) {
        if (
            swim_records[i].stroke.rfind("접", 0) == 0 &&
            swim_records[i + 1].stroke.rfind("배", 0) == 0 &&
            swim_records[i + 2].stroke.rfind("평", 0) == 0 &&
            swim_records[i + 3].stroke.rfind("자", 0) == 0
        ) {
            starts.push_back(i);
            i += 3;
        }
    }

    std::vector<ImSession> sessions;
    for (const std::size_t start : starts) {
        ImSession session{0.0, {}};
        for (std::size_t offset = 0; offset < 4; ++offset) {
            const double lap_seconds = swim_records[start + offset].lap_seconds;
            session.total_seconds += lap_seconds;
            session.lap_seconds.push_back(lap_seconds);
        }
        sessions.push_back(std::move(session));
    }
    return sessions;
}

void print_results(const std::vector<SwimRecord>& swim_records) {
    int total_rest = 0;
    double total_rest_seconds = 0.0;
    bool lap_warning = false;
    const int start_lap_number = swim_records.empty()
        ? 0
        : swim_records.front().lap_number;

    for (std::size_t index = 0; index < swim_records.size(); ++index) {
        const SwimRecord& record = swim_records[index];
        if (
            !lap_warning &&
            record.lap_number != start_lap_number + static_cast<int>(index)
        ) {
            lap_warning = true;
        }

        std::cout << record.lap_number << ' '
                  << record.stroke << ' '
                  << std::fixed << std::setprecision(3)
                  << record.lap_seconds << ' ';
        if (record.rest_seconds != 0.0) {
            std::cout << std::setprecision(1) << record.rest_seconds;
            ++total_rest;
            total_rest_seconds += record.rest_seconds;
        }
        std::cout << '\n';
    }

    std::cout << "\t-> Total lap: " << swim_records.size()
              << "  Rest: " << total_rest
              << "  Rest seconds: " << std::fixed << std::setprecision(1)
              << total_rest_seconds << "\n\n";

    if (lap_warning) {
        std::cout << "[경고]누락된 랩이 있을 수 있음\n";
    }

    const std::vector<ImSession> sessions = find_im_sessions(swim_records);
    if (sessions.empty()) {
        std::cout << "수행된 im100 세션을 찾을 수 없습니다.\n";
        return;
    }

    std::cout << "im100 세션 " << sessions.size() << "개를 찾았습니다.\n";
    for (std::size_t index = 0; index < sessions.size(); ++index) {
        const ImSession& session = sessions[index];
        std::cout << index + 1 << "번 세션: " << session.total_seconds << "s [";
        for (std::size_t lap = 0; lap < session.lap_seconds.size(); ++lap) {
            if (lap > 0) {
                std::cout << ", ";
            }
            std::cout << session.lap_seconds[lap];
        }
        std::cout << "]\n";
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "사용법: " << argv[0] << " <이미지 경로>\n";
        return 2;
    }

    try {
        const std::vector<std::string> ocr_lines = extract_lines(argv[1]);
        const std::vector<SwimRecord> swim_records =
            fix_swim_record_string_for_samsung_health(ocr_lines);
        print_results(swim_records);
    } catch (const std::exception& error) {
        std::cerr << "오류: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
