import argparse
import unicodedata
import warnings
from dataclasses import dataclass, field
from pathlib import Path

import cv2              # pip install opencv-python
import pytesseract      # pip install pytesseract, sudo apt install tesseract-ocr tesseract-ocr-kor

# 역할: Samsung Health 학습 데이터 폴더의 경로
TESSDATA_DIR = Path(__file__).resolve().parent / "tessdata_for_samsung_health"

PRINT_OCR_LINES = False             #! OCR 원문 행 출력 스위치
PRINT_PARSED_SWIM_RECORDS = True    #! 정돈된 수영 기록 출력 스위치
PRINT_IM_EVALUATION = True          #! IM 기록평가 출력 스위치
PRINT_STROKE_EVALUATION = True      #! 영법별 기록평가 출력 스위치

# 역할: OCR 영법 문자열의 접두어를 표준 영법명으로 변환하는 규칙
STROKE_PREFIXES = (
    ("자", "자유"),
    ("접", "접영"),
    ("배", "배영"),
    ("평", "평영"),
    ("H", "배영"),
    ("킥", "킥판"),
    ("혼", "혼영"),
)


@dataclass
class SwimRecord:
    """한 랩 또는 IM 세션의 거리·시간·휴식·구간 데이터를 보관

    Attributes:
        lap_number: 첫 랩 번호
        stroke: 표준 영법 이름 또는 IM
        time_seconds: 기록 시간(초)
        rest_seconds: 기록에 연결된 휴식 시간(초)
        distance_m: 기록 거리(미터)
        rest_count: 기록에 포함된 휴식 횟수
        lap_count: 이 기록이 포함하는 랩 수
        splits_seconds: IM 세션의 구간별 기록(초)
    """

    lap_number: int
    stroke: str
    time_seconds: float
    rest_seconds: float
    distance_m: int
    rest_count: int = 0
    lap_count: int = 1
    splits_seconds: tuple[float, ...] = field(default_factory=tuple)


@dataclass(frozen=True)
class StrokeSummary:
    """한 영법의 누적 랩·거리·시간·페이스·휴식 평가 데이터

    Attributes:
        stroke: 영법 이름
        lap_count: 누적 랩 수
        total_time_seconds: 총 기록 시간(초)
        total_distance_m: 총 거리(미터)
        pace_seconds_per_100m: 100m 기준 페이스(초)
        rest_count: 휴식 횟수
        total_rest_seconds: 총 휴식 시간(초)
    """

    stroke: str
    lap_count: int
    total_time_seconds: float
    total_distance_m: int
    pace_seconds_per_100m: float
    rest_count: int
    total_rest_seconds: float


@dataclass
class _StrokeTotals:
    """영법별 평가를 계산할 때 사용하는 내부 누적 데이터

    Attributes:
        lap_count: 누적 랩 수
        total_time_seconds: 누적 기록 시간(초)
        total_distance_m: 누적 거리(미터)
        rest_count: 휴식 횟수
        total_rest_seconds: 누적 휴식 시간(초)
    """

    lap_count: int = 0
    total_time_seconds: float = 0.0
    total_distance_m: int = 0
    rest_count: int = 0
    total_rest_seconds: float = 0.0


def extract_image(image_path: Path) -> list[str]:
    """이미지의 OCR 결과를 줄 단위 문자열 목록으로 반환

    Args:
        image_path: OCR 처리할 이미지 경로

    Returns:
        OCR 인식 텍스트를 줄 단위로 나눈 행 목록

    Raises:
        ValueError: 이미지를 읽지 못한 경우
    """
    image = cv2.imread(str(image_path))
    if image is None:
        raise ValueError(f"이미지를 읽을 수 없습니다: {image_path}")

    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gray = cv2.resize(
        gray,
        None,
        fx=1.5,
        fy=1.5,
        interpolation=cv2.INTER_CUBIC,
    )
    text = pytesseract.image_to_string(
        gray,
        lang="kor+eng",
        config=f'--tessdata-dir "{TESSDATA_DIR}" --psm 6',
    )
    return text.splitlines()


