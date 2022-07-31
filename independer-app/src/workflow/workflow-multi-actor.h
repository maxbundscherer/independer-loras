/*
 * ####################################
 *  Background Receiving Section
 * ####################################
 */

// TaskHandle_t Core0TaskHnd; //
void multi_actor_start_blinking();
void multi_actor_stop_blinking();
TaskHandle_t Core1TaskHnd;

String state_ticker_multi_actor_rec_actor_id = "";

String state_multi_actor_msgs[100];
int state_multi_actor_msgs_counter = 0;

void i_multi_res_proc_actor_rec_message_from_actor(void *parameter)
{
  String actorId = state_ticker_multi_actor_rec_actor_id;

  delay(C_INDEPENDER_SEND_DELAY);
  lora_send_msg_single_unsafe(state_my_id, actorId, "S", state_lora_gain);
  delay(C_INDEPENDER_SEND_DELAY_REPEAT);
  lora_send_msg_single_unsafe(state_my_id, actorId, "S", state_lora_gain);

  Serial.println("\n !!!!!!!!!!!!!!! START BACKGROUND RECEIVING actorId=" + actorId);

  int c_max_ping_retries = 1;
  int c_max_ping_delta = C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR;
  int c_max_ping_max_receive_attempts = (C_INDEPENDER_SEND_DELAY * 4 + C_INDEPENDER_SEND_DELAY) / c_max_ping_delta; // Add interval, sending

  boolean sendSuccess = false;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries and !sendSuccess)
  {
    l_attempt++;

    int l_cur_receive_attempt = 0;
    while (l_cur_receive_attempt < c_max_ping_max_receive_attempts and !sendSuccess)
    {
      l_cur_receive_attempt++;

      struct S_APP_PONG pong_ans = application_independer_pong(actorId, false, true);

      if (pong_ans.receivedSomething)
      {
        // Serial.println("----- RES SOMETHING " + String(pong_ans.receivedSomething) + " " + String(pong_ans.receivingCompleted) + "\n");
        l_cur_receive_attempt = 0;
      }

      if (pong_ans.receivingCompleted)
      {
        if (pong_ans.message == "S")
        {
          lora_send_msg_single_unsafe(state_my_id, actorId, "S", state_lora_gain);
        }
        else
        {
          delay(C_INDEPENDER_SEND_DELAY);
          lora_send_msg_single_unsafe(state_my_id, actorId, "N", state_lora_gain);
          delay(C_INDEPENDER_SEND_DELAY_REPEAT);
          lora_send_msg_single_unsafe(state_my_id, actorId, "N", state_lora_gain);
          Serial.println("Save Direct msg from " + actorId + ": '" + pong_ans.message + "'");
          multi_actor_start_blinking();
          state_multi_actor_msgs[state_multi_actor_msgs_counter] = "(" + actorId + ") " + utils_decode_data(pong_ans.message);
          state_multi_actor_msgs_counter++;
          sendSuccess = true;
        }
      }
      else
      {
        vTaskDelay(c_max_ping_delta);
      }
    }
  }

  state_ticker_multi_actor_rec_actor_id = "";
  Serial.println("!!!!!!!!!!!!!!! START BACKGROUND RECEIVING actorId=" + actorId);
  vTaskSuspend(NULL);
}

void i_multi_actor_rec_message_from_actor(String actorId)
{
  state_ticker_multi_actor_rec_actor_id = actorId;
  xTaskCreatePinnedToCore(i_multi_res_proc_actor_rec_message_from_actor, "CPU_1b", 1000 * 8, NULL, 1, &Core1TaskHnd, 1); // TODO: Warum Faktor 8
}

void multi_actor_background_show_messages()
{

  multi_actor_stop_blinking();

  if (state_multi_actor_msgs_counter == 0)
  {
    gui_msg_animated("Info", "keine Nachrichten\nvorhanden", C_GUI_DELAY_MSG_SHORT_I);
    return;
  }

  String gui_items[state_multi_actor_msgs_counter + 1]; // Add 1 for go back item

  for (int i = 0; i < state_multi_actor_msgs_counter; i++)
  {
    gui_items[i] = state_multi_actor_msgs[i];
  }

  gui_items[state_multi_actor_msgs_counter] = "[zurück]"; // Add go back item

  boolean hasMesageShown = false;
  while (!hasMesageShown)
  {
    int selected = gui_selection("Nachrichten", gui_items, state_multi_actor_msgs_counter - 1 + 1, false); // Add + 1 (go back item)
    if (selected == state_multi_actor_msgs_counter)
      hasMesageShown = true;
    else
      gui_msg_long_text("Nachricht", gui_items[selected]);
  }
}

