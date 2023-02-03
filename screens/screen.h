#ifndef SCREEN_H
#define SCREEN_H

#include <Keypad.h>
#include <U8g2lib.h>

#include "../context/application_context.h"

class Screen {
protected:
  ApplicationContext& context;
  bool reset = false;

public:
  Screen(ApplicationContext& context): context(context) {}
  virtual ~Screen() {}

  bool isReset() {
    return reset;
  }

  virtual void draw() = 0;
  virtual Screen* getNextScreen() = 0;
};

#endif
