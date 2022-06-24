/*
 * ####################################
 *  Background Receiving Section
 * ####################################
 */

#include <Ticker.h> //Call Ticker.h library

Ticker ticker_multi_actor_receiving; // Declare Ticker object for send later

String state_ticker_multi_actor_rec_actor_id = "";

void i_multi_res_proc_actor_rec_message_from_actor()
{

  String actorId = state_ticker_multi_actor_rec_actor_id;

  int c_max_ping_retries = 1;                                                             // Maximial attempts to receive pong message
  int c_max_ping_delta = C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR;                            // Waiting 1ms between receiving
  int c_max_ping_max_receive_attempts = (C_INDEPENDER_SEND_DELAY * 4) / c_max_ping_delta; // Waiting approx 2 seconds for next packet

  boolean sendSuccess = false;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries and !sendSuccess)
  {
    l_attempt++;

    int l_cur_receive_attempt = 0;
    while (l_cur_receive_attempt < c_max_ping_max_receive_attempts and !sendSuccess)
    {
      l_cur_receive_attempt++;

      struct S_APP_PONG pong_ans = application_independer_pong(actorId, false);

      if (pong_ans.receivedSomething)
      {
        l_cur_receive_attempt = 0;
      }

      if (pong_ans.receivingCompleted)
      {
        application_independer_send_later_single_unsafe(state_my_id, actorId, "N", C_INDEPENDER_SEND_DELAY);
        Serial.println("Direct msg from " + actorId + ": '" + pong_ans.message + "'");
        sendSuccess = true;
      }
      else
      {
        delay(c_max_ping_delta);
      }
    }
  }

  state_ticker_multi_actor_rec_actor_id = "";
}

void i_multi_actor_rec_message_from_actor(String actorId)
{
  application_independer_send_later_single_unsafe(state_my_id, actorId, "S", C_INDEPENDER_SEND_DELAY);
  Serial.println("Schedule receving background later in " + String(100) + " millis");
  state_ticker_multi_actor_rec_actor_id = actorId;
  ticker_independer_send_later.once_ms(100, i_multi_res_proc_actor_rec_message_from_actor);
}

/*
 * ####################################
 *  Background Job Section
 * ####################################
 */
// TaskHandle_t  Core0TaskHnd ; //Core0
TaskHandle_t Core1TaskHnd;
boolean state_multi_is_active = false;

// const int MULTI_STRING_BUFFER_MAX = 50;

// int state_multi_cur_string_i = 0;
// String state_multi_sting_buffer[MULTI_STRING_BUFFER_MAX];

// Maybe deprecated, important for string buffer
//  void i_multi_Task1_string_buffer(void * parameter) {
//    for (;;) {
//      // Serial.print("multi_Task1 runs on Core: ");
//      // Serial.println(xPortGetCoreID());

//     int packetSize = LoRa.parsePacket();

//     if (packetSize) {

//     //   Serial.println("Got packet");
//       String i_res = "";
//       for (int i = 0; i < packetSize; i++) {
//         i_res += (char) LoRa.read();
//       }

//     //   Serial.println("Before parse '" + i_res + "'");

//       if (state_multi_cur_string_i < MULTI_STRING_BUFFER_MAX) {
//         state_multi_sting_buffer[state_multi_cur_string_i] = i_res;
//         state_multi_cur_string_i++;

//         //Try to parse in this loop
//         ParserAnsTuple parser_ans = lora_stateful_parse(i_res, state_gateway_id);
//         if (parser_ans.message != "") {
//         Serial.println("Got ac-msg '" + String(parser_ans.message) + "'");
//         String msg = String(LoRa.packetRssi(), DEC) + " " + String(utils_get_battery()) + " oD";
//         lora_send_msg_single_unsafe(state_my_id, parser_ans.from, msg, state_lora_gain);
//         }

//       } else {
//         Serial.println("Error Buffer OverFlow in Message");
//       }

//     }

//     // delay (700); //Default
//     delay(10); //Between Trans
//   }
// }

// void i_multi_actor_proc_string_buffer() {

//   for (int i = 0; i < state_multi_cur_string_i; i++) {
//     Serial.println("\nGot i " + String(i));

//     ParserAnsTuple parser_ans = lora_stateful_parse(state_multi_sting_buffer[i], state_gateway_id);

//     if (parser_ans.message != "") {
//       Serial.println("Got message inactive'" + String(parser_ans.message) + "'");
//     }
//   }

//   state_multi_cur_string_i = 0;
// }

void i_multi_Task1_short_message(void *parameter)
{
  for (;;)
  {
    // Serial.print("multi_Task1 runs on Core: ");
    // Serial.println(xPortGetCoreID());

    int packetSize = LoRa.parsePacket();

    if (packetSize)
    {

      String i_res = "";
      for (int i = 0; i < packetSize; i++)
      {
        i_res += (char)LoRa.read();
      }

      ShortMessageAndTuple parser_ans = lora_short_message_parse(i_res, state_my_id);
      if (parser_ans.message != "")
      {

        if (parser_ans.message == C_INDEPENDER_SHORT_MESSAGE_CHAR_ALL or parser_ans.message == C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE)
        {
          String msg = String(LoRa.packetRssi(), DEC) + "-" + String(utils_get_battery());
          if (parser_ans.message == C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE)
            application_independer_send_later_single_unsafe(state_my_id, parser_ans.from, msg, C_INDEPENDER_SEND_DELAY);
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

    delay(C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR_MULTI); // Between Res
  }
}

void multi_actor_start()
{
  state_multi_is_active = true;
  // state_multi_cur_string_i = 0;
  xTaskCreatePinnedToCore(i_multi_Task1_short_message, "CPU_1", 1000 * 2, NULL, 1, &Core1TaskHnd, 1); // TODO: Warum Faktor 2
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

  // String post_string = " Buffer " + String(state_multi_cur_string_i);

  //   i_multi_actor_proc_string_buffer();

  if (state_multi_is_active)
    return "Aktiv"; // + post_string;
  return "Inaktiv";
}