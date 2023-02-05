#ifndef TABLE_LOCK_SENSOR
#define TABLE_LOCK_SENSOR

#include <Arduino.h>

class TableLockSensor {
  uint8_t pinNum;

public:
  TableLockSensor(uint8_t pinNum);
  bool isLocked();
};

#endif
