import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:get/get.dart';
import 'package:wheelchair/controllers/ble_controller.dart';
import 'package:wheelchair/ui/widgets/scan_ble_modal.dart';

class ActionsControl extends StatelessWidget {
  const ActionsControl({super.key});

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);

    return Row(
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
        IconButton(
          iconSize: 32,
          onPressed: () async {
            if (BleController.to.status == BleStatus.poweredOff) {
              showDialog(
                context: context,
                builder: (_) => AlertDialog(
                  title: Text(
                    "Bluetooth desconectado",
                    style: theme.textTheme.titleLarge!
                        .copyWith(fontWeight: FontWeight.w300),
                  ),
                  content: Column(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      Image.asset(
                        'assets/illustrations/welcome.png',
                        width: 200,
                      ),
                      const Text(
                        "Encienda su bluetooth para connectarse.",
                        textAlign: TextAlign.center,
                      ),
                    ],
                  ),
                ),
              );
            } else {
              showModalBottomSheet(
                context: context,
                builder: (_) => const ScanBleModal(),
              );
            }
          },
          icon: Obx(
            () => Icon(
              Icons.bluetooth,
              color: BleController.to.connectionState ==
                      DeviceConnectionState.connected
                  ? Colors.green
                  : null,
            ),
          ),
        ),
      ],
    );
  }
}
