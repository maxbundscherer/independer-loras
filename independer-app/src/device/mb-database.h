#include <Preferences.h>

const char *c_db_target_key = "independer-app";

Preferences preferences;

/*
 * ####################################
 *  Settings Section
 * ####################################
 */

void i_db_interactive_setup_actor();
void i_db_interactive_setup_gateway();

struct S_WIFI_CONFIG_WRAPPER
{
    boolean success;
    String ssid;
    String password;
};
S_WIFI_CONFIG_WRAPPER application_actor_automatic_wifi(boolean autoSave);

void db_init(boolean is_actor, boolean isDevMode)
{

    preferences.begin(c_db_target_key, true); // Read only

    String current_db_version = preferences.getString("pref_c_ver", "null");

    if (current_db_version == c_product_version)
    {
        Serial.println("Load from DB");
        state_my_id = preferences.getString("pref_my_id", state_my_id);
        state_gateway_id = preferences.getString("pref_gateway_id", state_gateway_id);
        state_gateway_owner = preferences.getString("pref_gat_own", state_gateway_owner);
        state_wifi_ssid = preferences.getString("pref_wifi_ssid", state_wifi_ssid);
        state_wifi_pw = preferences.getString("pref_wifi_pw", state_wifi_pw);
        state_lora_gain = preferences.getInt("pref_lora_gain", state_lora_gain);
        state_oled_brightness = preferences.getInt("pref_oled_bri", state_oled_brightness);
        state_auto_sleep_enabled = preferences.getInt("pref_aslp_en", state_auto_sleep_enabled);

        state_wifi_server_url = preferences.getString("pref_ws_url", state_wifi_server_url);
        state_wifi_server_port = preferences.getInt("pref_ws_port", state_wifi_server_port);
        state_wifi_server_timeout = preferences.getInt("pref_ws_to", state_wifi_server_timeout);

        state_wifi_server_device_token = preferences.getString("pref_ws_dt", state_wifi_server_device_token);

        preferences.end();
    }
    else
    {
        Serial.println("Init DB");
        preferences.clear();
        preferences.end();
        if (!isDevMode)
            gui_msg_animated(I18N_DEVICE_DB_INIT_TITLE, C_TEMPLATE_STRING_THX, C_GUI_DELAY_MSG_LONG_I);
        if (is_actor)
        {
            gui_msg_long_text(I18N_DEVICE_DB_INIT_SUB_TITLE, I18N_DEVICE_DB_INIT_DESC);
            i_db_interactive_setup_actor();
        }
        else
        {
            i_db_interactive_setup_gateway();
        }
    }

    preferences.end();
}

void i_db_write(char *key, String value)
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.putString(key, value);
    preferences.end();
}

void i_db_write(char *key, int value)
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.putInt(key, value);
    preferences.end();
}

void db_save_my_id(String value)
{
    state_my_id = value;
    i_db_write("pref_my_id", value);
}

void db_save_gateway_id(String value)
{
    state_gateway_id = value;
    i_db_write("pref_gateway_id", value);
}

void db_save_wifi_settings(String ssid, String pw)
{
    state_wifi_ssid = ssid;
    state_wifi_pw = pw;

    preferences.begin(c_db_target_key, false); // Read and write
    preferences.putString("pref_wifi_ssid", ssid);
    preferences.putString("pref_wifi_pw", pw);
    preferences.end();
}

void db_save_wifi_ssid(String value)
{
    state_wifi_ssid = value;
    i_db_write("pref_wifi_ssid", value);
}

void db_save_wifi_pw(String value)
{
    state_wifi_pw = value;
    i_db_write("pref_wifi_pw", value);
}

void db_save_lora_gain(int value)
{
    state_lora_gain = value;
    i_db_write("pref_lora_gain", value);
}

void db_save_oled_brightness(int value)
{
    state_oled_brightness = value;
    i_db_write("pref_oled_bri", value);
}

void db_save_auto_sleep_enabled(int value)
{
    state_auto_sleep_enabled = value;
    i_db_write("pref_aslp_en", value);
}

void db_save_wifi_server_url(String value)
{
    state_wifi_server_url = value;
    i_db_write("pref_ws_url", value);
}

void db_save_wifi_server_port(int value)
{
    state_wifi_server_port = value;
    i_db_write("pref_ws_port", value);
}

void db_save_wifi_server_timeout(int value)
{
    state_wifi_server_timeout = value;
    i_db_write("pref_ws_to", value);
}

void db_save_init_config_actor(String wifi_ssid, String wifi_pw, String my_id, String gateway_id, String device_token)
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.putString("pref_wifi_ssid", wifi_ssid);
    preferences.putString("pref_wifi_pw", wifi_pw);
    preferences.putString("pref_my_id", my_id);
    preferences.putString("pref_gateway_id", gateway_id);
    preferences.putString("pref_c_ver", c_product_version);
    preferences.putString("pref_ws_dt", device_token);
    preferences.putString("pref_gat_own", "");
    preferences.end();
}

