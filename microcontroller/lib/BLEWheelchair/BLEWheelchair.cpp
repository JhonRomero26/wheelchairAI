#include "BLEWheelchair.h"


void BLEWheelchair::begin(const char *name) {
  BLEDevice::init(name);
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  server = BLEDevice::createServer();

  server->setCallbacks(new ServerCallbacks());

  // Services
  BLEService *controlServ = server->createService(CONTROLS_SERVICE_UUID);
  controlServ->addCharacteristic(&controlsCharacteristic);
  controlServ->start();

  BLEService *batteryServ = server->createService(BATTERY_SERVICE_UUID);
  batteryServ->addCharacteristic(&batteryLevelCharacteristic);
  batteryServ->addCharacteristic(&batteryCriticalCharacteristic);
  batteryServ->start();

  // Advertising
  advertising->addServiceUUID(CONTROLS_SERVICE_UUID);
  advertising->setScanResponse(true);
  advertising->setMinPreferred(0x06);
  advertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

BLECharacteristic * BLEWheelchair::getControlCharacteristic() {
  return &controlsCharacteristic;
}
