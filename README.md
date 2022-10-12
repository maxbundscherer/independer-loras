# Independer

This repository is about a device called **Independer**. An Open-Source Project.

**Encrypted messaging & data sharing** via LoRaS & inexpensive hardware (ESP32). **Independent from mobile network & WIFI**. We use cheap *ESP32s*, *LoRa antennas*, *3D prototyping*, *mini keyboards* and develop our own encrypted *protocol* together with *software*.

**This page is intended for developers** - please visit the [official website](https://a-sdr.org/independer) for more information. If you want to **join, or have an idea**, feel free to [write us](mailto:maximilian@bundscherer-online.de) or [start a discussion](https://github.com/maxbundscherer/independer-loras/discussions). The current state of development can be viewed on the [project board](https://github.com/maxbundscherer/independer-loras/projects/2).

Presentation             |  Prototype-Video
:-------------------------:|:-------------------------:
<a href="http://a-sdr.org/independer/independer.pdf" target="_blank"><img src="docs/images/openpdf.png" style="max-height:250px" /></a> | <a href="https://www.youtube.com/watch?v=-8pI4nHZv2M" target="_blank"><img src="docs/images/play.png" style="max-height:250px"/></a>

``esp32 - lora - encryption - short-message - protocol - keyboard - platformio - 3d-printing - independent``

[![shields.io](https://img.shields.io/badge/license-Apache2-blue.svg)](http://www.apache.org/licenses/LICENSE-2.0.txt)

Maintainer: [Maximilian Bundscherer](https://bundscherer-online.de)

## Overview

This repository describes the concept, the project structure, the encrypted LoraS transfer protocol (LoRaS) and the Independer application protocol. There are two type of devices: **Actor** (ID e.g. `0x01` or `0x02`) with keyboard & accumulator and **Gateway** (ID e.g. `0g01` or `0g02`) opt. with accumulator.

### Features

- **Actor to Actor (via LoRaS)**: Send messages directly between two Actors.
- **Actor to Gateway (via LoRaS)**: Send messages via Gateway. Actors can query their messages from Gateways.
- **Actor to Actor (via WIFI/Internet)**: Send messages via Internet. Actors can query their messages from WIFI/Internet.
- **Who is near me?** Scan the environment to find other Independers.
- **Many other functions**: Various test functions (Reachability Check, Reception & Transmission Evaluation), Update via WIFI, Notification LED, Deep Sleep Mode, Background-Sync, Battery Status, Send Quota & Gain, NTP-Time-Sync, Auto-Sync, Auto-Sleep, Contacts...

### Specifications

- Built on inexpensive Hardware
- Open-Source Software & Protocol
- Open-Source 3D-printed Case
- Multiple ESP32-Boards Supported
- OLED-Screen
- LoRa & WIFI
- External Antenna Connector
- Mini Keyboard (QWERTY)
- 3000mAh LiPo Battery
- USB Charging (Micro-USB)

### Open-Source Project

Anyone can **contribute to the project** and **build their own device**. Many more features like GPS visualization, environment scanner, touch screen, alternative transmission and encryption functions are waiting **in the future**!

### Included

- [Website](https://a-sdr.org/independer)
- [Documentation](docs/)
- [Sourcecode Independer ESP32 (C/C++)](independer-app/)
- [Sourcecode Independer Server (Python Flask Application)](independer-server/)
- [Docker Image Independer Server for Linux & Raspberry Pi](independer-server/)
- [3D-printed Case](case/)
- [Releases](https://github.com/maxbundscherer/independer-loras/releases/)

### Documentation

- [Hardware, Cost Overview, and How-to](docs/hardware.md)
- [Antenna Measurements](docs/antenna-measurements.md)
- [Update over WIFI](docs/update.md)
- [Developer Overview](docs/developer.md)
- [LoraS-Protocol](docs/loras-protocol.md)
- [Independer-Protocol](docs/independer-protocol.md)
- [Server-Protocol](docs/server-protocol.md)

The current state of development can be viewed on the [project board](https://github.com/maxbundscherer/independer-loras/projects/2).

## More pictures

### Devices

<img src="docs/images/main.jpeg" width="600"/>

<img src="docs/images/hardware.jpeg" width="600"/>

<img src="docs/images/new_board.jpeg" width="600"/>

### 3D Printing

<img src="docs/images/cad.png" width="600"/>

<img src="docs/images/print.png" width="600"/>

<img src="docs/images/print-case.png" width="600"/>

### UI

<img src="docs/images/ui_actor.jpeg" width="600"/>

<img src="docs/images/ui_gateway.jpeg" width="600"/>

## Other

Also check out [Awesome/Automatic SDR](https://a-sdr.org/).
