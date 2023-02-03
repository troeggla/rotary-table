#ifndef MODE_SELECTOR_SCREEN_H
#define MODE_SELECTOR_SCREEN_H

#include "../util/types.h"
#include "screen.h"
#include "value_input_screen.h"

class ModeSelectorScreen : public Screen {
  Mode currentMode = Mode::DEG;
  Mode selectedMode = Mode::NONE;

  void updateDisplay();

public:
  ModeSelectorScreen(ApplicationContext& context) : Screen(context) {}

  virtual void draw();
  virtual Screen* getNextScreen();
};

#endif
