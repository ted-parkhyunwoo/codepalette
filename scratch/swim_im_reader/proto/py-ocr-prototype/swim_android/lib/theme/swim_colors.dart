import 'package:flutter/material.dart';

Color swimStrokeColor(BuildContext context, String stroke) {
  final isDark = Theme.of(context).brightness == Brightness.dark;
  return switch (stroke) {
    '자유' || '자유형' => isDark ? Colors.tealAccent : Colors.teal.shade800,
    '접영' => isDark ? Colors.purpleAccent : Colors.deepPurple.shade600,
    '배영' => isDark ? Colors.lightBlueAccent : Colors.blue.shade700,
    '평영' => isDark ? Colors.amberAccent : Colors.orange.shade800,
    '혼영' || 'IM' => isDark ? Colors.pinkAccent : Colors.pink.shade700,
    '킥판' => isDark ? Colors.lightGreenAccent : Colors.green.shade800,
    _ => isDark ? Colors.white70 : Colors.blueGrey.shade700,
  };
}

Color calendarWeekendColor(BuildContext context, int weekday) {
  final isDark = Theme.of(context).brightness == Brightness.dark;
  if (weekday == DateTime.sunday) {
    return isDark ? Colors.redAccent : Colors.red.shade700;
  }
  if (weekday == DateTime.saturday) {
    return isDark ? Colors.lightBlueAccent : Colors.blue.shade700;
  }
  return Theme.of(context).colorScheme.onSurface;
}

List<Color> heartRateZoneColors(BuildContext context) {
  final isDark = Theme.of(context).brightness == Brightness.dark;
  return [
    isDark ? const Color(0xff64b5f6) : const Color(0xff1976d2),
    isDark ? const Color(0xff81c784) : const Color(0xff388e3c),
    isDark ? const Color(0xffffd54f) : const Color(0xfff9a825),
    isDark ? const Color(0xffffb74d) : const Color(0xffef6c00),
    isDark ? const Color(0xffef9a9a) : const Color(0xffd32f2f),
  ];
}

Color restAnalysisStatusColor(
  BuildContext context, {
  required bool analyzed,
  required bool needsReview,
}) {
  final isDark = Theme.of(context).brightness == Brightness.dark;
  if (!analyzed) return isDark ? Colors.lightBlueAccent : Colors.blue.shade700;
  if (needsReview) return isDark ? Colors.orangeAccent : Colors.orange.shade800;
  return isDark ? Colors.lightGreenAccent : Colors.green.shade700;
}

Color ocrAccuracyColor(BuildContext context, double accuracyPercent) {
  final isDark = Theme.of(context).brightness == Brightness.dark;
  return accuracyPercent >= 99
      ? isDark
            ? Colors.lightGreenAccent
            : Colors.green.shade700
      : isDark
      ? Colors.orangeAccent
      : Colors.orange.shade800;
}
