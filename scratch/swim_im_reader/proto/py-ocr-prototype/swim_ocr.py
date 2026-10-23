import argparse
import re
import warnings
from datetime import timedelta
from pathlib import Path
from typing import cast

import cv2
import pytesseract

#! cv2 는 본인의 테스트 환경에서 .venv 로 실행해야 사용할 수 있는 상태가 보통임

# swim_records (리스트) 형식으로 데이터를 다룸 (구조체 느낌)
# [35, '평영', datetime.timedelta(seconds=25, microseconds=200000), 0.0]
SwimRecord = list[int | str | timedelta | float]

TESSDATA_DIR = Path(__file__).resolve().parent / "tessdata_for_samsung_health"
LAP_NUMBER_PATTERN = re.compile(r"^(\d+)")
TIME_PATTERN = re.compile(r"(\d+):(\d{2}(?:\.\d+)?)")
STROKE_PREFIXES = (
    ("자", "자유"),
    ("접", "접영"),
    ("배", "배영"),
    ("평", "평영"),
    ("H", "배영"),
    ("킥", "킥판"),
    ("혼", "혼영"),
)

# 이미지를 전처리하고 Tesseract에서 인식한 텍스트를 반환함
def extract_image(image_path):
    image = cv2.imread(str(image_path))

    if image is None:
        raise ValueError(f"이미지를 읽을 수 없습니다: {image_path}")

    # OCR 인식률을 높이기 위한 전처리
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gray = cv2.resize(
        gray, None, fx=1.5, fy=1.5,
        interpolation=cv2.INTER_CUBIC
    )

    text = pytesseract.image_to_string(
        gray,
        lang="kor+eng",
        config=f'--tessdata-dir "{TESSDATA_DIR}" --psm 6',
    )

    return text.splitlines()


# OCR 행을 수영 기록 목록으로 변환함
def fix_swim_record_string_for_samsung_health(
    ocr_lines: list[str],
) -> list[SwimRecord]:
    swim_records = []
    last_swim_record: SwimRecord | None = None

    passed_num = False

    for line in ocr_lines:

        # 처음은 숫자가 나올때 까지 보류해버림(랩번호로 추정되는 것이 나올 때 까지)
        s = line.strip()
        if s and s[0].isdigit():
            passed_num = True
        if not passed_num or not s:
            continue

        lap_match = LAP_NUMBER_PATTERN.match(s)
        if lap_match:
            time_match = TIME_PATTERN.search(s, lap_match.end())
            if time_match is None:
                warnings.warn(
                    f"랩 시간 OCR을 해석하지 못했습니다: {s!r}",
                    RuntimeWarning,
                )
                continue

            stroke_text = re.sub(
                r"\s+", "", s[lap_match.end():time_match.start()]
            )
            stroke = next(
                (
                    name for prefix, name in STROKE_PREFIXES
                    if stroke_text.startswith(prefix)
                ),
                "????",
            )

            lap_time = timedelta(
                minutes=int(time_match.group(1)),
                seconds=float(time_match.group(2)),
            )
            record: SwimRecord = [
                int(lap_match.group(1)),
                stroke,
                lap_time,
                0.0,
            ]
            swim_records.append(record)
            last_swim_record = record
        else:
            rest_match = TIME_PATTERN.search(s)
            if rest_match:
                if last_swim_record is None:
                    warnings.warn(
                        f"앞에 연결할 랩 기록이 없는 휴식 행입니다: {s!r}",
                        RuntimeWarning,
                    )
                    continue

                last_swim_record[3] = (
                    int(rest_match.group(1)) * 60
                    + float(rest_match.group(2))
                )
            else:
                warnings.warn(
                    f"OCR 행을 랩 또는 휴식으로 해석하지 못했습니다: {s!r}",
                    RuntimeWarning,
                )

    return swim_records


# 랩별 기록을 출력하고 총계와 누락 여부를 알림
def print_swim_records(swim_records: list[SwimRecord]) -> None:
    if not swim_records:
        print("수영 기록을 찾을 수 없습니다.")
        return

    total_rest = 0
    total_rest_sec = 0.0
    start_lap_num = cast(int, swim_records[0][0])
    lap_warning = False

    for counter, swim_record in enumerate(swim_records):
        lap_number, stroke, lap_time, rest_time = cast(
            tuple[int, str, timedelta, float],
            swim_record,
        )

        if not lap_warning and lap_number != start_lap_num + counter:
            lap_warning = True

        lap_seconds = lap_time.total_seconds()
        rest_display = f"{rest_time:.1f}" if rest_time else ""
        print(f"{lap_number}: {stroke} {lap_seconds:.3f} {rest_display}")

        if rest_time > 0:
            total_rest += 1
            total_rest_sec += rest_time

    total_lap = len(swim_records)
    print(
        f"\t-> Total lap: {total_lap}  Rest: {total_rest}  "
        f"Rest seconds: {total_rest_sec:.1f}"
    )

    print()
    if lap_warning:
        print("[경고]누락된 랩이 있을 수 있음")


# 연속된 접배평자 랩을 찾아 IM100 기록을 출력함
def im_finder(swim_records: list[SwimRecord]) -> None:
    sessions: list[tuple[int, tuple[timedelta, ...]]] = []
    strokes = ("접", "배", "평", "자")

    for start in range(len(swim_records) - len(strokes) + 1):
        laps = swim_records[start:start + len(strokes)]
        if tuple(cast(str, lap[1])[0] for lap in laps) != strokes:
            continue

        lap_number = cast(int, laps[0][0])
        lap_times = tuple(cast(timedelta, lap[2]) for lap in laps)
        sessions.append((lap_number, lap_times))

    if not sessions:
        print("수행된 im100 세션을 찾을 수 없습니다.")
        return

    print(f"im100 세션 기록 {len(sessions)}개를 찾았습니다.")
    for number, (lap_number, lap_times) in enumerate(sessions, start=1):
        total_seconds = sum(lap_times, timedelta()).total_seconds()
        splits = ", ".join(str(lap.total_seconds()) for lap in lap_times)
        print(
            f"{number}세션: {total_seconds}s ({splits}) "
            f"랩: {lap_number} - {lap_number + 3}"
        )

# 이미지에서 수영 기록을 읽고 결과를 출력함
def main():
    parser = argparse.ArgumentParser(
        description="수영 기록 이미지 OCR 추출"
    )
    parser.add_argument("image", help="입력 이미지 경로")
    args = parser.parse_args()

    image_path = Path(args.image)
    ocr_lines = extract_image(image_path)
    swim_records: list[SwimRecord] = (
        fix_swim_record_string_for_samsung_health(ocr_lines)
    )

    # 랩타임 누락검사/랩출력
    print_swim_records(swim_records)
    # im100 연속기록 찾기
    im_finder(swim_records)

if __name__ == "__main__":
    main()
