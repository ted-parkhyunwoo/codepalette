import 'package:flutter/material.dart';

import 'pages/calendar_page.dart';
import 'theme/app_theme.dart';

void main() {
  runApp(const SwimAndroidApp());
}

class SwimAndroidApp extends StatelessWidget {
  const SwimAndroidApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: '수영 기록 달력',
      debugShowCheckedModeBanner: false,
      theme: AppTheme.light,
      darkTheme: AppTheme.dark,
      themeMode: ThemeMode.system,
      home: const CalendarPage(),
    );
  }
}
