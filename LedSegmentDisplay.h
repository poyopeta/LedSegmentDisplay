#include "Arduino.h"

class LedSegmentDisplay {
  public:
    void LedSegmentDisplay(int d3Pin, int d2Pin, int d1Pin, int d0Pin, int dataPin, int srclkPin, int rclkPin, int refreshCycle);
    void display(int i);
    void display(float f);
  private:
    int LED[4];
    int SER, SRCLK, RCLK;
    int cycle;
    byte led_segments[12] {
      B11111100,  // 0
      B01100000,  // 1
      B11011010,  // 2
      B11110010,  // 3
      B01100110,  // 4
      B10110110,  // 5
      B10111110,  // 6
      B11100000,  // 7
      B11111110,  // 8
      B11100110,  // 9
      B00000001,  // D.P 
      B00000000,  // OFF
    };
    bool setShiftReg(byte data);
    int getDigit(int i, int d);
    int getDigitDecimal(float f, int d);
}
