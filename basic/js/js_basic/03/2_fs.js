// file system은 동기식, 비동기식(콜백, 프라미스) 등이 따로 제공됨.
// const { readdirSync } = require("fs");   //동기식. https://nodejs.org/docs/latest/api/fs.html#fsreadsyncfd-buffer-options

// 다음 예제들은 비동기식,콜백사용    
//! DOCS 참고: https://nodejs.org/docs/latest/api/fs.html#fsreaddirpath-options-callback

const fs = require('fs');
const path = require('path');
const currentPath = path.dirname(__filename);

//!  1. readdir(경로, [옵션], 콜백(err, files)) -> files 는 파일/경로의 이름(string) 배열로 리턴. 객체 아님을 주의.
// 문제점: 현재 코드는 files의 요소들이 string이며, file인지 dir인지 알 수가 없음. fs.stat(경로, 콜백)을 사용해야 구분함. stats.isDirectory(). docs 찾아볼것.
fs.readdir(currentPath, (err, files) => {
    if (err) { console.log(err); }
    console.log(files);
});

// TEST 콜백을 화살표함수로 쓰지 않을 때
function myCallback(err, files) { 
    if (err) { console.log(err); }
    console.log(files);
}
fs.readdir("./", myCallback);


//!  2. readFile(경로, [옵션], 콜백(err, data)) -> data 는 파일 내용을 Buffer객체로 return. 하지만 옵션에 "utf8" 명시하면 string으로 return.
const targetPath = path.join(currentPath, 'test.txt')
fs.readFile(targetPath, "utf8", (err, data) => {
    if (err) {
        console.error("파일을 읽는 중 오류 발생:", err);
        return;
    }
    console.log(data);

    //! 3. writeFile
    const newFilePath = path.join(currentPath, 'new.txt');
    const newData = data + "새로운 정보가 data 에 추가됨.";
    fs.writeFile(newFilePath, newData, (err) => {
        if (err) { console.log(err); }
        console.log('기록완료.');
    })
});


// TEST: buffer 객체 사용시 console.log에서 직접 utf-8로 디코딩. (객체.toString('utf8')) 옵션으로는 utf8,hex,base64 등으로 사용가능.
fs.readFile(targetPath, (err, data) => {
    if (err) {
        console.error("파일을 읽는 중 오류 발생:", err);
        return;
    }
    console.log(data.toString('utf8')); // console.log에서 직접 Buffer → UTF-8 문자열 변환

    // 쓸데없는 코드: 메모리 버퍼와 base64, utf8 간 서로 변환 방법을 제시함. (파이썬의 .decode() 기능이 조금 더 변환에 강력한듯.)
    const testbase64 = data.toString('base64');         //  aGVsbG8NCuyViOuFle2VmOyEuOyalA0K
    console.log(Buffer.from(testbase64, 'base64').toString('utf8'));  // base64 string -> base64 버퍼 -> utf8 string
});

