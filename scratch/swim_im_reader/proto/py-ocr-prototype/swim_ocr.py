

import argparse
import re
import warnings
from datetime import timedelta
from pathlib import Path
from typing import cast

import cv2
import pytesseract
from pytesseract import Output

SwimRecord = list[int | str | float | timedelta]
TESSDATA_DIR = Path(__file__).resolve().parent / "tessdata_for_samsung_health"


def extract_image(image_path):
    image = cv2.imread(str(image_path))

    if image is None:
        raise ValueError(f"이미지를 읽을 수 없습니다: {image_path}")

    height, width = image.shape[:2]

    # OCR 인식률을 높이기 위한 전처리
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gray = cv2.resize(
        gray, None, fx=1.5, fy=1.5,
        interpolation=cv2.INTER_CUBIC
    )

    # 한국어와 영어, 숫자를 함께 인식
    data = pytesseract.image_to_data(
        gray,
        lang="kor+eng",
        config=f'--tessdata-dir "{TESSDATA_DIR}" --psm 6',
        output_type=Output.DICT
    )

    words = []

    for i, text in enumerate(data["text"]):
        text = text.strip()

        if not text:
            continue

        # 전처리로 1.5배 확대했으므로 원본 좌표로 환산
        scale = 1.5
        x = round(data["left"][i] / scale)
        y = round(data["top"][i] / scale)
        h = round(data["height"][i] / scale)

        words.append({
            "text": text,
            "x": x,
            "y": y,
            "height": h,
        })

    # 글자의 세로 중심을 기준으로 행 분류
    sorted_words = sorted(
        words,
        key=lambda word: word["y"] + word["height"] / 2
    )

    lines = []

    for word in sorted_words:
        center_y = word["y"] + word["height"] / 2

        # 글자 크기를 고려해 같은 행인지 판단
        threshold = max(8, word["height"] * 0.65)

        matched_line = None

        for line in reversed(lines):
            if center_y - line["center_y"] > threshold:
                break

            if abs(center_y - line["center_y"]) <= threshold:
                matched_line = line
                break

        if matched_line is None:
            lines.append({
                "center_y": center_y,
                "words": [word]
            })
        else:
            matched_line["words"].append(word)

            # 행의 중심을 갱신
            matched_line["center_y"] = sum(
                w["y"] + w["height"] / 2
                for w in matched_line["words"]
            ) / len(matched_line["words"])

    # 행 내부는 왼쪽에서 오른쪽 순서로 정렬
    result_lines = []

    for line in lines:
        line_words = sorted(line["words"], key=lambda w: w["x"])

        result_lines.append({
            "y": round(line["center_y"]),
            "text": " ".join(w["text"] for w in line_words),
            "words": line_words
        })

    return {
        "source": str(image_path),
        "image_size": {
            "width": width,
            "height": height
        },
        "words": words,
        "lines": result_lines
    }

def fix_swim_record_string_for_samsung_health(
    ocr_lines: list[str],
) -> list[SwimRecord]:
    swim_records = []
    last_swim_record: SwimRecord | None = None

    passed_num = False

    for line in ocr_lines:
        s = line.strip()
        if s and s[0].isdigit():
            passed_num = True
        if not passed_num or not s:
            continue

        lap_match = re.match(r"(\d+)", s)
        if lap_match:
            time_match = re.search(r"(\d+):(\d{2}(?:\.\d+)?)", s[lap_match.end():])
            if time_match is None:
                warnings.warn(
                    f"랩 시간 OCR을 해석하지 못했습니다: {s!r}",
                    RuntimeWarning,
                )
                continue

            time_start = lap_match.end() + time_match.start()
            stroke = re.sub(r"\s+", "", s[lap_match.end():time_start])
            if stroke.startswith("자"):
                stroke = "자유"
            elif stroke.startswith("접"):
                stroke = "접영"
            elif stroke.startswith("배"):
                stroke = "배영"
            elif stroke.startswith("평"):
                stroke = "평영"
            # 특수 보정
            elif stroke.startswith("H"):
                stroke = "배영"
            elif stroke.startswith("킥"):
                stroke = "킥판"
            elif stroke.startswith("혼"):
                stroke = "혼영"

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
            rest_match = re.search(r"(\d+):(\d{2}(?:\.\d+)?)", s)
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

def im_finder(swim_records:list):

    #[35, '평영', datetime.timedelta(seconds=25, microseconds=200000), 0.0]
    # int, str, timedelta, float 타입으로 저장됨


    #! 접배평자로 입력된 것만 검사.
    #TODO 만약 랩타임을 알고있다면 시작~끝만 입력받아서 계산하도록 만들어도 될듯

    last_index = len(swim_records)

    i = 0
    im_start_idx = [] #! 랩번호가 아니라 인덱스임에 주의
    while i < last_index:
        if swim_records[i][1][0] == '접':
            if i + 3 <= last_index and swim_records[i + 1][1][0] == '배' and swim_records[i + 2][1][0] == '평' and swim_records[i + 3][1][0] == "자":
                im_start_idx.append(i)
                i += 3
                continue
        i += 1

    result:dict = {}
    i = 1
    for j in im_start_idx:
        res = timedelta()
        this_session_record = []
        for k in range(4):
            res += swim_records[j + k][2]
            this_session_record.append(swim_records[j + k][2])
        result[i] = [res.total_seconds()]
        result[i].extend([e.total_seconds() for e in this_session_record])
        i += 1

    if not result:
        print("수행된 im100 세션을 찾을 수 없습니다.")
        return

    print(f"im100 세션 {i-1}개를 찾았습니다.")
    for key in result.keys():
        print(f"{key}번 세션: {result[key][0]}s {[s for s in result[key][1:]]}")
    

def main():
    parser = argparse.ArgumentParser(
        description="수영 기록 이미지 OCR 추출"
    )
    parser.add_argument("image", help="입력 이미지 경로")
    args = parser.parse_args()

    image_path = Path(args.image)
    result = extract_image(image_path)

    ocr_lines = [line["text"] for line in result["lines"]]
    swim_records:list = (
        fix_swim_record_string_for_samsung_health(ocr_lines)
    )

    total_lap, total_rest, total_rest_sec = 0, 0, 0
    start_lap_num = int(swim_records[0][0]) # type: ignore
    counter = 0 #idx 카운터 (누락랩 검사용)
    lap_warning = False # 누락된 랩 경고
    for swim_record in swim_records:
        # swim_record = list type.
        lap_number, stroke, lap_time, rest_time = cast(
            tuple[int, str, timedelta, float],
            swim_record,
        )

        if not lap_warning and (lap_number != start_lap_num + counter):
            lap_warning = True
        counter += 1

        lap_seconds = lap_time.total_seconds()
        rest_display = f"{rest_time:.1f}" if rest_time else ""
        print(f"{lap_number} {stroke} {lap_seconds:.3f} {rest_display}")
        total_lap += 1

        if rest_time > 0:
            total_rest += 1
            total_rest_sec += rest_time
        # print(swim_record)
        #[35, '평영', datetime.timedelta(seconds=25, microseconds=200000), 0.0]
        # int, str, timedelta, float 타입으로 저장됨

    print(f'\t-> Total lap: {total_lap}  Rest: {total_rest}  Rest seconds: {total_rest_sec:.1f}')

    print() # 빈 라인 출력
    if lap_warning:
        print("[경고]누락된 랩이 있을 수 있음")

    im_finder(swim_records)

if __name__ == "__main__":
    main()
