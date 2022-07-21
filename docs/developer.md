## Developer Documentation

### Code Structure

The application is started through `Independer.ino`. Please set up parameters before compiling. Sourcecodes are located in `src/Independer`.

- `device/`: Baseline LoRaS transmit & receive, Hardware stuff and UI.
- `workflow/`: Baseline workflow and examples for Actor and Gateway.
- `application/`: Baseline Independer application.

### Install

#### Recommended Steps (Heltec Board)

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Install [Heltec ESP32 Board](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.5/package_heltec_esp32_index.json) in Arduino IDE.
    - Add additional board-url `https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.5/package_heltec_esp32_index.json`
    - Change Board to `WiFi LoRA 32 (V2)`

#### Recommended Steps (LILYGO TTGO Board)

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Install ESP32 Board in Arduino IDE.
    - Add additional board-url `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
    - Change Board to `TTGO LoRa32-OLED`
    - Change Board Revision to `TTGO LoRa32 V.2.1 (1.6.1)` (only TTGO Board)

#### Future Steps (all Boards)

1. (opt.) macOs Bugfix: Change Port to `*usbserial*` not `*usbmodem*`. Maybe install [custom driver](https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800/issues/139) ([download](https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800/files/7037260/CH9102_Mac_Driver.zip)).
2. Install [ArduinoOTA Library](https://www.arduino.cc/reference/en/libraries/arduinoota/)
3. Install [ESP8266 and ESP32 OLED driver for SSD1306 displays](https://github.com/ThingPulse/esp8266-oled-ssd1306)
4. Install [LoRa](https://github.com/sandeepmistry/arduino-LoRa)
5. Run and deploy software with `Upload` in in Arduino IDE. Debug logs are written to serial console.
6. (opt.) Use [Visual Studio Code](https://code.visualstudio.com/) as IDE.
7. (opt.) Use [Clang Format](https://www.dynamsoft.com/codepool/vscode-format-c-code-windows-linux.html) as Visual Studio Code Extension (with vs-code-style).

#### Sadly dont work - not recommend (Heltec and TTGO both)

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Install ESP32 Board in Arduino IDE.
    - Add additional board-url `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
    - Change Board to `Heltec WiFi LoRa 32(V2)`

### Upload code via WIFI

- Run ``Export compiled Binary`` in Arduino IDE.
- Upload ``.bin`` file via webbrowser (see update-doc).

### Additional Information

- [Heltec LoRa API](https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/lora/API.md)
- [Heltec API](https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/src/oled/API.md)