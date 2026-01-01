import 'package:flutter/material.dart';
import 'package:uuid/uuid.dart';
// flutter pub add uuid
import 'package:intl/intl.dart';
// date 정렬을 위해 사용. flutter pub add intl

final formatter = DateFormat.yMd(); // intl쪽이 로케일 다루기 까다로운것으로 앎.

const uuid = Uuid();

enum Category { food, travel, leisure, work }

const categoryIcons = {
  Category.food: Icons.lunch_dining,
  Category.travel: Icons.flight_takeoff,
  Category.leisure: Icons.movie,
  Category.work: Icons.work
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
    return DateFormat('yyyy/MM/dd').format(date);   // intl 방식으로 하지 않고 직접 지정함.(로케일 꼬임문제)
  }
}
