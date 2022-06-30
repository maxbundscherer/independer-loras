void db_init()
{
    state_my_id = "0x02";
    state_gateway_id = "0g02";
    state_wifi_ssid = "Bundscherer-Gast";
    state_wifi_pw = "test";
}

void db_save_my_id(String value)
{
    state_my_id = value;
}

void db_save_gateway_id(String value)
{
    state_gateway_id = value;
}

void db_save_wifi_ssid(String value)
{
    state_wifi_ssid = value;
}

void db_save_wifi_pw(String value)
{
    state_wifi_pw = value;
}