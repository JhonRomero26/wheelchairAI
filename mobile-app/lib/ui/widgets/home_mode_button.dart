import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:wheelchair/controllers/wheelchair_controller.dart';
import 'package:wheelchair/utils/colors.dart';

class HomeModeButton extends StatelessWidget {
  const HomeModeButton({super.key});

  @override
  Widget build(BuildContext context) {
    return Obx(
      () => IconButton(
        iconSize: 32,
        onPressed: WheelchairController.to.toggleHomeMode,
        icon: Icon(
          Icons.home,
          color: WheelchairController.to.homeMode
              ? Colors.green
              : KDarkTheme.typography.body,
        ),
      ),
    );
  }
}
