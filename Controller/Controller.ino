/*
 The implementation here is based on the example code
 from the USB Host Shield 2.0 library.
 (can also be found in PS4BT_example.ino)

 Authors:
  - Antoine Phan (@notkaramel)
  - Cyril El Feghali (@CyrilMyril)
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
uint8_t ENA = 9;
uint8_t IN1 = 8;
uint8_t IN2 = 7;
// MotorB
uint8_t ENB = 3;
uint8_t IN3 = 5;
uint8_t IN4 = 4;

int *LeftHatCoordinates = new int[2];
int *RightHatCoordinates = new int[2];

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

    // Setting up the motors
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);    
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

int getBatteryLevel()
{
    /**
     * @brief Get the battery level of the controller
     * @return battery level in percent
     */
    return PS4.getBatteryLevel();
}

void pressBreak()
{
    /**
     * @brief Press the break
     */
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}

int getAcceleration()
{
    /**
     * @brief Accelerate the car via right analog trigger
     * @return acceleration as int
     */
    return PS4.getAnalogButton(R2);
}

int getDeceleration()
{
    /**
     * @brief Decelerate the car via left analog trigger
     * @return deceleration as int
     */
    return PS4.getAnalogButton(L2);
}

int getDirection()
{
    /**
     * @brief Get the direction of the car via left analog stick
     * @return direction as int.
     * The magnitude of the value is the strength of the turn.
     */
    return PS4.getAnalogHat(LeftHatX);
}

void go(int speed, int direction)
{
    /**
     * @brief Go straight
     * @param speed: speed of the motors (0-255)
     * @param direction: direction of the car (0-255 | left-right)
     * 0    -   120: left
     * 121  -   132: straight
     * 133  -   255: right
     */

    int leftSpeed, rightSpeed;
    if (direction < 120)
    {
        leftSpeed = speed;
        rightSpeed = speed * (direction / 120);
    }
    else if (direction > 133)
    {
        leftSpeed = speed * ((255 - direction) / 133);
        rightSpeed = speed;
    }
    else
    {
        leftSpeed = speed;
        rightSpeed = speed;
    }

    // Assuming A is left and B is right
    // Set analog speed
    analogWrite(ENA, leftSpeed);
    analogWrite(ENB, rightSpeed);
    
    // digitalWrite(IN1, HIGH);
    // digitalWrite(IN2, LOW);

    // digitalWrite(IN3, HIGH);
    // digitalWrite(IN4, LOW);
}

void loop()
{
    Usb.Task();

    if (PS4.connected())
    {
        go(getAcceleration(), getDirection());

        if(PS4.getButtonPress(PS))
        {
            if(PS4.getButtonPress(SELECT))
            {
                disconnectController();
            }
            if(PS4.getButtonPress(UP))
            {
                setLED_Color(White);
            }
            else if(PS4.getButtonPress(RIGHT))
            {
                setLED_Color(Red);
            }
            else if(PS4.getButtonPress(DOWN))
            {
                setLED_Color(Blue);
            }
            else if(PS4.getButtonPress(LEFT))
            {
                setLED_Color(Green);
            }
        }
    }
}
