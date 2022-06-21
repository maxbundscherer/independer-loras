#include "heltec.h"
#include "device/mb-utils.h"
#include "device/mb-gui.h"
#include "Cipher.h"
#include "device/mb-crypt.h"
#include "device/mb-lora.h"

//TODO: Gateway Empfangen Layout fix
//TODO: Gateway Nicht Blocken bei Fehler anzeigen

//TODO: Sendekontigent mit echter Zeit

//TODO: Multi Task Decoding
//TODO: Warum Faktor 2 Multi Task Decoding

//TODOL Actor App: Scan Output Tmp Workaround, -2

//TODO: Refactoring c_id und Gateway id

/*
 * ####################################
 *  Config Section
 * ####################################
 */
//Product Config
String    c_product_version   = "v.0.1.3";
boolean   c_dev_mode          = false;
boolean   c_actor_mode        = true;

/*
 * ####################################
 *  State Section
 * ####################################
 */
String  state_my_id         = "0xMB";
String  state_gateway_id    = "0gMB";
int     state_lora_gain     = 20;
RTC_DATA_ATTR int boot_state_oled_brightness = 255;

/*
 * ####################################
 *  Setup Section
 * ####################################
 */

//Common
#include "application/application-independer.h"
#include "workflow/workflow-independer.h"

//Actor
#include "workflow/workflow-multi-actor.h"
#include "application/application-actor.h"
#include "workflow/workflow-actor.h"

//Gateway
#include "application/application-gateway.h"
#include "workflow/workflow-gateway.h"

void setup() {

  boolean isFirstBoot = workflow_independer_init(c_actor_mode, c_product_version, c_dev_mode);

  if (!c_dev_mode) {
    if (isFirstBoot or !c_actor_mode) { //Show every boot on gateway
      gui_logo_static(c_product_version, state_my_id, state_gateway_id, c_actor_mode);
      delay(C_GUI_DELAY_STATIC);
    }
  }

}

/*
 * ####################################
 *  Loop Section
 * ####################################
 */
void loop() {

  if(c_actor_mode) {
    multi_actor_start();
    workflow_actor_main_menu();
  }
  else {
    workflow_gateway_main();
  }

}
