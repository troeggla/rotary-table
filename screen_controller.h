#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#include "nema_stepper.h"

#include "screens/screen.h"
#include "screens/main_screen.h"
#include "screens/mode_selector_screen.h"
#include "screens/value_input_screen.h"

class ScreenController {
  U8G2& display;
  Keypad& keypad;
  NemaStepper& stepper;

  Screen* currentScreen;

public:
  ScreenController(U8G2& display, Keypad& keypad, NemaStepper& stepper) : display(display), keypad(keypad), stepper(stepper) {
    currentScreen = new ModeSelectorScreen(display, keypad);
  }

  ~ScreenController() {
    delete currentScreen;
  }

  void initialize();
  void draw();
};

#endif
