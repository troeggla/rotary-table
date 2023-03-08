#ifndef TABLE_LOCK_SENSOR
#define TABLE_LOCK_SENSOR

#include <Arduino.h>

class TableLockSensor {
  uint8_t sensorPinNum;
  uint8_t ledPinNum;

  uint8_t currentLedState;

public:
  TableLockSensor(uint8_t sensorPinNum, uint8_t ledPinNum);

  bool isLocked();
  void setLedState(uint8_t state);
  void flashLed();
};

#endif
