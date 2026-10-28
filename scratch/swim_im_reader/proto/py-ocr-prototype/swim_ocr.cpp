#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <tesseract/baseapi.h>

namespace {

constexpr double kScale = 1.5;
constexpr bool kPrintOcrLines = false;  //! OCR 원문 행 출력 스위치
constexpr bool kPrintParsedRecords = true;  //! 정돈된 수영 기록 출력 스위치
constexpr bool kPrintImEvaluation = true;  //! IM 기록평가 출력 스위치
constexpr bool kPrintStrokeEvaluation = true;  //! 영법별 기록평가 출력 스위치

struct SwimRecord {
    int lap_number;
    std::string stroke;
    double time_seconds;
    double rest_seconds = 0.0;
    int distance_m = 0;
    int rest_count = 0;
    int lap_count = 1;
    std::vector<double> splits_seconds;
};

struct StrokeSummary {
    std::string stroke;
    int lap_count = 0;
    double total_time_seconds = 0.0;
    int total_distance_m = 0;
    double pace_seconds_per_100m = 0.0;
    int rest_count = 0;
    double total_rest_seconds = 0.0;
};

struct TimeValue {
    int minutes;
    double seconds;
    std::size_t start;
    std::size_t end;
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

    std::vector<std::string> lines;
    const std::string text(recognized_text.get());
    std::size_t line_start = 0;
    while (line_start < text.size()) {
        const std::size_t line_end = text.find('\n', line_start);
        lines.push_back(text.substr(
            line_start,
            line_end == std::string::npos ? line_end : line_end - line_start
        ));
        if (line_end == std::string::npos) {
            break;
        }
        line_start = line_end + 1;
    }
    return lines;
}

// 문자열 앞뒤의 공백 문자를 제거합니다.
std::string trim(const std::string& value) {
    const std::size_t first = value.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) {
        return {};
    }
    const std::size_t last = value.find_last_not_of(" \t\n\r\f\v");
    return value.substr(first, last - first + 1);
}

// 지정된 위치부터 분:초 형식의 첫 시간값과 문자 위치를 찾습니다.
std::optional<TimeValue> find_time(
    const std::string& text,
    std::size_t start_at = 0
) {
    for (std::size_t colon = start_at; colon < text.size(); ++colon) {
        if (text[colon] != ':') {
            continue;
        }

        std::size_t minute_start = colon;
        while (
            minute_start > start_at &&
            std::isdigit(static_cast<unsigned char>(text[minute_start - 1]))
        ) {
            --minute_start;
        }
        if (minute_start == colon) {
            continue;
        }

        const std::size_t seconds_start = colon + 1;
        const std::size_t seconds_end = seconds_start + 2;
        if (seconds_end > text.size()) {
            continue;
        }
        if (
            !std::isdigit(static_cast<unsigned char>(text[seconds_start])) ||
            !std::isdigit(static_cast<unsigned char>(text[seconds_start + 1]))
        ) {
            continue;
        }

        std::size_t time_end = seconds_end;
        if (time_end < text.size() && text[time_end] == '.') {
            ++time_end;
            const std::size_t fraction_start = time_end;
            while (
                time_end < text.size() &&
                std::isdigit(static_cast<unsigned char>(text[time_end]))
            ) {
                ++time_end;
            }
            if (fraction_start == time_end) {
                time_end = seconds_end;
            }
        }

        const int minutes = std::stoi(
            text.substr(minute_start, colon - minute_start)
        );
        const double seconds = std::stod(
            text.substr(seconds_start, time_end - seconds_start)
        );
        return TimeValue{minutes, seconds, minute_start, time_end};
    }
    return std::nullopt;
}

