import 'package:flutter/material.dart';

class TablerIndicator extends StatelessWidget {
  const TablerIndicator({super.key});

  @override
  Widget build(BuildContext context) {
    return const Row(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        RotatedBox(
          quarterTurns: 1,
          // child: Icon(Icons.battery_0_bar),
          // child: Icon(Icons.battery_1_bar_outlined),
          // child: Icon(Icons.battery_2_bar_outlined),
          // child: Icon(Icons.battery_3_bar_outlined),
          // child: Icon(Icons.battery_4_bar_outlined),
          // child: Icon(Icons.battery_5_bar_outlined),
          // child: Icon(Icons.battery_6_bar_outlined),
          // child: Icon(Icons.battery_full),
          child: IconTheme(
            data: IconThemeData(color: Colors.green, size: 32),
            child: Icon(Icons.battery_charging_full),
          ),
        ),
        SizedBox(width: 4),
        Text('100%'),
        SizedBox(width: 8),
        Text('ꞏ'), // center dot char here
        SizedBox(width: 8),
        Text('10 km/h'),
      ],
    );
  }
}
