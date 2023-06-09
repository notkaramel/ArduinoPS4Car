/*
 The implementation here is based on the example code
 from the USB Host Shield 2.0 library.
 (can also be found in PS4BT_example.ino)

 Authors:
  - Antoine Phan (@notkaramel)
  - Cyril El Feghali (@?)
*/

// importing the libraries
#include <PS4BT.h>
#include <usbhub.h>

// creating the USB object for the Bluetooth dongle
USB Usb;
// BTD: Bluetooth Dongle Object
BTD BluetoothController(&Usb);

PS4BT PS4(&BluetoothController, PAIR);

// Defining constants
#define SERIAL_BAUD 2400


void setup()
{
    Serial.begin(SERIAL_BAUD);
    Serial.println("Starting on" + String(SERIAL_BAUD) + " baud");

    while (Usb.Init() != -1) // ??
    {
        Serial.println("OSC did not start"); 
    }

    Serial.println("\r\nPS4 Bluetooth Library Started");
}

void logHatCoordinate()
{
    // Left Hat (Left Joystick)
    Serial.println("-- Joystick --");
    Serial.print("| Left Joystick:");
    Serial.print("X: ");
    Serial.print(PS4.getAnalogHat(LeftHatX));
    Serial.print(" -- ");
    Serial.print("Y: ");
    Serial.print(PS4.getAnalogHat(LeftHatY));
    Serial.print("\r"); // ?

    // Right Hat (Right Joystick)
    Serial.print("\t| Right Joystick:");
    Serial.print("X: ");
    Serial.print(PS4.getAnalogHat(RightHatX));
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(PS4.getAnalogHat(RightHatY));
    Serial.print("|\r");
}

void disconnectController()
{
    Serial.println("Controller disconnected");
    PS4.disconnect();
}

void setRumble(int level)
{
    /**
     * @brief Set rumble (vibration) of the controller
     * @param level: 0 (stop), 1 (weak), 2 (strong)
     * NOTE: see setRumbleOn() in PS4Parser.h
     */
    if (level == 0)
    {
        PS4.setRumbleOff();
    }
    else if (level == 1)
    {
        PS4.setRumbleOn(RumbleLow);
    }
    else if (level == 2)
    {
        PS4.setRumbleOn(RumbleHigh);
    }
}

void setRumble(int level, int duration)
{
    /**
     * @brief Set rumble (vibration) of the controller
     * @param level: 0 (stop), 1 (weak), 2 (strong)
     * @param duration: duration in milliseconds
     */
    setRumble(level);
    delay(duration);
}

void setLED_Color(ColorsEnum color)
{
    /**
     * @brief Set the color of the LED
     * @param color: color of the LED
     * OPTIONS: Red, Green, Blue, Yellow, Lightblue, Purple, White, Off
     */
    PS4.setLed(color);
}


void setLED_RGB(uint8_t r, uint8_t g, uint8_t b)
{
    /**
     * @brief Set the color of the LED
     * @param r: red channel (0-255)
     * @param g: green channel (0-255)
     * @param b: blue channel (0-255)
     * NOTE: see setLed() in PS4Parser.h
     */
    PS4.setLed(r, g, b);
}

void setLED_Flashing(uint16_t period, unsigned int duration)
{
    /**
     * @brief Set the LED to flash
     * @param period: period of flashing in milliseconds
     * @param duration: duration of flashing in milliseconds
     * NOTE: see setLedFlash() in PS4Parser.h
     */
    PS4.setLedFlash(period, period);
    delay(duration);
}

void loop()
{
    Usb.Task(); // Check current state of the connection

    if (PS4.connected())
    {
        // do stuffs
        logHatCoordinate();
    }
}

