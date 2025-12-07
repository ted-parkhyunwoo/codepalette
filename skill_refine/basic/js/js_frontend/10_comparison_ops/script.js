// 비교연산자-> boolean data.

// 대소비교 - <, >, <=, >=
let a = 3;
let b = 5;
const compare1 = [a > b, a < b, a >= b, a <= b]
for (c of compare1) {
    console.log(c);
}

// 대소비교의 이상한점- 타입불일치시 암묵적 변환이 일어남.
let three = '3';
console.log(three <= 5);      // true
console.log(three >= 5);      // false

console.log(Number(three) >= 5);    // false (명시적 변환을 사용.)

// 등가비교 abstract:추상적 비교, 자료형이 달라도 데이터만 일치 검사 ==, !=
console.log(1 == "1");      // true

// 등가비교 strict:엄격비교, 타입(자료형)과 데이터 모두 일치 검사 ===, !==
console.log(1 === "1");     // false


