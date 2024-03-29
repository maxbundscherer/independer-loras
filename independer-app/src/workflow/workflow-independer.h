// Crypt Config
char *c_cipher_key = "kjew50fkjriowdj6";

// Send Config

#define PROP_868 1
#define PROP_915 2

#if FBAND == PROP_868
#define BAND 868E6                         // you can set band here directly,e.g. 868E6 915E6 433E6
#elif FBAND == PROP_915
#define BAND 915E6                         // you can set band here directly,e.g. 868E6 915E6 433E6
#endif

#define LORA_SYNC_WORD_REG 0x35            // 0x34 is default
#define LORA_SYNC_WORD_NOT_REG 0x34        // 0x34 is default
#define LORA_SIG_BANDWIDTH 125E3           // 125E3 is default - 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3, 41.7E3, 62.5E3, 125E3, and 250E3
#define LORA_SPREAD 12                     // 7 is default - between 6 and 12
#define LORA_SIG_CODING_RATE_DENOMINATOR 5 // 5 is default - Supported values are between 5 and 8, these correspond to coding rates of 4/5 and 4/8. The coding rate numerator is fixed at 4

// Keyboard Power Pin
#define KEYBOARD_POWER_PIN 13

// Boot State
RTC_DATA_ATTR int boot_state_count = 0;

RTC_DATA_ATTR char boot_state_auto_sync_msg[500];

void i_workflow_independer_auto_sync()
{
  String ans = wifi_auto_sync(state_my_id, state_wifi_server_url, state_wifi_server_port, state_wifi_server_timeout, state_wifi_server_device_token, boot_state_count);
  if (ans != "")
  {
    strcpy(boot_state_auto_sync_msg, ans.c_str());
  }
}

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

  Serial.println("- Set Language");
  i18n_display_lang();

  Serial.println("- Init Display");
  gui_init_display();

  Serial.println("- Init Cipher");
  crypt_init_cipher(c_cipher_key);

  Serial.println("- Init Battery Meas");
  utils_init_battery_meas();
  Serial.println("First Meas " + String(utils_get_battery()) + " mV");

  Serial.println("- Init Low Power Mode");
  rtc_gpio_deinit(GPIO_NUM_0);
  ++boot_state_count;
  Serial.println("Boot number: " + String(boot_state_count));

  Serial.println("- Init LoRa");
  lora_init();
  LoRa.setSyncWord(LORA_SYNC_WORD_REG);
  LoRa.setSpreadingFactor(LORA_SPREAD);
  LoRa.setSignalBandwidth(LORA_SIG_BANDWIDTH);
  LoRa.setCodingRate4(LORA_SIG_CODING_RATE_DENOMINATOR);

  Serial.println("- Init Database");
  db_init(isActor, isDevMode);
  display.setBrightness(state_oled_brightness); // Set brightness after db
  
  Serial.println("- Check Is Registered");
  Serial.println("Is Registered: " + String(state_is_registered_independer));

  Serial.println("- LORA Sync Word");

  if (!state_is_registered_independer)
  {
    Serial.println("Set to non register syncWord");
    LoRa.setSyncWord(LORA_SYNC_WORD_NOT_REG);
  }

  Serial.println("- Init LoRa Dev");

  if (isDevMode)
  {
    Serial.println("- Init Dev Mode");
    state_lora_gain = 6;

    Serial.println("- Dev Mode Output");
    time_debug_console_output();
  }

  Serial.println("- Wake up reason and sync");
  if (utils_wakeup_reason_and_sync_flag())
  {
    if (isActor)
    {
      if (state_is_registered_independer)
      {
        i_workflow_independer_auto_sync();
      }
      utils_go_to_sleep(true && state_is_registered_independer);
    }
  }
  else
  {
    if (String(boot_state_auto_sync_msg) != "")
    {
      gui_msg_long_text(I18N_ACTOR_AUTO_SYNC_BOOT_TITLE, String(boot_state_auto_sync_msg));
      strcpy(boot_state_auto_sync_msg, String("").c_str());
    }
  }

  Serial.println("[Finished Startup]");
  Serial.println();

  if (boot_state_count == 1)
    return true;
  else
    return false;
}