#include <Preferences.h>

const char *c_db_target_key = "independer-app";

Preferences preferences;

/*
 * ####################################
 *  Settings Section
 * ####################################
 */

void i_db_interactive_setup_actor();

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
        state_wifi_ssid = preferences.getString("pref_wifi_ssid", state_wifi_ssid);
        state_wifi_pw = preferences.getString("pref_wifi_pw", state_wifi_pw);
        state_lora_gain = preferences.getInt("pref_lora_gain", state_lora_gain);
        state_oled_brightness = preferences.getInt("pref_oled_bri", state_oled_brightness);

        state_wifi_server_url = preferences.getString("pref_ws_url", state_wifi_server_url);
        state_wifi_server_port = preferences.getInt("pref_ws_port", state_wifi_server_port);
        state_wifi_server_timeout = preferences.getInt("pref_ws_to", state_wifi_server_timeout);

        preferences.end();
    }
    else
    {
        Serial.println("Init DB");
        preferences.clear();
        preferences.end();
        if (!isDevMode)
            gui_msg_animated("Independer", "Danke, dass du dich\nfür den Independer\nentschieden hast!", C_GUI_DELAY_MSG_LONG_I);
        if (is_actor)
        {
            gui_msg_long_text("Einrichtungsmodus", "Nach dem Update oder beim ersten Starten muss der Independer konfiguriert werden. Dabei hilft dir der Konfigurationsassistent. Für diesen Schritt ist WIFI erforderlich.");
            i_db_interactive_setup_actor();
        }
        else
        {
            gui_msg_static("Einrichtungsmodus", "Auf dem Actor:\n G. Funktionen->Einrichtung\nID: 0x00");
            while (true)
            {
                delay(100);
            }
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

void db_save_init_config(String wifi_ssid, String wifi_pw, String my_id, String gateway_id, String device_token)
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.putString("pref_wifi_ssid", wifi_ssid);
    preferences.putString("pref_wifi_pw", wifi_pw);
    preferences.putString("pref_my_id", my_id);
    preferences.putString("pref_gateway_id", gateway_id);
    preferences.putString("pref_c_ver", c_product_version);
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
        "Automatisch",
        "(Manuell) SSID",
        "(Manuell) Passwort",
        "[Bestätigen]",
        "[Ausschalten]"};

    bool fin_wifi_config = false;
    while (!fin_wifi_config)
    {
        S_GUI_SELECTION_ITEM selected_wrapper = gui_selection("WIFI", menu_items, (int)sizeof(menu_items) / sizeof(menu_items[0]) - 1);

        if (selected_wrapper.success and selected_wrapper.value == 0)
        {
            S_WIFI_CONFIG_WRAPPER ans = application_actor_automatic_wifi(false);
            if (ans.success)
            {
                t_wifi_ssid = ans.ssid;
                t_wifi_pw = ans.password;
                state_wifi_ssid = t_wifi_ssid;
                state_wifi_pw = t_wifi_pw;
                gui_msg_static("Info", "Teste WiFi\n'" + state_wifi_ssid + "'");
                if (wifi_check_status())
                {
                    fin_wifi_config = true;
                }
                else
                {
                    gui_msg_animated("Fehler", "WiFi\nFehler", C_GUI_DELAY_MSG_SHORT_I);
                }
            }
        }
        else if (selected_wrapper.success and selected_wrapper.value == 1)
        {
            S_GUI_INPUT_TEXT s = gui_input_text("SSID", t_wifi_ssid);
            if (s.success)
                t_wifi_ssid = s.value;
        }
        else if (selected_wrapper.success and selected_wrapper.value == 2)
        {
            S_GUI_INPUT_TEXT s = gui_input_text("Passwort", t_wifi_pw);
            if (s.success)
                t_wifi_pw = s.value;
        }
        else if (selected_wrapper.success and selected_wrapper.value == 3)
        {
            state_wifi_ssid = t_wifi_ssid;
            state_wifi_pw = t_wifi_pw;
            gui_msg_static("Info", "Teste WiFi\n'" + state_wifi_ssid + "'");
            if (wifi_check_status())
            {
                fin_wifi_config = true;
            }
            else
            {
                gui_msg_animated("Fehler", "WiFi\nFehler", C_GUI_DELAY_MSG_SHORT_I);
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
                S_WIFI_REGISTER login_ans = wifi_register_device(t_my_id_wrapper.value, t_device_secret.value, state_wifi_server_url, state_wifi_server_port, state_wifi_server_timeout);

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

    // Save WIFI Config and ID and Gateway ID

    db_save_init_config(t_wifi_ssid, t_wifi_pw, t_my_id, t_gateway_id, t_device_token);

    gui_msg_animated("Hinweis", "Einrichtung\nabgeschlossen!", C_GUI_DELAY_MSG_SHORT_I);

    ESP.restart();
}