#include <Arduino.h>
#include <Keypad.h>
#include <AccelStepper.h>

#include "screens.h"

#define DRV_STEP A0
#define DRV_DIR A1

#define REVOLUTION 1600L
#define GEARREDUCTION 90L

#define NUM_ROWS 4
#define NUM_COLS 4

const char keys[NUM_ROWS][NUM_COLS] = {
  {'1', '2', '3', 'O'},
  {'4', '5', '6', 'R'},
  {'7', '8', '9', 'M'},
  {'<', '0', '>', '.'}
};

byte rowPins[NUM_ROWS] = {2, 3, 4, 5};
byte colPins[NUM_COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, NUM_ROWS, NUM_COLS);
AccelStepper stepper = AccelStepper(1, DRV_STEP, DRV_DIR);

float increment = 15;
MainScreen screen = MainScreen(increment);

long stepsRotaryTableRotation = REVOLUTION * GEARREDUCTION;

long getStepsPerDivision(long numDivisions) {
  return round(stepsRotaryTableRotation / numDivisions);
}

long degreesToSteps(double degrees) {
  return round(degrees * (stepsRotaryTableRotation / 360));
}

void runStepper(long steps) {
  stepper.setSpeed(1000);
  stepper.moveTo(steps);

  while (stepper.distanceToGo() > 0) {
    stepper.run();
  }

  stepper.setCurrentPosition(0);
}

void setup() {
  Serial.begin(115200);
  screen.initialize();

  stepper.setMaxSpeed(1500);
  stepper.setAcceleration(200);
}

void loop() {
  float angle = 0;
  screen.draw();

  while (angle < 360) {
    screen.setDirection(Direction::FWD);
    screen.setBusy();
    screen.draw();

    long steps = degreesToSteps(increment);
    runStepper(steps);

    screen.updateDisplayedAngle();
    screen.setReady();
    screen.draw();

    delay(2000);
    angle += increment;
  }
}
