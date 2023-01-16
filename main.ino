#include <Arduino.h>
#include <Keypad.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

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

#define ENABLE 8
#define STEPX 2
#define DIRX 5

#define REVOLUTION 1600L
#define GEARREDUCTION 90L

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10);

long stepsRotaryTableRotation = REVOLUTION * GEARREDUCTION;

long getStepsPerDivision(long numDivisions) {
  return round(stepsRotaryTableRotation / numDivisions);
}

long degreesToSteps(double degrees) {
  return round(degrees * (stepsRotaryTableRotation / 360));
}

void step() {
  digitalWrite(STEPX, HIGH);
  delayMicroseconds(500);

  digitalWrite(STEPX, LOW);
  delayMicroseconds(500);
}

void drawToScreen(char c) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);

    String keyPress = "Key: " + String(c);
    u8g2.drawStr(0, 14, keyPress.c_str());

    u8g2.drawCircle(22, 42, 20);
    u8g2.drawDisc(22, 42, 20, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_LEFT);
    fillCircleSegment(75, 22, 42, 20);
  } while(u8g2.nextPage());
}

void setup() {
  Serial.begin(115200);

  u8g2.begin();

  pinMode(ENABLE, OUTPUT);
  pinMode(STEPX, OUTPUT);
  pinMode(DIRX, OUTPUT);

  digitalWrite(ENABLE, LOW);
  digitalWrite(DIRX, HIGH);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Key:");
    Serial.println(key);

    drawToScreen(key);
  }

}
