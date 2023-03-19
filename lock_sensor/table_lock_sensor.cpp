#include "table_lock_sensor.h"

TableLockSensor::TableLockSensor(uint8_t sensorPinNum, uint8_t ledPinNum, uint8_t lockedState) : sensorPinNum(sensorPinNum), ledPinNum(ledPinNum), lockedState(lockedState) {
  pinMode(sensorPinNum, INPUT_PULLUP);
  pinMode(ledPinNum, OUTPUT);

  currentLedState = LOW;
  digitalWrite(ledPinNum, currentLedState);
}

bool TableLockSensor::isLocked() {
  return digitalRead(sensorPinNum) == lockedState;
}

void TableLockSensor::setLedState(uint8_t state) {
  digitalWrite(ledPinNum, state);
  currentLedState = state;
}

void TableLockSensor::updateLockLed() {
  currentLedState = (isLocked()) ? HIGH : LOW;
  digitalWrite(ledPinNum, currentLedState);
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
