/*
 * This code programs a number of pins on an ESP32 as buttons on a BLE gamepad
 */

#include <Arduino.h>
#include <BleGamepad.h> // https://github.com/lemmingDev/ESP32-BLE-Gamepad

BleGamepad bleGamepad("eTube", "Vincent Cusson", 90);
BleGamepadConfiguration bleGamepadConfig;

#define numOfButtons 2

byte previousButtonStates[numOfButtons];
byte currentButtonStates[numOfButtons];

byte buttonPins[numOfButtons] = { 21, 19 };
byte physicalButtons[numOfButtons] = { 1, 2 };

void setup()
{
  for (byte currentPinIndex = 0; currentPinIndex < numOfButtons; currentPinIndex++)
  {
    pinMode(buttonPins[currentPinIndex], INPUT_PULLUP);
    previousButtonStates[currentPinIndex] = HIGH;
    currentButtonStates[currentPinIndex] = HIGH;
  }

  bleGamepadConfig.setButtonCount(numOfButtons);

  // Optional: disable unused controls for a simple 2-button controller
  bleGamepadConfig.setHatSwitchCount(0);
  bleGamepadConfig.setWhichAxes(false, false, false, false, false, false, false, false);

  // Manual reporting, since this sketch calls sendReport() explicitly
  bleGamepadConfig.setAutoReport(false);

  bleGamepad.begin(&bleGamepadConfig);
}

void loop()
{
  if (bleGamepad.isConnected())
  {
    bool stateChanged = false;

    for (byte currentIndex = 0; currentIndex < numOfButtons; currentIndex++)
    {
      currentButtonStates[currentIndex] = digitalRead(buttonPins[currentIndex]);

      if (currentButtonStates[currentIndex] != previousButtonStates[currentIndex])
      {
        stateChanged = true;

        if (currentButtonStates[currentIndex] == LOW)
        {
          bleGamepad.press(physicalButtons[currentIndex]);
        }
        else
        {
          bleGamepad.release(physicalButtons[currentIndex]);
        }

        previousButtonStates[currentIndex] = currentButtonStates[currentIndex];
      }
    }

    if (stateChanged)
    {
      bleGamepad.sendReport();
    }

    delay(20);
  }
}
