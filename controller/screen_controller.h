#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#include "../context/application_context.h"
#include "../stepper/nema_stepper.h"
#include "../screens/screen.h"
#include "../screens/mode_selector_screen.h"

class ScreenController {
  ApplicationContext& context;
  Screen* currentScreen;

public:
  ScreenController(ApplicationContext &context) : context(context) {}

  ~ScreenController() {
    delete currentScreen;
  }

  void initialize();
  void draw();
};

#endif
