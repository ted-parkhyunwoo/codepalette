//! 1. 내장타입: 타입 지정 불가. 
// typeof 는 변수의 타입을 리턴하며, 정수,실수는 구분되지않음. 또한 number가 아닌 "number"처럼 string 으로 나옴.
// 컨테이너로 map같이생긴건 object(객체: 해시테이블처럼 보이지만 사실 프로토타입기반 해시매핑), map은 또 실직적인 해시테이블이며, 범위기반 for 문에는 보통의 컨테이너는 반복자 사용 가능하여 for ... of를 쓰는데, object는 반복자를 쓸 수 없는 컨테이너(컬렉션)라 for ... in으로 함(객체 키 순회)


// 타입 확인
console.log(typeof "hello");  // "string"
console.log(typeof 42);       // "number"
console.log(typeof {});       // "object"
console.log(typeof new Map()); // "object" (Map은 특별한 역할을 함)

// 배열의 범위기반 반복문 접근 (for ... of)
const arr = [1, 2, 3];
for (const num of arr) {
    console.log(num);
}

// 객체의 범위기반 반복문 접근 (for ... in in)
const obj = { a: 1, b: 2 };
for (const key in obj) {  // for...in: 객체 속성 순회
    console.log(key, obj[key]);
}

// 진정한 js의 해시테이블은 map으로 씀
// map 선언방식은 약간 독특하게 new Map()으로 초기화되며, [ [key, val], [key, val] ] 묶음.
// 요소 접근이 조금 독특함.
const map = new Map([
    ["a", 1],
    ["b", 2],
    ["c", 3]
]);

console.log(map.get("a"));      // 단일접근, 출력 : 1

for (let [key, val] of map) {   // 범위기반 접근, 출력: a 1   b 2   c 3
    console.log(key, val);
}


//! 2. 생성자 함수: js는 사실 아직 class가 없음. class기반이 아닌 '함수기반 프로토타입 상속'
// 다음 두 가지 a, b 예제는 문법은 다르지만 사실 같은 역할을 한다.
// a. 생성자 함수
function Person(name, age) {
    this.name = name;
    this.age = age;
}

Person.prototype.sayHello = function() {    // 이 문법에 주목한다.
    console.log(`안녕하세요, 저는 ${this.name}이고 ${this.age}살입니다.`);
};

const person1 = new Person("Ted", 25);
person1.sayHello(); // "안녕하세요, 저는 Ted이고 25살입니다."


// b. 클래스기반 ("문법적 설탕(syntactic sugar)")
class Person2 {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }

    sayHello() {
        console.log(`안녕하세요, 저는 ${this.name}이고 ${this.age}살입니다.`);
    }
}

const person2 = new Person2("Ted", 25);
person2.sayHello(); // "안녕하세요, 저는 Ted이고 25살입니다."


//! 3. 클래스 모듈 사용시 ECMA Script 2015(ES6) 을 따름. commonJS에서도 class 문법이 비슷하나, 작동 매커니즘이 많이 다름.
// commonJS vs ES6: 환경은 node전용/브라우저도 가능, 로딩 동기적/비동기적, 실행 런타임/정적분석 등.


/*      ES6 를 따른 클래스의 모듈화 예제
// person.mjs           //! 브라우저는 js확장자를 써도 되나, node에서ES6을 사용할땐 mjs확장자 씀.
export class Person {           // 하나만 내보낼 땐 export default 사용
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }

    sayHello() {
        console.log(`안녕하세요, 저는 ${this.name}이고 ${this.age}살입니다.`);
    }
}

// main.js      // node main.js
import Person from './person.mjs'; // export default이므로 중괄호 없이 import

const person1 = new Person("현우", 25);
person1.sayHello(); // "안녕하세요, 저는 현우이고 25살입니다."


// package.json  //! 추가하면 js확장자를 써도 node에서 동작 가능함. 물론 mjs확장자인경우도 작동함.
{
  "type": "module"
}
*/

