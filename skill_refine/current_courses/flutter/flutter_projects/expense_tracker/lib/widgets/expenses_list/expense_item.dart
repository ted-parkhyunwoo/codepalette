import 'package:expense_tracker/models/expense.dart';
import 'package:flutter/material.dart';

// 각개의 Expense 를 widget으로 전환(Card)
// ExpensesList에서 ListView로 로드하여 위젯으로 전환 사용중

class ExpenseItem extends StatelessWidget {
  const ExpenseItem({super.key, required this.expense});

  final Expense expense;

  @override
  Widget build(BuildContext context) {
    //! 새로운 위젯: Card
    return Card(
      // 하위 child로 Column 만 있었으나, Padding 으로 래핑(Card 내부!에서 간격조절)
      child: Padding(
        padding: const EdgeInsets.symmetric(
          horizontal: 20,
          vertical: 16,
        ),
        child: Column(
          children: [
            Text(expense.title),
            const SizedBox(height: 4),
            Row(
              // double 객체의 toString 과는 다르게 double의 2자리까지만 표현하도록 강제하는 toStringAsFixed()
              children: [
                Text('\$${expense.amount.toStringAsFixed(2)}'),
                // Expanded(child: SizedBox()), // 대신 Spacer() 사용.
                const Spacer(),
                Row(children: [
                  Icon(categoryIcons[expense.category]),
                  const SizedBox(width: 8),
                  Text(expense.formattedDate)
                ],)
                
              ],
            ),
          ],
        ),
      ),
    );
  }
}
