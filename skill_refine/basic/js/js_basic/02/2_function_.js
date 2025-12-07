// 함수선언
function greeting(name) {
    console.log(`Hello ${name}!`);
}

// 함수 표현식으로 선언
let greeting2 = function(name) {
    console.log(`Hello ${name}!`);
}

// 함수 호출
greeting("ted");
greeting2("TED");


// 즉시실행 함수 (선언과 호출 동시) : 화살표함수와 모양은 거의 비슷. function(params) {} 와 (params) => {} 정도의 형태 차이.
(function(a, b) {
    console.log(`sum res: ${a + b}`);
}(100, 200));


// 화살표함수
let hi = () => {
    return "Hi";        // 한줄만 있다면 중괄호와 리턴 생략 가능
}
console.log(hi());

// 화살표함수 : 매개변수(parameter) 가 있는. (참고로 인수 = argument)
let sum = (a, b) => a + b;
console.log(sum(2,3));


// +@. 화살표 함수를 즉시실행
((a, b) => {
    console.log(`${a} + ${b} = ${a + b}`);
})(3,5);
