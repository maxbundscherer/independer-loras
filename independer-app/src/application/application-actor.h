/*
 * ####################################
 *  Who is near? Section
 * ####################################
 */

struct S_I_Application_Device_Item
{
  String deviceId;
  String deviceMsg;
  String receivedRssi;
  String attempt;
};

void application_actor_who_is_in_my_area()
{

  boolean sync_was_on_flag = multi_actor_get_state();

  if (sync_was_on_flag)
  {
    multi_actor_stop();
  }

  int c_max_ping_retries = 3;                                                             // Maximial attempts to receive
  int c_max_ping_delta = C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR;                            // Waiting 1ms between receiving
  int c_max_ping_max_receive_attempts = (C_INDEPENDER_SCAN_MS + 2000) / c_max_ping_delta; // Waiting approx C_INDEPENDER_SCAN_MS seconds for next packet

  S_I_Application_Device_Item collected_db[30];
  int collected_counter = 0;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries)
  {
    l_attempt++;

    lora_send_msg_short_message(state_my_id, "*", C_INDEPENDER_SHORT_MESSAGE_CHAR_ALL, state_lora_gain);
    delay(C_INDEPENDER_SEND_DELAY_REPEAT);
    lora_send_msg_short_message(state_my_id, "*", C_INDEPENDER_SHORT_MESSAGE_CHAR_ALL, state_lora_gain);

    gui_display_prg_static(I18N_ACTOR_APP_ENV_SCAN, l_attempt, 0, c_max_ping_retries);

    int l_cur_receive_attempt = 0;
    while (l_cur_receive_attempt < c_max_ping_max_receive_attempts)
    {
      l_cur_receive_attempt++;

      int packetSize = LoRa.parsePacket();

      if (packetSize)
      {

        String i_res = "";
        while (LoRa.available())
        {
          i_res += LoRa.readString();
        }

        ParserAnsTuple parser_ans = lora_stateful_parse(i_res, state_my_id);

        if (parser_ans.message != "")
        {
          struct S_I_Application_Device_Item ret = {
              parser_ans.from,
              parser_ans.message,
              String(LoRa.packetRssi(), DEC),
              String(l_attempt)};
          collected_db[collected_counter] = ret;
          collected_counter++;
        }
      }

      delay(c_max_ping_delta);
    }
  }

  if (collected_counter > 0)
  {
    String gui_items[collected_counter + 1]; // Add + 1 (go back item)

    for (int i = 0; i < collected_counter; i++)
    {
      String r = collected_db[i].attempt + ": (" + collected_db[i].deviceId + ") '" + collected_db[i].deviceMsg + I18N_ACTOR_APP_ENV_SCAN_RS + collected_db[i].receivedRssi;
      // Serial.println("Scan Item '" + r + "'");
      gui_items[i] = r;
    }

    gui_items[collected_counter] = I18N_MENU_GO_BACK; // Add go back item

    boolean hasComp = false;
    while (!hasComp)
    {
      S_GUI_SELECTION_ITEM selected_wrapper = gui_selection(I18N_ACTOR_APP_ENV_SCAN_OUTPUT_T, gui_items, collected_counter - 1 + 1, false); // Add + 1 (go back item)
      if (selected_wrapper.success == false or selected_wrapper.value == collected_counter)
        hasComp = true;
      else
        gui_msg_long_text(I18N_ACTOR_APP_ENV_SCAN_DETAIL_T, gui_items[selected_wrapper.value]);
    }
  }

  if (sync_was_on_flag)
  {
    multi_actor_start();
  }
}

/*
 * ####################################
 *  Is Available Section
 * ####################################
 */

/**
 * @return boolean return if is available
 */
