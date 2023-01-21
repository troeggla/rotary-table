#include <Arduino.h>
#include <AccelStepper.h>
#include <Keypad.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "screen_controller.h"

#define LCD_CLK 13
#define LCD_DATA 11
#define LCD_CS 10

#define DRV_STEP A0
#define DRV_DIR A1

#define REVOLUTION 1600L
#define GEARREDUCTION 90L

#define NUM_ROWS 4
#define NUM_COLS 4

const char keys[NUM_ROWS][NUM_COLS] = {
  {'1', '2', '3', 'O'},
  {'4', '5', '6', 'R'},
  {'7', '8', '9', 'M'},
  {'<', '0', '>', '.'}
};

byte rowPins[NUM_ROWS] = {2, 3, 4, 5};
byte colPins[NUM_COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, NUM_ROWS, NUM_COLS);
U8G2_ST7920_128X64_1_SW_SPI u8g2 = U8G2_ST7920_128X64_1_SW_SPI(U8G2_R0, LCD_CLK, LCD_DATA, LCD_CS);
AccelStepper stepper = AccelStepper(1, DRV_STEP, DRV_DIR);

ScreenController controller = ScreenController(u8g2, keypad, stepper, REVOLUTION * GEARREDUCTION);

void setup() {
  Serial.begin(115200);

  controller.initialize();
  controller.draw();

}

void loop() {
  controller.draw();
}
