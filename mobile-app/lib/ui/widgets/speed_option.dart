import 'package:wheelchair/controllers/wheelchair_controller.dart';
import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:wheelchair/ui/widgets/gesture_button.dart';
import 'package:wheelchair/utils/colors.dart';

class SpeedOption extends StatelessWidget {
  final Icon icon;
  final Text title;
  final GestureTapCallback? onTap;
  final GestureTapCallback? onDoubleTap;
  final int index;

  const SpeedOption({
    super.key,
    required this.icon,
    required this.title,
    required this.index,
    this.onTap,
    this.onDoubleTap,
  });

  @override
  Widget build(BuildContext context) {
    final TextTheme textTheme = Theme.of(context).textTheme;

    return Expanded(
      child: GestureButton(
        onTap: onTap,
        onDoubleTap: onDoubleTap,
        splashColor: Colors.transparent,
        child: Obx(() {
          final isSelected = index == WheelchairController.to.speedModeIndex;
          return Container(
            padding: const EdgeInsets.all(12),
            color: isSelected ? KDarkTheme.primary.withAlpha(25) : null,
            child: Column(
              children: [
                IconTheme(
                  data: IconThemeData(
                    color: isSelected
                        ? KDarkTheme.primary
                        : KDarkTheme.typography.body,
                  ),
                  child: icon,
                ),
                // Widget for change style text widget child
                DefaultTextStyle(
                    style: textTheme.bodyMedium!.copyWith(
                      fontSize: 12,
                      color: isSelected
                          ? KDarkTheme.primary
                          : KDarkTheme.typography.body,
                    ),
                    child: title)
              ],
            ),
          );
        }),
      ),
    );
  }
}
