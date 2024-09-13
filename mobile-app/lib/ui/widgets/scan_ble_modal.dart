import "dart:async";
import "dart:developer";

import "package:flutter_reactive_ble/flutter_reactive_ble.dart";
import "package:flutter/material.dart";
import "package:get/get.dart";
import "package:wheelchair/controllers/ble_controller.dart";
import "package:wheelchair/ui/widgets/ble_device_tile.dart";

class ScanBleModal extends StatefulWidget {
  final bool startScanning;

  const ScanBleModal({super.key, this.startScanning = true});

  @override
  State<ScanBleModal> createState() => _ScanBleModalState();
}

class _ScanBleModalState extends State<ScanBleModal> {
  @override
  void initState() {
    super.initState();

    if (widget.startScanning) handleStartScan();
  }

  Future handleStartScan() async {
    BleController.to.startScan();
  }

  Future handleStopScan() async {
    try {
      BleController.to.stopScan();
    } catch (e) {
      log("Stop bluetooth scan fails with error: $e");
    }
  }

  void onConnectPressed(DiscoveredDevice device) async {
    handleStopScan();

    showDialog(
      barrierDismissible: false,
      context: context,
      builder: (_) => AlertDialog(
        title: Text("Conectandose a ${device.name}"),
        content: const SizedBox(
          child: SizedBox(
            width: double.infinity,
            child: LinearProgressIndicator(),
          ),
        ),
      ),
    );

    await BleController.to.connect(deviceId: device.id);
    await Future.delayed(const Duration(seconds: 2));

    if (BleController.to.connectionState == DeviceConnectionState.connected) {
      Get.back();
    }
  }

  Widget _buildScanResultTiles(BuildContext context) {
    if (BleController.to.devicesDiscovered.isEmpty) {
      return const SizedBox(
        child: Column(
          children: [
            SizedBox(height: 64),
            Text("No se encontraron dispositivos")
          ],
        ),
      );
    }

    return Column(
      children: BleController.to.devicesDiscovered.map((device) {
        return BleDeviceTile(
          device: device,
          rssi: device.rssi,
          onTap: () => onConnectPressed(device),
        );
      }).toList(),
    );
  }

  @override
  Widget build(BuildContext context) {
    return DraggableScrollableSheet(
      expand: false,
      initialChildSize: 0.5,
      maxChildSize: 0.9,
      builder: (context, controller) => SingleChildScrollView(
        controller: controller,
        child: Obx(
          () => Container(
            width: double.infinity,
            padding: const EdgeInsets.all(16),
            child: Column(
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    const Text("Escaneando dispositivos"),
                    Row(
                      children: [
                        if (!BleController.to.scanningDevices)
                          IconButton(
                            onPressed: handleStartScan,
                            icon: const Icon(Icons.replay),
                          ),
                        IconButton(
                          onPressed: () {
                            handleStopScan();
                            Navigator.of(context).pop();
                          },
                          color: Colors.red,
                          icon: const Icon(Icons.close_outlined),
                        ),
                      ],
                    ),
                  ],
                ),
                const Divider(),
                BleController.to.scanningDevices
                    ? const Column(children: [
                        SizedBox(height: 64),
                        Text("Buscando dispositivos..."),
                        SizedBox(height: 24),
                        LinearProgressIndicator(),
                      ])
                    : _buildScanResultTiles(context),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
