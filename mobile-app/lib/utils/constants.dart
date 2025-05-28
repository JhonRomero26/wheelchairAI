import 'package:wheelchair/utils/commands.dart';

enum BleServicesUUID {
  wheelchairUUID('0000ffe0-0000-1000-8000-00805f9b34fb');

  const BleServicesUUID(this.value);
  final String value;
}

enum BleCharacteristicsUUID {
  whleechairControl('0000ffe1-0000-1000-8000-00805f9b34fb');

  const BleCharacteristicsUUID(this.value);
  final String value;
}

final Map<int, String> speedMapping = {
  0: SpeedCommands.slow.value,
  1: SpeedCommands.normal.value,
  2: SpeedCommands.fast.value
};
