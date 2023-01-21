#ifndef NEMA_STEPPER
#define NEMA_STEPPER

#include <AccelStepper.h>

class NemaStepper {
  long stepsPerRotation;
  AccelStepper stepper;

  long degreesToSteps(double degrees);
  void runStepper(long steps);

public:
  NemaStepper(int stepPin, int dirPin, long stepsPerRotation) : stepsPerRotation(stepsPerRotation) {
    stepper = AccelStepper(1, stepPin, dirPin);

    stepper.setMaxSpeed(1500);
    stepper.setAcceleration(400);
  }

  void runDegrees(float degrees);
};

#endif