// OCR 행을 거리와 시간 정보가 있는 수영 기록으로 변환합니다.
std::vector<SwimRecord> parse_swim_records(
    const std::vector<std::string>& ocr_lines,
    int pool_length_m
) {
    std::vector<SwimRecord> records;
    std::optional<std::size_t> last_record;
    bool passed_number = false;

    for (const std::string& line : ocr_lines) {
        const std::string text = trim(line);
        if (
            !text.empty() &&
            std::isdigit(static_cast<unsigned char>(text.front()))
        ) {
            passed_number = true;
        }
        if (!passed_number || text.empty()) {
            continue;
        }

        std::size_t lap_end = 0;
        while (
            lap_end < text.size() &&
            std::isdigit(static_cast<unsigned char>(text[lap_end]))
        ) {
            ++lap_end;
        }

        if (lap_end > 0) {
            const std::optional<TimeValue> time = find_time(text, lap_end);
            if (!time) {
                std::cerr << "경고: 랩 시간 OCR을 해석하지 못했습니다: "
                          << text << '\n';
                continue;
            }

            std::string stroke_text;
            for (std::size_t index = lap_end; index < time->start; ++index) {
                if (!std::isspace(static_cast<unsigned char>(text[index]))) {
                    stroke_text.push_back(text[index]);
                }
            }

            std::string stroke = "기타";
            if (stroke_text.rfind("자", 0) == 0) {
                stroke = "자유";
            } else if (stroke_text.rfind("접", 0) == 0) {
                stroke = "접영";
            } else if (stroke_text.rfind("배", 0) == 0) {
                stroke = "배영";
            } else if (stroke_text.rfind("평", 0) == 0) {
                stroke = "평영";
            } else if (stroke_text.rfind("H", 0) == 0) {
                stroke = "배영";
            } else if (stroke_text.rfind("킥", 0) == 0) {
                stroke = "킥판";
            } else if (stroke_text.rfind("혼", 0) == 0) {
                stroke = "혼영";
            }

            records.push_back({
                std::stoi(text.substr(0, lap_end)),
                stroke,
                time->minutes * 60.0 + time->seconds,
                0.0,
                pool_length_m,
                0,
                1,
                {},
            });
            last_record = records.size() - 1;
            continue;
        }

        const std::optional<TimeValue> rest = find_time(text);
        if (!rest) {
            std::cerr << "경고: OCR 행을 랩 또는 휴식으로 해석하지 못했습니다: "
                      << text << '\n';
            continue;
        }
        if (!last_record) {
            std::cerr << "경고: 앞에 연결할 랩 기록이 없는 휴식 행입니다: "
                      << text << '\n';
            continue;
        }

        SwimRecord& record = records[*last_record];
        record.rest_seconds = rest->minutes * 60.0 + rest->seconds;
        record.rest_count = 1;
    }
    return records;
}

// 연속된 접·배·평·자유 랩을 IM 기록으로 합산합니다.
std::vector<SwimRecord> find_im_records(
    const std::vector<SwimRecord>& records
) {
    const std::vector<std::string> strokes = {"접영", "배영", "평영", "자유"};
    std::vector<SwimRecord> im_records;

    for (std::size_t start = 0; start + strokes.size() <= records.size(); ++start) {
        bool matches = true;
        for (std::size_t offset = 0; offset < strokes.size(); ++offset) {
            if (records[start + offset].stroke != strokes[offset]) {
                matches = false;
                break;
            }
            if (
                offset > 0 &&
                records[start + offset - 1].lap_number + 1 !=
                    records[start + offset].lap_number
            ) {
                matches = false;
                break;
            }
        }
        if (!matches) {
            continue;
        }

        SwimRecord im_record{
            records[start].lap_number,
            "IM",
            0.0,
            0.0,
            0,
            0,
            static_cast<int>(strokes.size()),
            {},
        };
        for (std::size_t offset = 0; offset < strokes.size(); ++offset) {
            const SwimRecord& lap = records[start + offset];
            im_record.time_seconds += lap.time_seconds;
            im_record.distance_m += lap.distance_m;
            im_record.splits_seconds.push_back(lap.time_seconds);
            if (offset + 1 < strokes.size()) {
                im_record.rest_seconds += lap.rest_seconds;
                im_record.rest_count += lap.rest_count;
            }
        }
        im_records.push_back(im_record);
    }
    return im_records;
}

// 원본 랩 기록을 영법별 누계와 100m 페이스로 요약합니다.
std::vector<StrokeSummary> summarize_by_stroke(
    const std::vector<SwimRecord>& records
) {
    std::vector<StrokeSummary> summaries;
    std::map<std::string, std::size_t> summary_indices;
    for (const SwimRecord& record : records) {
        auto found = summary_indices.find(record.stroke);
        if (found == summary_indices.end()) {
            const std::size_t index = summaries.size();
            summary_indices[record.stroke] = index;
            summaries.push_back({record.stroke});
            found = summary_indices.find(record.stroke);
        }

        StrokeSummary& summary = summaries[found->second];
        summary.lap_count += record.lap_count;
        summary.total_time_seconds += record.time_seconds;
        summary.total_distance_m += record.distance_m;
        if (record.rest_count > 0 || record.rest_seconds > 0.0) {
            summary.rest_count += record.rest_count > 0 ? record.rest_count : 1;
            summary.total_rest_seconds += record.rest_seconds;
        }
    }

    for (StrokeSummary& summary : summaries) {
        if (summary.total_distance_m > 0) {
            summary.pace_seconds_per_100m =
                summary.total_time_seconds * 100.0 / summary.total_distance_m;
        }
    }
    return summaries;
}

// 초 값을 소수 첫째 자리까지 표시하는 문자열로 변환합니다.
std::string format_duration(double seconds) {
    std::ostringstream output;
    output << std::fixed << std::setprecision(1) << seconds << 's';
    return output.str();
}

