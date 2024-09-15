#include "BLEWheelchair.h"


void BLEWheelchair::begin(const char *name) {
  BLEDevice::init(name);
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  server = BLEDevice::createServer();

  server->setCallbacks(new WheelchairCallbacks(&deviceConnected));

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
  server->getAdvertising()->start();
}

BLECharacteristic * BLEWheelchair::getControlCharacteristic() {
  return &controlsCharacteristic;
}


void BLEWheelchair::checkToReconnect() {
  if (!deviceConnected && oldDeviceConnected) {
    if (millis() - prevReconnectTime > 500) {
      server->startAdvertising();
      oldDeviceConnected = deviceConnected;
      prevReconnectTime = millis();
    }
  }

  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = deviceConnected;
  }
}

bool BLEWheelchair::isConnected() {
  return deviceConnected;
}
