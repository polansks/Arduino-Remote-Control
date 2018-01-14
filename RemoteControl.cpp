/*******************************************************************************
 * File: RemoteControl.cpp
 * Author: Scott Polansky
 * Description: The RemoteControl class represents a touchscreen remote control.
 *              It displays a user interface and handles the interaction with
 *              the user
 ******************************************************************************/

#include "RemoteControl.h"


/*******************************************************************************
 * Function: RemoteControl
 * Return Value: n/a
 * Description: Default constructor. Initializes the screen and the user
 *              interface with the buttons
  ******************************************************************************/
RemoteControl::RemoteControl() : tft(TFT_CS, TFT_DC)
{
  // Setup the screen
  Adafruit_FT6206 ts = Adafruit_FT6206();

  // Set the colors of the buttons
  inactiveColor.red = DEFAULT_INACTIVE_RED;
  inactiveColor.green = DEFAULT_INACTIVE_GREEN;
  inactiveColor.blue = DEFAULT_INACTIVE_BLUE;

  activeColor.red = DEFAULT_ACTIVE_RED;
  activeColor.green = DEFAULT_ACTIVE_GREEN;
  activeColor.blue = DEFAULT_ACTIVE_BLUE;

  
  // Instantiate the buttons
  uint16_t intColorInactive = inactiveColor.convertColor();
  uint16_t intColorActive = activeColor.convertColor();
  power = Button(POWER_X, POWER_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "POWER", intColorInactive, intColorActive, &tft);
  channelUp = Button(CHANNEL_UP_X, CHANNEL_UP_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "UP", intColorInactive, intColorActive, &tft);
  channelDown = Button(CHANNEL_DOWN_X, CHANNEL_DOWN_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "DOWN", intColorInactive, intColorActive, &tft);
  volumeUp = Button(VOLUME_UP_X, VOLUME_UP_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "UP", intColorInactive, intColorActive, &tft);
  volumeDown = Button(VOLUME_DOWN_X, VOLUME_DOWN_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "DOWN", intColorInactive, intColorActive, &tft);

  wasTouched = false;
  lastButton = nullptr;
  
  return;
}

/*******************************************************************************
 * Function: draw
 * Return Value: n/a
 * Description: Initializes the screen and draws the remote control on the screen.
 *               This should be called only in the setup() function of the sketch.
  ******************************************************************************/
void RemoteControl::draw()
{
  tft.begin();
  
  if (!ts.begin(40))
  {
    Serial.println("Unable to start touchscreen.");
  }
  else
  {
    Serial.println("Touchscreen started.");
  }

  
  // Fill the background of the screen and set the text settings
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  
  // Draw the buttons
  power.drawButton();
  channelUp.drawButton();
  channelDown.drawButton();
  volumeUp.drawButton();
  volumeDown.drawButton();

  // Draw the labels above the channel and volume buttons
  tft.setCursor(VOLUME_UP_X, VOLUME_UP_Y - 20);
  tft.println("Volume");
  tft.setCursor(CHANNEL_UP_X, CHANNEL_UP_Y - 20);
  tft.println("Channel");
}


/*******************************************************************************
 * Function: loop
 * Return Value: n/a
 * Description: Loops through repeatedly to see if the user has pushed a button
 *              and handles the necessary interaction like sending signals and
 *              changing the display.
 *              
 * Note: The buttons do not currently send any signals--that will be added later
  ******************************************************************************/
void RemoteControl::loop()
{
  // See if the screen has been touched
  bool currentTouch = ts.touched();

  if ((currentTouch && !wasTouched) || (!currentTouch && wasTouched))
  {
    // Get the location of the spot that was pushed
    TS_Point p = ts.getPoint();
    p.x = tft.width() - p.x;
    p.y = tft.height() - p.y;


    // See if the user just released a button
    if (!currentTouch && wasTouched)
    {
      if (lastButton != nullptr)
      {
        lastButton->flipColor();
      }
      wasTouched = false;
      return;
    }

    // Check to see what button was pushed
    if (power.inButton(p.x, p.y))
    {
      power.flipColor();
      lastButton = &power;
      delay(BUTTON_DELAY);
    }
    else if (channelUp.inButton(p.x, p.y))
    {
      channelUp.flipColor();
      lastButton = &channelUp;
      delay(BUTTON_DELAY);
    }
    else if (channelDown.inButton(p.x, p.y))
    {
      channelDown.flipColor();
      lastButton = &channelDown;
      delay(BUTTON_DELAY);
    }
    else if (volumeUp.inButton(p.x, p.y))
    {
      volumeUp.flipColor();
      lastButton = &volumeUp;
      delay(BUTTON_DELAY);
    }
    else if (volumeDown.inButton(p.x, p.y))
    {
      volumeDown.flipColor();
      lastButton = &volumeDown;
      delay(BUTTON_DELAY);
    }
    else
    {
      Serial.println("here");
      lastButton = nullptr;
    }

    wasTouched = true;
  }
    
  return;
}

