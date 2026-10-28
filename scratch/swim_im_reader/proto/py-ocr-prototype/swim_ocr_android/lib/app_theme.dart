import 'package:flutter/material.dart';

/// Centralizes the light and dark Material 3 color systems for the app.
abstract final class AppTheme {
  static const _seedColor = Color(0xFF167B88);

  /// Builds the light palette used when the device is in light mode.
  static ThemeData get light => _build(Brightness.light);

  /// Builds the dark palette used when the device is in dark mode.
  static ThemeData get dark => _build(Brightness.dark);

  static ThemeData _build(Brightness brightness) {
    final isDark = brightness == Brightness.dark;
    final scheme = ColorScheme.fromSeed(
      seedColor: _seedColor,
      brightness: brightness,
      surface: isDark ? const Color(0xFF172326) : Colors.white,
    );
    return ThemeData(
      useMaterial3: true,
      brightness: brightness,
      scaffoldBackgroundColor:
          isDark ? const Color(0xFF10191C) : const Color(0xFFF3F7F7),
      colorScheme: scheme,
      appBarTheme: AppBarTheme(
        backgroundColor:
            isDark ? const Color(0xFF10191C) : const Color(0xFFF3F7F7),
        foregroundColor: scheme.onSurface,
        elevation: 0,
        centerTitle: false,
      ),
      cardTheme: CardThemeData(
        color: scheme.surface,
        elevation: 0,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(20),
          side: BorderSide(color: scheme.outlineVariant),
        ),
      ),
    );
  }
}
