//! 1. 배열 선언, 대입, 초기화
let myArr = [];
for (let i = 0; i < 5; ++i) {
    if (i + 1 == 3) continue;
    myArr.push(i + 1);
}                                               // [1, 2, 4, 5]


//! 2. 배열 요소 삽입.
myArr.unshift(0);   // 시작 요소로 0요소 삽입.      [0, 1, 2, 4, 5]
myArr.push(6);      // 마지막 요소로 6 추가.        [0, 1, 2, 4, 5, 6]
myArr.splice(3, 0, 3);  // 중간 삽입                [0, 1, 2, 3, 4, 5, 6]


//! 3. 배열 요소 삭제, 대체.    shift와 pop은 삭제된 요소를 리턴값으로 갖는다
myArr.shift();  // 맨 앞 요소 삭제.                 [1, 2, 3, 4, 5, 6]
myArr.pop()     // 마지막 요소 삭제.                [1, 2, 3, 4, 5]
myArr.splice(1, 3);   //1번 인덱스부터 연속3개 삭제 [1, 5]
// myArr.splice(1, 3) 는 삭제된 요소들 [2, 3, 4] 를 리턴함.


//! 3. 배열 요소 정렬 알고리즘.
let sortThat = [ 1, 4, 3 ,5, 2];
sortThat.sort((a, b) => { return a - b; });     // 오름차순 [1, 2, 3, 4, 5]
sortThat.sort((a, b) => b - a);                 // 내림차순 [5, 4, 3, 2, 1]


//! 4. 배열 요소 접근
// 단일접근
let first_element = sortThat[0];                    // 첫요소접근
let [first_element2] = sortThat;                    // 첫요소접근
let last_element = sortThat[sortThat.length - 1];   // 마지막요소 접근
let last_element2 = sortThat.at(-1);                // 마지막요소 접근

// shift(), pop()를 이용한 첫번째 요소, 마지막요소 접근 방법도 있음.(배열원본 삭제됨)

console.log(`fe: ${first_element}, fe2: ${first_element2}, le: ${last_element}, le2: ${last_element2}`);

// 반복자를 활용한 배열요소 접근
for (let i = 0; i < sortThat.length; i++) { sortThat[i] += 1 }; //* 배열의 요소 수정됨. 
console.log(sortThat);                          // [6, 5, 4, 3, 2]
for (let val of sortThat) { val -= 1 }; //* 지역변수 val만 수정되고 원본배열요소는 수정안됨.
console.log(sortThat);


// 유용한 배열 내장기능들
//! .length 배열의 길이 (함수 아님을 주의.);
let sortThat_length = sortThat.length;

//! slice(start, end): idx기반 시작,끝점으로 새 배열리턴. 원본배열을 수정하지 않음.
let sliceThat = sortThat.slice(1, 4);   //  start(시작 idx 포함), end(idx 직전까지만)


//! splice() 의 다양한 기능. 
/*  splice(start: number, deleteCount?: number) 
start= 시작인덱스, deleteCount?= 삭제할 갯수(비우면 0) 
세번째 매개변수부터는 요소들이 추가됨. e.g(4, 0, 2, 3) 4번인덱스부터 삭제하지않고 2,3 삽입

splice()는 반환값이 존재함. 원본배열 수정 후 삭제된 요소들이 들어감(순서 보장).

다음은 splice로 구현가능한 기능들을 나열함.
1. 배열을 slice 할 수 있음. (배열을 손상시키지 않는 .slice(start, end) 가 더 많이 쓰임)
2. 원하는 요소(혹은 연속된 요소들)를 '삭제' 혹은 '대체' 할 수 있음.
3. 원하는 요소(혹은 연속된 요소들)를 원하는 위치에 삽입할 수 있음.

*/

// 개별요소 삽입
let test_splice = [1, 2, 4, 5];
test_splice.splice(2, 0, 3);        // [1, 2, 3, 4, 5]

// 배열 삽입
let addArr = [6, 7, 8];
test_splice.splice(5, 0, ...addArr); // 배열삽입시 ...(언팩: 전개연산자) 를 넣는다.
console.log(test_splice);           // [1, 2, 3, 4, 5, 6, 7, 8]

