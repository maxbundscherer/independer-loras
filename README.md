# Independer

This repository is about a device called **Independer**.

The goal is to develop a small **open-source communication gadget** (at the beginning we start with end-to-end encrypted messages) based on LoRa (thus **independent from normal infrastructures** like mobile radio or WIFI).

We use cheap *ESP32s*, *LoRa antennas*, *3D prototyping*, *mini keyboards* and develop our own encrypted *protocol* together with *software*.

The project is still in its initial phase. If you want to **join, or have an idea**, feel free to [write us](mailto:maximilian@bundscherer-online.de) or [start a discussion](https://github.com/maxbundscherer/independer-loras/discussions).

``esp32 - lora - encryption - short-message - protocol - keyboard - 3d-printing - independent``

<img src="docs/images/main.jpeg" width="600"/>

[![shields.io](https://img.shields.io/badge/license-Apache2-blue.svg)](http://www.apache.org/licenses/LICENSE-2.0.txt)

Author: [Maximilian Bundscherer](https://bundscherer-online.de)

## Overview

This repository describes the concept, the project structure, the encrypted LoraS transfer protocol (LoRaS) and the Independer application protocol. There are two type of devices: **Actor** (ID e.g. `0xMB` or `0x02`) with keyboard & accumulator and **Gateway** (ID e.g. `0gMB` or `0g02`) opt. with accumulator.

### Features

- **Actor to Actor (via LoRaS)** communcation: Send messages directly between two Actors.
- **Actor to Gateway (via LoRaS)** communcation: Send messages via a Gateway. Actors can query their messages via a gateway.
- **Actor to Actor (via WIFI/Internet)** communcation: Send messages via a Internet. Actors can query their messages via WIFI/Internet.
- 3D-printed and protoyped case with mini keyboard
- Custom Software and communication protocol LoRaS
- ESP32 with LoRa Antenna and multi-tasking features
- Deep Sleep Mode (battery saving)
- Communication Actor and Gateway test functions
- *Who is in my area?* or *Is available?* functions
- Over-the-Air-Update (update devices through WIFI)
- ...

### Included

- Documentation (`docs/`)
- Sourcecode (`src/`)
- 3D case (`case/`)
- [Releases](https://github.com/maxbundscherer/independer-loras/releases/) 

### Documentation

- [Hardware, Cost Overview, and How-to](docs/hardware.md)
- [Update over WIFI](docs/update.md)
- [Developer Overview](docs/developer.md)
- [LoraS-Protocol](docs/loras-protocol.md)
- [Independer-Protocol](docs/independer-protocol.md)

### Project stages

- [x] Antenna testing and 3D case prototyping
- [x] Crypt baseline implementations
- [x] Device (hardware, gui) baseline implementations
- [x] Gateway and Actor baseline implementations
- [x] Actor to Actor test functions
- [x] Actor to Gateway test functions
- [x] Gateway to Actor test functions
- [x] *Who is in my area?* or *Is available?* functions
- [x] Over-the-Air-Update
- [x] Inbox and outbox Actor to Gateway (via LoRaS) communcation
- [x] Inbox and outbox Actor to Actor (via LoRaS) communcation
- [ ] Inbox and outbox Actor to Actor (via WIFI/Internet) communcation (in progress)
- [ ] Complete docs
- [ ] 3D Case improvements
- [ ] Code Refactoring
- [ ] Deploy (secret keys, actor and gateway releated) configurations
- [ ] Crypt improvements
- [ ] GUI Multilanguage
- [ ] ...

## More pictures

<img src="docs/images/hardware.jpeg" width="600"/>

<img src="docs/images/ui_actor.jpeg" width="600"/>

<img src="docs/images/ui_gateway.jpeg" width="600"/>

<img src="docs/images/cad.png" width="600"/>

Also check out [Awesome/Automatic SDR](https://a-sdr.org/).
