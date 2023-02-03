#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <Arduino.h>
#include <U8g2lib.h>

#include "../util/types.h"
#include "../stepper/nema_stepper.h"
#include "../controller/screen_controller.h"
#include "screen.h"

class MainScreen : public Screen {
  double angle = 0;
  int radius = 20;
  int cx = 22;
  int cy = 22;
  bool isBusy = false;
  Mode mode;
  double increment;
  double angleIncrement;
  int divisions;
  int currentDivision = 0;

  Direction direction = Direction::NONE;

  void fillCircleSegment();
  void updateDisplay();
  void updateDisplayedAngle();

public:
  MainScreen(ApplicationContext& context, Mode mode, double increment) :
    Screen(context),
    mode(mode),
    increment(increment) {
    if (mode == Mode::DEG) {
      angleIncrement = increment;
    } else {
      angleIncrement = 360 / increment;
      divisions = (int)increment;
    }
  }

  virtual void draw();
  virtual Screen* getNextScreen();
};

#endif
