#include "main_screen.h"

MainScreen::MainScreen(ApplicationContext& context, Mode mode, double increment) : Screen(context), mode(mode), increment(increment) {
  if (mode == Mode::DEG) {
    angleIncrement = increment;
  } else {
    angleIncrement = 360 / increment;
    divisions = (int)increment;
  }
}

void MainScreen::updateDisplayedAngle() {
  if (direction == Direction::FWD) {
    angle += angleIncrement;

    if (mode == Mode::DIV && (currentDivision == divisions || currentDivision == 0)) {
      angle = 0;
    } else if (angle >= 360) {
      angle -= 360;
    }
  } else if (direction == Direction::BWD) {
    angle -= angleIncrement;

    if (mode == Mode::DIV && (currentDivision == divisions || currentDivision == 0)) {
      angle = 0;
    } else if (angle < 0) {
      angle = 360 + angle;
    }
  }
}

void MainScreen::updateDisplay() {
  U8G2& u8g2 = context.getDisplay();
  u8g2.firstPage();

  do {
    u8g2.setFont(u8g2_font_6x13_tr);

    String angle = String(this->angle);
    int width = u8g2.getStrWidth(angle.c_str());
    u8g2.drawStr(22 - width/2, 59, angle.c_str());

    this->fillCircleSegment();

    u8g2.drawVLine(45, 0, 64);
    u8g2.drawHLine(0, 45, 45);

    if (isBusy) {
      String busy = "BUSY";
      int width = u8g2.getStrWidth(busy.c_str());
      u8g2.drawStr(87 - width/2, 13, busy.c_str());

      if (direction == Direction::FWD) {
        u8g2.drawTriangle(119, 3, 124, 8, 119, 13);
      } else if (direction == Direction::BWD) {
        u8g2.drawTriangle(55, 3, 50, 8, 55, 13);
      }
    } else {
      String okStr = "OK";
      int width = u8g2.getStrWidth(okStr.c_str());
      u8g2.drawStr(87 - width/2, 13, okStr.c_str());
    }

    u8g2.drawHLine(46, 16, 82);

    u8g2.drawStr(49, 29, "MODE:");
    u8g2.drawStr(90, 29, (mode == Mode::DEG) ? "DEG" : "DIV");

    u8g2.drawHLine(46, 32, 82);

    u8g2.drawStr(49, 45, "INC:");
    u8g2.drawStr(90, 45, String(angleIncrement).c_str());

    u8g2.drawHLine(46, 48, 82);
    u8g2.drawVLine(85, 16, 32);

    if (mode == Mode::DEG) {
      int width = u8g2.getStrWidth("-/-");
      u8g2.drawStr(87 - width / 2, 61, "-/-");
    } else {
      if (currentDivision >= 0 && currentDivision <= divisions) {
        String numDivisions = String(currentDivision) + "/" + String(divisions);
        int width = u8g2.getStrWidth(numDivisions.c_str());

        u8g2.drawStr(87 - width / 2, 61, numDivisions.c_str());
      }
    }
  } while(u8g2.nextPage());
}

void MainScreen::draw() {
  Keypad& keypad = context.getKeypad();
  NemaStepper& stepper = context.getStepper();

  char key = keypad.getKey();

  if (key == KEY_RST) {
    reset = true;
  }

  if (key == '<' || key == '>') {
    direction = (key == '<') ? Direction::BWD : Direction::FWD;
    isBusy = true;
    this->updateDisplay();

    if (mode == Mode::DEG) {
      stepper.runDegrees((direction == Direction::BWD) ? -increment : increment);
    } else {
      double degrees = 360 / increment;
      stepper.runDegrees((direction == Direction:: BWD) ? -degrees : degrees);
    }

    currentDivision = (key == '<') ? currentDivision - 1 : currentDivision + 1;
    this->updateDisplayedAngle();
    isBusy = false;
    this->updateDisplay();
  } else {
    this->updateDisplay();
  }
}

void MainScreen::fillCircleSegment() {
  double angle = round(this->angle);

  U8G2& u8g2 = context.getDisplay();
  u8g2.drawCircle(cx, cy, radius);

  if (angle >= 0 && angle < 90) {
    if (angle == 0) {
      u8g2.drawLine(cx, cy, cx, cy - radius);
      return;
    }

    double angle_rad = (90 - angle) * M_PI / 180;
    double m = (radius * sin(angle_rad)) / (radius * cos(angle_rad));

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

    double angle_rad = (angle - 90) * M_PI / 180;
    double m = (radius * sin(angle_rad)) / (radius * cos(angle_rad));

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

    double angle_rad = (270 - angle) * M_PI / 180;
    double m = (radius * sin(angle_rad)) / (radius * cos(angle_rad));

    for (int x=0; x<radius; x++) {
      int y = round(m * x);

      for (int y2=y; y2<radius; y2++) {
        if (x*x + y2*y2 < radius * radius) {
          u8g2.drawPixel(-x + cx, y2 + cy);
        }
      }
    }
  } else if (angle >= 270 && angle < 360) {
    u8g2.drawDisc(cx, cy, radius, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_RIGHT | U8G2_DRAW_LOWER_LEFT);

    if (angle == 270) {
      return;
    }

    double angle_rad = (angle - 270) * M_PI / 180;
    double m = (radius * sin(angle_rad)) / (radius * cos(angle_rad));

    for (int x=0; x<radius; x++) {
      int y = round(m * x);

      for (int y2=y; y2>0; y2--) {
        if (x*x + y2*y2 < radius * radius) {
          u8g2.drawPixel(-x + cx, -y2 + cy);
        }
      }
    }
  } else {
    u8g2.drawLine(cx, cy, cx, cy - radius);
  }
}

Screen* MainScreen::getNextScreen() {
  if (reset) {
    return new ModeSelectorScreen(context);
  }

  return 0;
}
