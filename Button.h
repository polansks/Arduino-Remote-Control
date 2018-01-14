#ifndef BUTTON_H
#define BUTTON_H

#include <Adafruit_ILI9341.h>
#include "Arduino.h"

#define IR_TRANSMIT_PIN 3
#define PULSE_LENGTH 550
#define DELAY_LENGTH 600

class Button
{
private:
	int x_coord;
	int y_coord;
	int height;
	int width;
  String label;
  uint16_t inactiveColor;
  uint16_t activeColor;
  uint16_t currentColor;

	Adafruit_ILI9341* tft; // The screen that the button is on

public:
	Button();
	Button(int x, int y, int height, int width, String label, uint16_t inactiveColor, uint16_t activeColor, Adafruit_ILI9341* tft);
	~Button();
  void drawButton();
	void flipColor();
  bool inButton(int x, int y);
  //void transmitSignal(

};

#endif
