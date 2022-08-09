// Crypt Config
char *c_cipher_key = "kjew50fkjriowdj6";

// Send Config
#define BAND 868E6                         // you can set band here directly,e.g. 868E6 915E6 433E6
#define LORA_SYNC_WORD 0x35                // 0x34 is default
#define LORA_SIG_BANDWIDTH 125E3           // 125E3 is default - 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3, 41.7E3, 62.5E3, 125E3, and 250E3
#define LORA_SPREAD 12                     // 7 is default - between 6 and 12
#define LORA_SIG_CODING_RATE_DENOMINATOR 5 // 5 is default - Supported values are between 5 and 8, these correspond to coding rates of 4/5 and 4/8. The coding rate numerator is fixed at 4

// Keyboard Power Pin
#define KEYBOARD_POWER_PIN 13

// Boot State
RTC_DATA_ATTR int boot_state_count = 0;
#define BOOT_STATE_MSG_COUNT 20
RTC_DATA_ATTR char boot_state_msg[BOOT_STATE_MSG_COUNT] = "Boot-Msg ";

/**
 *
 * @return boolean isFirstBoot
 */
boolean workflow_independer_init(boolean isActor, String productVersion, boolean isDevMode)
{

  // Init before serial is ready
  if (isActor or true) // Some Gateways have keyboard too
  {
    pinMode(KEYBOARD_POWER_PIN, OUTPUT);
    digitalWrite(KEYBOARD_POWER_PIN, HIGH);
  }

  Serial.println("- Init Serial");
  Serial.begin(9600);

  Serial.println();
  Serial.println("[Start Independer " + productVersion + "] Actor-Mode=" + String(isActor) + " Dev-Mode=" + String(isDevMode));

  Serial.println("- Init Display");
  gui_init_display();

  Serial.println("- Init Database");
  db_init(isActor, isDevMode);

  display.setBrightness(state_oled_brightness); // Set brightness after db

  Serial.println("- Init LoRa");
  lora_init();

  if (isDevMode)
  {
    Serial.println("- Init Dev Mode");
    state_lora_gain = 6;
  }

  Serial.println("- Init Cipher");
  crypt_init_cipher(c_cipher_key);

  Serial.println("- Init LoRa");
  LoRa.setSyncWord(LORA_SYNC_WORD);
  LoRa.setSpreadingFactor(LORA_SPREAD);
  LoRa.setSignalBandwidth(LORA_SIG_BANDWIDTH);
  LoRa.setCodingRate4(LORA_SIG_CODING_RATE_DENOMINATOR);

  Serial.println("- Init Battery Meas");
  utils_init_battery_meas();
  Serial.println("First Meas " + String(utils_get_battery()) + " mV");

  Serial.println("- Init Low Power Mode");
  rtc_gpio_deinit(GPIO_NUM_0);
  ++boot_state_count;
  Serial.println("Boot number: " + String(boot_state_count));
  // String(String(boot_state_msg) + String(boot_state_count)).toCharArray(boot_state_msg, BOOT_STATE_MSG_COUNT);
  char *boot_state_msg = const_cast<char *>(String(boot_state_count).c_str());
  Serial.println("Boot msg: " + String(boot_state_msg));

  Serial.println("- Wake up reason");
  utils_print_wakeup_reason();

  Serial.println("[Finished Startup]");
  Serial.println();

  if (boot_state_count == 1)
    return true;
  else
    return false;
}