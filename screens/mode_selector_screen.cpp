#include "mode_selector_screen.h"

void ModeSelectorScreen::updateDisplay() {
  auto u8g2 = context.getDisplay();
  u8g2.firstPage();

  do {
    u8g2.setFont(u8g2_font_6x13_tr);

    String modeStr = "Select Mode";
    int width = u8g2.getStrWidth(modeStr.c_str());

    u8g2.drawStr(128/2 - width/2, 11, modeStr.c_str());
    u8g2.drawHLine(0, 13, 128);

    if (currentMode == Mode::DEG) {
      u8g2.drawButtonUTF8(32, 40, U8G2_BTN_SHADOW1 | U8G2_BTN_HCENTER | U8G2_BTN_BW2, 34,  2,  2, "DEG");
      u8g2.drawButtonUTF8(96, 40, U8G2_BTN_HCENTER | U8G2_BTN_BW2, 34,  2,  2, "DIV");
    } else {
      u8g2.drawButtonUTF8(32, 40, U8G2_BTN_HCENTER | U8G2_BTN_BW2, 34,  2,  2, "DEG");
      u8g2.drawButtonUTF8(96, 40, U8G2_BTN_SHADOW1 | U8G2_BTN_HCENTER | U8G2_BTN_BW2, 34,  2,  2, "DIV");
    }
  } while(u8g2.nextPage());
}

void ModeSelectorScreen::draw() {
  auto keypad = context.getKeypad();
  char key = keypad.getKey();

  if (key == '>' || key == '<') {
    currentMode = (currentMode == Mode::DIV) ? Mode::DEG : Mode::DIV;
  }

  if (key == KEY_OK) {
    selectedMode = currentMode;
  }

  this->updateDisplay();
}

Screen* ModeSelectorScreen::getNextScreen() {
  if (selectedMode != Mode::NONE) {
    return new ValueInputScreen(context, selectedMode);
  }

  return 0;
}
