#include "LedSegmentDisplay.h"

/* initialize */
LedSegmentDisplay::LedSegmentDisplay(int d3Pin, int d2Pin, int d1Pin, int d0Pin, int dataPin, int srclkPin, int rclkPin, int refreshCycle) {
  LED[3] = d3; LED[2] = d2; LED[1] = d1; LED[0] = d0;
  SER = dataPin;
  SRCLK = clockPin;
  RCLK = rclkPin;
  cycle = refreshCycle;
}

LedSegmentDisplay::display(int i) {
  // digiit 0
  delay(cycle);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigit(i, 0)]);
  delay(cycle);
  setShiftReg(11);

  // digiit 1
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigit(i, 1)]);
  delay(cycle);
  setShiftReg(11);

  // digiit 2
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], LOW);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigit(i, 2)]);
  delay(cycle);
  setShiftReg(11);

  // digiit 3
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], LOW);
  setShiftReg(led_segments[getDigit(i, 3)]);
  delay(cycle);
  setShiftReg(11);
}

LedSegmentDisplay::display(float f) {
  // digiit -1
  delay(cycle);
  digitalWrite(LED[0], LOW);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigitDecimal(f, -1)]);
  delay(cycle);
  setShiftReg(11);

  // digiit 0
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], LOW);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigitDecimal(f, 0)] | led_segments[10]);
  delay(cycle);
  setShiftReg(11);

  // digiit 1
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], LOW);
  digitalWrite(LED[3], HIGH);
  setShiftReg(led_segments[getDigitDecimal(f, 1)]);
  delay(cycle);
  setShiftReg(11);

  // digiit 2
  delay(cycle);
  digitalWrite(LED[0], HIGH);
  digitalWrite(LED[1], HIGH);
  digitalWrite(LED[2], HIGH);
  digitalWrite(LED[3], LOW);
  setShiftReg(led_segments[getDigitDecimal(f, 2)]);
  delay(cycle);
  setShiftReg(11);
}

LedSegmentDisplay::setShiftReg(byte data) {
  digitalWrite(RCLK, LOW);
  shiftOut(SER, SRCLK, LSBFIRST, data);
  digitalWrite(RCLK, HIGH);
}

LedSegmentDisplay::getDigit(int i, int d) {
  int res = (i / 10**d) % 10;
  if (res == 0 && i / 10**(d+1) == 0) {
    res = 11;
  }
  return res;
}

LedSegmentDisplay::getDigitDecimal(float f, int d) {
  // 小数の各桁を取り出す方法が思いつかない...
}
