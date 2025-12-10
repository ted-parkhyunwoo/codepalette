import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // 이 위젯은 애플리케이션의 최상위 루트 위젯입니다.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        // 이 부분은 애플리케이션의 테마(색상, 폰트 등) 설정입니다.
        //
        // 시도해 보세요: "flutter run" 명령으로 앱을 실행해 보세요.
        // 앱 상단에 보라색 툴바가 보일 것입니다.
        // 그 후, 앱을 종료하지 않고 아래 colorScheme의 seedColor를 Colors.green으로
        // 변경하고 "핫 리로드(Hot Reload)"를 실행하세요
        // (Flutter를 지원하는 IDE에서 핫 리로드 버튼을 누르거나, 명령줄에서 앱을 시작했다면 'r' 키를 누르세요).
        //
        // 카운터 숫자가 0으로 재설정되지 않고 그대로 유지되는 것을 확인하세요. 애플리케이션 상태는 리로드 중에 손실되지 않습니다.
        // 상태를 재설정하려면 대신 핫 리스타트(Hot Restart)를 사용하세요.
        //
        // 이 기능은 값뿐만 아니라 코드 변경에도 작동합니다. 대부분의 코드 변경은 핫 리로드만으로 테스트할 수 있습니다.
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.tealAccent),
      ),
      home: const MyHomePage(title: '369 simulator'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  // 이 위젯은 애플리케이션의 홈 페이지입니다. 이 위젯은 상태(State)를 가지는 위젯이며,
  // 외형에 영향을 미치는 필드를 포함하는 State 객체(아래에 정의됨)를 가집니다.

  // 이 클래스는 상태(State)를 위한 설정입니다.
  // 부모(여기서는 App 위젯)가 제공한 값(여기서는 title)을 보유하고
  // State의 build 메서드에서 사용됩니다.
  // Widget 서브클래스의 필드는 항상 'final'로 표시됩니다.

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _counter = 0;
  String _clap = " ";
  final String threeSixNine = "369";

  void _clapSwitch(int num) {
    // 369 로직 구현부
    _clap = "";
    String n = num.toString();
    bool clapped = false;  
    for (int i = 0; i < n.length; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (n[i] == threeSixNine[j]) {
          _clap += "짝!";
          clapped = true;
          break;
        }
      }
    }
    if (!clapped) {
      _clap = " ";
    }
  }

  void _incrementCounter() {
    setState(() {
      // setState를 호출하면 Flutter 프레임워크에
      // 이 State에서 무언가 변경되었음을 알려줍니다.
      // 이는 아래 build 메서드를 다시 실행하여 업데이트된 값이 화면에 반영되도록 합니다.
      // setState()를 호출하지 않고 _counter를 변경하면 build 메서드가 다시 호출되지 않아 아무 일도 일어나지 않습니다.
      _counter++;
      _clapSwitch(_counter);
    });
  }

  @override
  Widget build(BuildContext context) {
    // 이 메서드는 _incrementCounter 메서드에서처럼 setState가 호출될 때마다 다시 실행됩니다.
    //
    // Flutter 프레임워크는 build 메서드의 재실행 속도를 빠르게 하도록 최적화되어 있습니다.
    // 따라서 개별 위젯의 인스턴스를 일일이 변경하는 대신, 업데이트가 필요한 모든 것을 다시 빌드할 수 있습니다.
    return Scaffold(
      appBar: AppBar(
        // 시도해 보세요: 여기서 색상을 특정 색상(예: Colors.amber)으로 변경하고
        // 핫 리로드를 실행하여 AppBar의 색상은 바뀌지만 다른 색상은 그대로 유지되는지 확인해 보세요.
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        // 여기서는 App.build 메서드가 생성한 MyHomePage 객체의 값을 가져와
        // 앱바의 제목을 설정하는 데 사용합니다.
        title: Text(widget.title),
      ),
      body: Center(
        // Center는 레이아웃 위젯입니다. 단일 자식(child)을 받아 부모의 중앙에 배치합니다.
        child: Column(
          // Column 또한 레이아웃 위젯입니다. 자식(children) 목록을 받아 수직으로 배열합니다.
          // 기본적으로 자체적으로 수평 크기는 자식에 맞추려 하고, 수직 크기는 부모만큼 커지려 합니다.
          //
          // Column은 크기를 조정하고 자식을 배치하는 다양한 속성을 가지고 있습니다.
          // 여기서 우리는 mainAxisAlignment를 사용하여 자식들을 수직으로 중앙에 배치합니다.
          // Column은 수직 방향이 주 축(main axis)이 됩니다 (교차 축(cross axis)은 수평이 됩니다).
          //
          // 시도해 보세요: "디버그 페인팅(debug painting)"을 실행하여
          // (IDE에서 "Toggle Debug Paint" 액션을 선택하거나, 콘솔에서 'p'를 누르세요)
          // 각 위젯의 와이어프레임을 확인해 보세요.
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Text('삼육구삼육구 삼육구삼육구:'),
            // 카운터 숫자 표시
            Text(
              '$_counter',
              style: Theme.of(context).textTheme.headlineMedium,
            ),
            // '짝!' 소리 표시
            Text('$_clap', style: TextStyle(fontSize: 50),)
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ),
    );
  }
}