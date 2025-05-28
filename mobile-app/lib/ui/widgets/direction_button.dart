import 'package:flutter/material.dart';
import 'package:wheelchair/ui/widgets/gesture_button.dart';
import 'package:wheelchair/utils/colors.dart';

enum DRIVE_DIRECTION {
  left(0),
  up(1),
  right(2),
  down(3);

  const DRIVE_DIRECTION(this.value);
  final int value;
}

double cutStopPercentStart = 0.4;
double cutStopPercentEnd = 1 - cutStopPercentStart;

class DirectionButton extends StatelessWidget {
  final double width, height, iconSize;
  final Color? color;
  final Widget icon;
  final DRIVE_DIRECTION direction;
  final Function()? onPressed, onTapCancel;
  final Function(TapDownDetails)? onTapDown;
  final Function(TapUpDetails)? onTapUp;

  const DirectionButton({
    super.key,
    required this.width,
    required this.height,
    required this.icon,
    required this.iconSize,
    required this.direction,
    this.onPressed,
    this.onTapDown,
    this.onTapUp,
    this.onTapCancel,
    this.color = Colors.transparent,
  });

  @override
  Widget build(BuildContext context) {
    CustomClipper<Path> clipper = DirectionClipPath(direction);

    return ClipPath(
      clipper: clipper,
      child: GestureButton(
        onTap: onPressed,
        onTapDown: onTapDown,
        onTapUp: onTapUp,
        onTapCancel: onTapCancel,
        child: SizedBox(
          height: height,
          width: width,
          child: IconTheme(
            data: IconThemeData(
              size: iconSize,
              color: KDarkTheme.typography.body,
            ),
            child: icon,
          ),
        ),
      ),
    );
  }
}

class DirectionClipPath extends CustomClipper<Path> {
  final DRIVE_DIRECTION direction;

  DirectionClipPath(this.direction);

  @override
  Path getClip(Size size) {
    double w = size.width;
    double h = size.height;
    final path = Path();

    switch (direction) {
      case DRIVE_DIRECTION.left:
        path.lineTo(0, 0);
        path.lineTo(w, h * cutStopPercentStart);
        path.lineTo(w, h * cutStopPercentEnd);
        path.lineTo(0, h);
        break;
      case DRIVE_DIRECTION.up:
        path.lineTo(0, 0);
        path.lineTo(w * cutStopPercentStart, h);
        path.lineTo(w * cutStopPercentEnd, h);
        path.lineTo(w, 0);
        break;
      case DRIVE_DIRECTION.right:
        path.lineTo(0, h * cutStopPercentStart);
        path.lineTo(w, 0);
        path.lineTo(w, h);
        path.lineTo(0, h * cutStopPercentEnd);
        break;
      case DRIVE_DIRECTION.down:
        path.lineTo(w * cutStopPercentStart, 0);
        path.lineTo(0, h);
        path.lineTo(w, h);
        path.lineTo(w * cutStopPercentEnd, 0);
        break;
    }

    path.close();
    return path;
  }

  @override
  bool shouldReclip(CustomClipper<Path> oldClipper) => false;
}
