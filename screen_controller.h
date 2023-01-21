#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#include "screen.h"
#include "main_screen.h"
#include "mode_selector_screen.h"

class ScreenController {
  U8G2& display;
  Keypad& keypad;
  AccelStepper& stepper;

  Screen* currentScreen;

public:
  ScreenController(U8G2& display, Keypad& keypad, AccelStepper& stepper, long stepsRotaryTableRotation) : display(display), keypad(keypad), stepper(stepper) {
    // currentScreen = new MainScreen(display, keypad, stepper, stepsRotaryTableRotation, 30);
    currentScreen = new ModeSelectorScreen(display, keypad);
  }

  ~ScreenController() {
    delete currentScreen;
  }

  void initialize();
  void draw();
};

#endif
