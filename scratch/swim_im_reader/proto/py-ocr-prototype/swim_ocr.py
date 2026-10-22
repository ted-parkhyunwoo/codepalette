

import argparse
from pathlib import Path

import cv2
import pytesseract
from pytesseract import Output


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
        config="--psm 6",
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


def main():
    parser = argparse.ArgumentParser(
        description="수영 기록 이미지 OCR 추출"
    )
    parser.add_argument("image", help="입력 이미지 경로")
    args = parser.parse_args()

    image_path = Path(args.image)
    result = extract_image(image_path)

    # OCR로 리드된 string list 선언
    all_string_list = list()
    #! 랩넘버가 나오기 전까지 쓸데없는것은 출력하지 않게 하기 위한 트리거
    passedNum = False
    for line in result["lines"]:
        bf:str = f'{line["text"]}'
        if bf[0].isdigit():
            passedNum = True
        if passedNum:
            all_string_list.append(bf) 

    # TEST String List and counter
    record_str_list = list()
    swim_counter = 0
    rest_counter = 0

    for s in all_string_list:
        idx = 0
        if s[0].isdigit():
            idx+=1
            while s[idx].isdigit():
                idx+=1
            while s[idx] == ' ':
                idx+=1

            isFreestyle = False
            if s[idx] == '자':
                isFreestyle = True
            lastIdx = idx
            if s[idx] == '접' or s[idx] == '배' or s[idx] == '평' or isFreestyle:
                #! 's' is swimming(guessed) plain string.
                while not s[idx].isdigit():
                    idx+=1
                if (s[idx + 2] == ':'):
                    # 영법진행으로 확정된 string
                    swim_counter += 1
                    bf = (s[:idx + 7])
                    if isFreestyle:
                        # 자 유 형 (크롤)을 알맞게 재조정
                        timeStartIdx = lastIdx
                        while s[timeStartIdx] != ':':
                            timeStartIdx+=1
                        timeStartIdx -= 2
                        tmp = s[:lastIdx] + "자유 " + s[timeStartIdx:timeStartIdx+7]
                        bf = tmp
                    record_str_list.append(bf)
                else:
                    record_str_list.append(f'\tUnknown String: {s}')
        else:
            #! 여기서의 s는 휴식으로 추정되는 plain string
            
            idx = 0
            # s를 재가공하며 rest로 판명되면 rest_counter += 1
            while not s[idx].isdigit():
                idx+=1
            if (s[idx + 2] == ':'):
                #! rest 의 소수점까지는 폰트가 작아 인식이 안되므로 소수점 삭제
                record_str_list.append(f'\tRest: {s[idx:idx + 5]}')
                rest_counter += 1
            else:
                record_str_list.append(f'\tUnknown String: {s}')

    for s in record_str_list:
        print(s)
    print(f'[Counter] Swim: {swim_counter}\tRest: {rest_counter}')

if __name__ == "__main__":
    main()
