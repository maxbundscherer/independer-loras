#include <WiFi.h>
#include <NTPClient.h>
#include <UnixTime.h>
#include <ESP32Time.h>

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP);

UnixTime stamp(2); // UTC+2
ESP32Time rtc(0);  // Offset is already in stamp (else 3600 * 2)

String i_time_convert_current_time_to_string()
{
    stamp.getDateTime(rtc.getEpoch());
    return String(stamp.year) + "-" + String(stamp.month) + "-" + String(stamp.day) + " " + String(stamp.hour) + ":" + String(stamp.minute) + ":" + String(stamp.second);
}

String time_sync_get_ntp()
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
    rtc.setTime(timeClient.getEpochTime());
    // rtc.offset = 3600 * 2; //Offset is already in stamp
    ret = i_time_convert_current_time_to_string();
    timeClient.end();

    // disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);

    return ret;
}

String time_get_from_local()
{

    String ret = i_time_convert_current_time_to_string();

    return ret;
}

void time_debug_console_output()
{
    Serial.println("Current Time: '" + i_time_convert_current_time_to_string() + "'");
}