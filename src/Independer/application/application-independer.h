#include <Ticker.h> //Call Ticker.h library

Ticker ticker_independer_send_later; // Declare Ticker object for send later

#define C_INDEPENDER_SEND_DELAY 1000
#define C_INDEPENDER_SCAN_MS 6000

String C_INDEPENDER_SHORT_MESSAGE_CHAR_ALL = "?";
String C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE = "!";

/*
 * ####################################
 *  Send Later Section
 * ####################################
 */

String i_independer_send_later_from = "";
String i_independer_send_later_to = "";
String i_independer_send_later_message = "";

void i_callback_send_later() // Callback function
{
  lora_send_msg_single_unsafe(i_independer_send_later_from, i_independer_send_later_to, i_independer_send_later_message, state_lora_gain);
  i_independer_send_later_from = "";
  i_independer_send_later_to = "";
  i_independer_send_later_message = "";
}

void application_independer_send_later_single_unsafe(String from, String to, String msg, int delay_ms)
{
  i_independer_send_later_from = from;
  i_independer_send_later_to = to;
  i_independer_send_later_message = msg;
  Serial.println("Schedule send later in " + String(delay_ms) + " millis");
  ticker_independer_send_later.once_ms(delay_ms, i_callback_send_later);
}

/*
 * ####################################
 *  Pong Section
 * ####################################
 */

struct S_APP_PONG
{
  boolean receivedSomething;
  boolean receivingCompleted;
  String message;
};

/**
 * @param check_from_id device id (gateway)
 * @param addDebugDataToMsg flag true = add debug data to message
 */
S_APP_PONG application_independer_pong(String check_from_id, boolean addDebugDataToMsg)
{

  int packetSize = LoRa.parsePacket();

  if (packetSize)
  {

    String i_res = "";
    for (int i = 0; i < packetSize; i++)
    {
      i_res += (char)LoRa.read();
    }

    ParserAnsTuple parser_ans = lora_stateful_parse(i_res, state_my_id);

    if (parser_ans.message != "" and parser_ans.from == check_from_id)
    {
      String msg = parser_ans.message;
      if (addDebugDataToMsg)
      {
        msg = "'" + parser_ans.message + "'\nfrom '" + parser_ans.from + "'\nRS=" + String(LoRa.packetRssi(), DEC) + " PK=" + String(parser_ans.numPackets);
      }

      return S_APP_PONG{
          true,
          true,
          msg};
    }

    return S_APP_PONG{
        true,
        false,
        ""};
  }

  return S_APP_PONG{
      false,
      false,
      ""};
}