// 한글과 영문 혼합 문자열의 터미널 표시 너비를 계산합니다.
std::size_t display_width(const std::string& value) {
    std::size_t width = 0;
    for (unsigned char character : value) {
        if ((character & 0xC0) != 0x80) {
            width += character >= 0x80 ? 2 : 1;
        }
    }
    return width;
}

// 머리글과 데이터 행을 열 너비에 맞춰 정렬된 표로 변환합니다.
std::string format_table(
    const std::vector<std::string>& headers,
    const std::vector<std::vector<std::string>>& rows
) {
    std::vector<std::size_t> widths;
    for (std::size_t column = 0; column < headers.size(); ++column) {
        std::size_t width = display_width(headers[column]);
        for (const auto& row : rows) {
            width = std::max(width, display_width(row[column]));
        }
        widths.push_back(width);
    }

    auto format_row = [&widths](const std::vector<std::string>& row) {
        std::ostringstream output;
        for (std::size_t column = 0; column < row.size(); ++column) {
            if (column > 0) {
                output << " | ";
            }
            output << row[column]
                   << std::string(widths[column] - display_width(row[column]), ' ');
        }
        return output.str();
    };

    std::ostringstream output;
    output << format_row(headers) << '\n';
    for (std::size_t column = 0; column < widths.size(); ++column) {
        if (column > 0) {
            output << "-+-";
        }
        output << std::string(widths[column], '-');
    }
    for (const auto& row : rows) {
        output << '\n' << format_row(row);
    }
    return output.str();
}

// 수영 기록 목록을 정돈된 표로 변환합니다.
std::string format_swim_records(const std::vector<SwimRecord>& records) {
    if (records.empty()) {
        return "수영 기록을 찾을 수 없습니다.";
    }

    std::vector<std::vector<std::string>> rows;
    for (const SwimRecord& record : records) {
        rows.push_back({
            std::to_string(record.lap_number),
            record.stroke,
            std::to_string(record.distance_m) + "m",
            format_duration(record.time_seconds),
            record.rest_count > 0 || record.rest_seconds > 0.0
                ? format_duration(record.rest_seconds)
                : "-",
        });
    }
    return format_table({"랩", "영법", "거리", "기록", "휴식"}, rows);
}

// IM 세션별 기록과 평균을 표로 출력합니다.
void print_im_evaluation(const std::vector<SwimRecord>& records) {
    std::cout << "IM 기록평가\n";
    if (records.empty()) {
        std::cout << "수행된 IM 세션을 찾을 수 없습니다.\n";
        return;
    }

    double average_time = 0.0;
    double average_distance = 0.0;
    double average_rest_count = 0.0;
    double average_rest_seconds = 0.0;
    std::size_t split_count = 0;
    for (const SwimRecord& record : records) {
        average_time += record.time_seconds;
        average_distance += record.distance_m;
        average_rest_count += record.rest_count;
        average_rest_seconds += record.rest_seconds;
        split_count = std::max(split_count, record.splits_seconds.size());
    }
    const double session_count = static_cast<double>(records.size());
    average_time /= session_count;
    average_distance /= session_count;
    average_rest_count /= session_count;
    average_rest_seconds /= session_count;
    const double average_pace = average_distance > 0.0
        ? average_time * 100.0 / average_distance
        : 0.0;

    std::vector<std::vector<std::string>> rows;
    for (std::size_t index = 0; index < records.size(); ++index) {
        const SwimRecord& record = records[index];
        const double pace = record.distance_m > 0
            ? record.time_seconds * 100.0 / record.distance_m
            : 0.0;
        std::ostringstream lap_range;
        lap_range << record.lap_number << '-'
                  << record.lap_number + record.lap_count - 1;

        std::ostringstream split_text;
        for (std::size_t split = 0; split < record.splits_seconds.size(); ++split) {
            if (split > 0) {
                split_text << " / ";
            }
            split_text << format_duration(record.splits_seconds[split]);
        }

        rows.push_back({
            std::to_string(index + 1) + "세션",
            "IM" + std::to_string(record.distance_m),
            lap_range.str(),
            format_duration(record.time_seconds),
            format_duration(pace) + "/100m",
            split_text.str(),
            std::to_string(record.rest_count),
            format_duration(record.rest_seconds),
        });
    }

    std::vector<double> average_splits(split_count, 0.0);
    std::vector<std::size_t> split_sessions(split_count, 0);
    for (const SwimRecord& record : records) {
        for (std::size_t split = 0; split < record.splits_seconds.size(); ++split) {
            average_splits[split] += record.splits_seconds[split];
            ++split_sessions[split];
        }
    }
    std::ostringstream average_split_text;
    for (std::size_t split = 0; split < split_count; ++split) {
        if (split > 0) {
            average_split_text << " / ";
        }
        average_split_text << format_duration(
            average_splits[split] / static_cast<double>(split_sessions[split])
        );
    }
    std::ostringstream average_distance_text;
    average_distance_text << std::fixed << std::setprecision(0)
                          << average_distance << "m";

    rows.push_back({
        "평균",
        average_distance_text.str(),
        std::to_string(records.size()) + "세션",
        format_duration(average_time),
        format_duration(average_pace) + "/100m",
        average_split_text.str(),
        [&average_rest_count]() {
            std::ostringstream output;
            output << std::fixed << std::setprecision(1) << average_rest_count;
            return output.str();
        }(),
        format_duration(average_rest_seconds),
    });

    std::cout << format_table(
        {
            "세션",
            "거리",
            "랩",
            "기록",
            "페이스(/100m)",
            "구간 기록 (접/배/평/자)",
            "휴식 횟수",
            "휴식 시간",
        },
        rows
    ) << '\n';
}