boolean application_actor_is_available(String target_id, boolean flagHideAns, String testSendMsg = C_INDEPENDER_SHORT_MESSAGE_CHAR_SINGLE, int maxRetries = 5, String responseMsgCheck = "", boolean checkResponse = false)
{

  boolean sync_was_on_flag = multi_actor_get_state();

  if (sync_was_on_flag)
  {
    multi_actor_stop();
  }

  int c_max_ping_retries = maxRetries;                                                    // Maximial attempts to receive pong message
  int c_max_ping_delta = C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR;                            // Waiting 1ms between receiving
  int c_max_ping_max_receive_attempts = (C_INDEPENDER_SEND_DELAY * 4) / c_max_ping_delta; // Waiting approx 2 seconds for next packet

  String receivedMsg;
  boolean receivedSuccess = false;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries and !receivedSuccess)
  {
    l_attempt++;

    gui_display_prg_static(I18N_ACTOR_APP_REACH_CH_ATTEMPT, l_attempt, 0, c_max_ping_retries);

    lora_send_msg_short_message(state_my_id, target_id, testSendMsg, state_lora_gain);
    delay(C_INDEPENDER_SEND_DELAY_REPEAT);
    lora_send_msg_short_message(state_my_id, target_id, testSendMsg, state_lora_gain);

    int l_cur_receive_attempt = 0;
    while (l_cur_receive_attempt < c_max_ping_max_receive_attempts and !receivedSuccess)
    {
      l_cur_receive_attempt++;

      boolean appendDebug = !checkResponse;

      struct S_APP_PONG pong_ans = application_independer_pong(target_id, appendDebug);

      if (pong_ans.receivedSomething)
      {
        l_cur_receive_attempt = 0;
      }

      if (pong_ans.receivingCompleted and (!checkResponse or strcmp(pong_ans.message.c_str(), responseMsgCheck.c_str()) == 0)) // TODO: String compare wie in workflow-actor implementieren!
      {
        receivedMsg = pong_ans.message;
        receivedSuccess = true;
      }
      else
      {
        delay(c_max_ping_delta);
      }
    }
  }

  if (receivedSuccess and !flagHideAns)
  {
    gui_msg_animated(I18N_ANS_TITLE, receivedMsg, C_GUI_DELAY_MSG_MIDDLE_I);
  }
  else if (!flagHideAns)
  {
    gui_msg_animated(I18N_ERROR_TITLE, I18N_ACTOR_APP_REACH_ERR_NO_RES, C_GUI_DELAY_MSG_MIDDLE_I);
  }

  if (sync_was_on_flag)
  {
    multi_actor_start();
  }

  return receivedSuccess;
}

/*
 * ####################################
 *  Send Message to Gateway Section
 * ####################################
 */

boolean application_actor_send_msg_to_gateway(String receiverId, String userMsg)
{

  boolean sync_was_on_flag = multi_actor_get_state();

  if (sync_was_on_flag)
  {
    multi_actor_stop();
  }

  boolean isAvailable = application_actor_is_available(state_gateway_id, true);

  if (!isAvailable)
  {
    gui_msg_animated(I18N_ERROR_TITLE, I18N_ACTOR_APP_SEND_TO_GATEWAY_ERR_GA_NOT_REACH, C_GUI_DELAY_MSG_MIDDLE_I);
    if (sync_was_on_flag)
    {
      multi_actor_start();
    }
    return false;
  }

  int c_max_ping_retries = 3;                                                             // Maximial attempts to receive pong message
  int c_max_ping_delta = C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR;                            // Waiting 1ms between receiving
  int c_max_ping_max_receive_attempts = (C_INDEPENDER_SEND_DELAY * 4) / c_max_ping_delta; // Waiting approx 2 seconds for next packet

  boolean sendSuccess = false;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries and !sendSuccess)
  {
    l_attempt++;

    gui_display_prg_static(I18N_ACTOR_APP_SEND_TO_GATEWAY_SEND_ATT, l_attempt, 0, c_max_ping_retries);

    delay(C_INDEPENDER_SEND_DELAY);

    lora_send_msg(state_my_id, state_gateway_id, "M;" + receiverId + ";" + userMsg, state_lora_gain);

    int l_cur_receive_attempt = 0;
    while (l_cur_receive_attempt < c_max_ping_max_receive_attempts and !sendSuccess)
    {
      l_cur_receive_attempt++;

      struct S_APP_PONG pong_ans = application_independer_pong(state_gateway_id, false);

      if (pong_ans.receivedSomething)
      {
        l_cur_receive_attempt = 0;
      }

      if (pong_ans.receivingCompleted and pong_ans.message == "A;ok")
      {
        sendSuccess = true;
      }
      else
      {
        delay(c_max_ping_delta);
      }
    }
  }

  if (sync_was_on_flag)
  {
    multi_actor_start();
  }

  if (sendSuccess)
  {
    gui_msg_animated(I18N_INFO_TITLE, I18N_ACTOR_APP_SEND_TO_GATEWAY_SEND_SUC, C_GUI_DELAY_MSG_MIDDLE_I);
  }
  else
  {
    gui_msg_animated(I18N_ERROR_TITLE, I18N_ACTOR_APP_SEND_TO_GATEWAY_SEND_ERR, C_GUI_DELAY_MSG_MIDDLE_I);
  }

  return sendSuccess;
}

