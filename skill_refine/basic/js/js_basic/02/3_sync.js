function displayA() { console.log('A');}
function displayB() { 
    setTimeout(() => console.log('B'), 1000);
}
function displayC() { console.log('C');}

displayA();
displayB();
displayC();


// 순서조절 - 콜백함수 사용시 : 코드가 읽기 더러워짐.간단한 것만 사용.
function displaya() { console.log('a');}
function displayb(callback) { 
    setTimeout(() => {
        console.log('b');
        callback();
    }, 1000);
}
function displayc() { console.log('c');}

displaya();
displayb(displayc);


// 프로미스, 어웨이트 등으로 순서를 조절할 수도 있음.