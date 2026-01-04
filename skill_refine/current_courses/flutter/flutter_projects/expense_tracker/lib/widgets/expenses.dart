import 'package:expense_tracker/widgets/expenses_list/expenses_list.dart';
import 'package:expense_tracker/models/expense.dart';
import 'package:expense_tracker/widgets/new_expense.dart';
import 'package:flutter/material.dart';

class Expenses extends StatefulWidget {
  const Expenses({super.key});

  @override
  State<Expenses> createState() => _ExpensesState();
}

class _ExpensesState extends State<Expenses> {
  final List<Expense> _registeredExpenses = [
    // dummy data.
    Expense(
      title: "Flutter Course(샘플)",
      amount: 19.99,
      date: DateTime.now(),
      category: Category.work,
    ),
    Expense(
      title: "Cinema(샘플)",
      amount: 15.69,
      date: DateTime.now(),
      category: Category.leisure,
    ),
  ];

  // 새로 추가시 openAddExpenseOverlay의 showModalBottomSheet로 연결할 메서드
  void _addNewExpense(Expense expense) {
    setState(() {
      _registeredExpenses.add(expense);
    });
  }

  // 삭제: expenses_list 에서 스와이프시 작동
  void _removeExpense(Expense targetExpense) {
    final int lastIdx = _registeredExpenses.indexOf(targetExpense);
    setState(() {
      _registeredExpenses.remove(targetExpense);
    });

    // 이전의 스낵바가 떠있다면 이전 스낵바 우선 제거(연속제거시)
    ScaffoldMessenger.of(context).clearSnackBars();
    //! 스낵바 사용(삭제한 내역 취소 가능하게 함)
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(
        //! 무슨일인지 3초뒤 제거가 안됨: action속성 비활성화 주석처리시 3초내 정상적으로 사라짐
        duration: const Duration(seconds: 3),
        content: const Text("Expense deleted."),
        // undo 라벨에는 삭제취소 기능 구현
        action: SnackBarAction(
          label: "Undo",
          onPressed: () {
            setState(() {
              _registeredExpenses.insert(lastIdx, targetExpense);
            });
          },
        ),
      ),
    ).closed.then((r){print("[log] closed: $r");});
  }

  //! show ModalBottomSheet 는 context(현재 위젯의 주소: 위젯트리 위치정보 정도로 이해하면 됨)를 토대로 builder로 생성한 위젯을 화면 하단에 로드
  void _openAddExpenseOverlay() {
    showModalBottomSheet(
      isScrollControlled: true, // 창을 가득 채우고 스크롤 가능하게 함
      context: context,
      builder: (context) =>
          NewExpense(addNewExpense: _addNewExpense),
    );
  }

  @override
  Widget build(BuildContext context) {
    // 비어있는 경우, 아닌경우 구분해서 위젯 설정
    Widget mainContent = const Center(
      child: Text("No expenses found. Start adding some!"),
    );

    if (_registeredExpenses.isNotEmpty) {
      mainContent = ExpensesList(
        expenses: _registeredExpenses,
        onRemoveExpense: _removeExpense,
      );
    }
    return Scaffold(
      appBar: AppBar(
        title: Text("Flutter Expense Tracker"),
        actions: [
          IconButton(
            onPressed: _openAddExpenseOverlay,
            icon: Icon(Icons.add),
          ),
        ],
      ),
      body: Column(
        children: [
          const Text("The chart"),
          Expanded(child: mainContent),
        ],
      ),
    );
  }
}
