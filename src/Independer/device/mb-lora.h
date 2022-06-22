#include "heltec.h"

#define C_INDEPENDER_SEND_DELAY 500
#define C_INDEPENDER_RES_BETWEEN_DELAY 1
#define C_INDEPENDER_SCAN_MS 10000

/*
 * ####################################
 *  Internal Section
 * ####################################
 */

long i_lora_string_hash(char *str)
{

  long hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

long i_adapter_lora_string_hash(String msg)
{

  // Length (with one extra character for the null terminator)
  int msg_len = msg.length() + 1;

  // Prepare the character array (the buffer)
  char char_array[msg_len];

  // Copy it over
  msg.toCharArray(char_array, msg_len);

  return i_lora_string_hash(char_array);
}

/*
 * ####################################
 *  Trans Section
 * ####################################
 */
uint64_t state_du_global_tx_time = 0;

int lora_get_global_tx_time_millis()
{
  return state_du_global_tx_time / 1000;
}

int lora_get_global_tx_time_seconds()
{
  return lora_get_global_tx_time_millis() / 1000;
}

void i_lora_trans_encrypt(String msg, int sendGain)
{

  digitalWrite(LED, HIGH);

  if (sendGain <= 7)
  {
    Serial.println("Send now '" + msg + "' with gain " + String(sendGain) + " with RF_PACONFIG_PASELECT_RFO");
    uint64_t du_start = esp_timer_get_time();
    LoRa.beginPacket();
    LoRa.setTxPower(sendGain, RF_PACONFIG_PASELECT_RFO);
    LoRa.print(crypt_encrypt(msg));
    LoRa.endPacket();
    state_du_global_tx_time += (esp_timer_get_time() - du_start);
  }
  else
  {
    Serial.println("Send now '" + msg + "' with gain " + String(sendGain) + " with RF_PACONFIG_PASELECT_PABOOST");
    uint64_t du_start = esp_timer_get_time();
    LoRa.beginPacket();
    LoRa.setTxPower(sendGain, RF_PACONFIG_PASELECT_PABOOST);
    LoRa.print(crypt_encrypt(msg));
    LoRa.endPacket();
    state_du_global_tx_time += (esp_timer_get_time() - du_start);
  }

  Serial.println("Send Duration " + String(lora_get_global_tx_time_millis()) + " millis " + String(lora_get_global_tx_time_seconds()) + " seconds");

  digitalWrite(LED, LOW);
}

void i_trans_start(String from, String to, unsigned int numPackets, int sendGain)
{
  i_lora_trans_encrypt(from + ":" + to + ":+:" + String(numPackets), sendGain);
}

void i_trans_packet(String from, String to, unsigned int packetNumber, String packetMsg, int sendGain)
{
  i_lora_trans_encrypt(from + ":" + to + ":" + String(packetNumber) + ":" + packetMsg, sendGain);
}

void i_trans_stop(String from, String to, long hashCode, int sendGain)
{
  i_lora_trans_encrypt(from + ":" + to + ":-:" + String(hashCode), sendGain);
}

void i_trans_single_unssafe(String from, String to, String msg, int sendGain)
{
  i_lora_trans_encrypt(from + ":" + to + ":!:" + msg, sendGain);
}

void i_trans_short_message(String from, String to, String msg, int sendGain)
{
  i_lora_trans_encrypt(from + ":" + to + ":s:" + msg, sendGain);
}

void lora_send_msg(String from, String to, String msg, int sendGain)
{

  int c_max_length = 10;
  int c_send_delay = C_INDEPENDER_SEND_DELAY;

  long msg_hash = i_adapter_lora_string_hash(msg);
  int msg_length = msg.length();

  int numPackets = int(msg_length / c_max_length);
  if (numPackets * c_max_length < msg_length)
  {
    numPackets++;
  }

  int gui_max_packets = numPackets + 2; // 2 for Begin and Stop transfer
  int gui_current_packet = 0;

  i_trans_start(from, to, numPackets, sendGain);
  gui_current_packet++;
  gui_display_prg_static("Senden", gui_current_packet, 0, gui_max_packets);
  delay(c_send_delay);

  for (int i = 0; i < numPackets; i++)
  {
    i_trans_packet(from, to, i, msg.substring(i * c_max_length, (i + 1) * c_max_length), sendGain);
    gui_current_packet++;
    gui_display_prg_static("Senden", gui_current_packet, 0, gui_max_packets);
    delay(c_send_delay);
  }

  i_trans_stop(from, to, msg_hash, sendGain);
}

void lora_send_msg_single_unsafe(String from, String to, String msg, int sendGain)
{

  i_trans_single_unssafe(from, to, msg, sendGain);
}

void lora_send_msg_short_message(String from, String to, String msg, int sendGain)
{

  i_trans_short_message(from, to, msg, sendGain);
}

/*
 * ####################################
 *  Res Section
 * ####################################
 */

struct ShortMessageAndTuple
{
  String from;
  String message;
  boolean successFlag;
};

ShortMessageAndTuple lora_short_message_parse(String msg, String myId)
{

  struct ShortMessageAndTuple ret = {
      "",
      "",
      false};

  msg = crypt_decrypt(msg);
  int msg_len = msg.length();

  Serial.println("(Received raw message) '" + msg + "'");

  if (msg_len > 50)
  {
    Serial.println("Error short message is too long");
    return ret;
  }

  String p_from = "";
  String p_to = "";
  String p_type = "";
  String p_value = "";

  int currentCountsDelimiter = 0;

  for (int i = 0; i < msg_len; i++)
  {

    String current = msg.substring(i, i + 1);

    if (current == ":")
    {
      currentCountsDelimiter++;
    }
    else
    {
      if (currentCountsDelimiter == 0)
        p_from += current;
      if (currentCountsDelimiter == 1)
        p_to += current;
      if (currentCountsDelimiter == 2)
        p_type += current;
      if (currentCountsDelimiter == 3)
        p_value += current;
    }
  }

  // currentCountsDelimiter == 3 and
  if (p_type == "s" and (p_to == myId or p_to == "*"))
  {
    ret.from = p_from;
    ret.message = p_value;
    ret.successFlag = true;
  };

  return ret;
}

struct ParserAnsTuple
{
  String from;
  String message;
  int numPackets;
};

String state_parser_from = "";
int state_parser_last_index = -1;
int state_parser_max_packets = -1;
String state_parser_msg = "";

ParserAnsTuple lora_stateful_parse(String msg, String myId)
{

  String ret_from = "";
  String ret_msg = "";
  int ret_packets = 0;

  msg = crypt_decrypt(msg);

  Serial.println("(Received raw message) '" + msg + "'");

  String p_from = "";
  String p_to = "";
  String p_type = "";
  String p_value = "";

  int currentCountsDelimiter = 0;

  for (int i = 0; i < msg.length(); i++)
  {

    String current = msg.substring(i, i + 1);

    if (current == ":")
    {
      currentCountsDelimiter++;
    }
    else
    {
      if (currentCountsDelimiter == 0)
        p_from += current;
      if (currentCountsDelimiter == 1)
        p_to += current;
      if (currentCountsDelimiter == 2)
        p_type += current;
      if (currentCountsDelimiter == 3)
        p_value += current;
    }
  }

  if (p_to == myId or (p_type == "s" and p_to == "*"))
  {

    if (p_type == "+")
    {
      // Beginn (set from, clear)
      Serial.println("- Start transmit");
      state_parser_from = p_from;
      state_parser_last_index = -1;
      state_parser_max_packets = p_value.toInt() + 2; // Sync frames 2
      state_parser_msg = "";
      gui_display_prg_static("Empfangen", 1, 0, state_parser_max_packets);
    }
    else if (p_type == "-" and p_from == state_parser_from)
    {
      // End (check hashcode)
      if (p_value == String(i_adapter_lora_string_hash(state_parser_msg)))
      {
        Serial.println("- End transmit - hashcode good");
        ret_from = state_parser_from;
        ret_msg = state_parser_msg;
        ret_packets = state_parser_max_packets;
      }
      else
      {
        Serial.println("- End transmit - hashcode bad");
        gui_msg_animated("Fehler", "Received bad hashcode", C_GUI_DELAY_MSG_SHORT_I);
      }
      state_parser_from = "";
      state_parser_last_index = -1;
      state_parser_max_packets = -1;
      state_parser_msg = "";
    }
    else if (p_type.toInt() > state_parser_last_index and p_from == state_parser_from)
    {
      // Packet (set last_id and msg)
      Serial.println("- Between transmit");
      state_parser_last_index = p_type.toInt();
      state_parser_msg += p_value;
      gui_display_prg_static("Empfangen", state_parser_last_index + 2, 0, state_parser_max_packets);
    }
    else if (p_type == "!" or p_type == "s")
    {
      // Unsafe Single Transmit
      Serial.println("- Unsafe transmit - no hashcode check");
      ret_from = p_from;
      ret_msg = p_value;
      ret_packets = 1;
      state_parser_from = "";
      state_parser_last_index = -1;
      state_parser_max_packets = -1;
      state_parser_msg = "";
    }
    else
    {
      // Failure Reset Message
      Serial.println("Failure reset message (not matched values) " + state_parser_from + " " + p_from + " " + String(state_parser_last_index) + " " + String(p_type));
      state_parser_from = "";
      state_parser_last_index = -1;
      state_parser_max_packets = -1;
      state_parser_msg = "";
      gui_msg_animated("Fehler", "Received not matched values", C_GUI_DELAY_MSG_SHORT_I);
    }
  }
  else
  {
    Serial.println("Ignore message (not matched id)");
    gui_msg_animated("Fehler", "Received not matched id", C_GUI_DELAY_MSG_SHORT_I);
  }

  struct ParserAnsTuple ret = {
      ret_from,
      ret_msg,
      ret_packets};

  return ret;
}