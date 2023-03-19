#include "LedSegmentDisplay.h"
#include <math.h>

/* constructor */
LedSegmentDisplay::LedSegmentDisplay(int d3Pin, int d2Pin, int d1Pin, int d0Pin, int dataPin, int srclkPin, int rclkPin, int refreshCycle) {
  LED[3] = d3Pin; LED[2] = d2Pin; LED[1] = d1Pin; LED[0] = d0Pin;
  SER = dataPin;
  SRCLK = srclkPin;
  RCLK = rclkPin;
  cycle = refreshCycle;
}

LedSegmentDisplay::LedSegmentDisplay(int *digitPins, int dataPin, int srclkPin, int rclkPin, int refreshCycle) {
  for (int i = 0; i < LED_SEGMENT_DIGITS; ++i) {
    LED[LED_SEGMENT_DIGITS-1 - i] = digitPins[i];
  }
  SER = dataPin;
  SRCLK = srclkPin;
  RCLK = rclkPin;
  cycle = refreshCycle;
}

/* public functions */

void LedSegmentDisplay::begin() {
  // ここでpinMode()を実行しても良いかも
  for (int i = 0; i < LED_SEGMENT_DIGITS; ++i) {
    digitalWrite(LED[i], HIGH);
  }
  setShiftReg(led_segments[11]);  // off
}

void LedSegmentDisplay::display(int i) {
  // digiit 0
  delay(cycle);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigit(i, 0)]);
  delay(cycle);
  setShiftReg(led_segments[11]);

  // digiit 1
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigit(i, 1)]);
  delay(cycle);
  setShiftReg(led_segments[11]);

  // digiit 2
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], LOW);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigit(i, 2)]);
  delay(cycle);
  setShiftReg(led_segments[11]);

  // digiit 3
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], LOW);
  setShiftReg(led_segments[getDigit(i, 3)]);
  delay(cycle);
  setShiftReg(led_segments[11]);
}

void LedSegmentDisplay::display(float f) {
  // digiit -1
  delay(cycle);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigitDecimal(f, -1)]);
  delay(cycle);
  setShiftReg(led_segments[11]);

  // digiit 0
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigitDecimal(f, 0)] | led_segments[10]);
  delay(cycle);
  setShiftReg(led_segments[11]);

  // digiit 1
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], LOW);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigitDecimal(f, 1)]);
  delay(cycle);
  setShiftReg(led_segments[11]);

  // digiit 2
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], LOW);
  setShiftReg(led_segments[getDigitDecimal(f, 2)]);
  delay(cycle);
  setShiftReg(led_segments[11]);
}

void LedSegmentDisplay::display(int d3, int d2, int d1, int d0) {
  // digiit 3
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], LOW);
  setShiftReg(led_segments[d3]);
  delay(cycle);
  setShiftReg(led_segments[11]);

  // digiit 2
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], LOW);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[d2]);
  delay(cycle);
  setShiftReg(led_segments[11]);

  // digiit 1
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[d1]);
  delay(cycle);
  setShiftReg(led_segments[11]);

  // digiit 0
  delay(cycle);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[d0]);
  delay(cycle);
  setShiftReg(led_segments[11]);
}

void LedSegmentDisplay::display(int *number) {
  for (int i = 0; i < LED_SEGMENT_DIGITS; ++i) {
    showDigit(LED_SEGMENT_DIGITS-1 - i, led_segments[number[i]]);
  }
}

void LedSegmentDisplay::displayRaw(byte d3, byte d2, byte d1, byte d0) {
  showDigit(3, d3);
  showDigit(2, d2);
  showDigit(1, d1);
  showDigit(0, d0);
}

void LedSegmentDisplay::displayRaw(byte *data) {
  for (int i = 0; i < LED_SEGMENT_DIGITS; ++i) {
    showDigit(LED_SEGMENT_DIGITS-1 - i, data[i]);
  }
}

/* private functions */
void LedSegmentDisplay::showDigit(int digit, byte data) {
  delay(cycle);
  for (int i = 0; i < LED_SEGMENT_DIGITS; ++i) {
    if (i == digit) {
      digitalWrite(LED[i], LOW);
    }
    else {
      digitalWrite(LED[i], HIGH);
    }
  }
  setShiftReg(data);
  delay(cycle);
  setShiftReg(led_segments[11]);
}

bool LedSegmentDisplay::setShiftReg(byte data) {
  digitalWrite(RCLK, LOW);
  shiftOut(SER, SRCLK, LSBFIRST, data);
  digitalWrite(RCLK, HIGH);
}

int LedSegmentDisplay::getDigit(int i, int d) {
  int res = (i / (int)pow(10, d)) % 10;
  if (res == 0 && i / (int)pow(10, d+1) == 0) {
    res = 11;  // これで正しいのか？
  }
  return res;
}

int LedSegmentDisplay::getDigitDecimal(float f, int d) {
  // 小数の各桁を取り出す方法が思いつかない...
}
