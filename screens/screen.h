#ifndef SCREEN_H
#define SCREEN_H

#include "../context/application_context.h"

class Screen {
protected:
  ApplicationContext& context;
  bool reset = false;

public:
  Screen(ApplicationContext& context): context(context) {}
  virtual ~Screen() {}

  virtual void draw() = 0;
  virtual Screen* getNextScreen() = 0;
};

#endif
