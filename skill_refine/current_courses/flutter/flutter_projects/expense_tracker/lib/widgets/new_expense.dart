import 'package:flutter/material.dart';
import 'package:expense_tracker/models/expense.dart';

// 앱바의 +를 누르면 나오는 하단 팝업 위젯 (새로운 지출 추가 위젯)

class NewExpense extends StatefulWidget {
  const NewExpense({super.key});

  @override
  State<NewExpense> createState() => _NewExpenseState();
}

class _NewExpenseState extends State<NewExpense> {
  // String _enteredTitle = '';     // controller 대신 onChanged로 직접 변수 대입방식 - 주석처리

  //! dart는 보통 자동 회수하지만, 리스너 명시하면 자동회수 안되므로, 사용시에는 반드시 닫는것도 명시해야함 (dispose()참고)
  // TextEditingController() 는 cpp의 stringstream 과 유사한 개념 .text로 꺼내씀
  final _titleController = TextEditingController();
  final _amountController = TextEditingController();
  DateTime? _selectedDate;
  Category _selectedCategory = Category.leisure;

  //! TextEditingController 방식 사용시 소멸자(정확히는 소멸자를 흉내낸 closer) 작성해줘야 gc 자원회수 힌트 명시됨
  // 그냥 c++ 일상에서 쓰던 소멸자로 이해하면 편함. (java의 AutoClosable구현체 처리, close() 오버라이드처럼)
  // 어느 언어든 입출력스트림 관련 모듈을 열었을 때 사용 후 리소스 해제를 위해 닫아줘야 하는 것 처럼 gc가 명시적으로 열린 _titleController 리스너를 dispose()를 시행하도록 유도
  @override
  void dispose() {
    _titleController.dispose();
    _amountController.dispose();
    super.dispose();
  }

  // 날짜 선택기
  void _presentDatePicker() async {
    final DateTime now = DateTime.now();
    final DateTime firstDate = DateTime(
      now.year - 1,
      now.month,
      now.day,
    );

    //! async, await 사용
    final DateTime? pickedDate = await showDatePicker(
      context: context,
      initialDate: now,
      firstDate: firstDate,
      lastDate: now,
    );

    setState(() {
      _selectedDate = pickedDate;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: EdgeInsets.all(16),
      child: Column(
        children: [
          //! 제목입력필드
          TextField(
            // 필드에 입력된 문자열을 변수 _enteredTitle 로 저장하기 위한 함수연결 방식 - 주석처리
            // onChanged: (str) => _enteredTitle = str,

            // 리스너 사용방식으로 대체.
            controller: _titleController,
            // 필드에 입력된 문자열 길이 제한 파라미터 : 0/50 형식으로 하단표기
            maxLength: 50,
            // 라벨을 적기 위해 데코레이션 설정: InputDecoration(label: ) 로 지정
            decoration: InputDecoration(label: Text("Title")),
          ),

          Row(
            children: [
              Expanded(
                //! 소비금액 입력필드
                child: TextField(
                  controller: _amountController,
                  // 숫자만 사용할 수 있도록 키보드 타입을 숫자패드로 명시
                  keyboardType: TextInputType.number,
                  decoration: InputDecoration(
                    // 필드 선택시 달러표시 추가되며, 필드에 저장되는 string엔 영향 없음
                    prefixText: '\$ ',
                    label: Text("Amount"),
                  ),
                ),
              ),

              const SizedBox(width: 16),

              Expanded(
                //! 날짜 선택
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.end,
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: [
                    Text(
                      _selectedDate == null
                          // 날짜를 선택하지 않으면 표시될 문자열
                          ? 'No date selected'
                          // 변수 뒤 !를 붙여 null이 무조건 아니라는것을 명시 가능
                          : Expense.getFormattedDate(
                              _selectedDate!,
                            ),
                    ),
                    IconButton(
                      onPressed: _presentDatePicker,
                      icon: const Icon(Icons.calendar_month),
                    ),
                  ],
                ),
              ),
            ],
          ),

          SizedBox(height: 16),

          Row(
            children: [
              //! 카테고리 드롭다운
              DropdownButton(
                value: _selectedCategory,
                items: Category.values
                    .map(
                      (category) => DropdownMenuItem(
                        value: category,
                        //! dart 전용 문법중 하나로, name.toString 등으로 문자열로 열거체 요소 이름을 가져올 수 있음
                        child: Text(category.name.toUpperCase()),
                      ),
                    )
                    .toList(),
                onChanged: (value) {
                  print(value);

                  if (value == null) {
                    return;
                  }

                  setState(() {
                    _selectedCategory = value;
                  });
                },
              ),

              const Spacer(),

              //! 닫기버튼
              TextButton(
                //! Navigator.pop 으로 위젯을 닫는 방법임
                onPressed: () => Navigator.pop(context),
                child: const Text("Cancel"),
              ),

              //! 가계부 추가버튼
              ElevatedButton(
                onPressed: () {
                  // print(_enteredTitle);
                  print(_titleController.text);
                  print(_amountController.text);
                },
                child: Text("Save Expense"),
              ),
            ],
          ),
        ],
      ),
    );
  }
}
