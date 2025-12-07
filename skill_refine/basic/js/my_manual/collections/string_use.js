//! 1. 문자열 선언, 대입, 초기화
let myStr = "";         // 빈 문자열
myStr = "Hello";        // 문자열 대입
let otherStr = "World";
let concatStr = myStr + " " + otherStr; // 문자열 연결      "Hello World"


//! 2. 문자열 연결 및 템플릿 문자열
let name = "Alice";
let greet = "Hello, " + name + "!";              // 일반 연결       "Hello, Alice!"
let greet2 = `Hi, ${name}. Welcome!`;            // 템플릿 문자열   "Hi, Alice. Welcome!"


//! 3. 문자열 접근
let str = "abcdef";

let first_char = str[0];             // 단일 접근: 첫 문자 'a'
let last_char = str[str.length - 1]; // 마지막 문자 'f'
let last_char2 = str.at(-1);         // at() 사용: 'f'

// 문자열은 불변(immutable)하므로 직접 수정은 안 됨.
// str[0] = 'A'; // ❌ 변경 안 됨.


//! 4. 문자열 반복자 및 반복문 활용
for (let ch of str) {
    console.log(ch);  // 각 문자 출력
}


//! 5. 문자열 슬라이스, 서브스트링 추출
let sliced = str.slice(1, 4);   // 'bcd' (start idx 포함, end idx 직전까지)
let substr1 = str.substring(1, 4); // 'bcd' (slice와 유사하지만 음수 인덱스는 지원 안 함)


//! 6. 문자열 검색
str.includes("bc");     // true
str.indexOf("cd");      // 2 (없으면 -1)
str.lastIndexOf("c");   // 2
str.startsWith("ab");   // true
str.endsWith("ef");     // true


//! 7. 문자열 치환
let phrase = "I like apple";
let replaced = phrase.replace("apple", "banana");      // "I like banana"
let replacedAll = phrase.replaceAll("l", "L");          // "I Like appLe"


//! 8. 문자열 분할 & 결합
let csv = "red,green,blue";
let colors = csv.split(",");     // ["red", "green", "blue"]

let joined = colors.join("-");   // "red-green-blue"


//! 9. 문자열 공백 제거
let spaced = "  hello world  ";
let trimmed = spaced.trim();         // "hello world"
let trimmedStart = spaced.trimStart(); // "hello world  "
let trimmedEnd = spaced.trimEnd();     // "  hello world"


//! 10. 유용한 문자열 전용 메서드들

// 대소문자 변환
let msg = "JavaScript";
msg.toUpperCase();   // "JAVASCRIPT"
msg.toLowerCase();   // "javascript"

// 반복
"ab".repeat(3);      // "ababab"

// 문자 → 유니코드(ASCII) (정수)
"A".charCodeAt(0);   // 65

// 유니코드(ASCII) → 문자
String.fromCharCode(65);  // "A"

// 공백 여부 확인
let emptyStr = "   ";
emptyStr.trim().length === 0;  // true (사실상 비어있음)


//! 11. 문자열 불변성에 대한 주의
let s = "abc";
s[0] = "A";  // 변경 안 됨, 문자열은 불변(immutable)
console.log(s); // 여전히 "abc"
