#ifndef SCREEN_H
#define SCREEN_H

#include <Keypad.h>
#include <U8g2lib.h>

class Screen {
protected:
  U8G2& u8g2;
  Keypad& keypad;

public:
  Screen(U8G2& u8g2, Keypad& keypad): u8g2(u8g2), keypad(keypad) {}
  virtual ~Screen() {}

  virtual void draw() = 0;
};

#endif
