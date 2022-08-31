#include <WiFi.h>
#include <NTPClient.h>
#include <UnixTime.h>

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP);

UnixTime stamp(2); // UTC+2

unsigned long i_time_last_update_esp_time = 0; // millis
unsigned long i_time_last_update_unix_time = 0;

String i_time_convert_unix_time_to_string(int unixTime)
{
    stamp.getDateTime(unixTime);
    return String(stamp.year) + "-" + String(stamp.month) + "-" + String(stamp.day) + " " + String(stamp.hour) + ":" + String(stamp.minute) + ":" + String(stamp.second);
}

String time_get_from_ntp()
{

    String ret = "";

    Serial.println("(Sync NTP now)");

    // Connect to Wi-Fi
    char *char_array_ssid = const_cast<char *>(state_wifi_ssid.c_str());
    char *char_array_pw = const_cast<char *>(state_wifi_pw.c_str());

    WiFi.begin(char_array_ssid, char_array_pw);
    Serial.println("WiFi connection ");
    int failCounter = 20;
    while (WiFi.status() != WL_CONNECTED and failCounter > 0)
    {
        delay(500);
        Serial.print(".");
        failCounter--;
    }
    Serial.println("");
    Serial.println("WiFi connected.");

    timeClient.begin();
    timeClient.update();
    // Serial.println(timeClient.getFormattedTime() + " or " + timeClient.getEpochTime());
    i_time_last_update_esp_time = millis();
    i_time_last_update_unix_time = timeClient.getEpochTime();
    ret = i_time_convert_unix_time_to_string(i_time_last_update_unix_time);
    timeClient.end();

    // disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);

    return ret;
}

String time_get_from_local()
{
    unsigned long delta = millis() - i_time_last_update_esp_time;
    delta = delta / 1000;

    return i_time_convert_unix_time_to_string(i_time_last_update_unix_time + delta);
}