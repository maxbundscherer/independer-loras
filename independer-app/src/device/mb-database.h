#include <Preferences.h>

const char *c_db_target_key = "independer-app";

Preferences preferences;

/*
 * ####################################
 *  Settings Section
 * ####################################
 */

void db_init()
{

    preferences.begin(c_db_target_key, true); // Read only

    state_my_id = preferences.getString("pref_my_id", state_my_id);
    state_gateway_id = preferences.getString("pref_gateway_id", state_gateway_id);
    state_wifi_ssid = preferences.getString("pref_wifi_ssid", state_wifi_ssid);
    state_wifi_pw = preferences.getString("pref_wifi_pw", state_wifi_pw);
    state_lora_gain = preferences.getInt("pref_lora_gain", state_lora_gain);
    state_oled_brightness = preferences.getInt("pref_oled_bri", state_oled_brightness);

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