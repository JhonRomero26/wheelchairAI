import 'package:wheelchair/controllers/wheelchair_controller.dart';
import 'package:wheelchair/ui/widgets/speed_option.dart';
import 'package:flutter/material.dart';

class SpeedSelector extends StatelessWidget {
  const SpeedSelector({
    super.key,
  });

  @override
  Widget build(BuildContext context) {
    return Container(
      clipBehavior: Clip.hardEdge,
      decoration: const BoxDecoration(
        borderRadius: BorderRadius.all(Radius.circular(16)),
      ),
      child: Row(
        children: [
          SpeedOption(
            onTap: () => WheelchairController.to.setSpeedModeIndex(0),
            index: 0,
            icon: const Icon(Icons.eco),
            title: Text('Eco'),
          ),
          SpeedOption(
            onTap: () => WheelchairController.to.setSpeedModeIndex(1),
            index: 1,
            icon: const Icon(Icons.speed),
            title: Text('Moderado'),
          ),
          SpeedOption(
            onDoubleTap: () => WheelchairController.to.setSpeedModeIndex(2),
            index: 2,
            icon: const Icon(Icons.bolt),
            title: Text('Deportivo'),
          ),
        ],
      ),
    );
  }
}
