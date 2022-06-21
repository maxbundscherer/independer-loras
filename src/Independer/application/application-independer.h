#include <Ticker.h> //Call Ticker.h library

Ticker ticker_independer_send_later; //Declare Ticker object

#define C_INDEPENDER_SEND_DELAY 1000
#define C_INDEPENDER_SCAN_MS    6000

String C_INDEPENDER_SHORT_MESSAGE_CHAR_ALL      = "?";
String C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE   = "!";

String i_independer_send_later_from = "";
String i_independer_send_later_to = "";
String i_independer_send_later_message = "";

void i_callback_send_later() //Callback function 
{
  lora_send_msg_single_unsafe(i_independer_send_later_from, i_independer_send_later_to, i_independer_send_later_message, state_lora_gain);
  i_independer_send_later_from = "";
  i_independer_send_later_to = "";
  i_independer_send_later_message = "";
}

void application_independer_send_later_single_unsafe(String from, String to, String msg, int delay_ms) {
  i_independer_send_later_from = from;
  i_independer_send_later_to = to;
  i_independer_send_later_message = msg;
  Serial.println("Schedule send later in " + String(delay_ms) + " millis");
  ticker_independer_send_later.once_ms(delay_ms, i_callback_send_later);
}