void multi_actor_background_clear_messages()
{
  gui_msg_animated("Info", "Leere Nachrichten", C_GUI_DELAY_MSG_SHORT_I);
  state_multi_actor_msgs_counter = 0;
}

/*
 * ####################################
 *  Background Job Section
 * ####################################
 */

int c_led_blinking_delay = 1000;
boolean c_state_multi_led_blinking = false;

boolean state_multi_is_active = false;

boolean state_multi_led_blinking_state = false;
boolean state_multi_led_blinking_skip_one_interval = true;
int state_led_blinking_t_current = 0;

void i_multi_Task1_short_message(void *parameter)
{
  for (;;)
  {

    if (state_ticker_multi_actor_rec_actor_id == "")
    {

      int packetSize = LoRa.parsePacket();

      if (packetSize)
      {

        String i_res = "";
        while (LoRa.available())
        {
          i_res += LoRa.readString();
        }

        ShortMessageAndTuple parser_ans = lora_short_message_parse(i_res, state_my_id);
        if (parser_ans.message != "")
        {

          if (parser_ans.message == C_INDEPENDER_SHORT_MESSAGE_CHAR_ALL or parser_ans.message == C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE)
          {
            String msg = String(LoRa.packetRssi(), DEC) + "-" + String(utils_get_battery());
            if (parser_ans.message == C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE)
            {
              delay(C_INDEPENDER_SEND_DELAY);
              lora_send_msg_single_unsafe(state_my_id, parser_ans.from, msg, state_lora_gain);
              delay(C_INDEPENDER_SEND_DELAY_REPEAT);
              lora_send_msg_single_unsafe(state_my_id, parser_ans.from, msg, state_lora_gain);
              // application_independer_send_later_single_unsafe(state_my_id, parser_ans.from, msg, C_INDEPENDER_SEND_DELAY);
            }
            else
              application_independer_send_later_single_unsafe(state_my_id, parser_ans.from, msg, C_INDEPENDER_SEND_DELAY + (esp_random() % (C_INDEPENDER_SCAN_MS - 500)));
          }
          else if (parser_ans.message = "T")
          {
            i_multi_actor_rec_message_from_actor(parser_ans.from);
          }
          else
          {
            Serial.println("Error received unknown message in background '" + parser_ans.message + "'");
          }
        }
      }

      // LED Blinking
      if (c_state_multi_led_blinking)
      {

        if (state_led_blinking_t_current > c_led_blinking_delay)
        {
          if (state_multi_led_blinking_state)
          {
            digitalWrite(LED, LOW);
            state_multi_led_blinking_state = false;
            state_multi_led_blinking_skip_one_interval = true;
          }
          else
          {
            if (state_multi_led_blinking_skip_one_interval)
            {
              state_multi_led_blinking_skip_one_interval = false;
            }
            else
            {
              digitalWrite(LED, HIGH);
              state_multi_led_blinking_state = true;
            }
          }

          state_led_blinking_t_current = 0;
        }
        else
          state_led_blinking_t_current += C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR_MULTI;
      }

      vTaskDelay(C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR_MULTI); // Between Res
    }
    else
    {
      // Serial.println("Disable background");
    }
  }
}

void multi_actor_start_blinking()
{
  c_state_multi_led_blinking = true;
}

void multi_actor_stop_blinking()
{
  c_state_multi_led_blinking = false;
  digitalWrite(LED, LOW);
  state_multi_led_blinking_state = false;
  state_multi_led_blinking_skip_one_interval = true;
}

void multi_actor_start()
{
  state_multi_is_active = true;
  xTaskCreatePinnedToCore(i_multi_Task1_short_message, "CPU_1m", 1000 * 2, NULL, 1, &Core1TaskHnd, 1); // TODO: Warum Faktor 2
}

void multi_actor_stop()
{
  vTaskSuspend(Core1TaskHnd);
  state_multi_is_active = false;
}

boolean multi_actor_get_state()
{
  return state_multi_is_active;
}

String multi_actor_get_state_string()
{

  if (state_multi_is_active)
    return "Aktiv";
  return "Inaktiv";
}