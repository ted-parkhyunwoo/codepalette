
const array = []
console.log(array)

// 1. 요소 추가: push, unshift, splice

// push: 마지막에 추가됨
array.push(3);
array.push(4);
console.log(`push: ${array}`)

// unshift: 처음에 추가됨
array.unshift(2);
array.unshift(1);
console.log(`unshift: ${array}`)

// splice: (index, 0, e1, e2...)
array.splice(2, 0, "2다음에 삽입된 문자열", "그다음 삽입된 문자열")
console.log(`splice(insert): ${array}`)


// 2. 요소 삭제: pop, shift, splice

// pop: 마지막 요소를 삭제하며 반환
const poped = array.pop()
console.log(`poped: ${poped}`)
console.log(`pop: ${array}`)

// shift: 첫번째 요소를 삭제하며 반환
const shifted = array.shift()
console.log(`shifted: ${shifted}`)
console.log(`shift: ${array}`)

// splice: (index, 삭제갯수)
array.splice (1, 2)     // 1번부터 2개요소 삭제
console.log(`splice(delete): ${array}`)


// 하면 안될거같지만 추가와 삭제에 정상 작동되는것: index로 추가 및 length 변경- 마지막요소에 한해서.
array[2] = 4
console.log(`array[2] 추가: ${array}`)

array.length = array.length - 1
console.log(`array.length - 1: ${array}`)

// 추가한다면? empty item 으로 요소 추가됨. 꺼내보면 undefined
array.length++
console.log(`길이를 늘리기만 함: ${array}`)
console.log(array[2])
array.length--



// 3. map, filter, reduce, ...스프레드연산자 -> 새로운 배열로 리턴됨(복사)

// map : 동일한 함수를 적용가능
const plusArray = array.map(n => {return n + 1;})       // 리턴방식
console.log(plusArray)
console.log(array.map(n => ++n))                        // 직접 사용시

// filter: 특정 조건으로 배열 반환
const filtered = array.filter(n => n % 2 === 0)
console.log(filtered)

// ...스프레드 연산자
console.log(array)
const newArray = [1, ...array, 4, 5]
console.log(newArray)

const copyNew = [...newArray]       // 를 활용한 깊은복사
console.log(copyNew)

// reduce( (누적값, 현재값) => { ... }, 누적값의초기값 )
// 현재값은 배열의 요소가 순차적으로 들어감.
// 람다식은 웬만하면 남들이 보기도 이해하기 어려울 수 있으므로, 간단한 것 아니면 분리 구현하자
const evenSum = copyNew.reduce((res, elem) => {
    if (elem % 2 === 0)
        return res += current
    else return res
}, 0)
console.log(`evenSum: ${evenSum}`)


// sort정렬, reverse뒤집기: 내장메서드. 원본을 직접수정. 원하면 리턴도 됨.

// reverse: 배열 뒤집기
const revCopyNew = copyNew.reverse()
console.log(copyNew)
console.log(revCopyNew)             // 리턴을 저장했으므로 당연히 결과가 같음

// sort: 정렬
revCopyNew.sort()                   // 오름차순
console.log(revCopyNew)
revCopyNew.sort((a, b) => a - b)    // 오름차순 명시
console.log(revCopyNew)
revCopyNew.sort((a, b) => b - a)    // 내림차순 명시
console.log(revCopyNew)