def parse_lap_number_prefix(text: str) -> tuple[int, int] | None:
    """문자열 앞의 숫자 접두어를 랩 번호와 다음 문자 위치로 변환

    Args:
        text: OCR 행 문자열

    Returns:
        랩 번호와 번호 뒤 문자 위치의 튜플. 숫자 접두어가 없으면 None
    """
    lap_number_end = 0
    while lap_number_end < len(text) and text[lap_number_end].isdigit():
        lap_number_end += 1

    if lap_number_end == 0:
        return None

    return int(text[:lap_number_end]), lap_number_end


def find_time(
    text: str,
    start_at: int = 0,
) -> tuple[int, float, int, int] | None:
    """문자열에서 분:초 형식의 첫 시간값과 문자 위치를 찾음

    Args:
        text: 시간 문자열을 찾을 OCR 행
        start_at: 검색을 시작할 문자 위치

    Returns:
        분, 초, 시작 위치, 끝 위치의 튜플. 유효한 시간이 없으면 None
    """
    colon_position = start_at

    while colon_position < len(text):
        if text[colon_position] != ":":
            colon_position += 1
            continue

        minute_start = colon_position
        while minute_start > start_at and text[minute_start - 1].isdigit():
            minute_start -= 1

        if minute_start == colon_position:
            colon_position += 1
            continue

        seconds_start = colon_position + 1
        seconds_end = seconds_start + 2
        if (
            seconds_end > len(text)
            or not text[seconds_start:seconds_end].isdigit()
        ):
            colon_position += 1
            continue

        if seconds_end < len(text) and text[seconds_end] == ".":
            fraction_end = seconds_end + 1
            while fraction_end < len(text) and text[fraction_end].isdigit():
                fraction_end += 1
            if fraction_end > seconds_end + 1:
                seconds_end = fraction_end

        minutes = int(text[minute_start:colon_position])
        seconds = float(text[seconds_start:seconds_end])
        return minutes, seconds, minute_start, seconds_end

    return None


def parse_swim_records(
    ocr_lines: list[str],
    pool_length_m: int,
) -> list[SwimRecord]:
    """OCR 행을 거리와 시간 정보가 있는 수영 기록으로 변환

    Args:
        ocr_lines: 이미지에서 인식한 OCR 행
        pool_length_m: 한 랩의 수영장 길이(미터)

    Returns:
        랩 번호, 영법, 시간, 휴식, 거리가 채워진 수영 기록
    """
    swim_records: list[SwimRecord] = []
    last_swim_record: SwimRecord | None = None
    passed_num = False

    for line in ocr_lines:
        text = line.strip()
        if text and text[0].isdigit():
            passed_num = True
        if not passed_num or not text:
            continue

        lap_prefix = parse_lap_number_prefix(text)
        if lap_prefix is not None:
            lap_number, stroke_start = lap_prefix
            time_value = find_time(text, stroke_start)
            if time_value is None:
                warnings.warn(
                    f"랩 시간 OCR을 해석하지 못했습니다: {text!r}",
                    RuntimeWarning,
                )
                continue

            minutes, seconds, time_start, _ = time_value
            stroke_text = "".join(
                character
                for character in text[stroke_start:time_start]
                if not character.isspace()
            )
            stroke = next(
                (
                    name for prefix, name in STROKE_PREFIXES
                    if stroke_text.startswith(prefix)
                ),
                "기타",
            )
            lap_time = round(minutes * 60 + seconds, 6)
            record = SwimRecord(
                lap_number=lap_number,
                stroke=stroke,
                time_seconds=lap_time,
                rest_seconds=0.0,
                distance_m=pool_length_m,
            )
            swim_records.append(record)
            last_swim_record = record
            continue

        rest_time = find_time(text)
        if rest_time is None:
            warnings.warn(
                f"OCR 행을 랩 또는 휴식으로 해석하지 못했습니다: {text!r}",
                RuntimeWarning,
            )
            continue
        if last_swim_record is None:
            warnings.warn(
                f"앞에 연결할 랩 기록이 없는 휴식 행입니다: {text!r}",
                RuntimeWarning,
            )
            continue

        minutes, seconds, _, _ = rest_time
        last_swim_record.rest_seconds = round(minutes * 60 + seconds, 6)
        last_swim_record.rest_count = 1

    return swim_records


