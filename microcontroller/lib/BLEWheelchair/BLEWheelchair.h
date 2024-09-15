#ifndef BLE_WHEELCHAIR_H
#define BLE_WHEELCHAIR_H

#include "Arduino.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEUtils.h"
#include "BLEUUID.h"


#define CONTROLS_SERVICE_UUID BLEUUID("0000ffe0-0000-1000-8000-00805f9b34fb")
#define CONTROLS_CHARACTERISTIC_UUID BLEUUID("0000ffe1-0000-1000-8000-00805f9b34fb")

#define BATTERY_SERVICE_UUID BLEUUID((uint16_t)0x180F)
#define BATTERY_LEVEL_CHARACTERISTIC_UUID BLEUUID((uint16_t)0x2A19)
#define BATTERY_CRITICAL_CHARACTERISTIC_UUID BLEUUID((uint16_t)0x2BE9)


class BLEWheelchair {
  private:
    BLEServer *server;
    bool deviceConnected = false;
    bool oldDeviceConnected = false;
    unsigned long prevReconnectTime = 0;

    BLECharacteristic controlsCharacteristic = BLECharacteristic(
      CONTROLS_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE
    );
    BLECharacteristic batteryLevelCharacteristic = BLECharacteristic(
      BATTERY_LEVEL_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ
    );
    BLECharacteristic batteryCriticalCharacteristic = BLECharacteristic(
      BATTERY_CRITICAL_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ
    );

  public:
    void begin(const char *name);
    void checkToReconnect();
    bool isConnected();
    BLECharacteristic * getControlCharacteristic();
};

class WheelchairCallbacks: public BLEServerCallbacks {

  public:
    bool *deviceConnected;
    WheelchairCallbacks(bool* deviceConnected) {
      this->deviceConnected = deviceConnected;
    }

  void onConnect(BLEServer *Server) {
    *deviceConnected = true;
  }

  void onDisconnect(BLEServer *Server) {
    *deviceConnected = false;
  }
};

#endif