#include "screens.h"

void Screen::initialize() {
  u8g2.begin();
}

void MainScreen::advanceDisplayedAngle() {
  angle += angleIncrement;

  if (angle >= 360) {
    angle -= 360;
  }
}

void MainScreen::reverseDisplayedAngle() {
  angle -= angleIncrement;

  if (angle < 0) {
    angle = 360 + angle;
  }
}

void MainScreen::draw() {
  u8g2.firstPage();

  do {
    // u8g2.setFont(u8g2_font_7x13B_mr);
    // u8g2.setFont(u8g2_font_t0_13_mr);
    u8g2.setFont(u8g2_font_prospero_bold_nbp_tn);

    String angle = String(this->angle);

    int width = u8g2.getStrWidth(angle.c_str());
    u8g2.drawStr(22 - width/2, 58, angle.c_str());

    this->fillCircleSegment();
  } while(u8g2.nextPage());
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
