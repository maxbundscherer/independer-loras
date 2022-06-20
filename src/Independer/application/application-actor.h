struct S_I_Application_Device_Item {
  String deviceId;
  String deviceMsg;
  String receivedRssi;
  String attempt;
};

void application_actor_who_is_in_my_area() {

  int c_max_ping_retries = 3; //Maximial attempts to receive
  int c_max_ping_delta = 10; //Waiting 10ms between receiving
  int c_max_ping_max_receive_attempts = (C_INDEPENDER_SCAN_MS + 1000) / c_max_ping_delta; //Waiting approx C_INDEPENDER_SCAN_MS seconds for next packet

  S_I_Application_Device_Item collected_db[100];
  int collected_counter = 0;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries) {
    l_attempt++;

    lora_send_msg_short_message(state_my_id, "*", C_INDEPENDER_SHORT_MESSAGE_CHAR_ALL, state_lora_gain);

    gui_display_prg_static("Scan", l_attempt, 0, c_max_ping_retries);

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

  for (int i = 0; i < collected_counter; i++) {
    Serial.println("Scan ITEM '" + collected_db[i].deviceId + "'" + collected_db[i].deviceMsg + " " + collected_db[i].receivedRssi + " " + collected_db[i].attempt);
  }

}