#include <Arduino.h>
#include <Keypad.h>
#include <U8g2lib.h>
#include <AccelStepper.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define DRV_STEP A0
#define DRV_DIR A1

#define REVOLUTION 1600L
#define GEARREDUCTION 90L

#define LCD_CLK 13
#define LCD_DATA 11
#define LCD_CS 10

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
AccelStepper stepper = AccelStepper(1, DRV_STEP, DRV_DIR);
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, LCD_CLK, LCD_DATA, LCD_CS);

long stepsRotaryTableRotation = REVOLUTION * GEARREDUCTION;

long getStepsPerDivision(long numDivisions) {
  return round(stepsRotaryTableRotation / numDivisions);
}

long degreesToSteps(double degrees) {
  return round(degrees * (stepsRotaryTableRotation / 360));
}

void fillCircleSegment(float angle, int cx, int cy, int radius) {
  u8g2.drawCircle(cx, cy, radius);

  if (angle >= 0 && angle < 90) {
    if (angle == 0) {
      u8g2.drawLine(cx, cy, cx, cy - radius);
      return;
    }

    float angle_rad = (90 - angle) * M_PI / 180;
    float m = (radius * sin(angle_rad)) / (radius * cos(angle_rad));

    for (int x=0; x<radius; x++) {
      int y = round(m * x);

      for (int y2=y; y2<radius; y2++) {
        if (x*x + y2*y2 < radius * radius) {
          u8g2.drawPixel(x + cx, -y2 + cy);
        }
      }
    }
  } else if (angle >= 90 && angle < 180) {
    u8g2.drawDisc(cx, cy, radius, U8G2_DRAW_UPPER_RIGHT);

    if (angle == 90) {
      return;
    }

    float angle_rad = (angle - 90) * M_PI / 180;
    float m = (radius * sin(angle_rad)) / (radius * cos(angle_rad));

    for (int x=0; x<radius; x++) {
      int y = round(m * x);

      for (int y2=y; y2>0; y2--) {
        if (x*x + y2*y2 < radius * radius) {
          u8g2.drawPixel(x + cx, y2 + cy);
        }
      }
    }
  } else if (angle >= 180 && angle < 270) {
    u8g2.drawDisc(cx, cy, radius, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_RIGHT);

    if (angle == 180) {
      return;
    }

    float angle_rad = (270 - angle) * M_PI / 180;
    float m = (radius * sin(angle_rad)) / (radius * cos(angle_rad));

    for (int x=0; x<radius; x++) {
      int y = round(m * x);

      for (int y2=y; y2<radius; y2++) {
        if (x*x + y2*y2 < radius * radius) {
          u8g2.drawPixel(-x + cx, y2 + cy);
        }
      }
    }
  } else {
    u8g2.drawDisc(cx, cy, radius, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_RIGHT | U8G2_DRAW_LOWER_LEFT);

    if (angle == 270) {
      return;
    }

    float angle_rad = (angle - 270) * M_PI / 180;
    float m = (radius * sin(angle_rad)) / (radius * cos(angle_rad));

    for (int x=0; x<radius; x++) {
      int y = round(m * x);

      for (int y2=y; y2>0; y2--) {
        if (x*x + y2*y2 < radius * radius) {
          u8g2.drawPixel(-x + cx, -y2 + cy);
        }
      }
    }
  }
}

void runStepper(long steps) {
  stepper.setSpeed(1000);
  stepper.moveTo(steps);

  while (stepper.distanceToGo() > 0) {
    stepper.run();
  }

  stepper.setCurrentPosition(0);
}

void drawToScreen(char c, float angle) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);

    String keyPress = "Key: " + String(angle);
    u8g2.drawStr(0, 14, keyPress.c_str());

    fillCircleSegment(angle, 22, 42, 20);
  } while(u8g2.nextPage());
}

void setup() {
  Serial.begin(115200);
  u8g2.begin();

  stepper.setMaxSpeed(1500);
  stepper.setAcceleration(200);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Key:");
    Serial.println(key);

    drawToScreen(key);
  }
}
