/*
  A homemade library for seven segment led display.
  Use 74HC595 shift register.
*/

#pragma once
#include "Arduino.h"

#define LED_SEGMENT_DIGITS 4

class LedSegmentDisplay {
  public:
    LedSegmentDisplay(int d3Pin, int d2Pin, int d1Pin, int d0Pin, int dataPin, int srclkPin, int rclkPin, int refreshCycle);  // constructor
    LedSegmentDisplay(int *digitPins, int dataPin, int srclkPin, int rclkPin, int refreshCycle);  // constructor

    void begin();
    void display(int i);  // display integer
    void display(float f);  // display decimal
    void display(int, int, int, int);  // display each number
    void display(int *);
    void displayRaw(byte, byte, byte, byte);  // display each byte code
    void displayRaw(byte *);  // display each byte code

  private:
    int LED[LED_SEGMENT_DIGITS];
    int SER, SRCLK, RCLK;
    int cycle;
    const byte led_segments[12] = {
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
    void showDigit(int, byte);  // show one digit
    bool setShiftReg(byte data);  // send byte data through a shift register
    int getDigit(int i, int d);  // get a number for each digit from integer
    int getDigitDecimal(float f, int d);  // get a number for each digit from decimal
};
