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

int num = 0;

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
  Serial.begin(115200);
  while (!Serial) {
    //
  }
}

void loop() {
  String line = "";
  if (Serial.available() > 0) {
    line = Serial.readStringUntil('\n');    
  }
  if (line.length() > 0) {
    num = line.toInt();  // int is 16bit in Pro Micro, so numbers over 32767 will overflow...
    Serial.println(num);
  }
  led.display(num);
}
