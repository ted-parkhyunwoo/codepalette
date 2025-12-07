// if 문. 다른언어들과 같음(c스타일)

let a = 3;
let b = '3';

if (a == b) {
    console.log(" a == b ");
} else {
    console.log(" a != b ");
}


// 그냥 만든 콜백함수 a, b 엄격비교  boolean 리턴.
const strictCompare = function(a, b) {
    return a === b;
}

if (strictCompare(a, b)) {
    console.log(" a === b ");
} else {
    console.log(" a !== b ");
}