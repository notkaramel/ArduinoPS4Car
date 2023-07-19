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
// Motor A
#define ENA 9;
#define IN1 8;
#define IN2 7;
// MotorB
#define ENB 3;
#define IN3 5;
#define IN4 4;

void setup()
{
    Serial.begin(SERIAL_BAUD);
    Serial.println("Starting on " + String(SERIAL_BAUD) + " baud");

    // Init(): "Returns 0 if success, -1 if not"
    while (Usb.Init() == -1) // while not sucsessful
    {
        Serial.println("OSC did not start. Retrying in 1 second...");
        delay(1000);
    }

    Serial.println("Setup complete");
    
    // USB init() until established a connection
    
    Usb.Task();
}

void getHatsCoordinates()
{
    /**
     * @brief Log the hats' coordinates
     */
    uint8_t LeftX = PS4.getAnalogHat(LeftHatX);
    uint8_t LeftY = PS4.getAnalogHat(LeftHatY);

    uint8_t RightX = PS4.getAnalogHat(RightHatX);
    uint8_t RightY = PS4.getAnalogHat(RightHatY);

    boolean hasMovement = (LeftX > 137 || LeftX < 117 || LeftY > 137 || LeftY < 117 || RightX > 137 || RightX < 117 || RightY > 137 || RightY < 117);
    // Left Hat (Left Joystick)
    if (hasMovement)
    {
        Serial.print("LeftJoy: ");
        Serial.print("X: ");
        Serial.print(LeftX);
        Serial.print("| Y: ");
        Serial.print(LeftY);
        Serial.print("\t");

        // Right Hat (Right Joystick)
        Serial.print("RightJoy: ");
        Serial.print("X: ");
        Serial.print(RightX);
        Serial.print("| Y: ");
        Serial.print(RightY);
        Serial.println();
    }
}

void getHatsCoordinates(uint16_t delayTime)
{
    /**
     * @brief Log the hats' coordinates with a delay in between
     * @param delayTime: delay in milliseconds
     */
    getHatsCoordinates();
    delay(delayTime);
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

    if (PS4.connected())
    {
        setRumble(1, 1000);
    }
}
