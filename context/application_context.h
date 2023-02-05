#ifndef APPLICATION_CONTEXT_H
#define APPLICATION_CONTEXT_H

#include <Keypad.h>
#include <U8g2lib.h>

#include "../stepper/nema_stepper.h"
#include "../lock_sensor/table_lock_sensor.h"

class ApplicationContext {
  U8G2& display;
  Keypad& keypad;
  NemaStepper& stepper;
  TableLockSensor& lockSensor;

public:
  ApplicationContext(U8G2& display, Keypad& keypad, NemaStepper& stepper, TableLockSensor& lockSensor) : display(display), keypad(keypad), stepper(stepper), lockSensor(lockSensor) {}

  U8G2& getDisplay();
  Keypad& getKeypad();
  NemaStepper& getStepper();
  TableLockSensor& getLockSensor();
};

#endif
