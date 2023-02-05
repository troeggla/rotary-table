#include "application_context.h"

U8G2& ApplicationContext::getDisplay() {
  return display;
}

Keypad& ApplicationContext::getKeypad() {
  return keypad;
}

NemaStepper& ApplicationContext::getStepper() {
  return stepper;
}

TableLockSensor& ApplicationContext::getLockSensor() {
  return lockSensor;
}
