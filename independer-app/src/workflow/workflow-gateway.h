/*
 * ####################################
 *  Main Section
 * ####################################
 */

int state_gateway_received_packets = 0;
int state_gateway_received_messages = 0;
int state_gateway_db_items = 0;

boolean state_gateway_has_sth_changed = true;

void workflow_gateway_main()
{

  // LoRa.receive();
  int packetSize = LoRa.parsePacket();

  if (packetSize)
  {

    Serial.println("\n\n Got Packet");

    state_gateway_received_packets++;
    state_gateway_has_sth_changed = true;

    String i_res = "";
    while (LoRa.available())
    {
      i_res += LoRa.readString();
    }

    ParserAnsTuple parser_ans = lora_stateful_parse(i_res, state_gateway_id);

    if (parser_ans.message != "")
    {
      state_gateway_received_messages++;
      state_gateway_has_sth_changed = true;

      if (parser_ans.message == "C;slp")
      {
        if (parser_ans.from == state_gateway_owner)
          utils_go_to_sleep();
        else
          Serial.println("Gateway owner is not correct");
      }
      else if (parser_ans.message == "C;clmsg")
      {
        state_gateway_db_items = application_gateway_clear_user_msgs(parser_ans.from);
        state_gateway_has_sth_changed = true;
      }
      else if (parser_ans.message == C_INDEPENDER_SHORT_MESSAGE_CHAR_ALL or parser_ans.message == C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE)
      {
        String msg = String(LoRa.packetRssi(), DEC) + "-" + String(utils_get_battery());
        if (parser_ans.message == C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE)
        {
          delay(C_INDEPENDER_SEND_DELAY);
          lora_send_msg_single_unsafe(state_gateway_id, parser_ans.from, msg, state_lora_gain);
          delay(C_INDEPENDER_SEND_DELAY_REPEAT);
          lora_send_msg_single_unsafe(state_gateway_id, parser_ans.from, msg, state_lora_gain);
          // application_independer_send_later_single_unsafe(state_gateway_id, parser_ans.from, msg, C_INDEPENDER_SEND_DELAY);
        }

        else
          application_independer_send_later_single_unsafe(state_gateway_id, parser_ans.from, msg, C_INDEPENDER_SEND_DELAY + utils_random_int(C_INDEPENDER_SCAN_MS - 500));
      }
      else if (parser_ans.message == "Q;msg")
      {
        delay(C_INDEPENDER_SEND_DELAY);
        application_gateway_send_msgs_to_actor(parser_ans.from);
      }
      else if (parser_ans.message.startsWith("M;"))
      {
        delay(C_INDEPENDER_SEND_DELAY);
        lora_send_msg_single_unsafe(state_gateway_id, parser_ans.from, "A;ok", state_lora_gain);
        delay(C_INDEPENDER_SEND_DELAY_REPEAT);
        lora_send_msg_single_unsafe(state_gateway_id, parser_ans.from, "A;ok", state_lora_gain);
        // application_independer_send_later_single_unsafe(state_gateway_id, parser_ans.from, "A;ok", C_INDEPENDER_SEND_DELAY);
        state_gateway_db_items = application_gateway_store_msg(parser_ans.from, parser_ans.message);
        state_gateway_has_sth_changed = true;
      }
      else if (parser_ans.message.startsWith("C;up;"))
      {
        if (parser_ans.from == state_gateway_owner)
          application_gateway_update(parser_ans.message);
        else
          Serial.println("Gateway owner is not correct");
      }
      else if (parser_ans.message == "C;clgat")
      {
        if (parser_ans.from == state_gateway_owner)
        {
          db_clear();
          ESP.restart();
        }
        else
          Serial.println("Gateway owner is not correct");
      }
      else
      {
        Serial.println("Error received unknown message '" + parser_ans.message + "'");
      }
    }
  }

  if (state_gateway_has_sth_changed)
  {
    gui_msg_static_gateway(I18N_GATEWAY_MENU_TITLE, I18N_GATEWAY_MENU_PACKETS + String(state_gateway_received_packets) + I18N_GATEWAY_MENU_MSGS + String(state_gateway_received_messages) + I18N_GATEWAY_MENU_DB_ITEMS + String(state_gateway_db_items), time_lora_quota_update_get_millis());
    state_gateway_has_sth_changed = false;
  }

  delay(C_INDEPENDER_RES_BETWEEN_DELAY_GATEWAY);
}