/*
 * ####################################
 *  Query Messages from Gateway Section
 * ####################################
 */

void application_actor_query_msgs_from_gateway()
{

  boolean sync_was_on_flag = multi_actor_get_state();

  if (sync_was_on_flag)
  {
    multi_actor_stop();
  }

  int c_max_ping_retries = 3;                                                             // Maximial attempts to receive pong message
  int c_max_ping_delta = C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR;                            // Waiting 1ms between receiving
  int c_max_ping_max_receive_attempts = (C_INDEPENDER_SEND_DELAY * 4) / c_max_ping_delta; // Waiting approx 2 seconds for next packet

  boolean resSuccess = false;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries and !resSuccess)
  {
    l_attempt++;

    gui_display_prg_static(I18N_ACTOR_APP_QUERY_GATEWAY_ATT, l_attempt, 0, c_max_ping_retries);

    delay(C_GUI_DELAY_STATIC_SHORT);

    lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "Q;msg", state_lora_gain);
    delay(C_INDEPENDER_SEND_DELAY_REPEAT);
    lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "Q;msg", state_lora_gain);

    int l_cur_receive_attempt = 0;
    while (l_cur_receive_attempt < c_max_ping_max_receive_attempts and !resSuccess)
    {
      l_cur_receive_attempt++;

      struct S_APP_PONG pong_ans = application_independer_pong(state_gateway_id, false);

      if (pong_ans.receivedSomething)
      {
        l_cur_receive_attempt = 0;
      }

      if (pong_ans.receivingCompleted and pong_ans.message.startsWith("A;"))
      {
        resSuccess = true;

        pong_ans.message = pong_ans.message.substring(2, pong_ans.message.length());

        // Get Num of Messages
        int numMessages = 0;

        String m_buffer_nm = "";
        int currentCountsDelimiter = 0;
        boolean finParser = false;
        for (int i_single_char = 0; i_single_char < pong_ans.message.length() and !finParser; i_single_char++)
        {
          String current = pong_ans.message.substring(i_single_char, i_single_char + 1);
          if (current == ";")
            currentCountsDelimiter++;
          else
          {
            if (currentCountsDelimiter == 0)
              m_buffer_nm += current;
            else if (currentCountsDelimiter == 1)
            {
              pong_ans.message = pong_ans.message.substring(i_single_char, pong_ans.message.length());
              numMessages = m_buffer_nm.toInt();
              finParser = true;
            }
          }
        }

        if (numMessages > 0)
        {

          // Get Messages
          String gui_items[numMessages + 1]; // +1 for go back
          int lastDelimiterIndex = 0;

          for (int i_msg = 0; i_msg < numMessages; i_msg++)
          {

            String r = "";

            String tmp = pong_ans.message.substring(lastDelimiterIndex, pong_ans.message.length());

            // Parse Message Substring

            String m_buffer_author = "";
            String m_buffer_msg = "";
            int currentCountsDelimiter = 0;
            boolean finParser = false;
            for (int i_char_t = 0; i_char_t < tmp.length() and !finParser; i_char_t++)
            {
              String current = tmp.substring(i_char_t, i_char_t + 1);
              if (current == ";")
                currentCountsDelimiter++;
              else
              {
                if (currentCountsDelimiter == 0)
                  m_buffer_author += current;
                else if (currentCountsDelimiter == 1)
                  m_buffer_msg += current;

                if (currentCountsDelimiter == 2 or i_char_t == tmp.length() - 1)
                {

                  // Write message
                  r = "(" + m_buffer_author + ") " + utils_decode_data(m_buffer_msg);

                  lastDelimiterIndex = lastDelimiterIndex + i_char_t;
                  finParser = true;
                }
              }
            }

            // Serial.println("Message Item '" + r + "'");
            gui_items[i_msg] = r;
          }

          gui_items[numMessages] = I18N_MENU_GO_BACK; // Add go back item

          boolean hasMesageShown = false;
          while (!hasMesageShown)
          {
            S_GUI_SELECTION_ITEM selected_wrapper = gui_selection(I18N_ACTOR_APP_QUERY_GATEWAY_LETTERS, gui_items, numMessages - 1 + 1, false); // Add + 1 (go back item)
            if (selected_wrapper.success == false or selected_wrapper.value == numMessages)
              hasMesageShown = true;
            else
              gui_msg_long_text(I18N_ACTOR_APP_QUERY_GATEWAY_LETTER, gui_items[selected_wrapper.value]);
          }
        }
        else
          gui_msg_animated(I18N_INFO_TITLE, I18N_ACTOR_APP_QUERY_GATEWAY_ER_NO_LETTER, C_GUI_DELAY_MSG_MIDDLE_I);
      }
      else
      {
        delay(c_max_ping_delta);
      }
    }
  }

  if (sync_was_on_flag)
  {
    multi_actor_start();
  }

  if (!resSuccess)
  {
    gui_msg_animated(I18N_ERROR_TITLE, I18N_ACTOR_APP_QUERY_GATEWAY_ER_NO_RES, C_GUI_DELAY_MSG_MIDDLE_I);
  }
}

