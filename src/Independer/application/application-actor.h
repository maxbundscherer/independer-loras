/*
 * ####################################
 *  Who is near? Section
 * ####################################
 */

struct S_I_Application_Device_Item {
  String deviceId;
  String deviceMsg;
  String receivedRssi;
  String attempt;
};

void application_actor_who_is_in_my_area() {

  boolean sync_was_on_flag = multi_actor_get_state();

  if (sync_was_on_flag) {
    multi_actor_stop();
  }

  int c_max_ping_retries = 3; //Maximial attempts to receive
  int c_max_ping_delta = 10; //Waiting 10ms between receiving
  int c_max_ping_max_receive_attempts = (C_INDEPENDER_SCAN_MS + 2000) / c_max_ping_delta; //Waiting approx C_INDEPENDER_SCAN_MS seconds for next packet

  S_I_Application_Device_Item collected_db[30];
  int collected_counter = 0;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries) {
    l_attempt++;

    lora_send_msg_short_message(state_my_id, "*", C_INDEPENDER_SHORT_MESSAGE_CHAR_ALL, state_lora_gain);

    gui_display_prg_static("Umgebungs-Scan", l_attempt, 0, c_max_ping_retries);

    int l_cur_receive_attempt = 0;
    while (l_cur_receive_attempt < c_max_ping_max_receive_attempts) {
      l_cur_receive_attempt++;

      int packetSize = LoRa.parsePacket();

      if (packetSize) {

        String i_res = "";
        for (int i = 0; i < packetSize; i++) {
          i_res += (char) LoRa.read();
        }

        ParserAnsTuple parser_ans = lora_stateful_parse(i_res, state_my_id);

        if (parser_ans.message != "") {
          struct S_I_Application_Device_Item ret = {
            parser_ans.from,
            parser_ans.message,
            String(LoRa.packetRssi(), DEC),
            String(l_attempt)
          };
          collected_db[collected_counter] = ret;
          collected_counter++;
        }

      }

      delay(c_max_ping_delta);

    }

  }

  if (collected_counter > 0) {
    String gui_items[collected_counter];

    for (int i = 0; i < collected_counter; i++) {
      String r = collected_db[i].deviceId + " (" + collected_db[i].deviceMsg + ") " + collected_db[i].receivedRssi + " " + collected_db[i].attempt;
      // Serial.println("Scan Item '" + r + "'");
      gui_items[i] = r;
    }

    gui_selection("Scan Ausgabe", gui_items, collected_counter - 1, true);

    if (sync_was_on_flag) {
      multi_actor_start();
    }
  }

}

/*
 * ####################################
 *  Is Available Section
 * ####################################
 */

struct S_APP_PONG {
  boolean receivedSomething;
  boolean receivingCompleted;
  String message;
};

S_APP_PONG i_application_pong(String target_id) {

  int packetSize = LoRa.parsePacket();

  if (packetSize) {

    String i_res = "";
    for (int i = 0; i < packetSize; i++) {
      i_res += (char) LoRa.read();
    }

    ParserAnsTuple parser_ans = lora_stateful_parse(i_res, state_my_id);

    if (parser_ans.message != "" and parser_ans.from == target_id) {
      String msg = "'" + parser_ans.message + "'\nfrom '" + parser_ans.from + "'\nRS=" + String(LoRa.packetRssi(), DEC) + " PK=" + String(parser_ans.numPackets);
      return S_APP_PONG {
        true,
        true,
        msg
      };
    }

    return S_APP_PONG {
      true,
      false,
      ""
    };

  }

  return S_APP_PONG {
    false,
    false,
    ""
  };
}

/**
 * @return boolean return if is available 
 */
boolean application_actor_is_available(String target_id, boolean flagHideAns) {

  boolean sync_was_on_flag = multi_actor_get_state();

  if (sync_was_on_flag) {
    multi_actor_stop();
  }

  int c_max_ping_retries = 5; //Maximial attempts to receive pong message
  int c_max_ping_delta = 10; //Waiting 10ms between receiving
  int c_max_ping_max_receive_attempts = 3000 / c_max_ping_delta; //Waiting approx 2 seconds for next packet

  String receivedMsg;
  boolean receivedSuccess = false;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries and!receivedSuccess) {
    l_attempt++;

    gui_display_prg_static("Versuch", l_attempt, 0, c_max_ping_retries);

    lora_send_msg_short_message(state_my_id, target_id, C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE, state_lora_gain);

    int l_cur_receive_attempt = 0;
    while (l_cur_receive_attempt < c_max_ping_max_receive_attempts and!receivedSuccess) {
      l_cur_receive_attempt++;

      struct S_APP_PONG pong_ans = i_application_pong(target_id);

      if (pong_ans.receivedSomething) {
        l_cur_receive_attempt = 0;
      }

      if (pong_ans.receivingCompleted) {
        receivedMsg = pong_ans.message;
        receivedSuccess = true;
      } else {
        delay(c_max_ping_delta);

      }

    }

  }

  if (receivedSuccess and !flagHideAns) {
    gui_msg_animated("Antwort", receivedMsg, C_GUI_DELAY_MSG_MIDDLE_I);
  }

  if (sync_was_on_flag) {
    multi_actor_start();
  }

  return receivedSuccess;
}

/*
 * ####################################
 *  Send Message to Gateway Section
 * ####################################
 */

void application_actor_send_msg_to_gateway(String myId, String gatewayId, String receiverId, String userMsg) {

}