// 함수선언식
function hello(name){ return `Hello ${name}!`; }
const myName = "ted";
console.log(hello(myName));

// 화살표함수
const sum = (a, b) => a + b;
const sub = (a, b) => a - b;
const mul = (a, b) => { return a * b; }     // 중괄호 사용시 리턴작성 필수
const div = (a, b) => a / b;
console.log(sum(1, 2));
console.log(sub(5, 2));
console.log(mul(2, 5));

// wrapper, 함수 표현식
const calc = function (a, f, b) { return f(a, b) };
console.log(calc(1, sum, 2))
console.log(calc(20, sub, 5))
console.log(calc(5, div, 2));


// 즉시실행함수표현식
(function() { console.log("lambda")} ) ();
(function(a, b) { console.log(a + b); } ) (3, 4);

// 즉시실행 화살표함수
console.log(
    `lambda: ${((a, b) => { return a + b; }) (4, 5)}`
);


// let으로 선언된 화살표함수를 함수표현식으로 재정의
let sample = () => console.log("sample");
sample();
sample = function() { return "샘플"};
console.log(sample());