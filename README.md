# Independer

This repository is about a device called **Independer**.

The goal is to develop a small **open-source communication gadget** (at the beginning we start with end-to-end encrypted messaging and data sharing) based on LoRa (thus **independent from normal infrastructures** like mobile network or WIFI).

We use cheap *ESP32s*, *LoRa antennas*, *3D prototyping*, *mini keyboards* and develop our own encrypted *protocol* together with *software*.

The project is still in its development phase. If you want to **join, or have an idea**, feel free to [write us](mailto:maximilian@bundscherer-online.de) or [start a discussion](https://github.com/maxbundscherer/independer-loras/discussions). The current state of development can be viewed on the [project board](https://github.com/maxbundscherer/independer-loras/projects/2).

``esp32 - lora - encryption - short-message - protocol - keyboard - platformio - 3d-printing - independent``

[![](docs/images/play.png)](https://www.youtube.com/watch?v=-8pI4nHZv2M "Click to Watch!")

[![shields.io](https://img.shields.io/badge/license-Apache2-blue.svg)](http://www.apache.org/licenses/LICENSE-2.0.txt)

Author: [Maximilian Bundscherer](https://bundscherer-online.de)

## Overview

This repository describes the concept, the project structure, the encrypted LoraS transfer protocol (LoRaS) and the Independer application protocol. There are two type of devices: **Actor** (ID e.g. `0x01` or `0x02`) with keyboard & accumulator and **Gateway** (ID e.g. `0g01` or `0g02`) opt. with accumulator.

### Features

- **Actor to Actor (via LoRaS)** communcation: Send messages directly between two Actors.
- **Actor to Gateway (via LoRaS)** communcation: Send messages via a Gateway. Actors can query their messages via a gateway.
- **Actor to Actor (via WIFI/Internet)** communcation: Send messages via Internet. Actors can query their messages via WIFI/Internet.
- 3D-printed and protoyped Case with Mini Keyboard
- Custom Software and Communication Protocol LoRaS
- ESP32 with LoRa Antenna and Multi-Tasking Features
- Deep Sleep Mode (battery saving)
- Communication Actor and Gateway Test Functions
- *Who is in my area?* or *Is available?* Functions
- Large Data Test Functions
- Over-the-Air-Update (update devices through WIFI)
- Blinking led if you have new unseen messages
- Persistent storage (settings and messages)
- Python Flask Server included (messages via WIFI/Internet)
- Multiple ESP32 Boards Supported
- ...

### Included

- Documentation (`docs/`)
- Sourcecode Independer ESP32 (C/C++) (`independer-app/`)
- Sourcecode Independer Server (Python Flask Application) (`independer-server/`)
- 3D case (`case/`)
- [Releases](https://github.com/maxbundscherer/independer-loras/releases/)
- [Website](https://a-sdr.org/independer)

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
