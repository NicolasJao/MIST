#include <LedControl.h>
#include <avr/wdt.h>

#define BUTTON_PIN 4

LedControl lc = LedControl(/*DIN=*/11, /*CLK=*/13, /*CS=*/10, /*numDevices=*/1);

bool showHeart = false;
bool lastButtonState = HIGH;

byte pattern[8] = {
  B00000000,
  B11100111,
  B00100100,
  B11100111,
  B00000000,
  B00000000,
  B00100100,
  B00111100
};

byte heart[8] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

void displayPattern(byte p[]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, p[row]);
  }
}

void setup() {
  wdt_disable();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  delay(500);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  displayPattern(pattern);
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    showHeart = !showHeart;
    lc.clearDisplay(0);
    displayPattern(showHeart ? heart : pattern);
    delay(50);  // debounce
  }

  lastButtonState = currentButtonState;
}