/*
 * ####################################
 *  Send Message Actor to Actor Section
 * ####################################
 */

boolean application_actor_send_msg_actor_to_actor(String receiverId, String userMsg)
{

  boolean sync_was_on_flag = multi_actor_get_state();

  if (sync_was_on_flag)
  {
    multi_actor_stop();
  }

  int c_max_ping_retries = 6;                                                             // Maximial attempts to receive pong message
  int c_max_ping_delta = C_INDEPENDER_RES_BETWEEN_DELAY_ACTOR;                            // Waiting 1ms between receiving
  int c_max_ping_max_receive_attempts = (C_INDEPENDER_SEND_DELAY * 4) / c_max_ping_delta; // Waiting approx 2 seconds for next packet

  boolean sendSuccess = false;

  int l_attempt = 0;
  while (l_attempt < c_max_ping_retries and !sendSuccess)
  {
    l_attempt++;

    gui_display_prg_static("Sende Versuch", l_attempt, 0, c_max_ping_retries);

    delay(C_GUI_DELAY_STATIC_SHORT);

    boolean actorAva = application_actor_is_available(receiverId, true, "T", 1, "S", true);

    Serial.println("\nSending Message to Actor " + String(l_attempt) + " of " + String(c_max_ping_retries) + " Actor Ava=" + String(actorAva));

    if (!actorAva)
      delay(C_INDEPENDER_SEND_DELAY);
    else
    {

      delay(C_INDEPENDER_SEND_DELAY);
      lora_send_msg(state_my_id, receiverId, userMsg, state_lora_gain);

      int l_cur_receive_attempt = 0;
      while (l_cur_receive_attempt < c_max_ping_max_receive_attempts and !sendSuccess)
      {
        l_cur_receive_attempt++;

        struct S_APP_PONG pong_ans = application_independer_pong(receiverId, false);

        if (pong_ans.receivedSomething)
        {
          l_cur_receive_attempt = 0;
        }

        if (pong_ans.receivingCompleted and pong_ans.message == "N")
        {
          sendSuccess = true;
        }
        else
        {
          delay(c_max_ping_delta);
        }
      }
    }
  }

  if (sync_was_on_flag)
  {
    multi_actor_start();
  }

  if (sendSuccess)
  {
    gui_msg_animated("Info", "Nachricht wurde\ngesendet", C_GUI_DELAY_MSG_MIDDLE_I);
  }
  else
  {
    gui_msg_animated("Fehler", "Nachricht konnte\nnicht gesendet werden", C_GUI_DELAY_MSG_MIDDLE_I);
  }

  return sendSuccess;
}

