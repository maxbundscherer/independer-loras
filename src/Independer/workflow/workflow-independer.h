//Crypt Config
char * c_cipher_key = "kjew50fkjriowej6";

//Send Config
#define BAND 868E6 //you can set band here directly,e.g. 868E6 915E6 433E6
#define LORA_SYNC_WORD 0xF3
#define LORA_SIG_BANDWIDTH 125E3 //250E3 //125E3 is default
#define LORA_SPREAD 9 //12 //7 is default

//Keyboard Power Pin
#define KEYBOARD_POWER_PIN 13

//Boot State
RTC_DATA_ATTR int boot_state_count = 0;
#define BOOT_STATE_MSG_COUNT 20
RTC_DATA_ATTR char boot_state_msg[BOOT_STATE_MSG_COUNT] = "Boot-Msg ";

/**
 * 
 * @return boolean isFirstBoot
 */
boolean workflow_independer_init(boolean isActor, String productVersion, boolean isDevMode) {

  //Init before serial is ready
  if(isActor) {
    pinMode(KEYBOARD_POWER_PIN, OUTPUT);
    digitalWrite(KEYBOARD_POWER_PIN, HIGH);
  }

  Heltec.begin(true /*DisplayEnable Enable*/ , true /*Heltec.Heltec.Heltec.LoRa Disable*/ , true /*Serial Enable*/ , true /*PABOOST Enable*/ , BAND /*long BAND*/ );

  Serial.println();
  Serial.println("[Start Independer " + productVersion + "] Actor-Mode=" + String(isActor) + " Dev-Mode=" + String(isDevMode));

  if(isDevMode) {
    Serial.println("- Init Dev Mode");
    state_lora_gain = 1;
  }

  Serial.println("- Init Display");
  Heltec.display -> init();
  Heltec.display -> setBrightness(boot_state_oled_brightness);
  //Heltec.display -> flipScreenVertically();

  Serial.println("- Init Cipher");
  crypt_init_cipher(c_cipher_key);

  Serial.println("- Init LoRa");
  LoRa.setSyncWord(LORA_SYNC_WORD);
  LoRa.setSpreadingFactor(LORA_SPREAD);
  LoRa.setSignalBandwidth(LORA_SIG_BANDWIDTH);

  Serial.println("- Init Battery Meas");
  //utils_init_battery_meas();
  Serial.println("First Meas " + String(utils_get_battery()) + " mV");

  Serial.println("- Init Low Power Mode");
  rtc_gpio_deinit(GPIO_NUM_0);
  ++boot_state_count;
  Serial.println("Boot number: " + String(boot_state_count));
  String(String(boot_state_msg) + String(boot_state_count)).toCharArray(boot_state_msg, BOOT_STATE_MSG_COUNT);
  Serial.println("Boot msg: " + String(boot_state_msg));

  Serial.println("- Wake up reason");
  utils_print_wakeup_reason();

  Serial.println("[Finished Startup]");
  Serial.println();

  if(boot_state_count == 1) return true;
  else return false;
}