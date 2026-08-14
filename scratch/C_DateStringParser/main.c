#include <stdio.h>
#include <stdlib.h>

// 구분문자를 사용하든 안하든 작동함 다만,
// 연도는 4자리,2자리 사용가능하나 월 일 두가지는 반드시 두글자로만 가능한 상태

const char DEVCHARS[] = " /-.";         // 허용된 날짜 구분문자 상수

// 날짜를 저장에 사용할 자료구조(구조체)
typedef struct dataDate{
    short year, month, day, isValid;
    // isValid code (나중에 열거형 사용과 오류코드 구체화 등으로 더 정교하게 교정)
    // -1(string length error)
    // -2(not 6 digits but 6length string), 
    // 1(양식은 OK 유효데이터검사X), 
    // 0(완전OK) : 유효한 월/ 일인지 검사하는 함수까지 구현. 윤년도 활용
    // -3 : 구분문자가 앞과 뒤가 다름
    // -4 : 구분문자 갯수가 모자라거나 초과
    // -5 : 구분문자의 위치가 잘못됨
    // -6 : 유효한 구분문자가 아님
    // -7 : 매개변수 문자열 오류 
    // -8 : 날짜가 유효하지 않은 날짜임. (음수 혹은 12월이 넘는다는 등...)
} dataDate;


// leap year 검사기 (4년마다 윤년이나, 100으로 나누어떨어지면 아니지만, 400으로 나누어 떨어지는건 윤년)
int isLeapYear(short year) {
    // 서기 0년은 없음. 0년 = 기원전1년임. 기원전1년은 어차피 윤년이므로 수학적으로 문제없음.
    return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));   
}


// dateString 의 index들을 토대로 dataDate참조조작(year는 2, 4글자에따라 다르게 변환하며, month, day는 2글자로 자동인식)
void writeDataDateStructFromStringIdxs(dataDate* data, char* str, unsigned yBegin, unsigned yEnd, unsigned mBegin, unsigned dBegin) {
    
    char yStr[5], mStr[3], dStr[3];

    // month, day 부터 해결
    mStr[0] = *(str + mBegin),  mStr[1] = *(str + mBegin + 1),  mStr[2] = '\0';
    dStr[0] = *(str + dBegin),  dStr[1] = *(str + dBegin + 1),  dStr[2] = '\0';

    // year 2글자인 경우 예외처리: 앞에 20을 붙임
    // 2000년 강제 입력이 무조건 정답은 아니나, 연도생략 책임을 사용자에게 맞기는 의미의 관점으론 올바른 방법
    int isFourString = yEnd - yBegin != 1? 1 : 0;
    if (isFourString) {
        for (int i = 0; i < 4; ++i) {
            yStr[i] = *(str + yBegin + i);
        }
    } else {
        yStr[0] = '2', yStr[1] = '0';
        yStr[2] = *(str + yBegin),  yStr[3] = *(str + yBegin + 1);
    }
    yStr[4] = '\0';

    // 결과 구조체 데이터 작성
    data->year = atoi(yStr),    data->month = atoi(mStr),   data->day = atoi(dStr);
}


// 문자열(str)의 특정 인덱스 2개가 숫자가 아닌 문자인지 검사하는 함수(둘다 만족해야 1 return)
int hasTwoCharNotDigits(char* str, unsigned firstIdx, unsigned lastIdx) {
    if (str[firstIdx] < '0' || str[firstIdx] > '9')
        if (str[lastIdx] < '0' || str[lastIdx] > '9')
            return 1;
    return 0;
}


// isValidDate 함수로 dataDate를 참조하여 결점이 없는 날짜인지 검토하고 isValid를 수정
void checkValidDate(dataDate* data) {
    short year = data->year,    month = data->month,    day = data->day;

    if (year < 0 || month < 0 || day < 0 || month > 12 || day > 31) {
        data->isValid = -8;
        return;
    }

    // ERR 유효날짜 실패 (윤년까지 체크)
    switch(month) {
        case 4: case 6: case 9: case 11: 
            if (day > 30) {
                data->isValid = -8;
                return;
            }
            break;
        case 2: 
            // ERR: 윤년체크 실패시
            if (isLeapYear(year)) {
                if (day > 29) {
                    data->isValid = -8;
                    return;
                }
            } else {
                if (day > 28) {
                    data->isValid = -8;
                    return;
                }
            }
            break;
    }
    // ERR 날짜 무결성 확인코드
    data->isValid = 0;
}


