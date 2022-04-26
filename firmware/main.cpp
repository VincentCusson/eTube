/*
 * This code programs a number of pins on an ESP32 as buttons on a BLE gamepad
 * 
 * It uses arrays to cut down on code
 *
 * Before using, adjust the numOfButtons, buttonPins and physicalButtons to suit your senario
 *
 */
 
#include <Arduino.h>
#include <BleGamepad.h> // https://github.com/lemmingDev/ESP32-BLE-Gamepad

BleGamepad bleGamepad("eTube","Vincent Cusson",90);

#define numOfButtons 2

byte previousButtonStates[numOfButtons];
byte currentButtonStates[numOfButtons];
byte buttonPins[numOfButtons] = { 21, 19 };
byte physicalButtons[numOfButtons] = { 1, 2 };

void setup()
{
  for (byte currentPinIndex = 0 ; currentPinIndex < numOfButtons ; currentPinIndex++)
  {
    pinMode(buttonPins[currentPinIndex], INPUT_PULLUP);
    previousButtonStates[currentPinIndex] = HIGH;
    currentButtonStates[currentPinIndex] =  HIGH;
  }

  bleGamepad.begin(numOfButtons);
  bleGamepad.setAutoReport(false);
}

void loop()
{
  if(bleGamepad.isConnected())
  {
    for (byte currentIndex = 0 ; currentIndex < numOfButtons ; currentIndex++)
    {
      currentButtonStates[currentIndex]  = digitalRead(buttonPins[currentIndex]);

      if (currentButtonStates[currentIndex] != previousButtonStates[currentIndex])
      {
        if(currentButtonStates[currentIndex] == LOW)
        {
          bleGamepad.press(physicalButtons[currentIndex]);
        }
        else
        {
          bleGamepad.release(physicalButtons[currentIndex]);
        }
      } 
    }
    
    if (currentButtonStates != previousButtonStates)
    {
      for (byte currentIndex = 0 ; currentIndex < numOfButtons ; currentIndex++)
      {
        previousButtonStates[currentIndex] = currentButtonStates[currentIndex]; 
      }
      
      bleGamepad.sendReport();
    }
    
    delay(20);
  }
}