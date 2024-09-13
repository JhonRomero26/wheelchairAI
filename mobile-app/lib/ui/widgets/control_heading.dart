import 'package:flutter/material.dart';

class ControlHeading extends StatelessWidget {
  const ControlHeading({super.key});

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 8.0),
      child: Row(
        mainAxisSize: MainAxisSize.max,
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: [
          IconButton(
            iconSize: 32,
            style: IconButton.styleFrom(),
            onPressed: () => {},
            icon: const Icon(Icons.power_settings_new),
          ),
          Image.asset(
            'assets/images/logo-horizontal.png',
            width: 120,
            fit: BoxFit.contain,
          ),
          const SizedBox(
            width: 32,
          )
        ],
      ),
    );
  }
}
