#ifndef VALUE_INPUT_SCREEN_H
#define VALUE_INPUT_SCREEN_H

#include "types.h"
#include "screen.h"

class ValueInputScreen : public Screen {
  Mode mode;
  String currentValue;
  float selectedValue = -1;

  void updateDisplay();

public:
  ValueInputScreen(U8G2& u8g2, Keypad& keypad, Mode mode) : Screen(u8g2, keypad), mode(mode) {}
  float getSelectedValue();
  virtual String getName();
  virtual void draw();
};

#endif
