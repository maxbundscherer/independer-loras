#define C_APP_GATEWAY_MAX_MESSAGES 100

/*
 * ####################################
 *  Proc Incoming Message Section
 * ####################################
 */

struct S_I_Application_Gateway_Message
{
  String msgAuthor;
  String msgReceiver;
  String msgContent;
};

S_I_Application_Gateway_Message state_gateway_messages[C_APP_GATEWAY_MAX_MESSAGES];
int state_gateway_messages_count = 0;

/**
 * @return int number of stored messages
 */
int application_gateway_store_msg(String from, String messageString)
{

  messageString = messageString.substring(2, messageString.length());

  String p_receiver_id = "";
  String p_message = "";

  int currentCountsDelimiter = 0;

  for (int i = 0; i < messageString.length(); i++)
  {

    String current = messageString.substring(i, i + 1);

    if (current == ";")
    {
      currentCountsDelimiter++;
    }
    else
    {
      if (currentCountsDelimiter == 0)
        p_receiver_id += current;
      if (currentCountsDelimiter == 1)
        p_message += current;
    }
  }

  // Serial.println("Extracted p_receiver_id '" + p_receiver_id + "'");
  // Serial.println("Extracted p_message '" + p_message + "'");
  // Serial.println("Extracted from '" + from + "'");

  state_gateway_messages[state_gateway_messages_count] = {from, p_receiver_id, p_message};
  state_gateway_messages_count++;

  return state_gateway_messages_count;
}

/*
 * ####################################
 *  Send Messages to Actor (Response to Actor query) Section
 * ####################################
 */

void application_gateway_send_msgs_to_actor(String actorId)
{

  int msgCounter = 0;
  String msgString = "";

  for (int i = 0; i < state_gateway_messages_count; i++)
  {

    if (state_gateway_messages[i].msgReceiver == actorId)
    {
      String m = state_gateway_messages[i].msgAuthor + ";" + state_gateway_messages[i].msgContent;
      if (msgCounter == 0)
        msgString = msgString + m;
      else
        msgString = msgString + ";" + m;

      msgCounter++;
    }
  }

  String ret_string = "A;" + String(msgCounter) + ";" + msgString;

  lora_send_msg(state_gateway_id, actorId, ret_string, state_lora_gain);
}

/*
 * ####################################
 *  Clear user messages Section
 * ####################################
 */
/**
 * @return int number of stored messages
 */
int application_gateway_clear_user_msgs(String actorId)
{

  S_I_Application_Gateway_Message new_state_gateway_messages[C_APP_GATEWAY_MAX_MESSAGES];
  int new_state_gateway_messages_count = 0;

  for (int i = 0; i < state_gateway_messages_count; i++)
  {

    if (state_gateway_messages[i].msgReceiver != actorId)
    {
      new_state_gateway_messages[new_state_gateway_messages_count] = {state_gateway_messages[i].msgAuthor, state_gateway_messages[i].msgReceiver, state_gateway_messages[i].msgContent};
      new_state_gateway_messages_count++;
    }
  }

  for (int i = 0; i < new_state_gateway_messages_count; i++)
  {
    state_gateway_messages[i] = new_state_gateway_messages[i];
  }

  state_gateway_messages_count = new_state_gateway_messages_count;

  return state_gateway_messages_count;
}

/*
 * ####################################
 *  Update Section
 * ####################################
 */

int application_gateway_update(String credentialsString)
{

  credentialsString = credentialsString.substring(5, credentialsString.length());

  String p_ssid = "";
  String p_pw = "";

  int currentCountsDelimiter = 0;

  for (int i = 0; i < credentialsString.length(); i++)
  {

    String current = credentialsString.substring(i, i + 1);

    if (current == ";")
    {
      currentCountsDelimiter++;
    }
    else
    {
      if (currentCountsDelimiter == 0)
        p_ssid += current;
      if (currentCountsDelimiter == 1)
        p_pw += current;
    }
  }

  Serial.println("Update Mode '" + p_ssid + +" '" + p_pw + "'");

  state_wifi_ssid = p_ssid;
  state_wifi_pw = p_pw;

  ota_start();
}