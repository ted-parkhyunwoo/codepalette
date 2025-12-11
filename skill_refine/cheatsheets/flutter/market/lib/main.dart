import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // 당근 판매위젯
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        backgroundColor: Colors.white,

        // 스캐폴드 상단바
        appBar: AppBar(
          toolbarHeight: 50,
          backgroundColor: Colors.orangeAccent,
          foregroundColor: Colors.white,
          actions: [Icon(Icons.star), Icon(Icons.star)],
          leading: Icon(Icons.menu),
          title: Text("채찍마켓"),
        ),

        // 3가지 버튼의 사용예제
        // body: TextButton(onPressed: (){}, child: Text("Hi")),
        /*
        body: ElevatedButton(
          onPressed: (){},
          child: Text("hi"),
          style: ElevatedButton.styleFrom(
            backgroundColor: Colors.red,
            foregroundColor: Colors.black
          )
        ),
        */
        // body: IconButton(onPressed: (){}, icon: Icon(Icons.call)),

        // 스캐폴드 바디
        body: Container(
          // 상단만 좀 늘림.
          margin: EdgeInsets.fromLTRB(0, 10, 0, 0),
          // Column 이였으나, ListView로 바꾸면 스크롤 가능.
          // controller 속성으로 스크롤 위치를 알아낼수 있다 함.
          // 특정위치만 표시하여 메모리 절약등에 활용(쇼핑몰 목록, sns피드모음 등)
          child: ListView(children: [ShopItem(), ShopItem()]),
        ),

        // 스캐폴드 하단바
        bottomNavigationBar: BottomAppBar(
          height: 50,
          color: Colors.white10,
          shadowColor: Colors.white70,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              Icon(
                Icons.add_reaction_outlined,
                size: 30,
                color: Colors.black54,
              ),
              Icon(
                Icons.add_location_alt_outlined,
                size: 30,
                color: Colors.black54,
              ),
              Icon(Icons.add_circle_outline, size: 30, color: Colors.black54),
              Icon(Icons.add_a_photo_outlined, size: 30, color: Colors.black54),
            ],
          ),
        ),
      ),
    );
  }
}

// class 위젯 커스텀: 큰 UI, 자주쓰는 위젯 등을 분리활용하는것이 좋음.
// Widget 리턴 메서드로도 가능하지만 Class로도 가능. stless 탭으로 만들어진 보일러플레이트를 이용할 것.
class ShopItem extends StatelessWidget {
  const ShopItem({super.key});

  @override
  Widget build(BuildContext context) => Container(
    margin: EdgeInsets.fromLTRB(20, 15, 20, 15),
    alignment: Alignment.topCenter,
    child: Row(
      children: [
        // 사진파트
        Image.asset("assets/cannon.jpg", width: 110, height: 110),

        // 글씨 파트
        Expanded(
          // Flexible 은 비율설정(안써봄). Expanded는 한쪽만 알아서 채움
          child: Container(
            height: 110,
            margin: EdgeInsets.fromLTRB(15, 0, 0, 0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                // 제목
                Text(
                  "캐논 DSLR 100D (단렌즈, 충전기 16기가 SD 포함)",
                  style: TextStyle(fontSize: 15),
                ),
                // 지역/시간 정보
                Text(
                  "성동구 행당동 · 끌올 10분 전",
                  style: TextStyle(fontSize: 11, color: Colors.black54),
                ),
                // 가격
                Text("210,000원", style: TextStyle(fontSize: 14)),

                // 좋아요
                Expanded(
                  child: Row(
                    mainAxisAlignment: MainAxisAlignment.end,
                    crossAxisAlignment: CrossAxisAlignment.end,
                    children: [
                      Icon(
                        Icons.favorite_border,
                        size: 16,
                        color: Colors.black54,
                      ),
                      Text(
                        "4",
                        style: TextStyle(fontSize: 13, color: Colors.black54),
                      ),
                    ],
                  ),
                ),
              ],
            ),
          ),
        ),
      ],
    ),
  );
}
