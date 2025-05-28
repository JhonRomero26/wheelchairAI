import 'package:flutter/material.dart';
import 'package:wheelchair/ui/widgets/bluetooth_button.dart';

class ActionsControl extends StatelessWidget {
  const ActionsControl({super.key});

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // HomeModeButton(),
          ],
        ),
        const SizedBox(width: 8),
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            IconButton(
              iconSize: 32,
              onPressed: () async {},
              icon: const Icon(
                Icons.volume_up_rounded,
              ),
            ),
            const SizedBox(width: 16),
            BluetoothButton(),
          ],
        ),
      ],
    );
  }
}
