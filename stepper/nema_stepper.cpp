#include "nema_stepper.h"

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
