/*
 * ####################################
 *  Main Section
 * ####################################
 */

int state_gateway_received_packets = 0;
int state_gateway_received_messages = 0;

boolean state_gateway_has_sth_changed = true;

void workflow_gateway_main() {

  int c_max_res_delta = 10; //Waiting 10ms between receiving

  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    state_gateway_received_packets++;
    state_gateway_has_sth_changed = true;

    String i_res = "";
    for (int i = 0; i < packetSize; i++) {
      i_res += (char) LoRa.read();
    }

    ParserAnsTuple parser_ans = lora_stateful_parse(i_res, state_gateway_id);

    if (parser_ans.message != "") {
      state_gateway_received_messages++;
      state_gateway_has_sth_changed = true;

      if (parser_ans.message == "cmd_sleep") {
        utils_go_to_sleep();
      } 
      else if(parser_ans.message == "!" or parser_ans.message == "?")  {
        //TODO: Wait after ?
        delay(C_INDEPENDER_SEND_DELAY);
        String msg = String(LoRa.packetRssi(), DEC) + "-" + String(utils_get_battery());
        lora_send_msg_single_unsafe(state_gateway_id, parser_ans.from, msg, state_lora_gain);
      }
      else {
        Serial.println("Error received unknown message '" + parser_ans.message + "'");
      }

    }

  }

  if (state_gateway_has_sth_changed) {
    gui_msg_static("Independer Gateway", "Anzahl Pakete: " + String(state_gateway_received_packets) + "\nAnzahl Nachrichten: " + String(state_gateway_received_messages));
    state_gateway_has_sth_changed = false;
  }

  delay(c_max_res_delta);

}