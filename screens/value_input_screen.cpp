#include "value_input_screen.h"

void ValueInputScreen::updateDisplay() {
  U8G2& u8g2 = context.getDisplay();
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
  Keypad& keypad = context.getKeypad();
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
  case '.':
    currentValue += (mode == Mode::DEG) ? "." : "";
    break;
  case KEY_OK:
    selectedValue = currentValue;
    break;
  case KEY_CLR:
    currentValue = "";
    break;
  case KEY_RST:
    reset = true;
  }

  this->updateDisplay();
}

double ValueInputScreen::getSelectedValue() {
  if (selectedValue == "") {
    return -1;
  }

  double parsedValue = atof(selectedValue.c_str());

  if (mode == Mode::DEG) {
    if (parsedValue <= 0 || parsedValue > 360) {
      return -1;
    }
  } else if (mode == Mode::DIV) {
    if (parsedValue <= 0) {
      return -1;
    }
  }

  return parsedValue;
}

Screen* ValueInputScreen::getNextScreen() {
  if (reset) {
    return new ModeSelectorScreen(context);
  }

  double value = getSelectedValue();

  if (value != -1) {
    return new MainScreen(context, mode, value);
  }

  return 0;
}
