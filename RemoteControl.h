#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_FT6206.h>
#include "Button.h"

// The TFT screen variables
#define TFT_CS 10
#define TFT_DC 9
#define TS_MAX_X 240
#define TS_MAX_Y 320


// Button sizes
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 40

// Button locations
#define POWER_X 10
#define POWER_Y 10
#define CHANNEL_UP_X 10
#define CHANNEL_UP_Y 110
#define CHANNEL_DOWN_X 10
#define CHANNEL_DOWN_Y 160
#define VOLUME_UP_X 130
#define VOLUME_UP_Y 110
#define VOLUME_DOWN_X 130
#define VOLUME_DOWN_Y 160

// Button colors (represented in binary--see rgbColor struct definition for explanation)
#define DEFAULT_INACTIVE_RED 0b01010;
#define DEFAULT_INACTIVE_GREEN 0b010100;
#define DEFAULT_INACTIVE_BLUE 0b01010;

#define DEFAULT_ACTIVE_RED 0b11111;
#define DEFAULT_ACTIVE_GREEN 0b010000;
#define DEFAULT_ACTIVE_BLUE 0b01000;

#define BUTTON_DELAY 100

struct rgbColor
{
  // Colors on the screen are 16-bit
  /* MSB (5 bits of RED) (6 bits of GREEN) (5 bits of BLUE) LSB */
  int red;
  int green;
  int blue;

  int convertColor()
  {
    return blue + green * pow(2, 5) + red * pow(2, 11);
  }
};

class RemoteControl
{
private:
  Adafruit_ILI9341 tft;     // The TFT display
  Adafruit_FT6206 ts;       // The touchscreen
  Button power;
  Button volumeUp;
  Button volumeDown;
  Button channelUp;
  Button channelDown;
  rgbColor inactiveColor;   // The color of the buttons when they aren't being pressed
  rgbColor activeColor;     // The color of the buttons whey they are being pressed
  bool wasTouched;          // Indicator for whether the screen had been touched
  Button* lastButton;       // Keeps track of the last button pushed

public:
  RemoteControl();
  void draw();
  void loop();
  
};






#endif
