#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <AccelStepper.h>

#include "types.h"
#include "screen.h"

class MainScreen : public Screen {
  float angle = 0;
  int radius = 20;
  int cx = 22;
  int cy = 22;
  bool isBusy = false;
  AccelStepper& stepper;
  long stepsRotaryTableRotation;
  float angleIncrement;

  Direction direction = Direction::NONE;

  void fillCircleSegment();
  void updateDisplay();
  void updateDisplayedAngle();
  void runStepper(long steps);
  long getStepsPerDivision(long numDivisions);
  long degreesToSteps(double degrees);

public:
  MainScreen(U8G2& u8g2, Keypad& keypad, AccelStepper& stepper, long stepsRotaryTableRotation, float angleIncrement) : Screen(u8g2, keypad), stepper(stepper), stepsRotaryTableRotation(stepsRotaryTableRotation), angleIncrement(angleIncrement) {}
  virtual void draw();
  virtual String getName();
};

#endif
