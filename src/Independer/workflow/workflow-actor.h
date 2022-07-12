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
    int selected = gui_selection("Rettungsmenü", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
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
    else if (selected == 1)
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
    int selected = gui_selection("Briefe", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
    {
      String msg_res = gui_input_text("Empfänger (z.B.: 0xMB)", "0x");
      String msg_tx = gui_input_text("Brief", "");
      boolean suc = application_actor_send_msg_to_gateway(msg_res, msg_tx);
      if (!suc)
        db_store_letter(msg_res, msg_tx);
    }
    else if (selected == 1)
      application_actor_query_msgs_from_gateway();
    else if (selected == 2)
    {
      gui_msg_animated("Info", "Leere Briefe\n(Gateway)", C_GUI_DELAY_MSG_SHORT_I);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;clmsg", state_lora_gain);
      delay(C_INDEPENDER_SEND_DELAY_REPEAT);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;clmsg", state_lora_gain);
    }
    else if (selected == 3)
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
    int selected = gui_selection("Rettungsmenü", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
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
    else if (selected == 1)
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
    int selected = gui_selection("Nachrichten", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
    {
      String msg_res = gui_input_text("Empfänger (z.B.: 0xMB)", "0x");
      String msg_tx = gui_input_text("Nachricht", "");
      boolean suc = application_actor_send_msg_actor_to_actor(msg_res, msg_tx);
      if (!suc)
        db_store_msg(msg_res, msg_tx);
    }
    else if (selected == 1)
      multi_actor_background_show_messages();
    else if (selected == 2)
      multi_actor_background_clear_messages();
    else if (selected == 3)
      i_communication_messages_recovery_menu();
    else
      fin_flag = true;
  }
}

void i_communication_menu()
{
  String menu_items[] = {
      "Briefe (Gateway)",
      "Nachrichten (Actor)",
      "Kontakte",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    int selected = gui_selection("Kommunikation", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
      i_communication_letters_menu();
    else if (selected == 1)
      i_communication_messages_menu();
    else if (selected == 2)
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
    int selected = gui_selection("Status Menü", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
      gui_display_prg_animated("Batterie Status (mV)", utils_get_battery(), 1950, 3100, C_GUI_DELAY_MSG_SHORT_I);
    else if (selected == 1)
      gui_display_prg_animated("Sendekontingent (millis)", lora_get_global_tx_time_millis(), 0, 36000, C_GUI_DELAY_MSG_SHORT_I);
    else
      fin_flag = true;
  }
}

void i_actor_functions_test_function_menu()
{
  String menu_items[] = {
      "Erreichbar-Check",
      "Test Ausgabe",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    int selected = gui_selection("Test Menü", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
    {
      String ans = gui_input_text("Empfänger ID (z.B.: 0gMB)", state_gateway_id);
      application_actor_is_available(ans, false);
    }
    else if (selected == 1)
      gui_test();
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
      "Update",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    int selected = gui_selection("Actor Funktionen", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
      i_actor_functions_status_function_menu();
    else if (selected == 1)
    {
      i_actor_functions_test_function_menu();
    }
    else if (selected == 2)
    {
      gui_input_char_no_output();
      fin_flag = true;
    }
    else if (selected == 3)
    {
      gui_msg_animated("Info", "Aktiviere Schlafmodus\n(Actor)", C_GUI_DELAY_MSG_SHORT_I);
      utils_go_to_sleep();
    }
    else if (selected == 4)
      application_actor_who_is_in_my_area();
    else if (selected == 5)
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
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    int selected = gui_selection("Gateway Funktionen", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
    {
      gui_msg_animated("Info", "Aktiviere Schlafmodus\n(Gateway)", C_GUI_DELAY_MSG_SHORT_I);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;slp", state_lora_gain);
      delay(C_INDEPENDER_SEND_DELAY_REPEAT);
      lora_send_msg_single_unsafe(state_my_id, state_gateway_id, "C;slp", state_lora_gain);
    }
    else if(selected == 1){
      gui_msg_animated("Info", "Aktiviere Update-Modus\n(Gateway)", C_GUI_DELAY_MSG_SHORT_I);
      lora_send_msg(state_my_id, state_gateway_id, "C;up;" + state_wifi_ssid + ";" + state_wifi_pw, state_lora_gain);
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
    int selected = gui_selection("Hintergrundsync", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
    {
      gui_msg_animated("Info", "Status Hintergrundsync\n" + multi_actor_get_state_string(), C_GUI_DELAY_MSG_SHORT_I);
    }
    else if (selected == 1)
    {
      gui_msg_animated("Info", "Aktiviere Hintergrundsync", C_GUI_DELAY_MSG_SHORT_I);
      if (!multi_actor_get_state())
        multi_actor_start();
    }
    else if (selected == 2)
    {
      gui_msg_animated("Info", "Deaktiviere Hintergrundsync", C_GUI_DELAY_MSG_SHORT_I);
      if (multi_actor_get_state())
        multi_actor_stop();
    }
    else
      fin_flag = true;
  }
}

void i_setting_wifi_menu()
{
  String menu_items[] = {
      "SSID",
      "Passwort",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    int selected = gui_selection("WIFI", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
      db_save_wifi_ssid(gui_input_text("SSID", state_wifi_ssid));
    else if (selected == 1)
      db_save_wifi_pw(gui_input_text("Passwort", state_wifi_pw));
    else
      fin_flag = true;
  }
}

void i_settings_menu()
{
  String menu_items[] = {
      "Meine ID",
      "Gateway ID",
      "LoRa Gain",
      "Helligkeit",
      "Hintergrundsync",
      "WIFI",
      "Werkseinstellungen",
      "[zurück]"};

  bool fin_flag = false;
  while (!fin_flag)
  {
    int selected = gui_selection("Einstellungen", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

    if (selected == 0)
      db_save_my_id(gui_input_text("Meine ID (z.B.: 0xMB)", state_my_id));
    else if (selected == 1)
      db_save_gateway_id(gui_input_text("Gateway ID (z.B.: 0gMB)", state_gateway_id));
    else if (selected == 2)
    {
      int ans = gui_input_text("LoRa Gain (1-20)", String(state_lora_gain)).toInt();
      if (ans > 20)
        ans = 20;
      if (ans < 1)
        ans = 1;
      db_save_lora_gain(ans);
    }
    else if (selected == 3)
    {
      int ans = gui_input_text("Helligkeit (0-255)", String(state_oled_brightness)).toInt();
      if (ans > 255)
        ans = 255;
      if (ans < 0)
        ans = 0;
      db_save_oled_brightness(ans);
      Heltec.display->setBrightness(state_oled_brightness);
    }
    else if (selected == 4)
      i_setting_bg_syn_menu();
    else if (selected == 5)
      i_setting_wifi_menu();
    else if (selected == 6)
    {
      db_clear();
      ESP.restart();
    }
    else
      fin_flag = true;
  }
}

void workflow_actor_main_menu()
{
  String menu_items[] = {
      "Kommunikation",
      "Actor Funktionen",
      "Gateway Funktionen",
      "Einstellungen",
      "Info"};

  int selected = gui_selection("Independer", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

  if (selected == 0)
    i_communication_menu();
  else if (selected == 1)
    i_actor_functions_menu();
  else if (selected == 2)
    i_gateway_functions_menu();
  else if (selected == 3)
    i_settings_menu();
  else if (selected == 4)
  {
    gui_logo_static(c_product_version, state_my_id, state_gateway_id, c_actor_mode);
    delay(C_GUI_DELAY_STATIC);
  }
  else
    gui_msg_animated("Fehler", "Auswahl " + String(selected) + "\nnicht verfügbar.", C_GUI_DELAY_MSG_MIDDLE_I);
}