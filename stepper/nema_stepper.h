#ifndef NEMA_STEPPER
#define NEMA_STEPPER

#include <AccelStepper.h>

class NemaStepper {
  long stepsPerRotation;
  AccelStepper stepper;

  long degreesToSteps(double degrees);
  void runStepper(long steps);

public:
  NemaStepper(int stepPin, int dirPin, long stepsPerRotation);
  void runDegrees(double degrees);
};

#endif
