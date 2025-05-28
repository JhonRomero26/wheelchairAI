import 'package:flutter/material.dart';
import 'package:wheelchair/ui/widgets/rotation_control.dart';

class CentralControl extends StatelessWidget {
  const CentralControl({super.key});

  @override
  Widget build(BuildContext context) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      children: [
        const SizedBox(width: 16),
        const RotationControl(),
        const SizedBox(width: 16),
      ],
    );
  }
}
