import 'package:wheelchair/controllers/wheelchair_controller.dart';
import 'package:flutter/material.dart';
import 'package:get/get.dart';

class SpeedOption extends StatelessWidget {
  final Icon icon;
  final Text title;
  final GestureTapCallback onPress;
  final int index;

  SpeedOption({
    super.key,
    required this.icon,
    required this.title,
    required this.onPress,
    required this.index,
  });

  @override
  Widget build(BuildContext context) {
    final TextTheme textTheme = Theme.of(context).textTheme;

    return Expanded(
      child: InkWell(
        onTap: onPress,
        splashColor: Colors.transparent,
        child: Obx(() {
          final isSelected = index == WheelchairController.to.speedModeIndex;
          return Container(
            padding: const EdgeInsets.all(12),
            color: isSelected ? Colors.deepPurple : null,
            child: Column(
              children: [
                IconTheme(
                  data: IconThemeData(
                    color: isSelected ? Colors.white : Colors.deepPurple,
                  ),
                  child: icon,
                ),
                // Widget for change style text widget child
                DefaultTextStyle(
                    style: textTheme.bodyMedium!.copyWith(
                      color: isSelected ? Colors.white : Colors.deepPurple,
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
