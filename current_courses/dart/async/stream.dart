import 'dart:async';

// 주의: 개념 진짜 어려움. 


void main(List<String> args) {

  final controller = StreamController();
  final stream = controller.stream.asBroadcastStream();   // 리스너 두개이상(한개가 아닐 때) 는 asBroadcastStream() 을 붙임.

  final streamListener1 = stream.where((val) => val % 2 == 0).listen((val) { print("Listener1: $val"); });  // 짝수만 리스닝
  final streamListener2 = stream.where((val) => val % 2 == 1).listen((val) { print("Listener2: $val"); });  // 홀수만 리스닝

  // 얼마든지 삽입가능. 
  controller.sink.add(1);
  controller.sink.add(2);
  controller.sink.add(3);
  controller.sink.add(4);
  controller.sink.add(5);
  
  // Stream리턴방식 함수 사용
  calc(1).listen((val) { print("calc1: $val");});
  calc(5).listen((val) { print("calc5: $val");});  

  
  // await식으로 순서보장 (//Todo 다만 calc10은 먼저 실행됨: 해결하려 했으나 Future등과 결합해야 할 것 같음)
  playStream().listen((val) {print("playstream: $val");});

}


Stream<int> playStream() async* {
  yield* calc(10);
  yield* calc(1000);
}


Stream<int> calc(int number) async* {
  for (int i = 0; i < 5; ++i) {
    yield number * i;                             // yield는 리턴이 아니나 비슷하게 작동함. 다만 종료하지않고 연속적으로 갱신
    await Future.delayed(Duration(seconds: 1));   // async* 이지만 Future사용가능.
  }
}