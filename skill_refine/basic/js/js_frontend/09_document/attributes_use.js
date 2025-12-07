// 예) JS의 속성접근특징: getter와 setter 정의시 내부적으로 함수처럼 작동.

const myObject = {
  _textContent: '초기값',

  get text() {
    return this._textContent;
  },

  set text(value) {
    this._textContent = value;
    console.log(`값이 '${value}'로 변경되었습니다.`);
  }
};


console.log(myObject._textContent); // '초기값' 출력

myObject._textContent = '새 내용'; // setter 작동 + 콘솔 출력
console.log(myObject._textContent); // '새 내용' 출력