def find_im_records(swim_records: list[SwimRecord]) -> list[SwimRecord]:
    """연속된 접·배·평·자유 랩을 IM 기록으로 합산

    Args:
        swim_records: 파싱된 원본 랩 기록

    Returns:
        네 영법을 합산하고 구간별 기록을 포함한 IM 기록
    """
    im_records = []
    strokes = ("접영", "배영", "평영", "자유")

    for start in range(len(swim_records) - len(strokes) + 1):
        laps = swim_records[start:start + len(strokes)]
        if tuple(lap.stroke for lap in laps) != strokes:
            continue
        if any(
            laps[index].lap_number + 1 != laps[index + 1].lap_number
            for index in range(len(laps) - 1)
        ):
            continue

        im_records.append(
            SwimRecord(
                lap_number=laps[0].lap_number,
                stroke="IM",
                time_seconds=round(
                    sum(lap.time_seconds for lap in laps),
                    6,
                ),
                rest_seconds=round(
                    sum(lap.rest_seconds for lap in laps[:-1]),
                    6,
                ),
                distance_m=sum(lap.distance_m for lap in laps),
                rest_count=sum(lap.rest_count for lap in laps[:-1]),
                lap_count=len(laps),
                splits_seconds=tuple(lap.time_seconds for lap in laps),
            )
        )

    return im_records


def summarize_by_stroke(
    swim_records: list[SwimRecord],
) -> list[StrokeSummary]:
    """원본 랩 기록을 영법별 누계와 100m 페이스로 요약

    Args:
        swim_records: 파싱된 원본 랩 기록

    Returns:
        각 영법의 랩 수, 거리, 시간, 페이스, 휴식 집계
    """
    totals: dict[str, _StrokeTotals] = {}

    for record in swim_records:
        summary = totals.setdefault(record.stroke, _StrokeTotals())
        summary.lap_count += record.lap_count
        summary.total_time_seconds += record.time_seconds
        summary.total_distance_m += record.distance_m
        if record.rest_count > 0 or record.rest_seconds > 0:
            summary.rest_count += record.rest_count or 1
            summary.total_rest_seconds += record.rest_seconds

    summaries = []
    for stroke, summary in totals.items():
        total_time = round(summary.total_time_seconds, 6)
        total_distance = summary.total_distance_m
        summaries.append(
            StrokeSummary(
                stroke=stroke,
                lap_count=summary.lap_count,
                total_time_seconds=total_time,
                total_distance_m=total_distance,
                pace_seconds_per_100m=(
                    round(total_time * 100 / total_distance, 6)
                    if total_distance
                    else 0.0
                ),
                rest_count=summary.rest_count,
                total_rest_seconds=round(summary.total_rest_seconds, 6),
            )
        )

    return summaries


def format_duration(seconds: float) -> str:
    """초 값을 소수 첫째 자리까지 표시하는 문자열로 변환

    Args:
        seconds: 변환할 시간(초)

    Returns:
        초 단위 접미사(s)가 붙은 시간 문자열
    """
    return f"{seconds:.1f}s"


