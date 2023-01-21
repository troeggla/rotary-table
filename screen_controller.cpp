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
      currentScreen = new ValueInputScreen(display, keypad, selectedMode);
    }
  }

  if (currentScreen->getName().compareTo("ValueInputScreen") == 0) {
    float selectedValue = ((ValueInputScreen*)currentScreen)->getSelectedValue();

    if (selectedValue != -1) {
      delete currentScreen;
      currentScreen = new MainScreen(display, keypad, stepper, stepsRotaryTableRotation, selectedValue);
    }
  }

  currentScreen->draw();
}