// string -> dataDate구조체로 변환하는 wrapper 함수
dataDate parser(char* dateStr) {
    dataDate res;           // 결과 구조체
    res.year = 0, res.month = 0, res.day = 0, res.isValid = 1;  // 혹시모를 초기화

    // 매개변수 오류검사 
    if (dateStr == NULL || *dateStr == '\0') {
        res.isValid = -7;   // ERR 유효하지 않은 매개변수
        return res;
    }

    // strlen 비용대신 길이 구하는 겸 초기 변수 세팅
    unsigned hasChars = 0;                   // 디지트가 아닌 문자 포함 갯수 
    char lastDevChar = '\0';            // 마지막으로 검출된 구분문자
    unsigned dateStringLength = 0;      // dateStr 문자열의 총 길이
    char* bf = dateStr;                 // 임시버퍼

    // 초기 오류 검사 겸 변수 정하기
    while (*bf != '\0') {
        dateStringLength++;
        // 숫자 외 등장시
        if (*bf < '0' || *bf > '9') {
            if (hasChars == 2) {
                res.isValid = -4;       // ERR 구분문자의 갯수 초과
                return res;
            }
            if (lastDevChar != '\0') {
                if (lastDevChar != *bf) {
                    res.isValid = -3;       // ERR 구분문자가 앞뒤가 다름.
                    return res;
                }
            }

            lastDevChar = *bf;
            hasChars++;
        }
        bf++;
    }

    // 구분문자 갯수 검사
    if (hasChars == 1) {
        res.isValid = -4;
        return res;                 // ERR 구분문자 갯수 부족
    }

    // 유효구분문자 검사
    int isValidDevChar = 0;
    const char* DEVCHARSBUFFER = DEVCHARS;
    while (*DEVCHARSBUFFER != '\0') {
        if (lastDevChar == *DEVCHARSBUFFER) {
            isValidDevChar++;
            break;
        }
        DEVCHARSBUFFER++;       
    }
    if (hasChars && !isValidDevChar) {
        res.isValid = -6;           // ERR 유효하지 않은 구분문자 사용
        return res;
    }

    
    // case1. 6숫자인 경우 (260810)
    if (dateStringLength == 6) {
        // 문자포함시 오류처리 
        if (hasChars) {
            res.isValid = -2;       // ERR 6길이의 매개변수에는 숫자로된 문자만 사용 가능
            return res;
        }
        writeDataDateStructFromStringIdxs(&res, dateStr, 0, 1, 2, 4);
    }


    // case2. 8문자인 경우 (26-08-10 or 20260810)
    else if (dateStringLength == 8) {
        // 적절한 구분문자 위치인지 검사하는 함수 (문자가 포함된 경우)
        if (hasChars && !hasTwoCharNotDigits(dateStr, 2, 5)) {
            res.isValid = -5;       //ERR 구분문자 위치 오류
            return res;               
        }
        // 이제 여기까지 살아남은 dateStr문자열의 두 케이스는 26-08-10 혹은 20260810 형태
        // all digits case
        if (!hasChars) 
            writeDataDateStructFromStringIdxs(&res, dateStr, 0, 3, 4, 6);
        // 구분문자 case
        else
            writeDataDateStructFromStringIdxs(&res, dateStr, 0, 1, 3, 6);
    }


    // case3. 10문자: 항상 (2026c08c10)과 같은 형태, c는 digit가 아닌 문자를 뜻함
    else if (dateStringLength == 10) {
        // 적절한 구분문자 위치인지 검사하는 함수
        if (!hasTwoCharNotDigits(dateStr, 4, 7)) {
            res.isValid = -5;       // ERR 구분문자 위치 오류 
            return res;
        }
        writeDataDateStructFromStringIdxs(&res, dateStr, 0, 3, 5, 8);
    }


    // ERR 6, 8, 10개의 문자가 아니면 모두 -1처리 : string length err
    else {
        res.isValid = -1;
        return res;
    }

    // 마지막 관문으로 유효날짜검사
    checkValidDate(&res);
    return res;
}

// String의 null검사, 길이검사, 앞뒤 불필요 공백 자르기
// 0: 기능통과
// 1: string 마지막 공백 감지하여 변조됨
// -1: null 오류감지
int stringChecker(char* str) {
    if (str == NULL || *str == '\0')    return -1;
    char* bf;

    // get pure str length
    unsigned strLen = 0;
    bf = str;
    while (*bf != '\0') {
        strLen++;
        bf++;
    }

    // find start index without space char
    unsigned startIdx = 0;
    bf = str;
    while(*bf != '\0') {
        if (*(bf++) == ' ') startIdx++;
        else break;
    }
    
    // find last index without space char
    unsigned lastIdx = strLen - 1;
    bf = str + (lastIdx);
    while (*bf == ' ') {
        lastIdx--;
        bf--;
    }

    // printf("[DEBUG]str: '%s' \tstartIdx = %d  \tlastIdx = %d\n", str, startIdx, lastIdx);
    
    // 변경사항 발생시 str 메모리 재작성
    if (startIdx != 0 || lastIdx != strLen - 1) {
        unsigned trueLen = lastIdx - startIdx + 1;
        char res[11];
        bf = str + startIdx;
        for (int i = 0; i < trueLen; ++i) 
            *(res + i) = *(bf++);
        *(res + trueLen) = '\0';
    
        // printf("len : %d resStr : '%s'\n", trueLen, res);
        
        // res -> str 메모리 재작성
        for (int i = 0; i < trueLen; ++i)
            *(str + i) = *(res + i);
        *(str + trueLen) = '\0';

        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {

    printf("\n\n");
    // stringChecker function test
    if (argc == 1) {
        printf("[TEST MODE]\n");

        // Test 용 공백이 포함된 날짜
        char testStr[] = "    2024-05-02  ";
        printf("[CHANGE] '%s'  ->  ", testStr);
        printf("'%s'\t\tisChanged:%d\n", testStr, stringChecker(testStr));
        dataDate tmp = parser(testStr);
        printf("(%d)\tArg: %s\t\tres:'%d %d %d'\n", tmp.isValid, testStr, tmp.year, tmp.month, tmp.day);
        return 0;
    }
    // fin
    
    // 매개변수가 있는 경우 이쪽으로 진입됨. 연속입력 가능.
    for (int i = 1; i < argc; ++i) {
        stringChecker(argv[i]);         // 매개변수 입력 실수로 추정되는 앞뒤 공백 제거
        dataDate tmp = parser(argv[i]);
        printf("(%d)\tArg: %s\t\tres:%d  %d  %d\n", tmp.isValid, argv[i], tmp.year, tmp.month, tmp.day);
    }
    printf("\n\n");


    return 0;
}
