#include "screen_controller.h"

void ScreenController::initialize() {
  stepper.setMaxSpeed(1500);
  stepper.setAcceleration(400);
  display.begin();
}

void ScreenController::draw() {
  currentScreen->draw();
}

