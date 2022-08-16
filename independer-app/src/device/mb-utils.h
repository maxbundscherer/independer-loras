#include "driver/rtc_io.h" //Low Power Mode

// Welcome MSG Config
#define C_TEMPLATE_STRING_THX "Danke, dass du dich\nfür den Independer\nentschieden hast!"

void utils_init_battery_meas()
{
  pinMode(21, OUTPUT);
  digitalWrite(21, LOW);
}

int utils_get_battery()
{

  float XS = 0.00225; // The returned reading is multiplied by this XS to get the battery voltage.
  uint16_t MUL = 1000;
  uint16_t MMUL = 100;

  uint16_t c = analogRead(37) * XS * MUL;
  return c;
}

void utils_print_wakeup_reason()
{
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
  case ESP_SLEEP_WAKEUP_EXT0:
    Serial.println("Wakeup caused by external signal using RTC_IO");
    break;
  case ESP_SLEEP_WAKEUP_EXT1:
    Serial.println("Wakeup caused by external signal using RTC_CNTL");
    break;
  case ESP_SLEEP_WAKEUP_TIMER:
    Serial.println("Wakeup caused by timer");
    break;
  case ESP_SLEEP_WAKEUP_TOUCHPAD:
    Serial.println("Wakeup caused by touchpad");
    break;
  case ESP_SLEEP_WAKEUP_ULP:
    Serial.println("Wakeup caused by ULP program");
    break;
  default:
    Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
    break;
  }
}

void utils_go_to_sleep()
{

  Serial.println("Activate sleep mode");
  delay(1000); // is required

  /*
  First we configure the wake up source
  We set our ESP32 to wake up for an external trigger.
  There are two types for ESP32, ext0 and ext1 .
  ext0 uses RTC_IO to wakeup thus requires RTC peripherals
  to be on while ext1 uses RTC Controller so doesnt need
  peripherals to be powered on.
  Note that using internal pullups/pulldowns also requires
  RTC peripherals to be turned on.
  */
  rtc_gpio_pulldown_en(GPIO_NUM_0);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0); // 1 = High, 0 = Low

  // If you were to use ext1, you would use it like
  // esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

  esp_deep_sleep_start();
}

String utils_encode_data(String data)
{
  data.replace("`", "");

  data.replace(":", "`1`");
  data.replace(";", "`2`");
  data.replace("!", "`3`");

  data.replace("[", "`4`");
  data.replace("]", "`5`");

  data.replace("{", "`6`");
  data.replace("}", "`7`");

  data.replace("+", "`8`");
  data.replace("$", "`9`");
  data.replace("%", "`10`");

  data.replace("-", "`11`");
  data.replace("_", "`12`");

  data.replace("\"", "`13`");
  data.replace("'", "`14`");

  data.replace("\\", "`15`");

  return data;
}

String utils_decode_data(String data)
{
  data.replace("`1`", ":");
  data.replace("`2`", ";");
  data.replace("`3`", "!");

  data.replace("`4`", "[");
  data.replace("`5`", "]");

  data.replace("`6`", "{");
  data.replace("`7`", "}");

  data.replace("`8`", "+");
  data.replace("`9`", "$");
  data.replace("`10`", "%");

  data.replace("`11`", "-");
  data.replace("`12`", "_");

  data.replace("`13`", "\"");
  data.replace("`14`", "'");

  data.replace("`15`", "\\");

  return data;
}

boolean utils_is_valid_receiver(String input)
{
  boolean is_valid = false;

  if (input.length() == 4)
  {

    String v = input.substring(0, 1);
    String t = input.substring(1, 2);
    String id = input.substring(2, 4);

    if (t == "x" or t == "g")
    {
      is_valid = true;
    }
  }

  return is_valid;
}

int utils_random_int(int max_value) {
  return esp_random() % max_value;
}