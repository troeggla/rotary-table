#ifndef APPLICATION_CONTEXT_H
#define APPLICATION_CONTEXT_H

#include <Keypad.h>
#include <U8g2lib.h>

#include "../stepper/nema_stepper.h"

class ApplicationContext {
  U8G2& display;
  Keypad& keypad;
  NemaStepper& stepper;

public:
  ApplicationContext(U8G2& display, Keypad& keypad, NemaStepper& stepper) : display(display), keypad(keypad), stepper(stepper) {}

  U8G2& getDisplay();
  Keypad& getKeypad();
  NemaStepper& getStepper();
};

#endif
