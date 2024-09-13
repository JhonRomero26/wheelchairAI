import 'dart:async';
import 'dart:convert';
import 'dart:developer';
import 'dart:typed_data';

import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';
import 'package:get/get.dart';
import 'package:wheelchair/controllers/permissions_wheelchair.dart';
import 'package:wheelchair/utils/constants.dart';

class BleController extends GetxController {
  final FlutterReactiveBle _ble = FlutterReactiveBle();

  static BleController get to => Get.find();

  final _scanningDevices = false.obs;
  bool get scanningDevices => _scanningDevices.value;

  final _deviceId = "".obs;
  String get deviceId => _deviceId.value;

  final Rx<DeviceConnectionState> _connectionState =
      DeviceConnectionState.disconnected.obs;
  DeviceConnectionState get connectionState => _connectionState.value;

  BleStatus get status => _ble.status;

  final _isConnected = false.obs;
  bool get isConnected => _isConnected.value;

  final List<DiscoveredDevice> _devicesDiscovered = [];
  List<DiscoveredDevice> get devicesDiscovered => _devicesDiscovered;

  QualifiedCharacteristic? _characteristic;

  StreamSubscription<DiscoveredDevice>? _scanningDeviceStream;
  StreamSubscription<DiscoveredDevice>? get scanDeviceStream =>
      _scanningDeviceStream;

  StreamSubscription<ConnectionStateUpdate>? _connection;
  StreamSubscription<ConnectionStateUpdate>? get connectionStream =>
      _connection;

  Future<void> startScan({
    List<Uuid> serviceIds = const [],
    Duration duration = const Duration(seconds: 5),
  }) async {
    if (!_scanningDevices.value) {
      _scanningDevices.value = true;
      _devicesDiscovered.clear();
      _scanningDeviceStream?.cancel();

      await PermissionsWheelchair.bluetoothPermission();
      await PermissionsWheelchair.locationPermission();

      _scanningDeviceStream =
          _ble.scanForDevices(withServices: serviceIds).listen(
        (DiscoveredDevice device) {
          final name = device.name.toLowerCase();

          if (name.isNotEmpty &&
              _devicesDiscovered.where((el) => el.id == device.id).isEmpty) {
            _devicesDiscovered.add(device);
          }
        },
        onError: (e) => log("Device scan fails with error: $e"),
      );

      await Future.delayed(duration, stopScan);
      _scanningDevices.value = false;
    }
  }

  Future<void> stopScan() async {
    if (_scanningDeviceStream != null) {
      await _scanningDeviceStream!.cancel();
      _scanningDevices.value = false;
      _scanningDeviceStream = null;
    }
  }

  Future<void> connect({
    required String deviceId,
    Duration connectionTimeout = const Duration(seconds: 10),
  }) async {
    disconnect();
    _connection = _ble
        .connectToDevice(id: deviceId, connectionTimeout: connectionTimeout)
        .listen((state) async {
      if (connectionState != state.connectionState) {
        _connectionState.value = state.connectionState;
        if (state.connectionState == DeviceConnectionState.connected) {
          _isConnected.value = true;
        } else if (state.connectionState ==
            DeviceConnectionState.disconnected) {
          _isConnected.value = false;
        }
      }

      if (state.connectionState == DeviceConnectionState.connected) {
        _deviceId.value = deviceId;
        final services = await _discoverServices(deviceId: deviceId);

        for (Service service in services) {
          for (Characteristic characteristic in service.characteristics) {
            if (BleCharacteristicsUUID.whleechairControl.value ==
                characteristic.id.toString()) {
              _characteristic = QualifiedCharacteristic(
                characteristicId: characteristic.id,
                serviceId: service.id,
                deviceId: deviceId,
              );
              _connectionState.value = DeviceConnectionState.connected;
              _isConnected.value = true;
            }
          }
        }
      }
    });
  }

  Future<void> disconnect() async {
    try {
      if (connectionState == DeviceConnectionState.connected &&
          _connection != null &&
          deviceId == "") {
        _isConnected.value = false;
        await _connection?.cancel();
        _connection = null;
        _deviceId.value = "";
        _characteristic = null;
      }
    } on Exception catch (e) {
      log(e.toString());
    } finally {
      _connectionState.value = DeviceConnectionState.disconnected;
    }
  }

  Future<List<Service>> _discoverServices({required String deviceId}) async {
    await _ble.discoverAllServices(deviceId);
    return _ble.getDiscoveredServices(deviceId);
  }

  Future<void> sendData(String data) async {
    if (data.isEmpty) return;
    if (connectionState != DeviceConnectionState.connected) return;

    final dataCoded = utf8.encode("$data\r\n");
    try {
      await _ble.writeCharacteristicWithResponse(_characteristic!,
          value: Uint8List.fromList(dataCoded));
    } on Exception catch (_) {
      rethrow;
    }
  }
}
