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

S_I_Application_Gateway_Message state_gateway_messages[100];
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

  lora_send_msg(state_gateway_id, actorId, "A;0;", state_lora_gain);

  for (int i = 0; i < state_gateway_messages_count; i++)
  {
    Serial.println("Stored Message '" + state_gateway_messages[i].msgAuthor + " " + state_gateway_messages[i].msgReceiver + " " + state_gateway_messages[i].msgContent + "'");
  }

  // TODO
}