/*
 * ####################################
 *  Large Data Test
 * ####################################
 */

void application_actor_large_data_test()
{

  boolean sync_was_on_flag = multi_actor_get_state();

  if (sync_was_on_flag)
  {
    multi_actor_stop();
  }

  gui_msg_animated("Info", "Nachricht 1", 100);
  lora_send_msg(state_my_id, state_gateway_id, "M;" + state_my_id + ";" + utils_encode_data("Du bist mein Sonnenschein!"), state_lora_gain);

  gui_msg_animated("Info", "Nachricht 2", 100);
  lora_send_msg(state_my_id, state_gateway_id, "M;" + state_my_id + ";" + utils_encode_data("Hey. Wie geht es dir?"), state_lora_gain);

  gui_msg_animated("Info", "Nachricht 3", 100);
  lora_send_msg(state_my_id, state_gateway_id, "M;" + state_my_id + ";" + utils_encode_data("Hi. Wie geht es dir? Was machst du so?"), state_lora_gain);

  gui_msg_animated("Info", "Nachricht 4", 100);
  lora_send_msg(state_my_id, state_gateway_id, "M;" + state_my_id + ";" + utils_encode_data("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum iaculis semper diam, sit amet egestas nunc semper sodales. Suspendisse potenti. Nunc semper ac dolor sit amet dapibus. Maecenas dui dolor, fringilla id varius at, posuere at justo. Aenean a lacinia turpis, id maximus nibh. Quisque congue vestibulum feugiat. Nullam id dui gravida nunc aliquam aliquam sed at est. Suspendisse in lacinia leo, sit amet consectetur sem."), state_lora_gain);

  if (sync_was_on_flag)
  {
    multi_actor_start();
  }
}

/*
 * ####################################
 *  Query Messages from Internet Section
 * ####################################
 */

