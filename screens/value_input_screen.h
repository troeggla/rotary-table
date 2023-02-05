#ifndef VALUE_INPUT_SCREEN_H
#define VALUE_INPUT_SCREEN_H

#include "../util/types.h"
#include "screen.h"
#include "main_screen.h"
#include "mode_selector_screen.h"

class ValueInputScreen : public Screen {
  Mode mode;
  String currentValue;
  String selectedValue = "";
  bool hasComma = false;

  void updateDisplay();
  double getSelectedValue();

public:
  ValueInputScreen(ApplicationContext& context, Mode mode) : Screen(context), mode(mode) {}

  virtual void draw();
  virtual Screen* getNextScreen();
};

#endif
