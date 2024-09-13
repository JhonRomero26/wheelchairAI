import 'package:flutter/material.dart';
import 'package:get/get_state_manager/src/rx_flutter/rx_obx_widget.dart';
import 'package:wheelchair/controllers/wheelchair_controller.dart';
import 'package:wheelchair/ui/widgets/rotation_control.dart';
import 'package:wheelchair/ui/widgets/slider_widget.dart';

class CentralControl extends StatelessWidget {
  const CentralControl({super.key});

  @override
  Widget build(BuildContext context) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      children: [
        Obx(
          () => SliderWidget(
            value: WheelchairController.to.acceleration.toDouble(),
            min: WheelchairController.minAcceleration,
            max: WheelchairController.maxAcceleration,
            height: 150,
            divisions: 4,
            icon: const Icon(Icons.speed),
            onChanged: (value) {
              WheelchairController.to.setAcceleration(value.round());
            },
          ),
        ),
        const SizedBox(width: 16),
        const RotationControl(),
        const SizedBox(width: 16),
        Obx(
          () => SliderWidget(
            value: WheelchairController.to.engineCorrection.toDouble(),
            height: 150,
            min: WheelchairController.minEngineCorrection,
            max: WheelchairController.maxEngineCorrection,
            icon: const Icon(
              Icons.swap_horiz,
            ),
            divisions: (WheelchairController.maxEngineCorrection -
                    WheelchairController.minEngineCorrection)
                .toInt(),
            onChangeEnd: (_) {
              WheelchairController.to.sendEngineCorrection();
            },
            onChanged: (value) {
              WheelchairController.to.setEngineCorrection(value.round());
            },
          ),
        ),
      ],
    );
  }
}
