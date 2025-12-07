const http = require("http"); // http 모듈을 불러와서 http 변수로 할당.

let count = 0;


//! 관용적 표현이므로 분석하려 하지 말것  http.createServer(콜백함수) 정도의 형태로 이해하면됨. 화살표함수 대신 직접 함수를 정의해서 매개변수에 넣어도 작동함.
// 노드 서버 객체 생성 req = 요청. res = 응답
const server = http.createServer((req, res) => {
  log(count);   // count 1 추가 log함수는 아래에 정의됨.
  res.statusCode = 200;   //상태코드 200으로 설정(OK)
  res.setHeader("Content-Type", "text/plain"); // 부가정보설정. header에 설정됨. text/plain = 평문. text/html = html로 해석. (HTTP 프로토콜의 헤더 필드 정의 참고)
  res.write("hello\n"); // 응답으로 보낼 메시지.
  setTimeout(() => { // 2초뒤 Node.js를 응답으로 주고 종료. setTimeout(콜백함수, 지연시간) 구조임.
    res.end("Node.js");
  }, 2000);
});

function log(count) {
  console.log((count += 1)); // ❷
}

server.listen(8000, () => console.log("Hello Node.js")); // ➐ 접속 대기
// server.listen(포트번호, 콜백함수): 8000번 포트를 열고, 성공하면 콜백함수 실행.

// 여러군데 사용된 () => 는 람다식느낌임. js에서는 화살표함수 라고 표현함.