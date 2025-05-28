import 'dart:io';
import 'package:permission_handler/permission_handler.dart';
import 'package:device_info_plus/device_info_plus.dart';

class PermissionsWheelchair {
  static bool _bluetoothGranted = false;
  static bool _locationGranted = false;

  static bool get bluetoothGranted => _bluetoothGranted;
  static bool get locationGranted => _locationGranted;

  PermissionsWheelchair();

  static Future<bool> grantedAllPermissions() async {
    if (Platform.isAndroid) {
      final deviceInfo = await DeviceInfoPlugin().androidInfo;

      if (deviceInfo.version.sdkInt >= 32) {
        _bluetoothGranted = await Permission.bluetoothConnect.isGranted;
      } else {
        _bluetoothGranted = await Permission.bluetooth.isGranted;
      }

      _locationGranted = await Permission.location.isGranted;

      return _bluetoothGranted && _locationGranted;
    }

    return true;
  }

  static Future<void> bluetoothPermission() async {
    if (Platform.isAndroid) {
      final deviceInfo = await DeviceInfoPlugin().androidInfo;

      if (deviceInfo.version.sdkInt >= 32) {
        if (await Permission.bluetoothConnect.isDenied) {
          await Permission.bluetoothConnect.request();
        }

        if (await Permission.bluetoothScan.isDenied) {
          await Permission.bluetoothScan.request();
        }

        _bluetoothGranted = await Permission.bluetoothConnect.isGranted &&
            await Permission.bluetoothScan.isGranted;
        return;
      }

      if (await Permission.bluetooth.isDenied) {
        await Permission.bluetooth.request();
        _bluetoothGranted = await Permission.bluetooth.isGranted;
        return;
      }

      _bluetoothGranted = await Permission.bluetoothConnect.isGranted &&
          await Permission.bluetoothScan.isGranted;
      return;
    }

    _bluetoothGranted = true;
    return;
  }

  static Future<void> locationPermission() async {
    if (Platform.isAndroid) {
      if (await Permission.location.serviceStatus.isEnabled) {
        if (await Permission.location.isDenied) {
          await Permission.location.request();
        }
      } else {
        openAppSettings();
      }

      if (await Permission.location.isPermanentlyDenied) {
        openAppSettings();
      }
      _locationGranted = await Permission.location.isGranted;
      return;
    }

    _locationGranted = true;
  }
}
