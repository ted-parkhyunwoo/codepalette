// 클래스로 구현
class Calculating {
    constructor(a, b) {
        this.a = a;
        this.b = b;
    }

    add() { return this.a + this.b;}
    sub() { return this.a - this.b;}
    mul() { return this.a * this.b;}

    //! throw와 try- catch 사용은 사용자가 이 클래스의 구조를 모르면 사용이 복잡함. 보통은 class의 구조를 모르고도 사용할 수 있도록 구현해야 하기 때문에 간단한 예외처리는 콜백함수 구현의 div처럼 console.warn을 권장.
    div() { // 예외처리. throw의 경우 try - catch로 사용해야함
        if (this.b !== 0) { return this.a / this.b; } 
        else { throw new Error("div by zero is not allowed"); } // Error 객체 생성. (관례: 표준 객체 생성에 이름은 'Error') 로 할 것. 
        //! 이것이 궁금하면 Error를 다른이름으로 바꿔서 조작해볼 것. 예) 다른이름의 에러객체 생성 등.
    }
}

// 콜백함수로 구현
function calc(a, b, callback) { return callback(a, b); }
const add = function(a, b) { return a + b; };
const sub = function(a, b) { return a - b; };
const mul = (a, b) => { return a * b; };
const div = (a, b) => {     // 예외처리
    if (b == 0) { console.warn("div by zero is not allowed"); return null; } 
    else return a / b; 
};

function printdata(e) { console.log(e); }

function main() {
    // 콜백함수로 사용
    let res = calc(1,3, add);
    printdata(res);
    printdata(calc(5,4, mul));
    printdata(calc(3, 5, sub));
    printdata(calc(1,0, div));
    printdata(calc(0,1, div));

    // 클래스로 사용
    const calcInstance = new Calculating(10, 0);
    console.log(calcInstance.add());
    console.log(calcInstance.sub());
    console.log(calcInstance.mul());
    try { console.log(calcInstance.div()); }
    catch (error) {console.error("에러발생: ", error.message)}; 
    //! Error 객체 불러올땐 .message (표준 Error 객체를 불러옴)

    return 0;
}

main();