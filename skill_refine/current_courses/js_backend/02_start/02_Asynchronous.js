//! 비동기 처리 예제
/* 절차 설명: 이벤트 기반 아키텍처.
싱글 쓰레드 + 이벤트 루프 기반(비동기처리) 라서, 멀티쓰레드 처럼 작동한다.
예를들어 single core CPU 에서 windows 가 멀티태스킹 하던 방법과 개념이 유사함.

a,b,c,d,e 과제를 a하나, b하나, c하나.... 씩 싱글스레드(콜스택)가 정해진 순서로 업무를 검토하고, 
직접 바로 연산하거나, 시간이 걸리는건 node.js API(브라우저는 web api)로 넘김. 
따라서 뭐가 먼저 끝날지를 모르는거임. 원하는 순서를 보장하기 위해서는 콜백, Promise, async/await 등을 사용.
*/

console.log("1");   // 1. 콜스택에서 바로 출력

// 2. 콜스택에서 setTimeout() 을 Node.js API(libuv)로 넣고 Node.js api가 1초뒤 -> 태스크 큐(작업순서)로 넣음. 
// 태스크큐가 콜스택이 비워지는 순간 바로 console.log를 콜스택에 넣고 출력. 
setTimeout(() => console.log(2), 1000);     

console.log("3");   // 3. setTimeout()이 Node.js API로 넘어가는 순간 바로 다음과제인 console.log("3")을 콜스택에 넣고 바로 출력

/* 결과:
1
3
(1초 후)
2           <- 문자가 아닌 정수 타입
*/