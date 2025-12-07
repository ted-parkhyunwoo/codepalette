// undefined 와 null, 0의 차이.
let a;
console.log(typeof(a));     // type도 undefined.
console.log(a); // undefined: 정의되지않음.
let b = null;
console.log(b); // null: 비어있음.  type: object
let c = 0;
console.log(c); // 0으로 초기화됨
let d = b === c;
console.log(d)  // type: boolean.  null 과 0은 다름.



//! 비교연산자 (비교논리) == 와 ===의 차이(js의 특징)
const one = 1;
const strOne = "1";

console.log(one == strOne);     // 느슨한 비교
console.log(one === strOne);    // 정확한 비교(타입까지 체크)