// 영법별 기록과 전체 누계를 표로 출력합니다.
void print_stroke_evaluation(const std::vector<StrokeSummary>& summaries) {
    std::cout << "영법별 기록평가\n";
    if (summaries.empty()) {
        std::cout << "평가할 수영 기록이 없습니다.\n";
        return;
    }

    int total_laps = 0;
    int total_distance = 0;
    int total_rest_count = 0;
    double total_time = 0.0;
    double total_rest_seconds = 0.0;
    std::vector<std::vector<std::string>> rows;
    for (const StrokeSummary& summary : summaries) {
        total_laps += summary.lap_count;
        total_distance += summary.total_distance_m;
        total_rest_count += summary.rest_count;
        total_time += summary.total_time_seconds;
        total_rest_seconds += summary.total_rest_seconds;
        rows.push_back({
            summary.stroke,
            std::to_string(summary.lap_count),
            std::to_string(summary.total_distance_m) + "m",
            format_duration(summary.total_time_seconds),
            format_duration(summary.pace_seconds_per_100m) + "/100m",
            std::to_string(summary.rest_count),
            format_duration(summary.total_rest_seconds),
        });
    }

    const double total_pace = total_distance > 0
        ? total_time * 100.0 / total_distance
        : 0.0;
    rows.push_back({
        "전체",
        std::to_string(total_laps),
        std::to_string(total_distance) + "m",
        format_duration(total_time),
        format_duration(total_pace) + "/100m",
        std::to_string(total_rest_count),
        format_duration(total_rest_seconds),
    });

    std::cout << format_table(
        {
            "영법",
            "랩수",
            "거리",
            "총 시간",
            "페이스(/100m)",
            "휴식 횟수",
            "휴식 총시간",
        },
        rows
    ) << '\n';
}

// CLI 수영장 길이를 양의 정수로 변환하고 검증합니다.
int positive_pool_length(const std::string& value) {
    std::size_t parsed_characters = 0;
    int pool_length = 0;
    try {
        pool_length = std::stoi(value, &parsed_characters);
    } catch (const std::exception&) {
        throw std::invalid_argument("수영장 길이는 양의 정수여야 합니다.");
    }
    if (parsed_characters != value.size() || pool_length <= 0) {
        throw std::invalid_argument("수영장 길이는 양의 정수여야 합니다.");
    }
    return pool_length;
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "사용법: " << argv[0] << " <이미지 경로> [수영장 길이(m)]\n";
        return 2;
    }

    try {
        const int pool_length_m = argc == 3
            ? positive_pool_length(argv[2])
            : 25;
        const std::vector<std::string> ocr_lines = extract_lines(argv[1]);
        const std::vector<SwimRecord> swim_records =
            parse_swim_records(ocr_lines, pool_length_m);
        const std::vector<SwimRecord> im_records = find_im_records(swim_records);
        const std::vector<StrokeSummary> stroke_summaries =
            summarize_by_stroke(swim_records);

        if (kPrintOcrLines) {
            std::cout << "OCR 인식 행\n";
            for (const std::string& line : ocr_lines) {
                std::cout << line << '\n';
            }
        }
        if (kPrintParsedRecords) {
            std::cout << "\n인식된 수영 기록\n"
                      << format_swim_records(swim_records) << '\n';
        }
        if (kPrintImEvaluation) {
            std::cout << '\n';
            print_im_evaluation(im_records);
        }
        if (kPrintStrokeEvaluation) {
            std::cout << '\n';
            print_stroke_evaluation(stroke_summaries);
        }
    } catch (const std::exception& error) {
        std::cerr << "오류: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
