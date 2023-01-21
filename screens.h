#ifndef SCREENS_H
#define SCREENS_H

#include <AccelStepper.h>
#include <Keypad.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define LCD_CLK 13
#define LCD_DATA 11
#define LCD_CS 10

typedef enum {
  DEG,
  DIV,
  NONE
} Mode;

typedef enum {
  FWD,
  BWD,
  UNKNOWN
} Direction;

class Screen {
protected:
  U8G2& u8g2;
  Keypad& keypad;

public:
  Screen(U8G2& u8g2, Keypad& keypad): u8g2(u8g2), keypad(keypad) {}
  virtual ~Screen() {}

  virtual void draw() = 0;
};

class MainScreen : public Screen {
  float angle = 0;
  int radius = 20;
  int cx = 22;
  int cy = 22;
  bool isBusy = false;
  AccelStepper& stepper;
  long stepsRotaryTableRotation;
  float angleIncrement;

  Direction direction = Direction::UNKNOWN;

  void fillCircleSegment();
  void updateDisplay();
  void updateDisplayedAngle();
  void setDirection(Direction direction);
  void setBusy();
  void setReady();
  void runStepper(long steps);
  long getStepsPerDivision(long numDivisions);
  long degreesToSteps(double degrees);

public:
  MainScreen(U8G2& u8g2, Keypad& keypad, AccelStepper& stepper, long stepsRotaryTableRotation, float angleIncrement) : Screen(u8g2, keypad), stepper(stepper), stepsRotaryTableRotation(stepsRotaryTableRotation), angleIncrement(angleIncrement) {}
  virtual void draw();
};

class ScreenController {
  U8G2& display;
  Keypad& keypad;
  AccelStepper& stepper;

  Screen* currentScreen;

public:
  ScreenController(U8G2& display, Keypad& keypad, AccelStepper& stepper, long stepsRotaryTableRotation) : display(display), keypad(keypad), stepper(stepper) {
    currentScreen = new MainScreen(display, keypad, stepper, stepsRotaryTableRotation, 30);
  }

  ~ScreenController() {
    delete currentScreen;
  }

  void initialize();
  void draw();
};

#endif