def format_swim_records(swim_records: list[SwimRecord]) -> str:
    """수영 기록 목록을 열 너비가 정렬된 표 문자열로 변환

    Args:
        swim_records: 표시할 랩 기록

    Returns:
        랩, 영법, 거리, 기록, 휴식 열을 가진 표 문자열
    """
    if not swim_records:
        return "수영 기록을 찾을 수 없습니다."

    rows = [
        [
            str(record.lap_number),
            record.stroke,
            f"{record.distance_m}m",
            format_duration(record.time_seconds),
            (
                format_duration(record.rest_seconds)
                if record.rest_count > 0 or record.rest_seconds > 0
                else "-"
            ),
        ]
        for record in swim_records
    ]
    return format_table(
        ["랩", "영법", "거리", "기록", "휴식"],
        rows,
    )


def format_table(headers: list[str], rows: list[list[str]]) -> str:
    """머리글과 데이터 행을 열 너비에 맞춰 정렬된 표로 변환

    Args:
        headers: 표 머리글
        rows: 표 데이터 행

    Returns:
        한글 표시 너비를 고려해 정렬된 표 문자열
    """
    widths = [
        max(
            display_width(header),
            *(display_width(row[index]) for row in rows),
        )
        for index, header in enumerate(headers)
    ]
    separator = "-+-".join("-" * width for width in widths)
    formatted_rows = [
        " | ".join(
            cell + " " * (widths[index] - display_width(cell))
            for index, cell in enumerate(row)
        )
        for row in [headers, *rows]
    ]
    return "\n".join(
        [formatted_rows[0], separator, *formatted_rows[1:]]
    )


def display_width(value: str) -> int:
    """한글·영문 혼합 문자열이 차지하는 터미널 칸 수를 계산

    Args:
        value: 표시 너비를 계산할 문자열

    Returns:
        터미널에서 문자열이 차지하는 칸 수
    """
    return sum(
        2 if unicodedata.east_asian_width(character) in ("F", "W") else 1
        for character in value
    )


def print_im_evaluation(im_records: list[SwimRecord]) -> None:
    """IM 세션별 기록과 평균을 표로 출력

    Args:
        im_records: 출력할 IM 세션 기록

    Returns:
        IM 세션별 기록과 평균을 표준 출력으로 표시
    """
    print("IM 기록평가")
    if not im_records:
        print("수행된 IM 세션을 찾을 수 없습니다.")
        return

    average_time = (
        sum(record.time_seconds for record in im_records) / len(im_records)
    )
    average_distance = (
        sum(record.distance_m for record in im_records) / len(im_records)
    )
    average_pace = (
        average_time * 100 / average_distance if average_distance else 0.0
    )
    average_rest_count = (
        sum(record.rest_count for record in im_records) / len(im_records)
    )
    average_rest_seconds = (
        sum(record.rest_seconds for record in im_records) / len(im_records)
    )
    average_splits = tuple(
        sum(
            record.splits_seconds[index]
            for record in im_records
            if index < len(record.splits_seconds)
        )
        / sum(index < len(record.splits_seconds) for record in im_records)
        for index in range(
            max(len(record.splits_seconds) for record in im_records)
        )
    )
    rows = [
        [
            f"{index}세션",
            f"IM{record.distance_m}",
            (
                f"{record.lap_number}-"
                f"{record.lap_number + record.lap_count - 1}"
            ),
            format_duration(record.time_seconds),
            (
                f"{format_duration(record.time_seconds * 100 / record.distance_m)}"
                "/100m"
            ),
            " / ".join(
                format_duration(split) for split in record.splits_seconds
            ),
            str(record.rest_count),
            format_duration(record.rest_seconds),
        ]
        for index, record in enumerate(im_records, start=1)
    ]
    rows.append(
        [
            "평균",
            f"{average_distance:.0f}m",
            f"{len(im_records)}세션",
            format_duration(average_time),
            f"{format_duration(average_pace)}/100m",
            " / ".join(
                format_duration(split) for split in average_splits
            ),
            f"{average_rest_count:.1f}",
            format_duration(average_rest_seconds),
        ]
    )
    print(
        format_table(
            [
                "세션",
                "거리",
                "랩",
                "기록",
                "페이스(/100m)",
                "구간 기록 (접/배/평/자)",
                "휴식 횟수",
                "휴식 시간",
            ],
            rows,
        )
    )


