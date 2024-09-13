import 'package:get/get.dart';
import 'package:wheelchair/controllers/ble_controller.dart';
import 'package:wheelchair/utils/commands.dart';
import 'package:wheelchair/utils/constants.dart';

class WheelchairController extends GetxController {
  // Engine Correction
  static const double _maxEngineCorrection = 100;
  static double get maxEngineCorrection => _maxEngineCorrection;
  static const double _minEngineCorrection = 30;
  static double get minEngineCorrection => _minEngineCorrection;

  // Acceleration
  static const double _maxAcceleration = 5;
  static double get maxAcceleration => _maxAcceleration;
  static const double _minAcceleration = 1;
  static double get minAcceleration => _minAcceleration;

  final _engineCorrection = 85.obs;
  int get engineCorrection => _engineCorrection.value;

  final _acceleration = 2.obs;
  int get acceleration => _acceleration.value;

  // Speed Index
  final _speedModeIndex = 0.obs;
  int get speedModeIndex => _speedModeIndex.value;

  static WheelchairController get to => Get.find();

  void setEngineCorrection(int value) {
    _engineCorrection.value = value;
  }

  void sendEngineCorrection() {
    BleController.to
        .sendData("${CorrectionCommands.engine.value}$engineCorrection");
  }

  void setAcceleration(int value) {
    _acceleration.value = value;
    BleController.to
        .sendData("${CorrectionCommands.acceleration.value}$acceleration");
  }

  void setSpeedModeIndex(int idx) {
    _speedModeIndex.value = idx;
    BleController.to.sendData("${speedMapping[idx]}");
  }

  void cancelMoveLeft() =>
      BleController.to.sendData(MovementCommands.leftOff.value);
  void cancelMoveRight() =>
      BleController.to.sendData(MovementCommands.rightOff.value);

  void moveLeft() => BleController.to.sendData(MovementCommands.left.value);

  void moveRight() => BleController.to.sendData(MovementCommands.right.value);

  void rotateLeft() =>
      BleController.to.sendData(MovementCommands.rotateLeft.value);

  void rotateRight() =>
      BleController.to.sendData(MovementCommands.rotateRigh.value);

  void moveForward() {
    BleController.to.sendData(MovementCommands.forward.value);
  }

  void moveBackward() {
    BleController.to.sendData(MovementCommands.backward.value);
  }

  void moveStop() {
    BleController.to.sendData(MovementCommands.stop.value);
  }
}
