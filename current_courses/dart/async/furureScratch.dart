import 'dart:math';
import 'dart:io';

void main(List<String> args) async {

  // getRand 단독사용 예제
  for (int i = 0; i < 10; ++i) {
    int a = await getRand(3, 5);
    stdout.write(a);
  }
  stdout.write("\n");


  // getRandArray는 네트워크로 정보를 불러오는 시뮬레이트임(1~7초 뒤에 데이터를 받음)
  final Future<List<int>> Arr1 = getRandArray(size: 10, start: 1, maximum: 9); 
  final Future<List<int>> Arr2 = getRandArray(size: 10, start: 11, maximum: 19);
  final Future<List<int>> Arr3 = getRandArray(size: 10, start: 21, maximum: 29);
  final Future<List<int>> Arr4 = getRandArray(size: 10, start: 31, maximum: 39);
  final Future<List<int>> Arr5 = getRandArray(size: 10, start: 41, maximum: 49);

  // then(): 데이터 도착시 실행
  Arr1.then((v) => print("Arr1 ( 1~ 9): $v"));
  Arr2.then((v) => print("Arr2 (11~19): $v"));
  Arr3.then((v) => print("Arr3 (21~29): $v"));
  Arr4.then((v) => print("Arr4 (31~39): $v"));
  Arr5.then((v) => print("Arr5 (41~49): $v"));


  final List<Future<List<int>>> allFutures = [ Arr1, Arr2, Arr3, Arr4, Arr5 ];
  
  // wait(): await걸면 모든 데이터가 완성되기 전까지 대기시킴
  await Future.wait(allFutures);
  
  print("\n모든 5 배열의 비동기 작업 도착 완료!");
}


Future<int> getRand(int start, int maximum) async {
  return Random().nextInt(maximum + 1 - start) + start;
}


Future<List<int>> getRandArray({ required int size,  int start = 0, required int maximum}) async {
  List<int> res = List.filled(size, 0);

  for (int i = 0; i < size; ++i) {
    res[i] = await getRand(start, maximum);
  }

  // 1 ~ 7초뒤 불러오는 과정을 시뮬레이트
  int delayTime = await getRand(1, 7);
  return Future.delayed(Duration(seconds: delayTime), () => res);
}