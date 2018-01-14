#include "Button.h"

Button::Button()
{
	x_coord = 0;
	y_coord = 0;
	height = 0;
	width = 0;

	tft = nullptr;
	return;
}

Button::Button(int x, int y, int height, int width, String label, uint16_t inactiveColor, uint16_t activeColor, Adafruit_ILI9341* tft)
{
  // Set the attributes of the button
	this->x_coord = x;
	this->y_coord = y;
	this->height = height;
	this->width = width;
  this->label = label;

  // Set the colors
  this->activeColor = activeColor;
  this->inactiveColor = inactiveColor;

  currentColor = inactiveColor;
  
	// Setup the TFT and touchscreen
	this->tft = tft;

	return;
}

Button::~Button()
{
  return;
}


void Button::drawButton()
{
	tft->fillRoundRect(x_coord, y_coord, width, height, 4, currentColor);
  tft->setCursor(x_coord + 4, y_coord + 4);
  tft->println(label);
	return;
}

bool Button::inButton(int test_x, int test_y)
{
  if ((test_x >= x_coord)
      && (test_x <= x_coord + width)
      && (test_y >= y_coord)
      && (test_y <= y_coord + height))
  {
    return true;
  }
  else
  {
    return false;  
  }
}

void Button::flipColor()
{
  if (currentColor == inactiveColor)
  {
    currentColor = activeColor;
  }
  else
  {
    currentColor = inactiveColor;
  }

  tft->fillRoundRect(x_coord, y_coord, width, height, 4, currentColor);
  tft->setCursor(x_coord + 4, y_coord + 4);
  tft->println(label);

  return;
}

