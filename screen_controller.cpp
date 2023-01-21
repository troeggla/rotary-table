#include "screen_controller.h"

void ScreenController::initialize() {
  stepper.setMaxSpeed(1500);
  stepper.setAcceleration(400);
  display.begin();
}

void ScreenController::draw() {
  if (currentScreen->getName().compareTo("ModeSelectorScreen") == 0) {
    Mode selectedMode = ((ModeSelectorScreen*)currentScreen)->getSelectedMode();

    if (selectedMode != Mode::NONE) {
      delete currentScreen;
      currentScreen = new MainScreen(display, keypad, stepper, stepsRotaryTableRotation, 30);
    }
  }

  currentScreen->draw();
}
