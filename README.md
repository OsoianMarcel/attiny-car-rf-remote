# Car Garage Door Remote (RF 433 Mhz)

A device designed for controlling the remote garage doors (433Mhz). It can be powered and controlled from 7 to 30 volts which make it perfect for integrating and using in the cars.

## Features

* Wide power supply range: from 7V to 30V;
* The consumption: 9mA during idle, 20mA during transmission;
* The input pin accepts a wide range of voltage: from 3.3V to 30V;
* Overcurrent protection and reverse current protection;
* Transmission indicator (red led);
* JTAG pins (3x2) used for programming the microcontroller;
* 5V power pins (max current: 50mA), for supplying low current device;
* The device uses one the most popular RF 433MHz Transmitter (cheap and very popular).

## Hardware images

<img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/images/pcb-preview-top.png?raw=true" width="45%"></img> <img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/images/pcb-preview-bottom.png?raw=true" width="45%"></img> 

<img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/images/pcb-case-open-top.png?raw=true" width="23%"></img> <img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/images/pcb-case-open-angle.png?raw=true" width="23%"></img> <img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/images/pcb-case-closed-top.png?raw=true" width="23%"></img> <img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/images/pcb-case-closed-angle.png?raw=true" width="23%"></img> 

![PCB schematic V0.1](https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/pcb/schematic-v0.1.png?raw=true)

<img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/photos/assembled-pcb.webp?raw=true" width="23%"></img> <img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/photos/enclosure-open.webp?raw=true" width="23%"></img> <img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/photos/enclosure-and-lead.webp?raw=true" width="23%"></img> <img src="https://github.com/OsoianMarcel/attiny-car-rf-remote/blob/main/hdw/photos/enclosure-closed.webp?raw=true" width="23%"></img> 

## How it works 

The device is powered and controlled via the connector J1, where the pin 1 (top, left) is GND,  pin 2 is VCC, and pin 3 is the input pin. The input pin (3) is expected to be connected to a car button (which usually supply ~12v during pressing). Once the device is triggered via the input pin (high level signal), the device will send the RF signal repeatedly (number of reapeats are defined in the code). Each time the sending is triggered the signal will be different (the radio signals are defined in the code). 

The device does not have a RF receiver, so it can not scan/copy a RF signal from an existing remote, so you need to do the reverse engineering of the RF signal and to add it manually in the code.
If the device will get popularity, I’ll add this feature in the next versions.

## Precautions 

* The device is not designed to be powered from the 5V connector (J4). The 5V connector was added to PCB mostly for debugging purposes, but it can also be used for powering a low power device with maximum current of 50mA (the higher current may overheat the voltage regulator).
 * You can try to power the device via 5V connector but you risk to damage the voltage regulator because of reverse current (OUT -> IN). For more information check the Datasheet of LM7805 (section: Application and Implementation).
* During programming the MCU, power the device via J1 connector and disconnect the 5v pin from the programmer (JTAG). I tested to power and program the device from JTAG and all went ok, it's up to you.
* In the current PCB version, the MCU sleep mode can not be implemented, because the pin INT0 is triggered with high level signal, which can not wake up the MCU (attiny85) from sleep mode (check the datasheet about low level interrupt on INT0). 
* While idle, the device consumes 9mA, which may be too much for some car batteries, so to exclude the risk of draining the battery, the device has to be powered from ACC power line (the power is provided only then the ignition/engine is on).

## Possible improvements

* Add a diode between OUT and IN pins of LM78L05, to protect it from damaging by reverse current (to exclude the risk of damaging during powering from 5V connector or JTAG connector).
* Power the radio transmitter module with 12V (not 5V) to improve the range of radio signal.
* Solder an antenna to the radio module.
* Trigger the input pin by ground, which will reduce the number of componentes on PCB and also will make possible to put the MCU in sleep mode and wake it up by low level signal, which will reduce the power consumption significantly.
* Use smaller SMD components to reduce the PCB size (1206 -> 0805).
* Move the fuse component in another PCB place or use a SMD fuse holder, to simplify the replacing.
* Design a nicer PCB layout.

## Give a Star⭐

If you find this repository useful, please give it a star to show your support for this project. 😊

## License

All contents of this repository are licensed under the [MIT license].

[MIT license]: LICENSE