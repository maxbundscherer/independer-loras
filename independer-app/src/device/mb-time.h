#include <WiFi.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP);

void time_sync_ntp()
{

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
    Serial.println(timeClient.getFormattedTime());
    timeClient.end();

    // disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);
}
