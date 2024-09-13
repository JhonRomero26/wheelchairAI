import 'package:flutter/material.dart';
import 'package:wheelchair/controllers/ble_controller.dart';
import 'package:wheelchair/ui/widgets/actions_control.dart';
import 'package:wheelchair/ui/widgets/control_heading.dart';
import 'package:wheelchair/ui/widgets/central_control.dart';
import 'package:wheelchair/ui/widgets/directions_control.dart';
import 'package:wheelchair/ui/widgets/speed_selector.dart';

class ControllerScreen extends StatefulWidget {
  static const String id = 'ControlScreen';
  const ControllerScreen({super.key});

  @override
  State<ControllerScreen> createState() => _ControllerScreenState();
}

class _ControllerScreenState extends State<ControllerScreen> {
  @override
  void dispose() {
    BleController.to.scanDeviceStream?.cancel();
    BleController.to.connectionStream?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    const xPadding = 16.0;
    final textTheme = Theme.of(context).textTheme;

    return Scaffold(
      appBar: const PreferredSize(
        preferredSize: Size.fromHeight(80),
        child: SizedBox(
          child: SafeArea(child: ControlHeading()),
        ),
      ),
      body: SafeArea(
        child: SingleChildScrollView(
          child: Padding(
            padding: const EdgeInsets.symmetric(horizontal: xPadding),
            child: Column(
              children: [
                const SizedBox(height: 80),
                // const TablerIndicator(),
                // const SizedBox(height: 16),
                const ActionsControl(),
                const SizedBox(height: 32),
                const DirectionsControl(),
                const CentralControl(),
                const SizedBox(height: 24),
                // const RotationControl(),
                // const SizedBox(height: 32),
                Text(
                  'Velocidad',
                  style: textTheme.titleMedium,
                ),
                const SizedBox(height: 16),
                const SpeedSelector(),
                const SizedBox(height: 32),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