void db_save_init_config_gateway(String wifi_ssid, String wifi_pw, String gateway_id, String owner_id)
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.putString("pref_wifi_ssid", wifi_ssid);
    preferences.putString("pref_wifi_pw", wifi_pw);
    preferences.putString("pref_my_id", "");
    preferences.putString("pref_gateway_id", gateway_id);
    preferences.putString("pref_c_ver", c_product_version);
    preferences.putString("pref_ws_dt", "");
    preferences.putString("pref_gat_own", owner_id);
    preferences.end();
}

void db_clear()
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.clear();
    preferences.end();
}

/*
 * ####################################
 *  Letters Section
 * ####################################
 */

String db_i_get_content(char *key)
{
    preferences.begin(c_db_target_key, true); // Read only
    String r = preferences.getString(key, "");
    preferences.end();

    return r;
}

boolean db_has_stored_letter()
{
    String rec = db_i_get_content("letter_rec");
    String msg = db_i_get_content("letter_msg");

    if (rec != "" && msg != "")
        return true;
    else
        return false;
}

void db_store_letter(String rec, String msg)
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.putString("letter_rec", rec);
    preferences.putString("letter_msg", msg);
    preferences.end();
}

void db_clear_letter()
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.remove("letter_rec");
    preferences.remove("letter_msg");
    preferences.end();
}

String db_letter_get_rec() { return db_i_get_content("letter_rec"); }
String db_letter_get_msg() { return db_i_get_content("letter_msg"); }

/*
 * ####################################
 *  Msg Section
 * ####################################
 */

boolean db_has_stored_msg()
{
    String rec = db_i_get_content("msg_rec");
    String msg = db_i_get_content("msg_msg");

    if (rec != "" && msg != "")
        return true;
    else
        return false;
}

void db_store_msg(String rec, String msg)
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.putString("msg_rec", rec);
    preferences.putString("msg_msg", msg);
    preferences.end();
}

void db_clear_msg()
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.remove("msg_rec");
    preferences.remove("msg_msg");
    preferences.end();
}

String db_msg_get_rec() { return db_i_get_content("msg_rec"); }
String db_msg_get_msg() { return db_i_get_content("msg_msg"); }

/*
 * ####################################
 *  Interactive Section
 * ####################################
 */

