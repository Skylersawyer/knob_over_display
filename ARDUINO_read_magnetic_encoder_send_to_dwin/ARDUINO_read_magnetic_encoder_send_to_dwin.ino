// Custom made knob over DWIN display

// created by upir, 2025
// youtube channel: https://www.youtube.com/upir_upir

// YouTube Video: https://youtu.be/zIrAe23f8sg
// Source Files: https://github.com/upiir/knob_over_display

// Links from the video:
// Do you like this video? You can buy me a coffee ☕: https://www.buymeacoffee.com/upir
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// MT6701 Magnetic Encoder: https://s.click.aliexpress.com/e/_oBWfxpZ
// DWIN display: https://s.click.aliexpress.com/e/_oDUQWQR
// Magnetic Field viewer: https://s.click.aliexpress.com/e/_oFV4LRz
// Bearing 17x26x5mm: https://s.click.aliexpress.com/e/_olEp14J
// Solid Aluminium Knob: https://s.click.aliexpress.com/e/_DFPuloh

// Related videos:
// Knob over display: https://youtu.be/NPfaLKKsf_Q
// Knob over display faster: https://youtu.be/sFGsYZ0Hszk
// DWIN Ford Focus gauges: https://youtu.be/ugS3rKBZVVc
// DWIN gear indicator: https://youtu.be/qqmy5ZxKyq4

#include <Wire.h> // library used for the I2C communication
#include "MT6701.h" // library used for magnetic rotary encoder module MT6701

MT6701 encoder; // magnetic rotary encoder
// I2C connections from magnetic encoder module to Arduino UNO
// encoder -> UNO
// 5V - 5V
// GND - GND
// SCL - A5
// SDA - A4

// UART/serial connection between Arduino UNO and DWIN display
// UNO -> DWIN display
// Tx -> Rx2

void setup() {
  Serial.begin(115200); // start the serial communication with DWIN display
  Wire.begin(); // start the I2C communication (with the rotary magnetic encoder)
  encoder.initializeI2C(); // initialize the I2C connection
}

void loop() {
  float angle = encoder.angleRead(); // read the angle in degrees
  int angle_int = 360 - round(angle); // conver the angle to degrees

  // send the angle value to the DWIN display
  Serial.write(0x5a); // header
  Serial.write(0xa5); // header
  Serial.write(0x05); // number of bytes being send
  Serial.write(0x82); // send/set VP  
  Serial.write(0x10); // address
  Serial.write((byte)0x00); // address
  Serial.write(highByte(angle_int)); // value
  Serial.write(lowByte(angle_int)); // value
}
