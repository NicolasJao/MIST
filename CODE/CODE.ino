#include <LedControl.h>
#include <avr/wdt.h>

#define MIC_PIN A0
#define THRESHOLD 100000  // adjust this up or down based on your mic sensitivity 513

LedControl lc = LedControl(/*DIN=*/11, /*CLK=*/13, /*CS=*/10, /*numDevices=*/1);

void setAll(bool on) {
  byte val = on ? B11111111 : B00000000;
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, val);
  }
}

void setup() {
  wdt_disable();
  delay(500);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void loop() {
  int sample = analogRead(MIC_PIN);
  int centered = abs(sample - 512);

  if (centered > THRESHOLD) {
    // sound detected - stop blinking, turn full board on
    setAll(true);
  } else {
    // no sound - blink
    setAll(true);
    delay(100);
    setAll(false);
    delay(100);
  }
}