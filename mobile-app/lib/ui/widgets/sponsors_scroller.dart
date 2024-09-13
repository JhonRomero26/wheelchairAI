import 'package:flutter/material.dart';

class SponsorsScroller extends StatelessWidget {
  SponsorsScroller({super.key});

  final List<String> _images = [
    'assets/images/logo-horizontal.png',
    'assets/images/logo-i2tec.png',
    'assets/images/logo-unl.png',
  ];

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      scrollDirection: Axis.horizontal,
      child: Row(
        children: List.generate(
          _images.length,
          (index) {
            Widget image = Image.asset(
              _images[index],
              width: 130,
            );

            return index == 0
                ? image
                : Padding(
                    padding: const EdgeInsets.only(left: 24),
                    child: image,
                  );
          },
        ),
      ),
    );
  }
}
