/*
 * ####################################
 *  Ping Pong Section
 * ####################################
 */

// void i_workflow_ping(String msg, boolean safeTransmit, boolean shortMessageTransmit) {

//   if(shortMessageTransmit) {
//     lora_send_msg_short_message(state_my_id, state_gateway_id, msg, state_lora_gain);
//     return;
//   }

//   //Send Message
//   if (safeTransmit) {
//     lora_send_msg(state_my_id, state_gateway_id, msg, state_lora_gain);
//   } else {
//     lora_send_msg_single_unsafe(state_my_id, state_gateway_id, msg, state_lora_gain);
//   }

// }

// struct S_Workflow_Pong {
//   boolean receivedSomething;
//   boolean receivingCompleted;
//   String message;
// };

// S_Workflow_Pong i_workflow_pong() {

//   int packetSize = LoRa.parsePacket();

//   if (packetSize) {

//     String i_res = "";
//     for (int i = 0; i < packetSize; i++) {
//       i_res += (char) LoRa.read();
//     }

//     ParserAnsTuple parser_ans = lora_stateful_parse(i_res, state_my_id);

//     if (parser_ans.message != "") {
//       String msg = "'" + parser_ans.message + "'\nfrom '" + parser_ans.from + "'\nRS=" + String(LoRa.packetRssi(), DEC) + " PK=" + String(parser_ans.numPackets);
//       return S_Workflow_Pong {
//         true,
//         true,
//         msg
//       };
//     }

//     return S_Workflow_Pong {
//       true,
//       false,
//       ""
//     };

//   }

//   return S_Workflow_Pong {
//     false,
//     false,
//     ""
//   };
// }

// void i_workflow_ping_pong(String msg, boolean safeTransmit, boolean shortMessageTransmit) {

//   int c_max_ping_retries = 10; //Maximial attempts to receive pong message
//   int c_max_ping_delta = 10; //Waiting 10ms between receiving
//   int c_max_ping_max_receive_attempts = 1000 / c_max_ping_delta; //Waiting approx 1 seconds for next packet

//   String receivedMsg;
//   boolean receivedSuccess = false;

//   int l_attempt = 0;
//   while (l_attempt < c_max_ping_retries and!receivedSuccess) {
//     l_attempt++;

//     i_workflow_ping(msg + " A" + String(l_attempt), safeTransmit, shortMessageTransmit);

//     gui_display_prg_static("Versuch", l_attempt, 0, c_max_ping_retries);

//     int l_cur_receive_attempt = 0;
//     while (l_cur_receive_attempt < c_max_ping_max_receive_attempts and!receivedSuccess) {
//       l_cur_receive_attempt++;

//       struct S_Workflow_Pong pong_ans = i_workflow_pong();

//       if (pong_ans.receivedSomething) {
//         l_cur_receive_attempt = 0;
//       }

//       if (pong_ans.receivingCompleted) {
//         receivedMsg = pong_ans.message;
//         receivedSuccess = true;
//       } else {
//         delay(c_max_ping_delta);

//       }

//     }

//   }

//   if (receivedSuccess) {
//     gui_msg_animated("Antwort", receivedMsg, C_GUI_DELAY_MSG_LONG_I);
//   }

// }

/*
 * ####################################
 *  Menu Section
 * ####################################
 */

void i_communication_menu() {
  String menu_items[] = {
    "Brief schreiben",
    "Briefe abrufen",
    "Kontakte",
    "[zurück]"
  };

  bool fin_flag = false;
  while (!fin_flag) {
    int selected = gui_selection("Kommunikation", menu_items, (int) sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0) {

      String msg_res = gui_input_text("Empfänger (z.B.: 0xMB)", "");
      String msg_tx = gui_input_text("Nachricht", "");
      lora_send_msg(state_my_id, msg_res, msg_tx, state_lora_gain);

    }
    else if (selected == 1) gui_msg_animated("Info", "Leider ist die Funktion\n'Briefe abrufen'\nnoch nicht verfügbar.", C_GUI_DELAY_MSG_SHORT_I);
    else if (selected == 2) gui_msg_animated("Info", "Leider ist die Funktion\n'Kontakte'\nnoch nicht verfügbar.", C_GUI_DELAY_MSG_SHORT_I);
    else fin_flag = true;
  }

}

void i_actor_functions_bg_syn_menu() {
  String menu_items[] = {
    "Status",
    "Aktivieren",
    "Deaktivieren",
    "[zurück]"
  };

  bool fin_flag = false;
  while (!fin_flag) {
    int selected = gui_selection("Hintergrundsync", menu_items, (int) sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0) {
      gui_msg_animated("Info", "Status Hintergrundsync\n" + multi_actor_get_state_string(), C_GUI_DELAY_MSG_SHORT_I);
    }
    else if (selected == 1) {
      gui_msg_animated("Info", "Aktiviere Hintergrundsync", C_GUI_DELAY_MSG_SHORT_I);
      if(!multi_actor_get_state()) multi_actor_start();
    }
    else if (selected == 2) {
      gui_msg_animated("Info", "Deaktiviere Hintergrundsync", C_GUI_DELAY_MSG_SHORT_I);
      if(multi_actor_get_state()) multi_actor_stop();
    }
    else fin_flag = true;
  }

}

