# Puara Module template (module manager)

This repository can be used as a base to create musical controllers compatible with the Puara Framework.

It includes a Wi-Fi manager (set SSID/password for wireless networks), a [OSC](https://en.wikipedia.org/wiki/Open_Sound_Control) manager (set addresses to send OSC messages), setup tools, and [libmapper](http://libmapper.github.io/) compatibility*.

This pseudo-library currently has the following dependencies:

- [libmapper-arduino](https://github.com/puara/libmapper-arduino.git) (cloned from the [original library](https://github.com/mathiasbredholt/libmapper-arduino)).

## How to use

- Install [PlatformIO](https://platformio.org/) ([VSC](https://code.visualstudio.com/) recommended as the code editor)
- [Clone this repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository) locally
- Open the cloned folder as a PlatformIO project using the **Add Existing** button at the Project manager tab.
- You are ready to edit the template.
- Once finished, remember to change the board before uploading your firmware to the ESP32 board. This template is configured to the [TinyPico](https://www.tinypico.com/), but the firmware is compatible with any ESP32-based board.

## More Info on the related [GuitarAMI](https://github.com/Puara/GuitarAMI) and [Puara](https://github.com/Puara) research

[https://www.edumeneses.com](https://www.edumeneses.com)

[http://www-new.idmil.org/project/guitarami/](http://www-new.idmil.org/project/guitarami/)

## Licensing

The code in this project is licensed under the MIT license, unless otherwise specified within the file.
