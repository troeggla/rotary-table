#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <Arduino.h>
#include <U8g2lib.h>

#include "../types.h"
#include "../stepper/nema_stepper.h"
#include "screen.h"

class MainScreen : public Screen {
  float angle = 0;
  int radius = 20;
  int cx = 22;
  int cy = 22;
  bool isBusy = false;
  NemaStepper& stepper;
  Mode mode;
  float increment;
  float angleIncrement;

  Direction direction = Direction::NONE;

  void fillCircleSegment();
  void updateDisplay();
  void updateDisplayedAngle();

public:
  MainScreen(U8G2& u8g2, Keypad& keypad, NemaStepper& stepper, Mode mode, float increment) :
    Screen(u8g2, keypad),
    stepper(stepper),
    mode(mode),
    increment(increment) {
    if (mode == Mode::DEG) {
      angleIncrement = increment;
    } else {
      angleIncrement = 360 / increment;
    }
  }

  virtual void draw();
  virtual String getName();
};

#endif
