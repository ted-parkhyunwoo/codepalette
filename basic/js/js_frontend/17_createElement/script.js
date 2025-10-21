// 이렇게 한다고 요소가 바로 추가되진 않음
let h1tag1 = document.createElement('h1');
let button1 = document.createElement('button');
let button2 = document.createElement('input');
let textField = document.createElement('input');
const nextLine = () => document.body.append(document.createElement('br'));     // 공백추가 함수화.

// 요소의 내용을 바꾸고
h1tag1.textContent = '하이'
button1.textContent = "버튼입니다";

button2.type = "button";
button2.value = "인풋으로 생성한 버튼";

textField.type = "text";
textField.value = "텍스트필드의 내용.";


// appendChild 로 객체 전달시 요소 추가.    (append 와의 차이점도 서술됨)
let nodeH1 = document.body.appendChild(h1tag1);         // addChild는 chilldElement 객체만 들어감. 리턴값으로는 h1tag1객체를 반환함.
let contentH1 = nodeH1.textContent = "안녕";            //! nodeH1 노드객체는 h1tag1를 가리키므로 같은 오브젝트를 가리키기 때문에 contentH1멤버접근으로 내용변경도 가능
if (nodeH1 === h1tag1) nodeH1.remove();                  //! nodeH1과 h1tag1 이 같다는 증거.

document.body.append('문자열 추가')                     // append는 문자열이나 childElement를 둘다 요소로 추가가능.
document.body.append(document.createElement('br'));     // append 메소드는 반환하지 않고 추가함.
document.body.appendChild(button1);
nextLine();                                             // 공백처리 함수화 해봄.
document.body.appendChild(button2);
nextLine();
document.body.appendChild(textField);


// 다음 테스트를 위해 삭제불가능한 객체를 제외하고 모두 제거.
for (let obj of [button1, button2, textField]) obj.remove();
while (document.querySelector('br')) { document.querySelector('br').remove(); }

nextLine();

// 실습코드
let btn = document.createElement('button');
btn.textContent = "클릭하시오";

document.body.appendChild(btn);
let delBtn = document.createElement("button");
delBtn.textContent = "삭제";
document.body.appendChild(delBtn);


let makeDiv = document.createElement('div');
makeDiv.id = 'area';
document.body.appendChild(makeDiv);

let subdivArray = []

btn.addEventListener('click', function() {
    let subdiv = document.createElement('div');
    subdivArray.push(subdiv);
    subdiv.style.backgroundColor = 'red';
    subdiv.style.width = '50px';
    subdiv.style.height = "50px";
    makeDiv.appendChild(subdiv);
});

delBtn.addEventListener('click', ()=>{
    if (subdivArray) {
        subdivArray[0].remove();
        subdivArray.shift();
    }
}) ;