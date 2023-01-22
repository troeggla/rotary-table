#include "screen_controller.h"

void ScreenController::initialize() {
  display.begin();
}

void ScreenController::draw() {
  if (currentScreen->isReset()) {
    delete currentScreen;
    currentScreen = new ModeSelectorScreen(display, keypad);
  }

  if (currentScreen->getName().compareTo("ModeSelectorScreen") == 0) {
    Mode selectedMode = ((ModeSelectorScreen*)currentScreen)->getSelectedMode();

    if (selectedMode != Mode::NONE) {
      delete currentScreen;
      currentScreen = new ValueInputScreen(display, keypad, selectedMode);
    }
  }

  if (currentScreen->getName().compareTo("ValueInputScreen") == 0) {
    double selectedValue = ((ValueInputScreen*)currentScreen)->getSelectedValue();
    Mode mode = ((ValueInputScreen*)currentScreen)->getMode();

    if (selectedValue != -1) {
      delete currentScreen;
      currentScreen = new MainScreen(display, keypad, stepper, mode, selectedValue);
    }
  }

  currentScreen->draw();
}
