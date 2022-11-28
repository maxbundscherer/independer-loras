## Developer Documentation

### Code Structure

The application is started through [PlatformIO](https://platformio.org/). Please set up parameters before compiling. Sourcecodes are located in `independer-app/src`.

- `device/`: Baseline LoRaS transmit & receive, Hardware stuff and UI.
- `workflow/`: Baseline workflow and examples for Actor and Gateway.
- `application/`: Baseline Independer application.

### Environments

- Environment label describes board-type (e.g. Heltec or TTGO), contains developer flag (release or developer) and contains device-mode (actor or gateway).

#### Build and upload (single device)

- Select your specific PlatformIO-Enviroment.
- Run Task `Clean`
- Run Task `Build`
- Run Task `Upload`

#### Complete (all devices and all modes)

- Select no PlatformIO-Enviroment (global).
- Run Task `Clean`
- Run Task `Build`
- Run Script `independer-app/package.sh`
- View files in `independer-app/export/`

##### After Release (Release Workflow)

- Run previous steps.
- Merge `develop` into `master`.
- Create new release on GitHub (with files in `independer-app/export`).
- (Opt.) update Independer-Server.
- Increment Version in Independer-Server SQL-Table.
- Announcement new release (Signal, Facebook, Website, Product Presentation, GitHub)

### Upload code via WIFI

- See steps above.
- Upload ``independer-app/.pio/build/<BUILD-TYPE>/firmware.bin`` file via webbrowser (see update-doc).

### Additional Information

- [LoRa API](https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md)
- [Heltec LoRa API](https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/lora/API.md)
- [Heltec API](https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/oled/API.md)
