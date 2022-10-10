#include <WiFi.h>
#include <NTPClient.h>
#include <UnixTime.h>
#include <ESP32Time.h>

unsigned long C_LORA_QUOTA_CLEAN_SECONDS = 3600;    // 1h
unsigned long C_LORA_QUOTA_CONTINGENT_SECONDS = 36; // 36s

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP);

UnixTime stamp(2); // UTC+2
ESP32Time rtc(0);  // Offset is already in stamp (else 3600 * 2)

unsigned long i_time_get_current_unix_time()
{
    return rtc.getEpoch();
}

String i_time_convert_current_time_to_string()
{
    stamp.getDateTime(i_time_get_current_unix_time());
    return String(stamp.year) + "-" + String(stamp.month) + "-" + String(stamp.day) + " " + String(stamp.hour) + ":" + String(stamp.minute) + ":" + String(stamp.second);
}

/**
 * @return boolean update success
 */
boolean i_time_update()
{
    timeClient.begin();
    timeClient.update();

    if (timeClient.getEpochTime() < 500)
    {
        Serial.println("Could not update time");
        return false;
    }
    else
    {
        Serial.println("Could update time");
        rtc.setTime(timeClient.getEpochTime());
        // rtc.offset = 3600 * 2; //Offset is already in stamp
        return true;
    }

    timeClient.end();
}

String time_sync_get_ntp_and_connect()
{

    String ret = "(Fehler)";

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

    if (i_time_update())
    {
        ret = i_time_convert_current_time_to_string();
    }

    // disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);

    return ret;
}

String time_get_from_local()
{

    String ret = i_time_convert_current_time_to_string();

    return ret;
}

unsigned long time_get_current_unix_time()
{
    return i_time_get_current_unix_time();
}

void time_debug_console_output()
{
    Serial.println("Current Time: '" + i_time_convert_current_time_to_string() + "'");
}

// TODO: Speicherüberlaufschutz
#define BOOT_STATE_LORA_QUOTA_DATA 100
RTC_DATA_ATTR char boot_state_lora_quota_data[BOOT_STATE_LORA_QUOTA_DATA] = "";

void time_lora_quota_add(int microseconds)
{
    DynamicJsonDocument doc(1024 * 10);

    deserializeJson(doc, String(boot_state_lora_quota_data));

    doc[String(i_time_get_current_unix_time())] = microseconds;

    String data = "";
    serializeJson(doc, data);
    strcpy(boot_state_lora_quota_data, data.c_str());
}

int time_lora_quota_update_get_millis()
{
    DynamicJsonDocument doc(1024 * 10);

    deserializeJson(doc, String(boot_state_lora_quota_data));

    JsonObject root = doc.as<JsonObject>();

    unsigned long tx_duration_microseconds = 0;

    for (JsonPair kv : root)
    {

        const char *orgKey = kv.key().c_str();
        char *ptr;

        unsigned long t = strtoul(orgKey, &ptr, 10);
        int d = kv.value().as<int>();

        // Serial.println("----");
        // Serial.println("1 '" + String(i_time_get_current_unix_time()) + "'");
        // Serial.println("2 '" + String(t) + "'");
        // Serial.println("3 '" + String(d) + "'");

        if (t < (i_time_get_current_unix_time() - C_LORA_QUOTA_CLEAN_SECONDS) and (i_time_get_current_unix_time() > C_LORA_QUOTA_CLEAN_SECONDS))
        {
            // Is not in range
            // Serial.println("Filter out " + String(t));
            doc.remove(orgKey);
        }
        else
        {
            // Is in range
            // Serial.println("Take a look at " + String(t) + ": " + d);
            tx_duration_microseconds += d;
        }

        String data = "";
        serializeJson(doc, data);
        strcpy(boot_state_lora_quota_data, data.c_str());

        // Serial.println("----");
        // Serial.println();
    }

    return tx_duration_microseconds / 1000;
}

void time_update_time_and_quota_connected()
{
    Serial.println("Update Time Start");
    if (i_time_update())
    {

        DynamicJsonDocument doc(1024 * 10);

        deserializeJson(doc, String(boot_state_lora_quota_data));

        JsonObject root = doc.as<JsonObject>();

        for (JsonPair kv : root)
        {

            const char *orgKey = kv.key().c_str();
            char *ptr;

            unsigned long t = strtoul(orgKey, &ptr, 10);
            int d = kv.value().as<int>();

            if (t >= i_time_get_current_unix_time())
            {
                // Is not in range
                doc.remove(orgKey);
            }

            String data = "";
            serializeJson(doc, data);
            strcpy(boot_state_lora_quota_data, data.c_str());
        }
    }
    Serial.println("Update Time End");
}