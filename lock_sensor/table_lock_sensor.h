#ifndef TABLE_LOCK_SENSOR
#define TABLE_LOCK_SENSOR

#include <Arduino.h>
#include "../util/types.h"

class TableLockSensor {
  const uint8_t sensorPinNum;
  const uint8_t ledPinNum;
  const uint8_t lockedState;

public:
  TableLockSensor(uint8_t sensorPinNum, uint8_t ledPinNum, uint8_t lockedState);
  TableLockSensor(uint8_t sensorPinNum, uint8_t ledPinNum) : TableLockSensor(sensorPinNum, ledPinNum, HIGH) {};

  bool isLocked();
  void resetLockSensor();
  void updateLockLed();
  void flashLed();
  void turnOnLockLed();
};

#endif
