//! 사용할 수 없는 함수 사용. 변수처럼 선언X
let work = console.log("HELLO");
work;


//! JS 관례 : 함수이름: 동사를 사용하여 소문자시작의 카멜표기법(변수도 마찬가지로 카멜표기법)


myFunc();       //! 함수선언식은 어디에 선언되든 사용은 어디서든 가능(표현: 호이스팅이 가능하다.)
// 함수선언식 (함수를 이름지어 선언)    
function myFunc() {
    console.log("함수선언식");
}
// 함수표현식 (익명함수-> 이름지음).
const myFunc2 = function(){
    console.log("함수표현식");
}

//호출
myFunc();
myFunc2();





//! 콜백.(강의엔 없음)
const myCallback = function() {
    console.log("콜백함수입니다");
}

let a = 3;
// js의 특징으로 매개변수에 함수가 들어감.(다른언어는 lambda식 필요.)
const callFuncNTimes = (n, callback) => {       // n번 콜백을 호출하는 화살표함수
    for (let i = 0; i < n; i++) {
        callback();
    }
}

callFuncNTimes(a, myCallback);

// 위 화살표함수와 같은 방식의 function 선언
const callFuncNTimes2 = function(n, callback) {
    for (let i = 0; i < n; i++) {
        callback();
    }
} 

callFuncNTimes2(a, myCallback);