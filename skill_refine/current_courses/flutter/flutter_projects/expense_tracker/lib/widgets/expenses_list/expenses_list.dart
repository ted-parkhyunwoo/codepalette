import 'package:expense_tracker/models/expense.dart';
import 'package:expense_tracker/widgets/expenses_list/expense_item.dart';
import 'package:flutter/material.dart';

// Expenses 내 Card 형태로(ExpenseItem) 지출내역을 열거하는 ListView 위젯

class ExpensesList extends StatelessWidget {
  final List<Expense> expenses;
  // 삭제 기능 추가를 위한 멤버변수
  final void Function(Expense expense) onRemoveExpense;

  const ExpensesList({
    super.key,
    required this.expenses,
    required this.onRemoveExpense,
  });

  @override
  Widget build(BuildContext context) {
    //! ListView.builder = itemCount 갯수만큼 itemBuilder로 List를 전개하여 표현(렌더링)할 위젯: ExpensiveItem을 설정
    // map과 거의 동일하게 작동하나, ListView 는 필요한만큼만 지연하여 생성: 데이터가 많을 때 스크롤시 그때그때 생성
    // map은 한번에 다 로드하기 때문에 앱이 멈춘것 처럼 표현 될 수 있음
    return ListView.builder(
      itemCount: expenses.length,
      // Dismissable은 지울 수 있게 만듬(스와이프), key와 child 필수.
      // key 는 super.key같은 것들과 같은 타입임. 대부분 이것을 만질일은 없음.
      // 위젯에 특별한 식별자 부여. ValueKey로 생성가능(마치 HashCode처럼...) context는 주소로 이해, key는 List 요소들의 식별로 이해하면 편함
      itemBuilder: (context, index) => Dismissible(
        key: ValueKey(expenses[index]),
        onDismissed: (direction) {
          onRemoveExpense(expenses[index]);
        },
        child: ExpenseItem(expense: expenses[index]),
      ),
    );
  }
}
