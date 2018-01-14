
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_FT6206.h>
#include "Button.h"
#include "RemoteControl.h"

bool priorTouch = false;
TS_Point priorPoint;
RemoteControl r;

// Run setup to draw the buttons
void setup()
{
  Serial.begin(9600);
  r.draw();
}


// Loop repeatedly to receive button inputs and perform actions
void loop()
{
  r.loop();
}
