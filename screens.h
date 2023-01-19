#ifndef SCREENS_H
#define SCREENS_H

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define LCD_CLK 13
#define LCD_DATA 11
#define LCD_CS 10

typedef enum {
  DEG,
  DIV
} Mode;

typedef enum {
  FWD,
  BWD,
  NONE
} Direction;

class Screen {
protected:
  U8G2_ST7920_128X64_1_SW_SPI u8g2 = U8G2_ST7920_128X64_1_SW_SPI(U8G2_R0, LCD_CLK, LCD_DATA, LCD_CS);

public:
  virtual ~Screen() {}
  void initialize();
  virtual void draw() = 0;
};

class MainScreen : public Screen {
  float angle = 0;
  int radius = 20;
  int cx = 22;
  int cy = 22;
  bool isBusy = false;
  Direction direction = Direction::FWD;
  float angleIncrement;

  void fillCircleSegment();

public:
  MainScreen(float angleIncrement) : angleIncrement(angleIncrement) {}

  virtual void draw();

  void advanceDisplayedAngle();
  void reverseDisplayedAngle();
  void setBusy();
  void setReady();
};

#endif
