import 'package:flutter/material.dart';

class SliderWidget extends StatelessWidget {
  final double value, min, max, width;
  final double? height;
  final int divisions;
  final Widget? icon;
  final void Function(double)? onChanged, onChangeEnd, onChangeStart;
  const SliderWidget({
    super.key,
    required this.value,
    required this.min,
    required this.max,
    required this.divisions,
    this.onChanged,
    this.icon,
    this.height = 200,
    this.width = 45,
    this.onChangeEnd,
    this.onChangeStart,
  });

  @override
  Widget build(BuildContext context) {
    final labelColor = Colors.white;

    return SliderTheme(
      data: SliderThemeData(
        trackHeight: width,
        thumbShape: SliderComponentShape.noOverlay,
        overlayShape: SliderComponentShape.noOverlay,
        valueIndicatorShape: SliderComponentShape.noOverlay,
        activeTrackColor: Colors.deepPurple,
        inactiveTrackColor: Colors.deepPurple.shade200.withAlpha(192),
        trackShape: const RoundedRectSliderTrackShape(),
        rangeTrackShape: const RectangularRangeSliderTrackShape(),
      ),
      child: SizedBox(
        height: height,
        child: Stack(
          alignment: Alignment.center,
          children: [
            RotatedBox(
              quarterTurns: 3,
              child: Slider(
                value: value,
                min: min,
                max: max,
                divisions: divisions,
                label: "${value.round()}",
                onChanged: onChanged,
                onChangeStart: onChangeStart,
                onChangeEnd: onChangeEnd,
              ),
            ),
            Positioned.fill(
              child: Align(
                alignment: Alignment.center,
                child: SizedBox(
                  height: 1,
                  child: OverflowBox(
                    minHeight: 0,
                    maxHeight: double.infinity,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      children: [
                        Text(
                          "${value.round()}",
                          overflow: TextOverflow.visible,
                          style: TextStyle(
                            color: labelColor,
                            fontWeight: FontWeight.bold,
                            fontSize: 24,
                          ),
                        ),
                        if (icon != null)
                          IconTheme(
                            data: IconThemeData(
                              color: labelColor,
                            ),
                            child: icon!,
                          )
                      ],
                    ),
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
