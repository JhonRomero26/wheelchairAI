import 'package:flutter/material.dart';
import 'package:wheelchair/controllers/ble_controller.dart';
import 'package:wheelchair/controllers/wheelchair_controller.dart';
import 'package:wheelchair/utils/commands.dart';

class DirectionsControl extends StatelessWidget {
  const DirectionsControl({super.key});

  @override
  Widget build(BuildContext context) {
    final Size size = MediaQuery.of(context).size;
    final driveContainerSize = size.width * 0.65 + 16;
    final driveButtonSize = driveContainerSize * 0.27;
    final driveButtonCenterSize = driveContainerSize - (driveButtonSize * 2);
    const distance = Offset(4, 4);

    return Container(
      width: driveContainerSize,
      height: driveContainerSize,
      decoration: BoxDecoration(
        color: Colors.white,
        boxShadow: [
          BoxShadow(
            blurRadius: 15,
            offset: distance,
            color: Colors.grey.shade300,
            spreadRadius: 1,
          ),
          BoxShadow(
            blurRadius: 15,
            offset: -distance,
            color: Colors.grey.shade100,
            spreadRadius: 1,
          ),
        ],
        shape: BoxShape.circle,
      ),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.center,
        mainAxisSize: MainAxisSize.max,
        children: [
          IconButton(
            padding: const EdgeInsets.all(0),
            iconSize: driveButtonSize,
            onPressed: () {},
            icon: GestureDetector(
              onTapDown: (_) => WheelchairController.to.moveLeft(),
              onTapUp: (_) => WheelchairController.to.cancelMoveLeft(),
              onTapCancel: WheelchairController.to.cancelMoveLeft,
              child: const Icon(Icons.keyboard_arrow_left),
            ),
          ),
          Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              IconButton(
                padding: const EdgeInsets.all(0),
                iconSize: driveButtonSize,
                onPressed: () {
                  BleController.to.sendData(MovementCommands.forward.value);
                },
                icon: const Icon(Icons.keyboard_arrow_up),
              ),
              ElevatedButton(
                  onPressed: WheelchairController.to.moveStop,
                  style: ElevatedButton.styleFrom(
                    shape: const CircleBorder(),
                    padding: const EdgeInsets.all(0),
                    maximumSize:
                        Size(driveButtonCenterSize, driveButtonCenterSize),
                    minimumSize:
                        Size(driveButtonCenterSize, driveButtonCenterSize),
                    backgroundColor: Colors.deepPurple,
                    foregroundColor: Colors.white,
                  ),
                  child: const Text('Freno')),
              IconButton(
                padding: const EdgeInsets.all(0),
                iconSize: driveButtonSize,
                onPressed: WheelchairController.to.moveBackward,
                icon: const Icon(Icons.keyboard_arrow_down),
              )
            ],
          ),
          IconButton(
            padding: const EdgeInsets.all(0),
            iconSize: driveButtonSize,
            onPressed: () {},
            icon: GestureDetector(
              onTapDown: (_) => WheelchairController.to.moveRight(),
              onTapUp: (_) => WheelchairController.to.cancelMoveRight(),
              onTapCancel: WheelchairController.to.cancelMoveRight,
              child: const Icon(Icons.keyboard_arrow_right),
            ),
          )
        ],
      ),
    );
  }
}
