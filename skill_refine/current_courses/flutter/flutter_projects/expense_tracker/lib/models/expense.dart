import 'package:flutter/material.dart';
import 'package:uuid/uuid.dart';
// flutter pub add uuid
import 'package:intl/intl.dart';
// date 정렬을 위해 사용. flutter pub add intl

// 지출내역 데이터 타입 구조체: 내부 card id(uuid 사용), title, amount, date, category(열거체) 담음
// 추가기능: Category 타입별 icon을 사전정의. formattedDate, getFormattedDate 를 통해 Stirng 타입의 날짜를 받을 수 있음

final formatter = DateFormat.yMd(); // intl쪽이 로케일 다루기 까다로운것으로 앎.

const uuid = Uuid();

enum Category { food, travel, leisure, work }

const categoryIcons = {
  Category.food: Icons.restaurant,
  Category.travel: Icons.flight_takeoff,
  Category.leisure: Icons.movie,
  Category.work: Icons.work,
};

class Expense {
  final String id;
  final String title;
  final double amount;
  final DateTime date;
  final Category category;

  // id 는 uuid v4메서드(다른것도 가능은 함) 를 통해 고유 id를 부여받음
  Expense({
    required this.title,
    required this.amount,
    required this.date,
    required this.category,
  }) : id = uuid.v4();

  String get formattedDate {
    // return formatter.format(date);
    return DateFormat(
      'yyyy/MM/dd',
    ).format(date); // intl 방식으로 하지 않고 직접 지정함.(로케일 꼬임문제)
  }

  //! 개인적으로 intl이 영 불편해서 직접 만든 함수.
  static String getFormattedDate(DateTime time) {
    return DateFormat('yyyy/MM/dd').format(time);
  }
}

// chart 를 위한 버킷 모델
class ExpenseBucket {
  final Category category;
  final List<Expense> expenses;

  const ExpenseBucket({
    required this.category,
    required this.expenses,
  });

  //! 대체생성자: 카테고리가 사용자 지정된 this.category의 가계부만 where필터 정렬 후 다시 리스트화
  ExpenseBucket.forCategory(List<Expense> allExpenses, this.category)
    : expenses = allExpenses.where((expense) => expense.category == category).toList();

  // 총지출 getter.
  double get totalExpenses {
    double res = 0;
    for (final Expense expense in expenses) {
      res += expense.amount;
    }
    return res;
  }
}
