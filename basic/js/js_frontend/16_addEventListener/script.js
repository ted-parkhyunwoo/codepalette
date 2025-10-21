const target = document.querySelector("#button");
const target2 = document.querySelector("#button2");
const target3 = document.querySelector("#button3");

const handleClick = function() {
    console.log("clicked.");
}

// onclick 방식 : 
target.onclick = () => {window.alert("버튼눌림")}           
target.onclick = () => {window.alert("!!!버튼눌림!!!")}           // 여러개 등록시, 마지막에 등록된것만 사용가능.

// addEventListener 방식:   
//! 이점: removeEventListener 사용가능. 같은 타겟에 여러 핸들러 등록가능.)
// click 말고 여러 이벤트들: https://developer.mozilla.org/en-US/docs/Web/Events 대표적으로 마우스, 키보드, 포커스, 폼, 터치 등.
target2.addEventListener('click', handleClick);         // 대부분의 web요소는 addEventListener를 가지고 있음.
target2.addEventListener('click', function(){ console.log("또다른 핸들러 호출됨.") })
target2.removeEventListener('click', handleClick);      //! 제거도 가능.


// 좀 이상하지만, 매개변수 event는 event객체를 함수로 전달가능. 매개변수 이름은 관습임.(e, event 등)
target3.addEventListener('click', (event) => { 
    console.log(event.target)       //! target 속성은 이벤트를 누른 버튼의 ID 등도 불러올 수 있음!
    const element_id = event.target.id;         // 스트링으로도 가져올 수 있음.
    console.log(element_id);
    console.log(event) 
})    