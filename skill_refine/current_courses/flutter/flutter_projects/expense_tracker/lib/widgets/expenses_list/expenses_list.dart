import 'package:expense_tracker/models/expense.dart';
import 'package:expense_tracker/widgets/expenses_list/expense_item.dart';
import 'package:flutter/material.dart';

class ExpensesList extends StatelessWidget {
  final List<Expense> expenses;

  const ExpensesList({super.key, required this.expenses});

  @override
  Widget build(BuildContext context) {
    //! ListView.builder = itemCount 갯수만큼 itemBuilder로 List를 전개하여 표현(렌더링)할 위젯: ExpensiveItem을 설정
    // map과 거의 동일하게 작동하나, ListView 는 필요한만큼만 지연하여 생성: 데이터가 많을 때 스크롤시 그때그때 생성
    // map은 한번에 다 로드하기 때문에 앱이 멈춘것 처럼 표현 될 수 있음
    return ListView.builder(
      itemCount: expenses.length,
      itemBuilder: (context, index) =>
          ExpenseItem(expense: expenses[index]),
    );
  }
}
