#include <Arduino.h>
#include <AccelStepper.h>
#include <Keypad.h>
#include <U8g2lib.h>

#include "util/types.h"
#include "stepper/nema_stepper.h"
#include "context/application_context.h"
#include "controller/screen_controller.h"

// Pins for LCD screen
#define LCD_CLK 13
#define LCD_DATA 11
#define LCD_CS 10

// Pins for stepper driver
#define DRV_STEP A0
#define DRV_DIR A1

// Number of steps per revolution of stepper motor
#define REVOLUTION 1600L
// Gear reduction of dividing head
#define GEARREDUCTION 90L

// Number of rows and columns of keypad
#define NUM_ROWS 4
#define NUM_COLS 4

// Keymap definition
const char keys[NUM_ROWS][NUM_COLS] = {
  {'1', '2', '3', KEY_OK},
  {'4', '5', '6', KEY_CLR},
  {'7', '8', '9', KEY_RST},
  {'<', '0', '>', '.'}
};

// Pins for keypad rows and columns
byte rowPins[NUM_ROWS] = {2, 3, 4, 5};
byte colPins[NUM_COLS] = {6, 7, 8, 9};

// Initialise hardware devices
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, NUM_ROWS, NUM_COLS);
U8G2_ST7920_128X64_1_SW_SPI u8g2 = U8G2_ST7920_128X64_1_SW_SPI(U8G2_R0, LCD_CLK, LCD_DATA, LCD_CS);
NemaStepper stepper = NemaStepper(DRV_STEP, DRV_DIR, REVOLUTION * GEARREDUCTION);

// Initialise application context and screen controller
ApplicationContext context = ApplicationContext(u8g2, keypad, stepper);
ScreenController controller = ScreenController(context);

void setup() {
  // Initialise controller
  controller.initialize();
}

void loop() {
  // Render current screen
  controller.draw();
}