void i_db_interactive_setup_actor()
{

    String t_wifi_ssid = "";
    String t_wifi_pw = "";

    String menu_items[] = {
        I18N_DEVICE_DB_INIT_WIFI_AUTO,
        I18N_DEVICE_DB_INIT_WIFI_MAN_SSID,
        I18N_DEVICE_DB_INIT_WIFI_MAN_PW,
        I18N_DEVICE_DB_INIT_WIFI_OK,
        I18N_DEVICE_DB_INIT_WIFI_OFF};

    bool fin_wifi_config = false;
    while (!fin_wifi_config)
    {
        S_GUI_SELECTION_ITEM selected_wrapper = gui_selection(I18N_DEVICE_DB_INIT_WIFI_TITLE, menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

        if (selected_wrapper.success and selected_wrapper.value == 0)
        {
            S_WIFI_CONFIG_WRAPPER ans = application_actor_automatic_wifi(false);
            if (ans.success)
            {
                t_wifi_ssid = ans.ssid;
                t_wifi_pw = ans.password;
                state_wifi_ssid = t_wifi_ssid;
                state_wifi_pw = t_wifi_pw;
                gui_msg_static(I18N_INFO_TITLE, I18N_DEVICE_DB_INIT_WIFI_FUN_TEST + state_wifi_ssid + "'");
                if (wifi_check_status())
                {
                    fin_wifi_config = true;
                }
                else
                {
                    gui_msg_animated(I18N_ERROR_TITLE, I18N_DEVICE_DB_INIT_WIFI_ERR, C_GUI_DELAY_MSG_SHORT_I);
                }
            }
        }
        else if (selected_wrapper.success and selected_wrapper.value == 1)
        {
            S_GUI_INPUT_TEXT s = gui_input_text(I18N_DEVICE_DB_INIT_WIFI_SSID, t_wifi_ssid);
            if (s.success)
                t_wifi_ssid = s.value;
        }
        else if (selected_wrapper.success and selected_wrapper.value == 2)
        {
            S_GUI_INPUT_TEXT s = gui_input_text(I18N_DEVICE_DB_INIT_WIFI_PW, t_wifi_pw);
            if (s.success)
                t_wifi_pw = s.value;
        }
        else if (selected_wrapper.success and selected_wrapper.value == 3)
        {
            state_wifi_ssid = t_wifi_ssid;
            state_wifi_pw = t_wifi_pw;
            gui_msg_static(I18N_INFO_TITLE, I18N_DEVICE_DB_INIT_WIFI_FUN_TEST + state_wifi_ssid + "'");
            if (wifi_check_status())
            {
                fin_wifi_config = true;
            }
            else
            {
                gui_msg_animated(I18N_ERROR_TITLE, I18N_DEVICE_DB_INIT_WIFI_ERR, C_GUI_DELAY_MSG_SHORT_I);
            }
        }
        else
        {
            utils_go_to_sleep();
        }
    }

    // WIFI Check is completed

    String t_my_id = "";
    String t_gateway_id = "";
    String t_device_token = "";
    bool fin_id_config = false;
    while (!fin_id_config)
    {

        S_GUI_INPUT_TEXT t_my_id_wrapper = gui_input_text("Meine ID (z.B.: 0xMB)", "0x");
        S_GUI_INPUT_TEXT t_device_secret = gui_input_text("Independer Passwort", "");
        if (t_my_id_wrapper.success and t_device_secret.success)
        {
            if (utils_is_valid_receiver(t_my_id_wrapper.value))
            {

                gui_msg_static("Info", "Prüfe Anmeldung\nID\n'" + t_my_id_wrapper.value + "'\n...");
                S_WIFI_REGISTER login_ans = wifi_register_device_actor(t_my_id_wrapper.value, t_device_secret.value, state_wifi_server_url, state_wifi_server_port, state_wifi_server_timeout);

                if (login_ans.success)
                {
                    S_GUI_INPUT_TEXT t_g_id_wrapper = gui_input_text("Gateway ID (z.B.: 0gMB)", "0g");
                    if (t_g_id_wrapper.success)
                    {
                        if (utils_is_valid_receiver(t_g_id_wrapper.value))
                        {
                            t_my_id = t_my_id_wrapper.value;
                            t_gateway_id = t_g_id_wrapper.value;
                            t_device_token = login_ans.token;
                            fin_id_config = true;
                        }
                        else
                            gui_msg_animated("Fehler", "Ungültige ID", C_GUI_DELAY_MSG_SHORT_I);
                    }
                }
                else
                    gui_msg_animated("Fehler", "ID konnte nicht\nangemeldet werden.", C_GUI_DELAY_MSG_SHORT_I);
            }
            else
                gui_msg_animated("Fehler", "Ungültige ID", C_GUI_DELAY_MSG_SHORT_I);
        }
    }

    db_save_init_config_actor(t_wifi_ssid, t_wifi_pw, t_my_id, t_gateway_id, t_device_token);

    gui_msg_animated("Hinweis", "Einrichtung\nabgeschlossen!", C_GUI_DELAY_MSG_SHORT_I);

    gui_msg_animated("Independer", C_TEMPLATE_STRING_THX, C_GUI_DELAY_MSG_LONG_I);

    ESP.restart();
}

void i_db_interactive_setup_gateway()
{
    String randId = "0g" + utils_random_char() + utils_random_char();
    int timeout = 120 * 1000;
    int old_showed_value = -1;

    while (timeout > 0)
    {
        int new_value = int(timeout / 1000);
        if (new_value != old_showed_value)
        {
            old_showed_value = new_value;
            gui_msg_static("Einrichtungsmodus", "Auf dem Actor:\n G. Funktionen->Einrichtung\nID: '" + randId + "' (" + String(old_showed_value) + "s)");
        }

        int packetSize = LoRa.parsePacket();

        if (packetSize)
        {

            Serial.println("\n\n Got Packet");

            String i_res = "";
            while (LoRa.available())
            {
                i_res += LoRa.readString();
            }

            ParserAnsTuple parser_ans = lora_stateful_parse(i_res, randId);

            if (parser_ans.message != "")
            {

                if (parser_ans.message.startsWith("C;init"))
                {
                    Serial.println("Should init gateway");

                    String configString = parser_ans.message.substring(7, parser_ans.message.length());

                    String p_ssid = "";
                    String p_pw = "";
                    String p_id = "";

                    int currentCountsDelimiter = 0;

                    for (int i = 0; i < configString.length(); i++)
                    {

                        String current = configString.substring(i, i + 1);

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
                            if (currentCountsDelimiter == 2)
                                p_id += current;
                        }
                    }

                    p_ssid = utils_decode_data(p_ssid);
                    p_pw = utils_decode_data(p_pw);
                    p_id = utils_decode_data(p_id);

                    // Serial.println("p_ssid '" + p_ssid + "'");
                    // Serial.println("p_pw '" + p_pw + "'");
                    // Serial.println("p_id '" + p_id + "'");
                    // Serial.println("p_owner '" + parser_ans.from + "'");

                    db_save_init_config_gateway(p_ssid, p_pw, p_id, parser_ans.from);

                    gui_msg_animated("Hinweis", "Einrichtung\nabgeschlossen!", C_GUI_DELAY_MSG_SHORT_I);

                    gui_msg_animated("Independer", C_TEMPLATE_STRING_THX, C_GUI_DELAY_MSG_LONG_I);

                    ESP.restart();
                }
                else
                    Serial.println("Error received unknown message '" + parser_ans.message + "'");
            }
        }

        delay(C_INDEPENDER_RES_BETWEEN_DELAY_GATEWAY);
        timeout -= C_INDEPENDER_RES_BETWEEN_DELAY_GATEWAY;
    }

    utils_go_to_sleep();
}