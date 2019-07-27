/******************************************************************
  Project name : PLC-OLED
  Author       :
  Date Time    : 2019-07-05
  Description  : 
  CPU BOARD    : PLC-Micro
  URL          : www.plc-expert.com
******************************************************************/

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;

void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  // 0X3C+SA0 - 0x3C or 0x3D
  oled.begin(&Adafruit128x32, 0x3C);
  oled.setFont(Adafruit5x7);

  oled.clear();
  
  // first row
  oled.println("Plc-Expert");

  // second row
  oled.set2X();
  oled.println("OLED test");

  // third row
  oled.set1X();
  oled.print("Time=");
  oled.print(micros());
}

void loop(){
}
