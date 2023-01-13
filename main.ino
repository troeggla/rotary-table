#include <Arduino.h>

#define ENABLE 8
#define STEPX 2
#define DIRX 5

#define REVOLUTION 1600L
#define GEARREDUCTION 90L

long stepsRotaryTableRotation = REVOLUTION * GEARREDUCTION;

long getStepsPerDivision(long numDivisions) {
  return round(stepsRotaryTableRotation / numDivisions);
}

long degreesToSteps(double degrees) {
  return round(degrees * (stepsRotaryTableRotation / 360));
}

void step() {
  digitalWrite(STEPX, HIGH);
  delayMicroseconds(500);

  digitalWrite(STEPX, LOW);
  delayMicroseconds(500);
}

void setup() {
  pinMode(ENABLE, OUTPUT);
  pinMode(STEPX, OUTPUT);
  pinMode(DIRX, OUTPUT);

  digitalWrite(ENABLE, LOW);
  digitalWrite(DIRX, HIGH);
}

void loop() {
  for (int x = 0; x < getStepsPerDivision(6); x++) {
    step();
  }

  delay(3000);
}