void i_actor_functions_menu() {
  String menu_items[] = {
    "Batterie Status",
    "Sendekontingent",
    "Hintergrundsync",
    "Test Ausgabe",
    "Schlaf Modus",
    "[zurück]"
  };

  bool fin_flag = false;
  while (!fin_flag) {
    int selected = gui_selection("Actor Funktionen", menu_items, (int) sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0) {
      gui_display_prg_animated("Batterie Status (mV)", utils_get_battery(), 1950, 3100, C_GUI_DELAY_MSG_SHORT_I);
    }
    else if (selected == 1) {
      gui_display_prg_animated("Sendekontingent (millis)", lora_get_global_tx_time_millis(), 0, 36000, C_GUI_DELAY_MSG_SHORT_I);
    }
    else if(selected == 2) i_actor_functions_bg_syn_menu();
    else if(selected == 3) gui_print_test_buffer();
    else if (selected == 4) {
      gui_msg_animated("Info", "Aktiviere Schlafmodus\n(Actor)", C_GUI_DELAY_MSG_SHORT_I);
      utils_go_to_sleep();
    }
    else fin_flag = true;
  }

}

void i_gateway_functions_menu() {
  String menu_items[] = {
    // "Test Nachricht (klein)",
    // "Test Nachricht (groß)",
    // "Test Nachricht (sM)",
    "Umgebung?",
    "Erreichbar?",
    "Schlaf Modus",
    "[zurück]"
  };

  bool fin_flag = false;
  while (!fin_flag) {
    int selected = gui_selection("Gateway Funktionen", menu_items, (int) sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    // if (selected == 0) {
    //   gui_msg_animated("Info", "Sende\nTest Nachricht (klein)", C_GUI_DELAY_MSG_SHORT_I);
    //   i_workflow_ping_pong("Test klein", false, false);
    // }
    // else if (selected == 1) {
    //   gui_msg_animated("Info", "Sende\nTest Nachricht (groß)", C_GUI_DELAY_MSG_SHORT_I);
    //   i_workflow_ping_pong("Das ist jetzt eine größere Test-Nachricht. Ich teste jetzt einmal eine längere Nachricht.", true, false);
    // }
    // else if (selected == 2) {
    //   gui_msg_animated("Info", "Sende\nTest Nachricht (sM)", C_GUI_DELAY_MSG_SHORT_I);
    //   i_workflow_ping_pong("Test", true, true);
    // }
    if(selected == 0) {
      application_actor_who_is_in_my_area();
    }
    else if(selected == 1) {
      gui_msg_animated("Info", "Leider ist die Funktion\n'Erreichbar?'\nnoch nicht verfügbar.", C_GUI_DELAY_MSG_SHORT_I);
    }
    else if (selected == 2) {
      gui_msg_animated("Info", "Aktiviere Schlafmodus\n(Gateway)", C_GUI_DELAY_MSG_SHORT_I);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "cmd_sleep", state_lora_gain);
    }
    else fin_flag = true;
  }

}

void i_settings_menu() {
  String menu_items[] = {
    "Meine ID",
    "Gateway ID",
    "LoRa Gain",
    "Helligkeit",
    "[zurück]"
  };

  bool fin_flag = false;
  while (!fin_flag) {
    int selected = gui_selection("Einstellungen", menu_items, (int) sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0) state_my_id = gui_input_text("Meine ID (z.B.: 0xMB)", state_my_id);
    else if (selected == 1) state_gateway_id = gui_input_text("Gateway ID (z.B.: 0gMB)", state_gateway_id);
    else if (selected == 2) {
      int ans = gui_input_text("LoRa Gain (1-20)", String(state_lora_gain)).toInt();
      if(ans>20) ans = 20;
      if(ans<1) ans = 1;
      state_lora_gain = ans;
    }
    else if (selected == 3) {
      int ans = gui_input_text("Helligkeit (0-255)", String(boot_state_oled_brightness)).toInt();
      if(ans>255) ans = 255;
      if(ans<0) ans = 0;
      boot_state_oled_brightness = ans;
      Heltec.display -> setBrightness(boot_state_oled_brightness);
      }
    else fin_flag = true;
  }

}

void workflow_actor_main_menu() {
  String menu_items[] = {
    "Kommunikation",
    "Actor Funktionen",
    "Gateway Funktionen",
    "Einstellungen",
    "Info"
  };

  int selected = gui_selection("Independer", menu_items, (int) sizeof(menu_items) / sizeof(menu_items[0]) - 1);

  if (selected == 0) i_communication_menu();
  else if (selected == 1) i_actor_functions_menu();
  else if (selected == 2) i_gateway_functions_menu();
  else if (selected == 3) i_settings_menu();
  else if (selected == 4) {
    gui_logo_static(c_product_version, state_my_id, state_gateway_id, c_actor_mode);
    delay(C_GUI_DELAY_STATIC);
  } else gui_msg_animated("Fehler", "Auswahl " + String(selected) + "\nnicht verfügbar.", C_GUI_DELAY_MSG_MIDDLE_I);
}