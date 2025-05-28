import 'package:flutter/material.dart';

class KColors {
  static const black = Color(0xFF0F0F0F);
  static const white = Color(0xFFFFFFFF);

  static const MaterialColor primary = MaterialColor(
    0xFFFE001B,
    <int, Color>{
      50: Color(0xFFFCDDE0),
      100: Color(0xFFFBC0C6),
      200: Color(0xFFF8939C),
      300: Color(0xFFF75563),
      400: Color(0xFFFE001B),
      500: Color(0xFFF50000),
      600: Color(0xFFCF0000),
      700: Color(0xFFAA0000),
      800: Color(0xFF8D0004),
      900: Color(0xFF4D0004),
    },
  );

  static const MaterialColor neutral = MaterialColor(
    0xFF5D5D5D,
    <int, Color>{
      50: Color(0xFFE7E7E7),
      100: Color(0xFFD1D1D1),
      200: Color(0xFFB0B0B0),
      300: Color(0xFF888888),
      400: Color(0xFF6D6D6D),
      500: Color(0xFF5D5D5D),
      600: Color(0xFF4F4F4F),
      700: Color(0xFF454545),
      800: Color(0xFF3D3D3D),
      900: Color(0xFF0F0F0F),
    },
  );
}

class TypographyColors {
  final Color primary, body, muted, accent;

  const TypographyColors({
    required this.primary,
    required this.body,
    required this.muted,
    required this.accent,
  });
}

class KDarkTheme {
  static const primary = KColors.primary;
  static const background = KColors.black;

  static Color ui01 = KColors.neutral.shade800;
  static Color ui02 = KColors.neutral.shade700;
  static Color ui04 = KColors.neutral.shade600;
  static Color ui05 = KColors.white;

  static TypographyColors typography = TypographyColors(
    primary: KColors.white,
    body: KColors.neutral.shade400,
    muted: KColors.neutral.shade600,
    accent: KColors.primary,
  );
}
