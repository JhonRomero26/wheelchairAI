import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:get/get_state_manager/src/rx_flutter/rx_obx_widget.dart';
import 'package:wheelchair/controllers/ble_controller.dart';
import 'package:wheelchair/ui/widgets/scan_ble_modal.dart';

class BluetoothButton extends StatelessWidget {
  const BluetoothButton({super.key});

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);

    return IconButton(
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
        () => Stack(children: [
          Positioned(
            top: 0,
            right: 0,
            child: Container(
                decoration: BoxDecoration(
                  shape: BoxShape.circle,
                  color: BleController.to.connectionState ==
                          DeviceConnectionState.connected
                      ? Colors.green
                      : Colors.red,
                ),
                width: 8,
                height: 8),
          ),
          Icon(
            Icons.bluetooth,
            color: BleController.to.connectionState ==
                    DeviceConnectionState.connected
                ? Colors.green
                : null,
          ),
        ]),
      ),
    );
  }
}
