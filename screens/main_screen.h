#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "../util/types.h"
#include "screen.h"
#include "mode_selector_screen.h"

class MainScreen : public Screen {
  int radius = 20;
  int cx = 22;
  int cy = 22;

  bool isBusy = false;

  double angleIncrement;
  double currentAngle = 0;

  int divisions;
  int currentDivision = 0;

  Direction direction = Direction::NONE;

  Mode mode;
  double increment;

  void fillCircleSegment();
  void updateDisplay();
  void updateDisplayedAngle();

public:
  MainScreen(ApplicationContext& context, Mode mode, double increment);

  virtual void draw();
  virtual Screen* getNextScreen();
};

#endif
