## Developer Documentation

### Code Structure

The application is started through [PlatformIO](https://platformio.org/). Please set up parameters before compiling. Sourcecodes are located in `independer-app/src`.

- `device/`: Baseline LoRaS transmit & receive, Hardware stuff and UI.
- `workflow/`: Baseline workflow and examples for Actor and Gateway.
- `application/`: Baseline Independer application.

### Run Tasks

- Enviroment label describes board-type (e.g. Heltec or TTGO), contains developer flag (release or developer) and contains device-mode (actor or gateway).

### Upload code via WIFI

- Run `Compile`.
- Upload ``independer-app/.pio/build/<BOARD>/firmware.bin`` file via webbrowser (see update-doc).

### Additional Information

- [Heltec LoRa API](https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/lora/API.md)
- [Heltec API](https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/oled/API.md)
