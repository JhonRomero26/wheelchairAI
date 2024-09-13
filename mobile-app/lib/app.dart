import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:wheelchair/controllers/ble_controller.dart';
import 'package:wheelchair/controllers/wheelchair_controller.dart';
import 'package:wheelchair/ui/screens/controller_screen.dart';
import 'package:wheelchair/ui/screens/welcome_screen.dart';
import 'package:flutter/services.dart';

class App extends StatelessWidget {
  const App({super.key});

  @override
  Widget build(BuildContext context) {
    SystemChrome.setPreferredOrientations([
      DeviceOrientation.portraitUp,
    ]);
    SystemChrome.setSystemUIOverlayStyle(const SystemUiOverlayStyle(
      statusBarColor: Colors.transparent,
      statusBarIconBrightness: Brightness.dark,
    ));
    Get.put(BleController());
    Get.put(WheelchairController());

    return GetMaterialApp(
      title: 'Hanalab Wheelchair App',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      initialRoute: WelcomeScreen.id,
      routes: {
        WelcomeScreen.id: (context) => const WelcomeScreen(),
        ControllerScreen.id: (context) => const ControllerScreen(),
      },
    );
  }
}
