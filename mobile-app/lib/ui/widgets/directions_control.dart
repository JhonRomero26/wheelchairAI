import 'package:flutter/material.dart';
import 'package:wheelchair/controllers/wheelchair_controller.dart';
import 'package:wheelchair/ui/widgets/direction_button.dart';
import 'package:wheelchair/ui/widgets/gesture_button.dart';
import 'package:wheelchair/utils/colors.dart';

class DirectionsControl extends StatelessWidget {
  const DirectionsControl({super.key});

  @override
  Widget build(BuildContext context) {
    final Size size = MediaQuery.of(context).size;
    final driveContainerSize = size.width * 0.62;
    final driveButtonSize = driveContainerSize * 0.4;

    return ClipOval(
      child: Container(
        width: driveContainerSize,
        height: driveContainerSize,
        decoration: BoxDecoration(
          color: KDarkTheme.ui01,
          shape: BoxShape.circle,
        ),
        child: Stack(
          children: [
            Positioned(
              left: 0,
              top: 0,
              child: DirectionButton(
                direction: DRIVE_DIRECTION.left,
                height: driveContainerSize,
                width: driveButtonSize,
                onTapDown: (_) => WheelchairController.to.moveLeft(),
                onTapUp: (_) => WheelchairController.to.cancelMoveLeft(),
                onTapCancel: WheelchairController.to.cancelMoveLeft,
                icon: Icon(Icons.keyboard_arrow_left),
                iconSize: 48,
              ),
            ),
            Positioned(
              top: 0,
              left: 0,
              child: DirectionButton(
                direction: DRIVE_DIRECTION.up,
                height: driveButtonSize,
                width: driveContainerSize,
                onPressed: WheelchairController.to.moveForward,
                icon: Icon(Icons.keyboard_arrow_up),
                iconSize: 48,
              ),
            ),
            Positioned(
              right: 0,
              top: 0,
              child: DirectionButton(
                direction: DRIVE_DIRECTION.right,
                height: driveContainerSize,
                width: driveButtonSize,
                onTapDown: (_) => WheelchairController.to.moveRight(),
                onTapUp: (_) => WheelchairController.to.cancelMoveRight(),
                onTapCancel: WheelchairController.to.cancelMoveRight,
                icon: Icon(Icons.keyboard_arrow_right),
                iconSize: 48,
              ),
            ),
            Positioned(
              bottom: 0,
              left: 0,
              child: DirectionButton(
                direction: DRIVE_DIRECTION.down,
                height: driveButtonSize,
                width: driveContainerSize,
                onPressed: WheelchairController.to.moveBackward,
                icon: Icon(Icons.keyboard_arrow_down),
                iconSize: 48,
              ),
            ),
            Positioned(
              top: 0,
              right: 0,
              child: ClipPath(
                clipper: ClipPathX(),
                child: Container(
                  color: KDarkTheme.background,
                  width: driveContainerSize,
                  height: driveContainerSize,
                ),
              ),
            ),
            Positioned(
              top: driveContainerSize * 0.3,
              left: driveContainerSize * 0.3,
              child: GestureButton(
                borderRadius: BorderRadius.circular(1000),
                splashColor: KColors.primary.withAlpha(45),
                highlightColor: KColors.primary.withAlpha(45),
                foregroundColor: KDarkTheme.typography.accent,
                color: KDarkTheme.background,
                onTap: WheelchairController.to.moveStop,
                child: SizedBox(
                  width: driveButtonSize,
                  height: driveButtonSize,
                  child: Icon(
                    Icons.stop_circle_outlined,
                    size: 48,
                    color: KDarkTheme.typography.accent,
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}

class ClipPathX extends CustomClipper<Path> {
  @override
  Path getClip(Size size) {
    double h = size.height;
    double w = size.width;

    double weight = 2;
    double middle = 0.5;
    double middleStoke = middle;

    final path = Path();
    path.lineTo(0, 0);
    path.lineTo(w * middle, h * middleStoke - weight);
    path.lineTo(w, 0);

    path.lineTo(w, weight);
    path.lineTo(w * middleStoke + weight, h * middle);

    path.lineTo(w, h - weight);
    path.lineTo(w, h);
    path.lineTo(w * middle, h * middleStoke + weight);

    path.lineTo(0, h);
    path.lineTo(0, h - weight);
    path.lineTo(w * middleStoke - weight, h * middle);

    path.lineTo(0, weight);
    path.close();

    return path;
  }

  @override
  bool shouldReclip(CustomClipper<Path> oldClipper) {
    return false;
  }
}

// Stack(
//           children: [
//             Flex(
//               direction: Axis.horizontal,
//               crossAxisAlignment: CrossAxisAlignment.stretch,
//               mainAxisAlignment: MainAxisAlignment.center,
//               // mainAxisAlignment: MainAxisAlignment.center,
//               // mainAxisSize: MainAxisSize.max,
//               children: [
//                 ClipPath(),
//                 IconButton(
//                   padding: const EdgeInsets.all(0),
//                   iconSize: driveButtonSize,
//                   onPressed: () {},
//                   icon: GestureDetector(
//                     onTapDown: (_) => WheelchairController.to.moveLeft(),
//                     onTapUp: (_) => WheelchairController.to.cancelMoveLeft(),
//                     onTapCancel: WheelchairController.to.cancelMoveLeft,
//                     child: const Icon(Icons.keyboard_arrow_left),
//                   ),
//                 ),
//                 Column(
//                   // mainAxisAlignment: MainAxisAlignment.center,
//                   // crossAxisAlignment: CrossAxisAlignment.center,
//                   mainAxisSize: MainAxisSize.max,
//                   mainAxisAlignment: MainAxisAlignment.center,
//                   crossAxisAlignment: CrossAxisAlignment.stretch,
//                   direction: Axis.vertical,
//                   children: [
//                     ClipPath(
//                       clipper: ClipPathRemote(),
//                       child: Container(
//                         width: driveButtonSize,
//                         height: driveButtonSize - driveButtonSize * 0.025,
//                         color: Colors.green,
//                       ),
//                       // child: IconButton(
//                       //   padding: const EdgeInsets.all(0),
//                       //   iconSize: driveButtonSize,
//                       //   onPressed: () {
//                       //     BleController.to
//                       //         .sendData(MovementCommands.forward.value);
//                       //   },
//                       //   icon: const Icon(Icons.keyboard_arrow_up),
//                       // ),
//                     ),
//                     IconButton(
//                       onPressed: WheelchairController.to.moveStop,
//                       iconSize: 48,
//                       style: ElevatedButton.styleFrom(
//                         shape: const CircleBorder(),
//                         padding: const EdgeInsets.all(0),
//                         maximumSize:
//                             Size(driveButtonCenterSize, driveButtonCenterSize),
//                         minimumSize:
//                             Size(driveButtonCenterSize, driveButtonCenterSize),
//                         foregroundColor: KDarkTheme.typography.accent,
//                         backgroundColor: KDarkTheme.background,
//                       ),
//                       icon: const Icon(Icons.stop_circle_outlined),
//                     ),
//                     IconButton(
//                       padding: const EdgeInsets.all(0),
//                       iconSize: driveButtonSize,
//                       onPressed: WheelchairController.to.moveBackward,
//                       icon: const Icon(Icons.keyboard_arrow_down),
//                     )
//                   ],
//                 ),
//                 IconButton(
//                   padding: const EdgeInsets.all(0),
//                   iconSize: driveButtonSize,
//                   onPressed: () {},
//                   icon: GestureDetector(
//                     onTapDown: (_) => WheelchairController.to.moveRight(),
//                     onTapUp: (_) => WheelchairController.to.cancelMoveRight(),
//                     onTapCancel: WheelchairController.to.cancelMoveRight,
//                     child: const Icon(Icons.keyboard_arrow_right),
//                   ),
//                 )
//               ],
//             ),
//           ],
//         ),