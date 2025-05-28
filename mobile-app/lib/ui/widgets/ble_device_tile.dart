import 'package:flutter/material.dart';
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';

class BleDeviceTile extends StatelessWidget {
  final DiscoveredDevice device;
  final int? rssi;
  final GestureTapCallback? onTap;
  final bool isConnected;

  const BleDeviceTile({
    super.key,
    required this.device,
    this.rssi,
    this.onTap,
    this.isConnected = false,
  });

  static Color? _computeTextColor(int rssi) {
    /**/ if (rssi >= -35) {
      return Colors.greenAccent[700];
    }
    if (rssi >= -45) {
      return Color.lerp(
          Colors.greenAccent[700], Colors.lightGreen, -(rssi + 35) / 10);
    }
    if (rssi >= -55) {
      return Color.lerp(Colors.lightGreen, Colors.lime[600], -(rssi + 45) / 10);
    }
    if (rssi >= -65) {
      return Color.lerp(Colors.lime[600], Colors.amber, -(rssi + 55) / 10);
    }
    if (rssi >= -75) {
      return Color.lerp(
          Colors.amber, Colors.deepOrangeAccent, -(rssi + 65) / 10);
    }
    if (rssi >= -85) {
      return Color.lerp(
          Colors.deepOrangeAccent, Colors.redAccent, -(rssi + 75) / 10);
    }

    return Colors.redAccent;
  }

  @override
  Widget build(BuildContext context) {
    final ThemeData theme = Theme.of(context);

    return InkWell(
      splashColor: Colors.black12,
      onTap: onTap,
      child: Container(
        padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
        child: Row(
          mainAxisSize: MainAxisSize.max,
          children: [
            const Icon(Icons.devices),
            const SizedBox(width: 16),
            Expanded(
              child: Column(
                mainAxisSize: MainAxisSize.min,
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(device.name),
                  Text(
                    device.id.toString(),
                    style: theme.textTheme.bodySmall!
                        .copyWith(color: Colors.grey.shade600),
                  ),
                ],
              ),
            ),
            Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                rssi != null
                    ? Row(
                        children: [
                          DefaultTextStyle(
                            style: theme.textTheme.bodySmall!
                                .copyWith(color: _computeTextColor(rssi!)),
                            child: Text("${rssi.toString()} dBm"),
                          ),
                        ],
                      )
                    : const SizedBox(),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
