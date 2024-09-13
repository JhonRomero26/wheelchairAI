import 'package:flutter/material.dart';
import 'package:wheelchair/controllers/permissions_wheelchair.dart';
import 'package:wheelchair/ui/screens/controller_screen.dart';
import 'package:wheelchair/ui/widgets/welcome_layout.dart';

class WelcomeScreen extends StatefulWidget {
  static const String id = "WelcomeScreen";
  const WelcomeScreen({super.key});

  @override
  State<WelcomeScreen> createState() => _WelcomeScreenState();
}

class _WelcomeScreenState extends State<WelcomeScreen> {
  final _pageController = PageController();
  final Map<String, int> _pageIndexPermission = {
    'bluetooth': 1,
    'location': 2,
    'microphone': 3,
  };
  final _switchPageDuration = const Duration(milliseconds: 300);
  final _switchPageCurve = Curves.fastOutSlowIn;

  @override
  void initState() {
    super.initState();
    WidgetsBinding.instance.addPostFrameCallback((_) async {
      final granted = await PermissionsWheelchair.grantedAllPermissions();
      if (granted) {
        Navigator.pushReplacementNamed(context, ControllerScreen.id);
      }
    });
  }

  @override
  void dispose() {
    _pageController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    Widget welcomeHanalab() {
      return WelcomeLayout(
        background: Colors.indigo.shade50,
        title: "Bienvenido a Hanalab",
        image: "assets/illustrations/welcome.png",
        description:
            "Este aplicación esta pensado para que puedas controlar tu silla de ruedas por comandos de voz.",
        actions: [
          ElevatedButton(
            onPressed: () {
              _pageController.nextPage(
                  duration: _switchPageDuration, curve: _switchPageCurve);
            },
            style: ElevatedButton.styleFrom(
              backgroundColor: const Color(0xFF7D4DFF),
              foregroundColor: Colors.white,
            ),
            child: const Text('Comenzar'),
          )
        ],
      );
    }

    Widget bluetoothPermissions() {
      return WelcomeLayout(
        background: Colors.amber.shade100,
        title: "Permisos de Bluetooth",
        image: "assets/illustrations/service.png",
        description:
            "Esta aplicación requiere permisos de bluetooth para enviar y recibir imformación de su silla de ruedas.",
        actions: [
          ElevatedButton(
            onPressed: () async {
              await PermissionsWheelchair.bluetoothPermission();

              if (PermissionsWheelchair.bluetoothGranted) {
                _pageController.nextPage(
                  duration: _switchPageDuration,
                  curve: _switchPageCurve,
                );
              }
            },
            style: ElevatedButton.styleFrom(
              backgroundColor: const Color(0xFF7D4DFF),
              foregroundColor: Colors.white,
            ),
            child: const Text('Acceder al bluetooth'),
          ),
        ],
      );
    }

    Widget locationPermissions() {
      return WelcomeLayout(
        background: Colors.teal.shade100,
        title: "Permisos de Ubicación",
        image: "assets/illustrations/globe.png",
        description:
            "Esta aplicación requiere permisos de ubicación para encontrar tu silla de ruedas bluetooth más cercana.",
        actions: [
          ElevatedButton(
            onPressed: () async {
              await PermissionsWheelchair.locationPermission();

              if (PermissionsWheelchair.locationGranted) {
                _pageController.nextPage(
                  duration: _switchPageDuration,
                  curve: _switchPageCurve,
                );
              }
            },
            style: ElevatedButton.styleFrom(
              backgroundColor: const Color(0xFF7D4DFF),
              foregroundColor: Colors.white,
            ),
            child: const Text('Acceder a la ubicación'),
          ),
        ],
      );
    }

    Widget getStartedPage() {
      return WelcomeLayout(
        background: Colors.blue.shade100,
        image: 'assets/illustrations/travels.png',
        title: 'Comencemos',
        description:
            'Estamos listos para comenzar con nuestro recorrido en silla de ruedas.',
        actions: [
          ElevatedButton(
            onPressed: () {
              if (!PermissionsWheelchair.bluetoothGranted) {
                _pageController.animateToPage(
                  _pageIndexPermission['bluetooth']!,
                  duration: _switchPageDuration,
                  curve: _switchPageCurve,
                );
                showDialog(
                  context: context,
                  builder: (_) => const AlertDialog(
                    title: Text('Permisos de bluetooth'),
                    content: Text('Esta aplicación requiere bluetooth.'),
                  ),
                );
                return;
              }

              if (!PermissionsWheelchair.locationGranted) {
                _pageController.animateToPage(
                  _pageIndexPermission['location']!,
                  duration: _switchPageDuration,
                  curve: _switchPageCurve,
                );
                showDialog(
                  context: context,
                  builder: (_) => const AlertDialog(
                    title: Text('Permisos de ubicación'),
                    content: Text('Esta aplicación requiere la ubicación.'),
                  ),
                );
                return;
              }

              _pageController.dispose();
              Navigator.of(context).pushReplacementNamed(ControllerScreen.id);
            },
            style: ElevatedButton.styleFrom(
              backgroundColor: const Color(0xFF7D4DFF),
              foregroundColor: Colors.white,
            ),
            child: const Text('Comenzar'),
          )
        ],
      );
    }

    return Scaffold(
      body: PageView(
        controller: _pageController,
        children: [
          welcomeHanalab(),
          bluetoothPermissions(),
          locationPermissions(),
          getStartedPage(),
        ],
      ),
    );
  }
}
