#include "nema_stepper.h"

NemaStepper::NemaStepper(int stepPin, int dirPin, long stepsPerRotation) : stepsPerRotation(stepsPerRotation) {
  stepper = AccelStepper(1, stepPin, dirPin);

  stepper.setMaxSpeed(2000);
  stepper.setSpeed(1600);
  stepper.setAcceleration(400);
}

void NemaStepper::runStepper(long steps) {
  stepper.moveTo(steps);

  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  stepper.setCurrentPosition(0);
}

void NemaStepper::runDegrees(double degrees) {
  runStepper(degreesToSteps(degrees));
}

long NemaStepper::degreesToSteps(double degrees) {
  return round(degrees * (stepsPerRotation / 360));
}
