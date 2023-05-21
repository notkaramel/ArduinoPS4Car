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

void loop()
{
    Usb.Task(); // Check current state of the connection

    if (PS4.connected())
    {
        // do stuffs
        // PS4.getAnalogHat()
    }
}

