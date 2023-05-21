# Arduino PS4 Car Controller (?)

## Setup
> Here I use Arch Linux, other linux distros may have different package manager. For Windows, idk :)

- Install Arduino IDE, Arduino CLI
```sh
sudo pacman -S arduino arduino-cli
```

- Install Arduino AVR Core (for UNO AVR Boards)
```sh
arduino-cli core install arduino:avr
```
or directly from `pacman`
```sh
sudo pacman -S arduino-avr-core
```

- It was a bit confusing to set up the project directly on VSCode, so I create a folder within the project, use Arduino IDE to create a sketch, and then open the project folder on VSCode
```sh
mkdir ArduinoPS4Car # the *project* folder
cd ArduinoPS4Car
arduino-cli sketch new controller.ino # create a folder named `controller` and a sketch .ino file with the same name
arduino controller/controller.ino # open the sketch on Arduino IDE
```

- Here, the Arduino IDE will automatically configure the project folder, so we can open it on VSCode
```sh
cd ArduinoPS4Car
code .
```
- Make sure user is in `uucp` group
```sh
sudo usermod -aG uucp $USER
# you may have to reboot
```

- Make sure to install the Arduino extension on VSCode
- Install the **board manager** for Arduino UNO
- Install the **library manager** for USB Host Shield 2.0 (search for "PS4")
- Make sure your Arduino UNO is connected to your PC

## Establish Connection
- Can start with the example sketch [**`PS4BT.ino`**](https://raw.githubusercontent.com/felis/USB_Host_Shield_2.0/master/examples/Bluetooth/PS4BT/PS4BT.ino) from the library. It gives a good idea of how to use the library effectively with all the buttons and joysticks.

- Since we're using CSR 4.0 Bluetooth dongle, we have to plug it into the host shield, wait for it to blink, and then hold the `PS` button **AND** the `Share` on the controller (until it starts blinking rapidly) to start connecting. 
  
## Documentation
- [USB Host Shield 2.0 - PS4 Library](https://github.com/felis/USB_Host_Shield_2.0#ps4-library)
- [Arduino CLI](https://arduino.github.io/arduino-cli/latest/)
- [Arduino (archwiki)](https://wiki.archlinux.org/title/arduino)
- [PS4BT Class](https://felis.github.io/USB_Host_Shield_2.0/class_p_s4_b_t.html)
- [PS4Parser Class](https://felis.github.io/USB_Host_Shield_2.0/class_p_s4_parser.html): Getting data/raw value from the controller
- [Controller Enumerations](https://felis.github.io/USB_Host_Shield_2.0/controller_enums_8h.html)