def print_stroke_evaluation(summaries: list[StrokeSummary]) -> None:
    """영법별 기록과 전체 누계를 표로 출력

    Args:
        summaries: 출력할 영법별 집계

    Returns:
        영법별 기록과 전체 누계를 표준 출력으로 표시
    """
    print("영법별 기록평가")
    if not summaries:
        print("평가할 수영 기록이 없습니다.")
        return

    total_laps = sum(summary.lap_count for summary in summaries)
    total_time = round(
        sum(summary.total_time_seconds for summary in summaries),
        6,
    )
    total_distance = sum(summary.total_distance_m for summary in summaries)
    total_pace = total_time * 100 / total_distance if total_distance else 0.0
    total_rest_count = sum(summary.rest_count for summary in summaries)
    total_rest_seconds = round(
        sum(summary.total_rest_seconds for summary in summaries),
        6,
    )
    rows = [
        [
            summary.stroke,
            str(summary.lap_count),
            f"{summary.total_distance_m}m",
            format_duration(summary.total_time_seconds),
            f"{format_duration(summary.pace_seconds_per_100m)}/100m",
            str(summary.rest_count),
            format_duration(summary.total_rest_seconds),
        ]
        for summary in summaries
    ]
    rows.append(
        [
            "전체",
            str(total_laps),
            f"{total_distance}m",
            format_duration(total_time),
            f"{format_duration(total_pace)}/100m",
            str(total_rest_count),
            format_duration(total_rest_seconds),
        ]
    )
    print(
        format_table(
            [
                "영법",
                "랩수",
                "거리",
                "총 시간",
                "페이스(/100m)",
                "휴식 횟수",
                "휴식 총시간",
            ],
            rows,
        )
    )


def positive_pool_length(value: str) -> int:
    """CLI 수영장 길이를 양의 정수로 변환하고 검증

    Args:
        value: CLI에서 입력된 수영장 길이

    Returns:
        검증된 수영장 길이(미터)

    Raises:
        argparse.ArgumentTypeError: 입력이 정수가 아니거나 0 이하인 경우
    """
    try:
        pool_length = int(value)
    except ValueError as error:
        raise argparse.ArgumentTypeError(
            "수영장 길이는 양의 정수여야 합니다."
        ) from error
    if pool_length <= 0:
        raise argparse.ArgumentTypeError("수영장 길이는 양의 정수여야 합니다.")
    return pool_length


def main() -> None:
    """CLI 인자로 OCR·평가를 실행하고 설정된 결과를 표준 출력으로 표시"""
    parser = argparse.ArgumentParser(
        description="수영 기록 이미지 OCR 추출 및 평가"
    )
    parser.add_argument("image", help="입력 이미지 경로")
    parser.add_argument(
        "pool_length",
        nargs="?",
        type=positive_pool_length,
        default=25,
        help="수영장 길이(m), 기본값: 25",
    )
    args = parser.parse_args()

    ocr_lines = extract_image(Path(args.image))
    swim_records = parse_swim_records(ocr_lines, args.pool_length)
    im_records = find_im_records(swim_records)
    stroke_summaries = summarize_by_stroke(swim_records)

    if PRINT_OCR_LINES:
        print("OCR 인식 행")
        for line in ocr_lines:
            print(line)

    if PRINT_PARSED_SWIM_RECORDS:
        print("\n인식된 수영 기록")
        print(format_swim_records(swim_records))

    if PRINT_IM_EVALUATION:
        print()
        print_im_evaluation(im_records)

    if PRINT_STROKE_EVALUATION:
        print()
        print_stroke_evaluation(stroke_summaries)


if __name__ == "__main__":
    main()
