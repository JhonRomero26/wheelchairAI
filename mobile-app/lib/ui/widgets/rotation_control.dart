import 'package:wheelchair/controllers/wheelchair_controller.dart';
import 'package:flutter/material.dart';

class RotationControl extends StatelessWidget {
  const RotationControl({super.key});

  @override
  Widget build(BuildContext context) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        IconButton(
          iconSize: 42,
          onPressed: () {},
          icon: GestureDetector(
            onTapUp: (_) => WheelchairController.to.cancelMoveLeft(),
            onTapCancel: WheelchairController.to.cancelMoveLeft,
            onTapDown: (_) => WheelchairController.to.rotateLeft(),
            child: const Icon(
              Icons.rotate_left_rounded,
            ),
          ),
        ),
        const SizedBox(width: 24),
        IconButton(
          iconSize: 42,
          onPressed: () {},
          icon: GestureDetector(
            onTapUp: (_) => WheelchairController.to.cancelMoveRight(),
            onTapCancel: WheelchairController.to.cancelMoveRight,
            onTapDown: (_) => WheelchairController.to.rotateRight(),
            child: const Icon(
              Icons.rotate_right_rounded,
            ),
          ),
        ),
      ],
    );
  }
}
