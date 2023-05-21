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
    Serial.println("Left Hat (Left Joystick):");
    Serial.print("X: ");
    Serial.print(PS4.getAnalogHat(LeftHatX));
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(PS4.getAnalogHat(LeftHatY));
    Serial.print("\r\n");

    // Right Hat (Right Joystick)
    Serial.println("Right Hat (Right Joystick):");
    Serial.print("X: ");
    Serial.print(PS4.getAnalogHat(RightHatX));
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(PS4.getAnalogHat(RightHatY));
    Serial.print("\r\n");
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

