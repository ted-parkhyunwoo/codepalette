const path = require("path");

// join() 파일 전체 경로를 만듬.
const fullPath = path.join('some', 'work', 'example.txt');
console.log(fullPath);  // some\work\ex.txt

// dirname() : 경로만 추출
const dir = path.dirname(fullPath);
console.log(dir);

// basename() : 파일이름만 추출
const fn = path.basename(fullPath);
console.log(fn);
console.log(path.basename(__filename));

// basename() 에서 파일이름만 추출하되 특정확장자 '.js' 확장자 제거.
const fn2 = path.basename(__filename, '.js');
console.log(fn2);

// extname() : 파일확장자.
const en1 = path.extname(fullPath);
console.log(en1);
// 확장자를 모르는 상태에서 확장자 제거
const myFnWithoutExt = path.basename(fullPath, en1);
console.log(myFnWithoutExt);