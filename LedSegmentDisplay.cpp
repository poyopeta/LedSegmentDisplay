#include "LedSegmentDisplay.h"

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

void LedSegmentDisplay::display(int num) {
  if (num >= power(10, LED_SEGMENT_DIGITS) || num < 0) {
    return;
  }
  for (int i = 0; i < LED_SEGMENT_DIGITS; i++) {
    showDigit(LED_SEGMENT_DIGITS-1 - i, led_segments[getDigit(num, LED_SEGMENT_DIGITS-1 - i)]);
  }
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

void LedSegmentDisplay::display(int *numbers) {
  for (int i = 0; i < LED_SEGMENT_DIGITS; ++i) {
    showDigit(LED_SEGMENT_DIGITS-1 - i, led_segments[numbers[i]]);
  }
}

void LedSegmentDisplay::displayRaw(byte *bytes) {
  for (int i = 0; i < LED_SEGMENT_DIGITS; ++i) {
    showDigit(LED_SEGMENT_DIGITS-1 - i, bytes[i]);
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

int LedSegmentDisplay::getDigit(int num, int digit) {
  int res = (num % power(10, digit+1)) / power(10, digit);
  if (res == 0 && digit != 0 && (num / power(10, digit+1) == 0)) {
    res = 11;
  }
  return res;
}

int LedSegmentDisplay::getDigitDecimal(float num, int digit) {
  // 小数の各桁を取り出す方法が思いつかない...
}

int LedSegmentDisplay::power(int x, int y) {
  int result = 1;
  for (int i = 0; i < y; ++i) {
    result *= x;
  }
  return result;
}
