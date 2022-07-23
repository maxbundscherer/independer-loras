#include <SPI.h>
#include <Wire.h>
#include "SSD1306Wire.h"
#include <LoRa.h>

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
// TODO: Auch HelTec Board neuer Kompiler (auch wegen Gain PABOOST Beachten)
// TODO: Gateway Deep Sleep geht nicht

/*
 * ####################################
 *  Config Section
 * ####################################
 */
// Product Config
String c_product_version = "v.0.2.2";
boolean c_demo_mode = false;

/*
 * ####################################
 *  State Section
 * ####################################
 */
String state_my_id = "0x01";      // Saved in db
String state_gateway_id = "0g01"; // Saved in db
String state_wifi_ssid = "";      // Saved in db
String state_wifi_pw = "";        // Saved in db

String state_wifi_hostname = "independer-" + String(esp_random());

int state_lora_gain = 20; // Supported values are between 2 and 17 for PA_OUTPUT_PA_BOOST_PIN, 0 and 14 for PA_OUTPUT_RFO_PIN - Saved in db

int state_oled_brightness = 255; // saved in db

#include "device/mb-base64.h"
#include "device/mb-utils.h"
#include "device/mb-gui.h"
#include "device/mb-crypt.h"
#include "device/mb-lora.h"

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
      gui_logo_static(c_product_version, state_my_id, state_gateway_id, c_actor_mode);
      delay(C_GUI_DELAY_STATIC);
      if (c_demo_mode)
        delay(1000 * 60 * 10);
    }
  }
  else
  {
    gui_msg_animated("Info", "Dev Mode\nactive", C_GUI_DELAY_MSG_VERY_SHORT_I);
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