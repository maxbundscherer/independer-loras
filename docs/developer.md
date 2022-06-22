## Developer Documentation

### Code Structure

The application is started through `Independer.ino`. Please set up parameters before compiling. Sourcecodes are located in `src/Independer`.

- `device/`: Baseline LoRaS transmit & receive, Hardware stuff and UI.
- `workflow/`: Baseline workflow and examples for Actor and Gateway.
- `application/`: Baseline Independer application.

### Recommended Steps

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Install [Heltec ESP32 Board](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.5/package_heltec_esp32_index.json) in Arduino IDE.
    - Add additional board-url `https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.5/package_heltec_esp32_index.json`
    - Change Board to `WiFi LoRA 32 (V2)`
3. Run and deploy software with `Upload` in in Arduino IDE. Debug logs are written to serial console.
4. (opt.) Use [Visual Studio Code](https://code.visualstudio.com/) as IDE.
4. (opt.) Use [Clang Format](https://www.dynamsoft.com/codepool/vscode-format-c-code-windows-linux.html) as Visual Studio Code Extension (with vs-code-style).
