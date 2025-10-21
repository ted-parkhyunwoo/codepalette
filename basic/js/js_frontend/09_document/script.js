/*
document는 HTML 문서 등(XML, SVG)을 JavaScript가 조작할 수 있도록 객체화한 DOM의 대표 객체.
HTML 문서는 브라우저가 자동으로 파싱하여 DOM을 구성.
이러한 DOM은 문서 구조를 탐색하고 조작할 수 있는 API도 함께 제공.
document.createElement, appendChild 등으로 직접 동적 요소 생성 및 조작 가능.
*/

//! 1. querySelector
const qsArray = [
    document.querySelector("h1"),
    document.querySelector("p"),
    document.querySelector("#text"),
    document.querySelector(".paragraph"),
    document.querySelector("test")  // null
]

for (let obj of qsArray) {
    console.log(obj);
}


const h1 = qsArray.at(0);

//! 2. getElementById     : id 가 있는요소만 찾음.
const p_text = document.getElementById("text");


//! 3. textContent  : 태그가 담고 있는 컨텐츠(내용) 리턴
console.log(h1.textContent);

// content 변경시
h1.textContent = "!변경된 제목";
p_text.textContent = "!변경된 문단"
console.log(p_text);
