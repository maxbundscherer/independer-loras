## Deprecated

### Install (Deprecated - Arduino IDE)

#### Recommended Steps (Heltec Board) Deprecated

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Install Heltec ESP32 Board in Arduino IDE.
    - Add additional board-url `https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.5/package_heltec_esp32_index.json`
    - Change Board to `WiFi LoRA 32 (V2)`

#### Recommended Steps (LILYGO TTGO Board) Deprecated

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Install ESP32 Board in Arduino IDE.
    - Add additional board-url `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
    - Change Board to `TTGO LoRa32-OLED`
    - Change Board Revision to `TTGO LoRa32 V.2.1 (1.6.1)` (only TTGO Board)
3. Install [ESP8266 and ESP32 OLED driver for SSD1306 displays](https://github.com/ThingPulse/esp8266-oled-ssd1306)
4. Install [LoRa](https://github.com/sandeepmistry/arduino-LoRa)

#### Future Steps (all Boards) Deprecated

1. (opt.) macOs Bugfix: Change Port to `*usbserial*` not `*usbmodem*`. Maybe install [custom driver](https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800/issues/139) ([download](https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800/files/7037260/CH9102_Mac_Driver.zip)).
2. Install [ArduinoOTA Library](https://www.arduino.cc/reference/en/libraries/arduinoota/)
3. Run and deploy software with `Upload` in in Arduino IDE. Debug logs are written to serial console.
4. (opt.) Use [Visual Studio Code](https://code.visualstudio.com/) as IDE.
5. (opt.) Use [Clang Format](https://www.dynamsoft.com/codepool/vscode-format-c-code-windows-linux.html) as Visual Studio Code Extension (with vs-code-style).

#### Sadly dont work - not recommend (Heltec and TTGO both) Deprecated

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Install ESP32 Board in Arduino IDE.
    - Add additional board-url `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
    - Change Board to `Heltec WiFi LoRa 32(V2)`
