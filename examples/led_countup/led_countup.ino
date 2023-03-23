#include "LedSegmentDisplay.h"

#define ENABLE_D3 15
#define ENABLE_D2 14
#define ENABLE_D1 16
#define ENABLE_D0 10

#define SHIFTREG_D 7
#define SHIFTREG_RCLK 8
#define SHIFTREG_SRCLK 9

int digitPins[4] = {ENABLE_D3, ENABLE_D2, ENABLE_D1, ENABLE_D0};
//LedSegmentDisplay led(ENABLE_D3, ENABLE_D2, ENABLE_D1, ENABLE_D0, SHIFTREG_D, SHIFTREG_SRCLK, SHIFTREG_RCLK, 1);
LedSegmentDisplay led(digitPins, SHIFTREG_D, SHIFTREG_SRCLK, SHIFTREG_RCLK, 1);

int keepTime = 10;  // keep display state

void setup() {
  // put your setup code here, to run once:
  pinMode(ENABLE_D3, OUTPUT);
  pinMode(ENABLE_D2, OUTPUT);
  pinMode(ENABLE_D1, OUTPUT);
  pinMode(ENABLE_D0, OUTPUT);
  pinMode(SHIFTREG_D, OUTPUT);
  pinMode(SHIFTREG_SRCLK, OUTPUT);
  pinMode(SHIFTREG_RCLK, OUTPUT);
  led.begin();
  randomSeed(analogRead(0));
}

void loop() {
  for (int i = 0; i < 10000; i++) {
    keepNumber(i);
  }
  for (int i = 0; i < 10000; i++) {
    keepNumber(9999 - i);
  }
}

void keepNumber(int number) {
  int i = 0;
  while (i < keepTime) {
    led.display(number);
    ++i;
  }
}
