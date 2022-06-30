#include <Preferences.h>

const char* c_db_target_key = "independer-app";

Preferences preferences;

void db_init()
{

    preferences.begin(c_db_target_key, true); // Read only

    state_my_id = preferences.getString("pref_my_id", state_my_id);
    state_gateway_id = preferences.getString("pref_gateway_id", state_gateway_id);
    state_wifi_ssid = preferences.getString("pref_wifi_ssid", state_wifi_ssid);
    state_wifi_pw = preferences.getString("pref_wifi_pw", state_wifi_pw);
    state_lora_gain = preferences.getInt("pref_lora_gain", state_lora_gain);

    preferences.end();
}

void i_db_write(char* key, String value)
{
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.putString(key, value);
    preferences.end();
}

void i_db_write(char* key, int value)
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

void db_clear() {
    preferences.begin(c_db_target_key, false); // Read and write
    preferences.clear();
    preferences.end();
}