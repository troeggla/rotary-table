#include "value_input_screen.h"

String ValueInputScreen::getName() {
  return "ValueInputScreen";
}

void ValueInputScreen::updateDisplay() {
  u8g2.firstPage();

  do {
    u8g2.setFont(u8g2_font_6x13_tr);

    String titleStr = (mode == Mode::DIV) ? "Num. Divisions" : "Input Degrees";
    int titleWidth = u8g2.getStrWidth(titleStr.c_str());

    u8g2.drawStr(128/2 - titleWidth/2, 11, titleStr.c_str());
    u8g2.drawHLine(0, 13, 128);

    int valueWidth = u8g2.getStrWidth(currentValue.c_str());
    u8g2.drawStr(128/2 - valueWidth/2, 40, currentValue.c_str());
  } while(u8g2.nextPage());
}

void ValueInputScreen::draw() {
  char key = keypad.getKey();

  switch (key) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    currentValue += key;
    break;
  case 'O':
    selectedValue = currentValue;
    break;
  case 'C':
    currentValue = "";
    break;
  case 'R':
    reset = true;
  }

  if (mode == Mode::DEG && key == '.') {
    currentValue += ".";
  }

  this->updateDisplay();
}

Mode ValueInputScreen::getMode() {
  return mode;
}

float ValueInputScreen::getSelectedValue() {
  if (selectedValue == "") {
    return -1;
  }

  return atof(selectedValue.c_str());
}