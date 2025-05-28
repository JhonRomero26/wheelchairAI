import 'package:flutter/material.dart';
import 'package:wheelchair/utils/colors.dart';

class GestureButton extends InkWell {
  final Color? color, foregroundColor;

  GestureButton({
    super.key,
    required Widget super.child,
    Color? splashColor,
    Color? highlightColor,
    super.hoverColor,
    this.color = Colors.transparent,
    this.foregroundColor = KColors.white,
    super.focusColor,
    super.borderRadius,
    super.overlayColor,
    super.radius,
    super.onTap,
    super.onDoubleTap,
    super.onLongPress,
    super.onTapCancel,
    super.onHighlightChanged,
    super.onHover,
    super.onTapDown,
    super.onTapUp,
  }) : super(
          splashColor: splashColor ??
              color?.withAlpha(25) ??
              KColors.primary.withAlpha(25),
          highlightColor: highlightColor ??
              color?.withAlpha(3) ??
              KColors.primary.withAlpha(3),
        );

  @override
  Widget build(BuildContext context) {
    // Agrega comportamiento adicional o personalización si es necesario
    return Material(
      borderRadius: borderRadius,
      color: color, // Fondo transparente por defecto
      child: super.build(context),
    );
  }
}
