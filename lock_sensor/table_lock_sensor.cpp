#include "table_lock_sensor.h"

TableLockSensor::TableLockSensor(uint8_t sensorPinNum, uint8_t ledPinNum, uint8_t lockedState) : sensorPinNum(sensorPinNum), ledPinNum(ledPinNum), lockedState(lockedState) {
  pinMode(sensorPinNum, INPUT_PULLUP);
  pinMode(ledPinNum, OUTPUT);
}

bool TableLockSensor::isLocked() {
  return digitalRead(sensorPinNum) == lockedState;
}

void TableLockSensor::resetLockSensor() {
  digitalWrite(ledPinNum, LOW);
}

void TableLockSensor::updateLockLed() {
  digitalWrite(ledPinNum, (isLocked()) ? HIGH : LOW);
}

void TableLockSensor::flashLed() {
  if (isLocked()) {
    for (int i=0; i<3; i++) {
      digitalWrite(ledPinNum, LOW);
      delay(100);
      digitalWrite(ledPinNum, HIGH);
      delay(100);
    }
  }
}
