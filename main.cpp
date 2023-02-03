#include <Arduino.h>
#include <AccelStepper.h>
#include <Keypad.h>
#include <U8g2lib.h>

#include "util/types.h"
#include "stepper/nema_stepper.h"
#include "context/application_context.h"
#include "controller/screen_controller.h"

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
  {'1', '2', '3', KEY_OK},
  {'4', '5', '6', KEY_CLR},
  {'7', '8', '9', KEY_RST},
  {'<', '0', '>', '.'}
};

byte rowPins[NUM_ROWS] = {2, 3, 4, 5};
byte colPins[NUM_COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, NUM_ROWS, NUM_COLS);
U8G2_ST7920_128X64_1_SW_SPI u8g2 = U8G2_ST7920_128X64_1_SW_SPI(U8G2_R0, LCD_CLK, LCD_DATA, LCD_CS);
NemaStepper stepper = NemaStepper(DRV_STEP, DRV_DIR, REVOLUTION * GEARREDUCTION);

ApplicationContext context = ApplicationContext(u8g2, keypad, stepper);
ScreenController controller = ScreenController(context);

void setup() {
  controller.initialize();
}

void loop() {
  controller.draw();
}
