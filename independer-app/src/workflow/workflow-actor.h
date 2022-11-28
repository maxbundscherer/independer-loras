/*
 * ####################################
 *  Menu Section
 * ####################################
 */

void i_communication_letters_recovery_menu()
{
  String menu_items[] = {
      "Erneut senden",
      "Speicher löschen",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Rettungsmenü", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      if (db_has_stored_letter())
      {
        boolean ans = application_actor_send_msg_to_gateway(db_letter_get_rec(), db_letter_get_msg());
        if (ans)
          db_clear_letter();
      }
      else
      {
        gui_msg_animated("Fehler", "Keine Briefe\ngespeichert", C_GUI_DELAY_MSG_SHORT_I);
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
    {
      gui_msg_animated("Hinweis", "Briefe werden\ngelöscht", C_GUI_DELAY_MSG_SHORT_I);
      db_clear_letter();
    }

    else
      fin_flag = true;
  }
}

void i_communication_letters_menu()
{
  String menu_items[] = {
      "Brief schreiben",
      "Briefe abrufen",
      "Briefe leeren",
      "Rettungsmenü",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Briefe", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      S_GUI_INPUT_TEXT msg_res_wrapper = gui_input_text("Empfänger (z.B.: 0xMB)", "0x");
      if (msg_res_wrapper.success)
      {
        if (utils_is_valid_receiver(msg_res_wrapper.value))
        {
          S_GUI_INPUT_TEXT msg_tx_wrapper = gui_input_text("Brief", "");
          if (msg_tx_wrapper.success)
          {
            msg_tx_wrapper.value = utils_encode_data(msg_tx_wrapper.value);
            boolean suc = application_actor_send_msg_to_gateway(msg_res_wrapper.value, msg_tx_wrapper.value);
            if (!suc)
              db_store_letter(msg_res_wrapper.value, msg_tx_wrapper.value);
          }
        }
        else
        {
          gui_msg_animated("Fehler", "Ungültiger Empfänger", C_GUI_DELAY_MSG_SHORT_I);
        }
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
      application_actor_query_msgs_from_gateway();
    else if (selected_wrapper.success and selected_wrapper.value == 2)
    {
      gui_msg_animated("Info", "Leere Briefe\n(Gateway)", C_GUI_DELAY_MSG_SHORT_I);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;clmsg", state_lora_gain);
      delay(C_INDEPENDER_SEND_DELAY_REPEAT);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;clmsg", state_lora_gain);
    }
    else if (selected_wrapper.success and selected_wrapper.value == 3)
      i_communication_letters_recovery_menu();
    else
      fin_flag = true;
  }
}

void i_communication_messages_recovery_menu()
{
  String menu_items[] = {
      "Erneut senden",
      "Speicher löschen",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Rettungsmenü", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      if (db_has_stored_msg())
      {
        boolean ans = application_actor_send_msg_actor_to_actor(db_msg_get_rec(), db_msg_get_msg());
        if (ans)
          db_clear_msg();
      }
      else
      {
        gui_msg_animated("Fehler", "Keine Nachrichten\ngespeichert", C_GUI_DELAY_MSG_SHORT_I);
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
    {
      gui_msg_animated("Hinweis", "Nachrichten werden\ngelöscht", C_GUI_DELAY_MSG_SHORT_I);
      db_clear_msg();
    }

    else
      fin_flag = true;
  }
}

void i_communication_messages_menu()
{
  String menu_items[] = {
      "Nachricht schreiben",
      "Nachrichten lesen",
      "Nachrichten leeren",
      "Rettungsmenü",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Nachrichten", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      S_GUI_INPUT_TEXT msg_res_wrapper = gui_input_text("Empfänger (z.B.: 0xMB)", "0x");

      if (msg_res_wrapper.success)
      {

        if (utils_is_valid_receiver(msg_res_wrapper.value))
        {
          S_GUI_INPUT_TEXT msg_tx_wrapper = gui_input_text("Nachricht", "");
          if (msg_tx_wrapper.success)
          {
            msg_tx_wrapper.value = utils_encode_data(msg_tx_wrapper.value);
            boolean suc = application_actor_send_msg_actor_to_actor(msg_res_wrapper.value, msg_tx_wrapper.value);
            if (!suc)
              db_store_msg(msg_res_wrapper.value, msg_tx_wrapper.value);
          }
        }
        else
        {
          gui_msg_animated("Fehler", "Ungültiger Empfänger", C_GUI_DELAY_MSG_SHORT_I);
        }
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
      multi_actor_background_show_messages();
    else if (selected_wrapper.success and selected_wrapper.value == 2)
      multi_actor_background_clear_messages();
    else if (selected_wrapper.success and selected_wrapper.value == 3)
      i_communication_messages_recovery_menu();
    else
      fin_flag = true;
  }
}

void i_communication_chat_menu()
{
  String menu_items[] = {
      "Nachricht schreiben",
      "Chat abrufen",
      "Chat leeren",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Chat", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      S_GUI_INPUT_TEXT msg_res_wrapper = gui_input_text("Empfänger (z.B.: 0xMB)", "0x");
      if (msg_res_wrapper.success)
      {
        if (utils_is_valid_receiver(msg_res_wrapper.value))
        {
          S_GUI_INPUT_TEXT msg_tx_wrapper = gui_input_text("Inhalt", "");
          if (msg_tx_wrapper.success)
          {

            msg_tx_wrapper.value = utils_encode_data(msg_tx_wrapper.value);

            gui_msg_static("Hinweis", "Nachricht wird\ngesendet");
            boolean suc = wifi_send_chat_message(msg_res_wrapper.value, state_my_id, msg_tx_wrapper.value, state_wifi_server_url, state_wifi_server_port, state_wifi_server_timeout, state_wifi_server_device_token);
            if (suc)
            {
              gui_msg_animated("Info", "Nachricht gesendet", C_GUI_DELAY_MSG_SHORT_I);
            }
            else
            {
              gui_msg_animated("Info", "Nachricht konnte\nnicht versendet werden", C_GUI_DELAY_MSG_SHORT_I);
            }
          }
        }
        else
        {
          gui_msg_animated("Fehler", "Ungültiger Empfänger", C_GUI_DELAY_MSG_SHORT_I);
        }
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
      application_actor_query_msgs_from_internet(state_my_id);
    else if (selected_wrapper.success and selected_wrapper.value == 2)
    {
      gui_msg_static("Hinweis", "Chat wird\ngelöscht...");
      if (wifi_clear_message(state_my_id, state_wifi_server_url, state_wifi_server_port, state_wifi_server_timeout, state_wifi_server_device_token))
        gui_msg_animated("Info", "Chat wurde\ngelöscht.", C_GUI_DELAY_MSG_SHORT_I);
      else
        gui_msg_animated("Info", "Chat konnte nicht\ngelöscht werden.", C_GUI_DELAY_MSG_SHORT_I);
    }
    else
      fin_flag = true;
  }
}

void i_communication_menu()
{
  String menu_items[] = {
      "Briefe (Gateway)",
      "Nachrichten (Actor)",
      "Chat (Internet)",
      "Kontakte",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Kommunikation", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
      i_communication_letters_menu();
    else if (selected_wrapper.success and selected_wrapper.value == 1)
      i_communication_messages_menu();
    else if (selected_wrapper.success and selected_wrapper.value == 2)
      i_communication_chat_menu();
    else if (selected_wrapper.success and selected_wrapper.value == 3)
      gui_msg_animated("Info", "Leider ist die Funktion\n'Kontakte'\nnoch nicht verfügbar.", C_GUI_DELAY_MSG_SHORT_I);

    else
      fin_flag = true;
  }
}

void i_actor_functions_status_function_menu()
{
  String menu_items[] = {
      "Batterie Status",
      "Sendekontingent",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {

    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Status Menü", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
      gui_display_prg_animated("Batterie Status (mV)", utils_get_battery(), 1950, 3100, C_GUI_DELAY_MSG_SHORT_I);
    else if (selected_wrapper.success and selected_wrapper.value == 1)
      gui_display_prg_animated("Sendekontingent (millis)", time_lora_quota_update_get_millis(), 0, (C_LORA_QUOTA_CONTINGENT_SECONDS * 1000), C_GUI_DELAY_MSG_SHORT_I);
    else
      fin_flag = true;
  }
}

void i_actor_functions_test_function_menu()
{
  String menu_items[] = {
      "Erreichbar-Check",
      "Test Ausgabe",
      "Test Datenaustausch",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Test Menü", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      S_GUI_INPUT_TEXT ans_wrapper = gui_input_text("Empfänger (z.B.: 0xMB)", "0x");
      if (ans_wrapper.success)
      {
        if (utils_is_valid_receiver(ans_wrapper.value))
        {
          application_actor_is_available(ans_wrapper.value, false);
        }
        else
        {
          gui_msg_animated("Fehler", "Ungültiger Empfänger", C_GUI_DELAY_MSG_SHORT_I);
        }
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
      gui_test();
    else if (selected_wrapper.success and selected_wrapper.value == 2)
      application_actor_large_data_test();
    else
      fin_flag = true;
  }
}

void i_actor_functions_menu()
{
  String menu_items[] = {
      "Status Menü",
      "Test Menü",
      "Standby",
      "Schlaf Modus",
      "Umgebungs-Scan",
      "Sync",
      "Update",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Actor Funktionen", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
      i_actor_functions_status_function_menu();
    else if (selected_wrapper.success and selected_wrapper.value == 1)
    {
      i_actor_functions_test_function_menu();
    }
    else if (selected_wrapper.success and selected_wrapper.value == 2)
    {
      gui_input_char_no_output(true);
      fin_flag = true;
    }
    else if (selected_wrapper.success and selected_wrapper.value == 3)
    {
      gui_msg_animated("Info", "Aktiviere Schlafmodus\n(Actor)", C_GUI_DELAY_MSG_SHORT_I);
      utils_go_to_sleep(true);
    }
    else if (selected_wrapper.success and selected_wrapper.value == 4)
      application_actor_who_is_in_my_area();
    else if (selected_wrapper.success and selected_wrapper.value == 5)
    {
      String d = wifi_auto_sync(state_my_id, state_wifi_server_url, state_wifi_server_port, state_wifi_server_timeout, state_wifi_server_device_token, boot_state_count);
      if (d != "")
      {
        gui_msg_long_text("Auto-Sync", d);
      }
      else
      {
        gui_msg_animated("Info", "Keine Daten", C_GUI_DELAY_MSG_SHORT_I);
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 6)
      ota_start();
    else
      fin_flag = true;
  }
}

void i_gateway_functions_menu()
{
  String menu_items[] = {
      "Schlaf Modus",
      "Update",
      "Einrichtung",
      "Werkseinstellungen",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Gateway Funktionen", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      gui_msg_animated("Info", "Aktiviere Schlafmodus\n(Gateway)", C_GUI_DELAY_MSG_SHORT_I);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;slp", state_lora_gain);
      delay(C_INDEPENDER_SEND_DELAY_REPEAT);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;slp", state_lora_gain);
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
    {
      gui_msg_animated("Info", "Aktiviere Update-Modus\n(Gateway)", C_GUI_DELAY_MSG_SHORT_I);
      String sendString = "C;up;" + utils_encode_data(state_wifi_ssid) + ";" + utils_encode_data(state_wifi_pw);
      lora_send_msg(state_my_id, state_gateway_id, sendString, state_lora_gain);
    }
    else if (selected_wrapper.success and selected_wrapper.value == 2)
    {
      S_GUI_INPUT_TEXT msg_showed_id_wrapper = gui_input_text("Angezeigte ID (z.B.: 0g01)", "0g");
      if (msg_showed_id_wrapper.success)
      {
        if (utils_is_valid_receiver(msg_showed_id_wrapper.value))
        {
          S_GUI_INPUT_TEXT msg_gateway_id_wrapper = gui_input_text("Gateway ID (z.B.: 0g01)", "0g");
          if (msg_gateway_id_wrapper.success)
          {
            if (utils_is_valid_receiver(msg_gateway_id_wrapper.value))
            {
              gui_msg_static("Info", "Prüfe ID");
              if (wifi_register_device_gateway(state_my_id, msg_gateway_id_wrapper.value, state_wifi_server_url, state_wifi_server_port, state_wifi_server_timeout, state_wifi_server_device_token))
              {
                gui_msg_static("Info", "Sende Konfiguration");
                String sendString = "C;init;" + utils_encode_data(state_wifi_ssid) + ";" + utils_encode_data(state_wifi_pw) + ";" + utils_encode_data(msg_gateway_id_wrapper.value);
                lora_send_msg(state_my_id, msg_showed_id_wrapper.value, sendString, state_lora_gain);
              }
              else
              {
                gui_msg_animated("Fehler", "ID nicht im\ngültig!", C_GUI_DELAY_MSG_SHORT_I);
              }
            }
            else
              gui_msg_animated("Fehler", "Ungültige ID", C_GUI_DELAY_MSG_SHORT_I);
          }
        }
        else
          gui_msg_animated("Fehler", "Ungültige ID", C_GUI_DELAY_MSG_SHORT_I);
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 3)
    {
      gui_msg_animated("Info", "Werkseinstellungen\n(Gateway)", C_GUI_DELAY_MSG_SHORT_I);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;clgat", state_lora_gain);
      delay(C_INDEPENDER_SEND_DELAY_REPEAT);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;clgat", state_lora_gain);
    }
    else
      fin_flag = true;
  }
}

void i_setting_bg_syn_menu()
{
  String menu_items[] = {
      "Status",
      "Aktivieren",
      "Deaktivieren",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Hintergrundsync", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      gui_msg_animated("Info", "Status Hintergrundsync\n" + multi_actor_get_state_string(), C_GUI_DELAY_MSG_SHORT_I);
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
    {
      gui_msg_animated("Info", "Aktiviere Hintergrundsync", C_GUI_DELAY_MSG_SHORT_I);
      if (!multi_actor_get_state())
        multi_actor_start();
    }
    else if (selected_wrapper.success and selected_wrapper.value == 2)
    {
      gui_msg_animated("Info", "Deaktiviere Hintergrundsync", C_GUI_DELAY_MSG_SHORT_I);
      if (multi_actor_get_state())
        multi_actor_stop();
    }
    else
      fin_flag = true;
  }
}

void i_setting_auto_sleep_menu()
{
  String menu_items[] = {
      "Status",
      "Aktivieren",
      "Deaktivieren",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Auto-Schlaf", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      String f = "Inaktiv";
      if (state_auto_sleep_enabled)
        f = "Aktiv";
      gui_msg_animated("Info", "Status Auto-Schlaf\n" + f, C_GUI_DELAY_MSG_SHORT_I);
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
    {
      gui_msg_animated("Info", "Aktiviere Auto-Schlaf", C_GUI_DELAY_MSG_SHORT_I);
      db_save_auto_sleep_enabled(1);
    }
    else if (selected_wrapper.success and selected_wrapper.value == 2)
    {
      gui_msg_animated("Info", "Deaktiviere Auto-Schlaf", C_GUI_DELAY_MSG_SHORT_I);
      db_save_auto_sleep_enabled(0);
    }
    else
      fin_flag = true;
  }
}

void i_setting_wifi_menu()
{
  String menu_items[] = {
      "Automatisch",
      "Testen",
      "(Manuell) SSID",
      "(Manuell) Passwort",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("WIFI", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
      application_actor_automatic_wifi(true);
    else if (selected_wrapper.success and selected_wrapper.value == 1)
    {
      gui_msg_static("Info", "Teste WiFi\n'" + state_wifi_ssid + "'");
      if (wifi_check_status())
      {
        gui_msg_animated("Info", "WiFi\nOk", C_GUI_DELAY_MSG_SHORT_I);
      }
      else
      {
        gui_msg_animated("Fehler", "WiFi\nFehler", C_GUI_DELAY_MSG_SHORT_I);
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 2)
    {
      S_GUI_INPUT_TEXT s = gui_input_text("SSID", state_wifi_ssid);
      if (s.success)
        db_save_wifi_ssid(s.value);
    }
    else if (selected_wrapper.success and selected_wrapper.value == 3)
    {
      S_GUI_INPUT_TEXT s = gui_input_text("Passwort", state_wifi_pw);
      if (s.success)
        db_save_wifi_pw(s.value);
    }
    else
      fin_flag = true;
  }
}

void i_setting_server_menu()
{
  String menu_items[] = {
      // "URL",
      // "Port",
      "Timeout",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Server", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    // if (selected_wrapper.success and selected_wrapper.value == 0)
    // {
    //   S_GUI_INPUT_TEXT s = gui_input_text("URL", state_wifi_server_url);
    //   if (s.success)
    //     db_save_wifi_server_url(s.value);
    // }
    // else if (selected_wrapper.success and selected_wrapper.value == 1)
    // {
    //   S_GUI_INPUT_TEXT ans_wrapper = gui_input_text("Port (z.B. 5000)", String(state_wifi_server_port));
    //   if (ans_wrapper.success)
    //     db_save_wifi_server_port(ans_wrapper.value.toInt());
    // }
    if (selected_wrapper.success and selected_wrapper.value == 0)
    {

      S_GUI_INPUT_TEXT ans_wrapper = gui_input_text("Timeout (z.B. 5000)", String(state_wifi_server_timeout));
      if (ans_wrapper.success)
        db_save_wifi_server_timeout(ans_wrapper.value.toInt());
    }
    else
      fin_flag = true;
  }
}

void i_setting_time()
{
  String menu_items[] = {
      "Zeit sync/anzeigen",
      "Zeit anzeigen",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("Zeit", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      gui_msg_static("Hinweis", "Frage Zeit\nab ...");
      String r = time_sync_get_ntp_and_connect();
      gui_msg_animated("Zeit", "Empfangen\n'" + r + "'", C_GUI_DELAY_MSG_MIDDLE_I);
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
    {
      String r = time_get_from_local();
      gui_msg_animated("Zeit", "Lokal\n'" + r + "'", C_GUI_DELAY_MSG_MIDDLE_I);
    }
    else
      fin_flag = true;
  }
}

void i_settings_menu()
{
  String menu_items[] = {
      // "Meine ID",
      I18N_ACTOR_SETTINGS_MENU_GID,
      I18N_ACTOR_SETTINGS_MENU_LORA_GAIN,
      I18N_ACTOR_SETTINGS_MENU_BRI,
      I18N_ACTOR_SETTINGS_MENU_BACKGROUND_SYNC,
      I18N_ACTOR_SETTINGS_MENU_AUTO_SLP,
      I18N_ACTOR_SETTINGS_MENU_WIFI,
      I18N_ACTOR_SETTINGS_MENU_SERVER,
      I18N_ACTOR_SETTINGS_MENU_TIME,
      I18N_ACTOR_SETTINGS_MENU_RESET,
      I18N_MENU_GO_BACK};

  bool fin_flag = false;
  while (!fin_flag)
  {
    S_GUI_SELECTION_ITEM selected_wrapper = gui_selection(I18N_ACTOR_SETTINGS_MENU_TITLE, menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    // if (selected_wrapper.success and selected_wrapper.value == 0)
    // {
    //   S_GUI_INPUT_TEXT m_wrapper = gui_input_text("Meine ID (z.B.: 0xMB)", state_my_id);
    //   if (m_wrapper.success)
    //   {
    //     if (utils_is_valid_receiver(m_wrapper.value))
    //     {
    //       db_save_my_id(m_wrapper.value);
    //     }
    //     else
    //     {
    //       gui_msg_animated("Info", "Ungültige ID", C_GUI_DELAY_MSG_SHORT_I);
    //     }
    //   }
    // }
    if (selected_wrapper.success and selected_wrapper.value == 0)
    {
      S_GUI_INPUT_TEXT m_wrapper = gui_input_text(I18N_ACTOR_SETTINGS_MENU_GID, state_gateway_id);
      if (m_wrapper.success)
      {
        if (utils_is_valid_receiver(m_wrapper.value))
        {
          db_save_gateway_id(m_wrapper.value);
        }
        else
        {
          gui_msg_animated(I18N_ERROR_TITLE, I18N_ACTOR_SETTINGS_MENU_ERR_INV_ID, C_GUI_DELAY_MSG_SHORT_I);
        }
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 1)
    {
      S_GUI_INPUT_TEXT ans_wrapper = gui_input_text(I18N_ACTOR_SETTINGS_MENU_LORA_GAIN + " (1-20)", String(state_lora_gain));

      if (ans_wrapper.success)
      {
        if (ans_wrapper.value.toInt() > 20)
          ans_wrapper.value = String(20);
        if (ans_wrapper.value.toInt() < 1)
          ans_wrapper.value = String(1);
        db_save_lora_gain(ans_wrapper.value.toInt());
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 2)
    {
      S_GUI_INPUT_TEXT ans_wrapper = gui_input_text(I18N_ACTOR_SETTINGS_MENU_BRI + " (0-255)", String(state_oled_brightness));
      if (ans_wrapper.success)
      {
        if (ans_wrapper.value.toInt() > 255)
          ans_wrapper.value = String(255);
        if (ans_wrapper.value.toInt() < 0)
          ans_wrapper.value = String(0);
        db_save_oled_brightness(ans_wrapper.value.toInt());
        gui_set_screen_brightness(ans_wrapper.value.toInt());
      }
    }
    else if (selected_wrapper.success and selected_wrapper.value == 3)
      i_setting_bg_syn_menu();
    else if (selected_wrapper.success and selected_wrapper.value == 4)
      i_setting_auto_sleep_menu();
    else if (selected_wrapper.success and selected_wrapper.value == 5)
      i_setting_wifi_menu();
    else if (selected_wrapper.success and selected_wrapper.value == 6)
    {
      i_setting_server_menu();
    }
    else if (selected_wrapper.success and selected_wrapper.value == 7)
    {
      i_setting_time();
    }
    else if (selected_wrapper.success and selected_wrapper.value == 8)
    {
      db_clear();
      ESP.restart();
    }
    else
      fin_flag = true;
  }
}

String i_workflow_rewrite_boolean(boolean value)
{
  if (value)
    return I18N_ACTOR_MAIN_REWRITE_BOOL_ACTIV;
  else
    return I18N_ACTOR_MAIN_REWRITE_BOOL_INACTIV;
}

String i_workflow_rewrite_int(int value)
{
  if (1)
    return I18N_ACTOR_MAIN_REWRITE_BOOL_ACTIV;
  else
    return I18N_ACTOR_MAIN_REWRITE_BOOL_INACTIV;
}

void workflow_actor_main_menu()
{
  String menu_items[] = {
      I18N_ACTOR_MAIN_MENU_COMMUNICATIONS,
      I18N_ACTOR_MAIN_MENU_ACTOR_FUNCTIONS,
      I18N_ACTOR_MAIN_MENU_GATEWAY_FUNCTIONS,
      I18N_ACTOR_MAIN_MENU_SETTINGS,
      I18N_ACTOR_MAIN_MENU_INFO};

  S_GUI_SELECTION_ITEM selected_wrapper = gui_selection(I18N_ACTOR_MAIN_MENU_TITLE, menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

  if (selected_wrapper.success and selected_wrapper.value == 0)
    i_communication_menu();
  else if (selected_wrapper.success and selected_wrapper.value == 1)
    i_actor_functions_menu();
  else if (selected_wrapper.success and selected_wrapper.value == 2)
    i_gateway_functions_menu();
  else if (selected_wrapper.success and selected_wrapper.value == 3)
    i_settings_menu();
  else if (selected_wrapper.success and selected_wrapper.value == 4)
  {
    gui_logo_static(c_product_version, state_my_id, state_gateway_id, c_actor_mode, state_gateway_owner);
    gui_input_char_no_output(false);

    gui_msg_static(I18N_ACTOR_MAIN_MENU_INFO_PREFIX + " (1/5)", I18N_ACTOR_MAIN_MENU_INFO_VERSION + c_product_version + I18N_ACTOR_MAIN_MENU_INFO_ID + state_my_id + I18N_ACTOR_MAIN_MENU_INFO_GID + state_gateway_id);
    gui_input_char_no_output(false);

    gui_msg_static(I18N_ACTOR_MAIN_MENU_INFO_PREFIX + " (2/5)", I18N_ACTOR_MAIN_MENU_INFO_ACTOR_MODE + i_workflow_rewrite_boolean(c_actor_mode) + I18N_ACTOR_MAIN_MENU_INFO_DEVELOPER + i_workflow_rewrite_boolean(c_dev_mode) + I18N_ACTOR_MAIN_MENU_INFO_LORA_GAIN + state_lora_gain);
    gui_input_char_no_output(false);

    gui_msg_static(I18N_ACTOR_MAIN_MENU_INFO_PREFIX + " (3/5)", I18N_ACTOR_MAIN_MENU_INFO_BRIGHTNESS + String(state_oled_brightness) + I18N_ACTOR_MAIN_MENU_INFO_WIFI + state_wifi_ssid + I18N_ACTOR_MAIN_MENU_INFO_WIFI_T + state_wifi_server_timeout);
    gui_input_char_no_output(false);

    gui_msg_static(I18N_ACTOR_MAIN_MENU_INFO_PREFIX + " (4/5)", I18N_ACTOR_MAIN_MENU_INFO_BACKGROUND_SYNC + i_workflow_rewrite_boolean(multi_actor_get_state()) + I18N_ACTOR_MAIN_MENU_INFO_AUTO_SLP + i_workflow_rewrite_int(state_auto_sleep_enabled) + I18N_ACTOR_MAIN_MENU_INFO_BATTERY + String(utils_get_battery()) + I18N_ACTOR_MAIN_MENU_INFO_BATTERY_U);
    gui_input_char_no_output(false);

    gui_msg_static(I18N_ACTOR_MAIN_MENU_INFO_PREFIX + " (5/5)", I18N_ACTOR_MAIN_MENU_INFO_TIME + time_get_from_local());
    gui_input_char_no_output(false);
  }
  else if (selected_wrapper.success == false)
  {
  }
  else
    gui_msg_animated(I18N_ERROR_TITLE, I18N_ACTOR_MAIN_MENU_ERR, C_GUI_DELAY_MSG_MIDDLE_I);
}