#include "screen_controller.h"

void ScreenController::initialize() {
  context->getDisplay().begin();
  currentScreen = new ModeSelectorScreen(*context);
}

void ScreenController::draw() {
  if (currentScreen->isReset()) {
    delete currentScreen;
    currentScreen = new ModeSelectorScreen(*context);
  }

  Screen* nextScreen = currentScreen->getNextScreen();
  if (nextScreen != 0) {
    delete currentScreen;
    currentScreen = nextScreen;
  }

  currentScreen->draw();
}
