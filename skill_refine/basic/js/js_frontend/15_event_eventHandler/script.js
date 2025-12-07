//! 이벤트핸들러 handleClick : 함수표현식임.
const handleClick = () => {
    window.alert("Welcome");
    buttonObj.value = "Pushed";
    textObj.value = "누르면 안녕";
};

// 함수선언식의 이벤트핸들러.
function changeH1Tag(msg) {
    h1tag.textContent = msg;
}


// 아래는 같은코드. 쿼리셀렉터를 #으로 하면 id로 불러올 수 있음.
// const button = document.getElementById("push");
const buttonObj = document.querySelector("#push")
const textObj = document.querySelector("#typing");
textObj.value = "처음은 비워두자";  // input 요소 내용은 textContent가 아니라 value.
const h1tag = document.querySelector("h1");


//! 다음 구문은 '이벤트 핸들러 등록' 이라 함. 이벤트 핸들러 작성과 등록을 하는 전체 과정을 이벤트핸들링 이라 함
buttonObj.onclick = handleClick;   // callback 넘겨주듯이 ()를 넣지않음.
h1tag.onclick = () => {
    if (h1tag.textContent == "h1태그를 누르셨네요") {
        h1tag.textContent = "다시 누르셨네요";
    } else h1tag.textContent = "h1태그를 누르셨네요";
};

textObj.onclick = function(){textObj.value = "입력대기중"};


// 매개변수 전달시에는 콜백을 이용한다. () => 콜백() 형태가 아니라면 정상실행 안됨.
// 함수를 대입해야하지, 함수호출문을 대입(리턴값을 대입하게됨)하는것이 아니므로...
textObj.onkeydown = () => changeH1Tag("타이핑");
textObj.onkeyup = () => changeH1Tag("타이핑끝");







