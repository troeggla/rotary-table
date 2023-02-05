#include "table_lock_sensor.h"

TableLockSensor::TableLockSensor(uint8_t pinNum) : pinNum(pinNum) {
  pinMode(pinNum, INPUT_PULLUP);
}

bool TableLockSensor::isLocked() {
  return digitalRead(pinNum) == HIGH;
}
