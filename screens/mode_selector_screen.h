#ifndef MODE_SELECTOR_SCREEN_H
#define MODE_SELECTOR_SCREEN_H

#include "../types.h"
#include "screen.h"

class ModeSelectorScreen : public Screen {
  Mode currentMode = Mode::DIV;
  Mode selectedMode = Mode::NONE;
  void updateDisplay();

public:
  ModeSelectorScreen(U8G2& u8g2, Keypad& keypad) : Screen(u8g2, keypad) {}

  Mode getSelectedMode();
  virtual void draw();
  virtual String getName();
};

#endif
