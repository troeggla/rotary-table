#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#include "screen.h"
#include "main_screen.h"
#include "mode_selector_screen.h"

class ScreenController {
  U8G2& display;
  Keypad& keypad;
  AccelStepper& stepper;
  long stepsRotaryTableRotation;

  Screen* currentScreen;

public:
  ScreenController(U8G2& display, Keypad& keypad, AccelStepper& stepper, long stepsRotaryTableRotation) : display(display), keypad(keypad), stepper(stepper), stepsRotaryTableRotation(stepsRotaryTableRotation) {
    currentScreen = new ModeSelectorScreen(display, keypad);
  }

  ~ScreenController() {
    delete currentScreen;
  }

  void initialize();
  void draw();
};

#endif
