#include <SPI.h>
#include <Wire.h>
#include "SSD1306Wire.h"
#include <LoRa.h>
#include <ArduinoJson.h>
#include "device/mb-i18n.h"
#include "device/mb-utils.h"

#if IS_RELEASE
boolean c_dev_mode = false;
#else
boolean c_dev_mode = true;
#endif

#if IS_ACTOR
boolean c_actor_mode = true;
#else
boolean c_actor_mode = false;
#endif

// TODO: LillgoGo Actor noch testen
// TODO: Hashcode Check verbessern

/*
 * ####################################
 *  Config Section
 * ####################################
 */
// Product Config
String c_product_version = "v.0.3.8";

/*
 * ####################################
 *  State Section
 * ####################################
 */
String state_my_id = "0x01";         // Saved in db and INIT CONFIG (fixed)
String state_gateway_id = "0g01";    // Saved in db and INIT CONFIG
String state_gateway_owner = "0x01"; // Saved in db and INIT CONFIG
String state_wifi_ssid = "";         // Saved in db and INIT CONFIG
String state_wifi_pw = "";           // Saved in db and INIT CONFIG

String state_wifi_hostname = "independer-" + String(utils_random_int(10000));

int state_lora_gain = 20; // Supported values are between 2 and 17 for PA_OUTPUT_PA_BOOST_PIN, 0 and 14 for PA_OUTPUT_RFO_PIN - Saved in db

int state_oled_brightness = 255;  // saved in db
int state_auto_sleep_enabled = 1; // saved in db

String state_wifi_server_url = "independer.ddns.net"; // saved in db (fixed)
int state_wifi_server_port = 5001;                    // saved in db (fixed)
int state_wifi_server_timeout = 10000;                // saved in db
String state_wifi_server_device_token = "";           // saved in db and INIT CONFIG
bool state_is_registered_independer = false;          // saved in db and INIT CONFIG (fixed)

#include "device/mb-time.h"
#include "device/mb-base64.h"
#include "device/mb-gui.h"
#include "device/mb-crypt.h"
#include "device/mb-lora.h"
#include "device/mb-wifi.h"

/*
 * ####################################
 *  Setup Section
 * ####################################
 */

// Database
#include "device/mb-database.h"

// OTA
#include "device/mb-ota.h"

// Common
#include "application/application-independer.h"
#include "workflow/workflow-independer.h"

// Actor
#include "workflow/workflow-multi-actor.h"
#include "application/application-actor.h"
#include "workflow/workflow-actor.h"

// Gateway
#include "application/application-gateway.h"
#include "workflow/workflow-gateway.h"

void setup()
{

  boolean isFirstBoot = workflow_independer_init(c_actor_mode, c_product_version, c_dev_mode);

  if (!c_dev_mode)
  {
    if (isFirstBoot or !c_actor_mode)
    { // Show every boot on gateway
      gui_logo_static(c_product_version, state_my_id, state_gateway_id, c_actor_mode, state_gateway_owner);
      delay(C_GUI_DELAY_STATIC);
    }
  }
  else
  {
    gui_msg_animated(I18N_INFO_TITLE, I18N_BOOT_DEV_ACTIVE, C_GUI_DELAY_MSG_VERY_SHORT_I);
  }

  if (c_actor_mode)
    multi_actor_start();
}

/*
 * ####################################
 *  Loop Section
 * ####################################
 */
void loop()
{

  if (c_actor_mode)
  {
    workflow_actor_main_menu();
  }
  else
  {
    workflow_gateway_main();
  }
}

// TODO: Bug Senden fällt bei Actoren im Background aus (vielleicht mal bei Verwendung von sendLaster bei Near me ?)
// TODO: Bug Hostname bei WIFI wird nicht übertragen

// TODO: Warum Faktor 2 und 8 Multi Task Decoding

// TODO: Verbesser Start/Stop Actor Multi in Briefe abrufen
// TODO: UI Verbessern Leerzeichen bei Long Text ausgabe und Text Eingabe

// TODO: Refactoring c_id und Gateway id
// TODO: Refactoring disableShortcuts bei gui_selection wieder ausbauen, hat nicht funktioniert

// TODO: String compare wie in workflow-actor implementieren!