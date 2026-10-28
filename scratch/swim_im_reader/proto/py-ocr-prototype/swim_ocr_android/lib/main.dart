import 'package:flutter/material.dart';

import 'app_theme.dart';
import 'pages/upload_page.dart';

/// Starts the offline swim-record analysis application.
void main() {
  runApp(const SwimOcrApp());
}

/// Configures app navigation and follows the operating system color scheme.
class SwimOcrApp extends StatelessWidget {
  const SwimOcrApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: '수영 기록 분석',
      debugShowCheckedModeBanner: false,
      theme: AppTheme.light,
      darkTheme: AppTheme.dark,
      themeMode: ThemeMode.system,
      home: const UploadPage(),
    );
  }
}
