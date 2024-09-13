import 'package:flutter/material.dart';

class WelcomeLayout extends StatelessWidget {
  final String image, title, description;
  final List<Widget>? actions;
  final Color? background;

  const WelcomeLayout({
    super.key,
    required this.image,
    required this.title,
    required this.description,
    this.actions,
    this.background,
  });

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);

    return Scaffold(
      backgroundColor: background,
      body: SizedBox(
        width: double.infinity,
        child: SafeArea(
          child: Column(
            mainAxisSize: MainAxisSize.max,
            crossAxisAlignment: CrossAxisAlignment.center,
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Image.asset(
                'assets/images/logo-horizontal.png',
                width: 80,
                fit: BoxFit.contain,
              ),
              Image.asset(
                image,
                width: 320,
                height: 250,
                fit: BoxFit.cover,
              ),
              const SizedBox(height: 32),
              Container(
                constraints: const BoxConstraints(maxWidth: 320),
                child: Column(
                  children: [
                    Text(
                      title,
                      style: theme.textTheme.titleLarge!
                          .copyWith(fontWeight: FontWeight.w500),
                      textAlign: TextAlign.center,
                    ),
                    const SizedBox(height: 8),
                    Text(
                      description,
                      textAlign: TextAlign.center,
                      style: theme.textTheme.bodyMedium!.copyWith(
                        color: Colors.grey.shade700,
                      ),
                    ),
                  ],
                ),
              ),
              const SizedBox(height: 24),
              if (actions != null)
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: actions!,
                ),
            ],
          ),
        ),
      ),
    );
  }
}
