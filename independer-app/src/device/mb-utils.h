#include "driver/rtc_io.h" //Low Power Mode

#define C_INDEPENDER_SEND_DELAY 2000
#define C_INDEPENDER_SEND_DELAY_REPEAT 100
#define C_INDEPENDER_SEND_DELAY_BETWEEN_MESSAGES 500
#define C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR 1
#define C_INDEPENDER_RES_BETWEEN_DELAY_GATEWAY 10
#define C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR_MULTI 10
#define C_INDEPENDER_TX_MAX_LEN_PACKET 15
#define C_INDEPENDER_SCAN_MS 8000

#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define C_TIME_TO_SLEEP 60 * 30   /* Time ESP32 will go to sleep (in seconds) */

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

boolean utils_wakeup_reason_and_sync_flag()
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
    return true;
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

  return false;
}

void utils_go_to_sleep(boolean activateAuto = false)
{

  Serial.println("Activate sleep mode, activateAuto=" + String(activateAuto));
  delay(1000); // is required

  if (!activateAuto)
  {

    rtc_gpio_pulldown_en(GPIO_NUM_0);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0); // 1 = High, 0 = Low

    esp_deep_sleep_start();
  }
  else
  {
    rtc_gpio_pulldown_en(GPIO_NUM_0);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0); // 1 = High, 0 = Low

    esp_sleep_enable_timer_wakeup(C_TIME_TO_SLEEP * uS_TO_S_FACTOR);
    esp_deep_sleep_start();
  }
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

int utils_random_int(int max_value)
{
  return esp_random() % max_value;
}

String utils_random_char()
{
  char randomletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[esp_random() % 26];

  return String(randomletter);
}