//! localStorage 는 브라우저 자체가 할당한 클라이언트의 로컬 저장소에 데이터를 영구적으로 저장. (tmp랑은 좀 다름)

localStorage.setItem("key", "value");           // key , value가 저장소-로컬저장소에 저장됨.
console.log(localStorage.getItem("key"));       // getItem은 key로 불러옴.
localStorage.setItem("key", "hello");           // key,value는 하나씩만 가능하므로, 기존것이 수정됨.
localStorage.removeItem('key');                 // 데이터 삭제

localStorage.setItem("key", "1");
localStorage.setItem("key1", "2");
localStorage.setItem("key2", "3");

// localStorage.clear();                           // 모두 삭제.