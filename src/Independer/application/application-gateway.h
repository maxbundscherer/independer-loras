/*
 * ####################################
 *  Proc Incoming Message Section
 * ####################################
 */

void application_gateway_store_msg(String from, String messageString) {

  messageString = messageString.substring(2, messageString.length());

  String p_receiver_id = "";
  String p_message = "";

  int currentCountsDelimiter = 0;

  for (int i = 0; i < messageString.length(); i++) {

    String current = messageString.substring(i, i + 1);

    if (current == ";") {
      currentCountsDelimiter++;
    } else {
      if (currentCountsDelimiter == 0) p_receiver_id += current;
      if (currentCountsDelimiter == 1) p_message += current;
    }
  }

  Serial.println("Extracted p_receiver_id '" + p_receiver_id + "'");
  Serial.println("Extracted p_message '" + p_message + "'");
  Serial.println("Extracted from '" + from + "'");

  //TODO

}

/*
 * ####################################
 *  Send Messages to Actor (Response to Actor query) Section
 * ####################################
 */

void application_gateway_send_msgs_to_actor(String actorId) {

}