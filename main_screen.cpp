#include "main_screen.h"

String MainScreen::getName() {
  return "MainScreen";
}

void MainScreen::updateDisplayedAngle() {
  if (direction == Direction::FWD) {
    angle += angleIncrement;

    if (angle >= 360) {
      angle -= 360;
    }
  } else if (direction == Direction::BWD) {
    angle -= angleIncrement;

    if (angle < 0) {
      angle = 360 + angle;
    }
  }
}

void MainScreen::runStepper(long steps) {
  stepper.setSpeed(1000);
  stepper.moveTo(steps);

  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  stepper.setCurrentPosition(0);
}

long MainScreen::getStepsPerDivision(long numDivisions) {
  return round(stepsRotaryTableRotation / numDivisions);
}

long MainScreen::degreesToSteps(double degrees) {
  return round(degrees * (stepsRotaryTableRotation / 360));
}

void MainScreen::updateDisplay() {
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
  } while(u8g2.nextPage());
}

void MainScreen::draw() {
  char key = keypad.getKey();

  if (key == 'R') {
    reset = true;
  }

  if (key == '<' || key == '>') {
    direction = (key == '<') ? Direction::BWD : Direction::FWD;
    isBusy = true;
    this->updateDisplay();

    long steps = (mode == Mode::DEG) ? (
      degreesToSteps(increment)
    ): (
      getStepsPerDivision((long)increment)
    );

    runStepper((key == '<') ? -steps : steps);

    this->updateDisplayedAngle();
    isBusy = false;
    this->updateDisplay();
  } else {
    this->updateDisplay();
  }
}

void MainScreen::fillCircleSegment() {
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
