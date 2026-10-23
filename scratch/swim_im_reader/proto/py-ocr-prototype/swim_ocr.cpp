#include <cctype>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <tesseract/baseapi.h>

namespace {

constexpr double kScale = 1.5;

struct SwimRecord {
    int lap_number;
    std::string stroke;
    double lap_seconds;
    double rest_seconds = 0.0;
};

// 이미지 전처리 후 Tesseract가 인식한 행 문자열을 반환합니다.
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
    if (api.Init(SWIM_OCR_TESSDATA_DIR, "kor+eng") != 0) {
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

    std::unique_ptr<char[]> recognized_text(api.GetUTF8Text());
    if (!recognized_text) {
        throw std::runtime_error("Tesseract OCR 결과를 가져오지 못했습니다.");
    }

    std::vector<std::string> result;
    std::string text(recognized_text.get());
    std::size_t line_start = 0;
    while (line_start < text.size()) {
        const std::size_t line_end = text.find('\n', line_start);
        result.push_back(text.substr(
            line_start,
            line_end == std::string::npos ? line_end : line_end - line_start
        ));
        if (line_end == std::string::npos) {
            break;
        }
        line_start = line_end + 1;
    }
    return result;
}

// 문자열 앞뒤의 공백 문자를 제거합니다.
std::string trim(const std::string& value) {
    const auto first = value.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) {
        return {};
    }
    const auto last = value.find_last_not_of(" \t\n\r\f\v");
    return value.substr(first, last - first + 1);
}

// 문자열 내부의 모든 공백 문자를 제거합니다.
std::string remove_whitespace(const std::string& value) {
    std::string result;
    for (unsigned char character : value) {
        if (!std::isspace(character)) {
            result.push_back(static_cast<char>(character));
        }
    }
    return result;
}

// Samsung Health OCR 행을 랩 기록으로 변환하고 휴식 시간을 해당 랩에 연결합니다.
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
            } else {
                stroke = "????";
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

// 연속된 접배평자 랩을 찾아 IM100 기록을 출력합니다.
std::vector<std::size_t> find_im_session_starts(
    const std::vector<SwimRecord>& swim_records
) {
    std::vector<std::size_t> session_starts;
    for (std::size_t i = 0; i + 4 <= swim_records.size(); ++i) {
        if (
            swim_records[i].stroke.rfind("접", 0) == 0 &&
            swim_records[i + 1].stroke.rfind("배", 0) == 0 &&
            swim_records[i + 2].stroke.rfind("평", 0) == 0 &&
            swim_records[i + 3].stroke.rfind("자", 0) == 0
        ) {
            session_starts.push_back(i);
        }
    }

    return session_starts;
}

// 숫자를 불필요한 0 없이 문자열로 변환합니다.
std::string format_number(double value) {
    std::ostringstream output;
    output << std::setprecision(15) << value;
    std::string result = output.str();
    if (result.find('.') == std::string::npos &&
        result.find('e') == std::string::npos) {
        result += ".0";
    }
    return result;
}

// 랩별 기록과 총계 및 누락 여부를 출력합니다.
void print_results(const std::vector<SwimRecord>& swim_records) {
    if (swim_records.empty()) {
        std::cout << "수영 기록을 찾을 수 없습니다.\n";
        std::cout << "수행된 im100 세션을 찾을 수 없습니다.\n";
        return;
    }

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

        std::cout << record.lap_number << ": "
                  << record.stroke << ' '
                  << std::fixed << std::setprecision(3) << record.lap_seconds
                  << ' ';
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

    const std::vector<std::size_t> session_starts =
        find_im_session_starts(swim_records);
    if (session_starts.empty()) {
        std::cout << "수행된 im100 세션을 찾을 수 없습니다.\n";
        return;
    }

    std::cout << "im100 세션 기록 " << session_starts.size()
              << "개를 찾았습니다.\n";
    for (std::size_t index = 0; index < session_starts.size(); ++index) {
        const std::size_t start = session_starts[index];
        double total_seconds = 0.0;
        std::vector<double> lap_seconds;
        lap_seconds.reserve(4);
        for (std::size_t offset = 0; offset < 4; ++offset) {
            const double seconds = swim_records[start + offset].lap_seconds;
            total_seconds += seconds;
            lap_seconds.push_back(seconds);
        }

        std::cout << index + 1 << "세션: " << format_number(total_seconds)
                  << "s (";
        for (std::size_t offset = 0; offset < lap_seconds.size(); ++offset) {
            if (offset > 0) {
                std::cout << ", ";
            }
            std::cout << format_number(lap_seconds[offset]);
        }
        std::cout << ") 랩: " << swim_records[start].lap_number
                  << " - " << swim_records[start].lap_number + 3 << '\n';
    }
}

}  // namespace

// 입력 이미지의 OCR을 수행하고 수영 기록을 분석해 출력합니다.
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
