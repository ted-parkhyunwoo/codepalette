
//setTimeout    : 
setTimeout(()=>console.log("hi"), 5000);        // 5초뒤 실행.


// setInterval(callback, ms_time) ms_time마다 계속 실행
let i = 0
let loop = setInterval(() => {
    console.log('HELLO');
    i++;
    if (i === 5) clearInterval(loop);       // html이면 click event로 설정 가능하나, 콘솔용 코드이므로 루프 내 기저조건 적음.
}, 1000);



//! 함수들이 동시에 실행됨 ㅡㅡ. 