void application_actor_query_msgs_from_internet(String myId)
{

  gui_msg_static("Hinweis", "Nachrichten werden\nabgerufen");
  String ret = wifi_get_chat_messages(myId, state_wifi_server_url, state_wifi_server_port, state_wifi_server_timeout, state_wifi_server_device_token);
  // Serial.println("Query Messages from Internet: '" + ret + "'");

  if (ret != "")
  {

    int startPos = 0;

    for (int i = 0; i < ret.length() and startPos == 0; i++)
    {

      String current = ret.substring(i, i + 1);

      if (current == "{")
      {
        startPos = i;
      }
    }

    if (startPos != 0)
    {
      ret = ret.substring(startPos);
      // Serial.println("Should proc: '" + ret + "'");

      DynamicJsonDocument doc(1024 * 10);

      deserializeJson(doc, ret);
      JsonObject obj = doc.as<JsonObject>();

      // TODO: Speicherüberlaufschutz
      int c_max_messages = 100;
      int i_msg_count = 0;
      boolean hasAllMessages = false;
      String messages_buffer[c_max_messages];

      for (int i = 0; i < c_max_messages and hasAllMessages == false; i++)
      {

        String tString = obj[String(i)];

        if (tString != "null")
        {
          DynamicJsonDocument doc1(1024 * 10);
          deserializeJson(doc1, tString);
          JsonObject d = doc1.as<JsonObject>();
          String m = d["msg"];
          String a = d["author"];
          // Serial.println("Message: " + m + " from " + a);
          messages_buffer[i] = "(" + a + ") " + utils_decode_data(m);
          i_msg_count += 1;
        }
        else
        {
          hasAllMessages = true;
        }
      }

      if (i_msg_count > 0)
      {

        messages_buffer[i_msg_count] = "[zurück]"; // Add go back item

        boolean hasMesageShown = false;
        while (!hasMesageShown)
        {
          S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Chats", messages_buffer, i_msg_count - 1 + 1, false); // Add + 1 (go back item)
          if (selected_wrapper.success == false or selected_wrapper.value == i_msg_count)
            hasMesageShown = true;
          else
            gui_msg_long_text("Chat", messages_buffer[selected_wrapper.value]);
        }
      }
      else
      {
        gui_msg_animated("Hinweis", "Keine Nachrichten\nvorhanden", C_GUI_DELAY_MSG_MIDDLE_I);
      }

      return;
    }
  }

  gui_msg_animated("Fehler", "Chat konnte nicht\nabgerufen werden", C_GUI_DELAY_MSG_MIDDLE_I);

  return;
}

/*
 * ####################################
 *  WIFI Automatic Wifi Section
 * ####################################
 */

S_WIFI_CONFIG_WRAPPER application_actor_automatic_wifi(boolean s_autoSave)
{

  boolean sync_was_on_flag = multi_actor_get_state();

  if (sync_was_on_flag)
  {
    multi_actor_stop();
  }

  gui_msg_static("Hinweis", "Scanne...");
  Serial.println("WiFI AutoSave=" + String(s_autoSave));
  Serial.print("Scan start ... ");
  int n = WiFi.scanNetworks();
  Serial.print(n);
  Serial.println(" network(s) found");

  if (sync_was_on_flag)
  {
    multi_actor_start();
  }

  if (n > 0)
  {

    String gui_items[n + 1];

    gui_items[0] = "[abbrechen]"; // Add go back item

    for (int i = 0; i < n; i++)
    {
      String s = WiFi.SSID(i);
      gui_items[i + 1] = s;
      Serial.println("Found " + s);
    }

    boolean hasMesageShown = false;
    while (!hasMesageShown)
    {
      S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("SSIDs", gui_items, n - 1 + 1, false); // Add + 1 (go back item)
      if (selected_wrapper.success == false or selected_wrapper.value == 0)
        hasMesageShown = true;
      else
      {
        String t_ssid = gui_items[selected_wrapper.value];

        S_GUI_INPUT_TEXT t_password_wrapper = gui_input_text("Passwort", "");

        if (t_password_wrapper.success == false)
        {
          return S_WIFI_CONFIG_WRAPPER{false, "", ""};
        }

        if (s_autoSave)
        {
          Serial.println("Save now WIFI Config");
          db_save_wifi_settings(t_ssid, t_password_wrapper.value);
          gui_msg_animated("Info", "Einstellungen\ngespeichert", C_GUI_DELAY_MSG_SHORT_I);
        }
        else
        {
          Serial.println("Skip now Save WIFI Config");
        }

        return S_WIFI_CONFIG_WRAPPER{true, t_ssid, t_password_wrapper.value};
      }
    }
  }
  else
  {
    gui_msg_animated("Info", "Keine Netzwerke\ngefunden", C_GUI_DELAY_MSG_MIDDLE_I);
  }

  return S_WIFI_CONFIG_WRAPPER{false, "", ""};
}