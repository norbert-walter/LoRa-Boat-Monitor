## LoRa Boat Monitor

![LoRa Boat Monitor](Pictures/LoRa_Bootsmonitor.png)

Image: LoRa Boat Monitor

The LoRa boat monitor is used to monitor the boat when it is absent. Various measured values are continuously recorded at freely adjustable time intervals and transferred to the [LoRaWAN](https://www.lora-wan.de/) forwarded. The data is from the TTN server ([The Thinks Network](https://thethingsnetwork.org/)) received in Amsterdam and cached and then sent to [Ubidots](https://ubidots.com/) forwarded as a web frontend. The data transmission is secured by encryption up to Ubidots. The measured data is displayed in Ubidots and various notifications can be sent by email when measured values are exceeded.

There are a large number of [LoRa gateways](https://thethingsnetwork.org/map) which can receive the sent measurement data and forward it to the TTN server. Many LoRa gateways are run by private individuals on a non-profit basis. Anyone who wants can operate their own gateway and make it available to the general public. The radio technology uses the license-free frequency range around 868 MHz and uses a special transmission technology (chirp) to achieve large ranges of up to 50 km at low data rates. The ranges depend on the type of transmission, the antenna height and the environment. In built-up areas such as cities, typical ranges of 1… 4 km are possible. In open environments such as lakes and the sea, up to 50 km can be reached. There are no costs for data transmission when sending LoRa telegrams. This is the big difference to other long range transmission technologies like [SIGFOX](https://www.sigfox.com/) and mobile data networks such as 3G / 4G / 5G. If no LoRa gateway is within range, a simple 1-channel or 3-channel LoRa gateway can be set up with the same board. Only a few components are then left out and a different firmware used. Alternatively, the measured values can also be sent directly to Ubidots via WLAN, provided that a WLAN is within range.


![LoRa Data Transmission](Pictures/LoRaWAN_Technology.jpg)

Image: LoRa data transmission Semtech GmbH

![LoRa Data Transmission](Pictures/LoRa_Blockschaltbild.png)

Image: Block diagram LoRa boat monitor

## The LoRa boat monitor has the following functions:

* 10… 32V supply voltage
* 1.2W power consumption
* LoRa transmitter and receiver with OLED display
* 868 MHz, SF7… SF12, 100 mW transmission power
* Dynamic spreeding factor adjustable SF7… FS10
* Supports channel 0...7 dynamic and fix
* Data transfer rate: 0.3 to 50 kbit / s
* Max. Telegram length for user data: 200 bytes
* Range: built-up area 1… 4km, open area up to 50km
* LoRa transmission interval 30s… 2.1h
* One-channel, three-channel and eight-channel modes can be set
* Feeding the data into The Thinks Network (TTN)
* Parameterization of the LoRa boat monitor possible via return channel (channel, SF, transmission interval, relay)
* WLAN (2.4 GHz) for alternative data transmission
* Web interface for operation
* Firmware update possible via WLAN and Internet
* GPS sensor for geographic location coordinates
* BME280 for measuring temperature, humidity and air pressure
* 1x battery voltage measurement (0… 32V service battery)
* 1x potential-free alarm contact eg for bilge and door monitoring
* 2x tank sensors (0 ... 180 Ohm) with percentage display
* Calibratable tank and voltage sensors
* 1x Reais output for potential-free switching of loads with specified time (5min ... 21h) up to 3A (12V or 230V)
* 2x 1Wire connection for temperature sensors DS18B20 for battery monitoring and refrigerator
* Monitoring and alerting via Ubidots web frontend
* Alerting by e-mail if limit values are exceeded via Ubidots
* Automatic data storage for the last 31 days at Ubidots
* Use of cheap embedded modules
* No SMD components on the board and easy to build
* Board can be ordered here:  [https://aisler.net/p/TUFQWBEF](https://aisler.net/p/TUFQWBEF)
* Android app

## How can I use it?


## What is the current status?

I have completed many tasks but still not everything is perfect so far.

- [x] Technical recherche
- [x] Evaluation of function
    - [x] LoRa trasmission tests
    - [x] Accessibility of gateways
    - [x] Measurement of telegram losses 
    - [x] Test spreeding factors
    - [x] Antenna test
    - [x] TTN configuration
    - [x] Ubitots configutarion and restrictions
- [x] Mechanical design
    - [x] 3D parts für Onshape
- [ ] Electronic design
    - [x] Circuit design
    - [x] Board design
    - [ ] Customer sample circuit
- [ ] Software
    - [x] Basic functionality for LoRa
    - [x] LoRa back channel for configuration
    - [x] Dynamic spreedung factor
    - [x] Voltage measurement
    - [x] Tank sensors
    - [x] GPS modul
    - [x] BME280
    - [x] Alarm sensors
    - [x] Relay function
    - [x] JSON
    - [x] Web-Updater
    - [x] Web-Configurator
    - [x] Web server as data display
    - [ ] Ubidots connection via WiFi
    - [ ] NMEA0183 WiFi
    - [ ] NMEA0183 Serial
    - [ ] MQTT
    - [x] Andoid App
    - [x] LoRa gateway firmware
- [x] Components ordering
    - [x] Electronic board
    - [x] Mechanical parts
    - [x] Fittings
- [x] Prototyp creation
    - [x] LoRa boat monitor
    - [x] LoRa gateway
- [ ] Production Zero series
    - [ ] DIY Kits
    - [x] Assembled LoRa boat monitor
- [x] Shipping Zero Series
- [ ] Documentation
    - [x] Documentation and update server on GitLab
    - [ ] Technical description
    - [ ] Construction manual
    - [x] Part list
    - [x] User manual
    - [ ] Data sheet
    - [ ] Flash instructions
- [x] Application tests
    - [x] Temperature 20...40°C
    - [x] LoRa range test (SF7...SF12)
    - [x] WiFi stability test
    - [x] Connection test
    - [x] Long time test
    - [x] User experiences
- [ ] Extensions
    - [ ] Battery current sensor
    - [ ] Actions and alarms depends on events and measuring values
    - [ ] Build a LoRa gateway structure on two towers for the IJsselmeer in Netherlands 
- [ ] Certification
    - [ ] CE Certification


## Questions?

For questions or suggestions please get in contact via email at norbert-walter(at)web.de.

If you like to help or consider this project useful, please donate. Thanks for your support!

![Donate](Pictures/Donate.gif)

[Donate with PayPal](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=5QZJZBM252F2L)
