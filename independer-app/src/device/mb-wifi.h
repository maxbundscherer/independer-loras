#include <WiFi.h>
#include <HTTPClient.h>

const char root_ca[] PROGMEM = R"=====(
-----BEGIN CERTIFICATE-----
MIIGTTCCBDWgAwIBAgIUEuWTf64/OkGlC9DGTY2d2174M34wDQYJKoZIhvcNAQEL
BQAwgbUxCzAJBgNVBAYTAkRFMRAwDgYDVQQIDAdCYXZhcmlhMQ8wDQYDVQQHDAZN
dW5pY2gxHzAdBgNVBAoMFk1heGltaWxpYW4gQnVuZHNjaGVyZXIxEzARBgNVBAsM
CkluZGVwZW5kZXIxHDAaBgNVBAMME2luZGVwZW5kZXIuZGRucy5uZXQxLzAtBgkq
hkiG9w0BCQEWIG1heGltaWxpYW5AYnVuZHNjaGVyZXItb25saW5lLmRlMB4XDTIy
MDgyOTE4MDMyMVoXDTIyMDkyODE4MDMyMVowgbUxCzAJBgNVBAYTAkRFMRAwDgYD
VQQIDAdCYXZhcmlhMQ8wDQYDVQQHDAZNdW5pY2gxHzAdBgNVBAoMFk1heGltaWxp
YW4gQnVuZHNjaGVyZXIxEzARBgNVBAsMCkluZGVwZW5kZXIxHDAaBgNVBAMME2lu
ZGVwZW5kZXIuZGRucy5uZXQxLzAtBgkqhkiG9w0BCQEWIG1heGltaWxpYW5AYnVu
ZHNjaGVyZXItb25saW5lLmRlMIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKC
AgEApz7BvdHki4l+/p6ZFF6YGiEco2wJvZptpNqO6x5+EZMo/7jjYGISkiNl1obo
iIoQjzUg64GVcXMS9yNqwSXKQvoevKLHmMfVdvfHUIIQPNx0ykP9+qxEiCqqkaaz
Nf3N7IZ2y5uvrLCdzbE6VhXBwdOzdFSY+S1XlzKdSfje0kbcCgw1qi40i517PeVr
LQYjmdpVd2hplFh9OwEYNR/UO0G6PILwb/yAY4OuVPeK1AU517UnIo8wfstgbI5s
Zjv+tGBKkSRHdB8KpwRSvfEA5YM/Q/UZCo6nnIIMWUr2wYU7gbZ3BVLzjLboDv33
h73DmPIqXsxcq0OHyE4VEZhGWsHqd3Ao/5OyvCMnl3D2qTr3mT2cnU9Jvf4glZuX
M5khAA7iQnOX2HmTKVO3vvGF6e2Suiry/0UkLICSypXf9fscVSXgv6A6tHdNAUFa
GOSRNXYJSDHdrpoE5xdDY6pJjYGSS3AqduesLb4ivnMkqxZsp0FHoYQ8jSGa2kh+
mLAukpJkzSr5mfxUKNO93guPs/McD2UaDrzahlOrcfeZsCIODo2Hj5ifh5K9mb2g
KDRl1Er3vD99VJFC/5WcYUWXfaORTsrEsHoibscK3Knyvf/5lfz+BKE6jmEqNBG0
WuK7oF7bcSKpTF7IPOEkq6SzCzV5QbZv2t8IWfupy0OvdPUCAwEAAaNTMFEwHQYD
VR0OBBYEFOKrEr8njFGdhayja8l9t9Lc2UUZMB8GA1UdIwQYMBaAFOKrEr8njFGd
hayja8l9t9Lc2UUZMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggIB
AC6Yi77LJq7nb7PA3NICPn/4ebyyUwqX8/nrLoLYois96Vc9tJ+fPduKoUIDeQaz
Og5cA9XEzWJz8S/2+IDFBTzognYwhOK6IPwLmDaPEJH/ujV7phNFMG0JiYmrYoxU
6iNFnrE1pMEJbE0fcJqPxnpeCIesxM+fmR7+0JuVjbnETZbZ8Tg37QxnwsaiWRF7
RxZE2iAip26NnKuMIKAHU+DmcUJtGIDZNbdkAhb5keypwgO4aDpyexhygGaGEN7e
1TnhYfVvzrkIhG3DGwd0eHVri/KO1ylgM15xsY7vVfKgWi2vNZ6YGXzQ5R6Gp1uM
0x6cPgscBbb6Ky6imKZFZVljdyAbjP3fZ2xzi8LRbt6X4rSvZIcmtYr1bOEQ1LDj
0Dsros3tj5D1PkzHWB/v8XoIQbVhrFDevB7miPrLMsJ6AMFFNyGbJEjDCXzxnutc
AQNTaB6C2gDGZt02aDydYAkJkew92LAMJVUcqYOuT5yFQovr0XymJ4pkWBI8SCf0
3L3WACsw6h5WTSL/3ulAhS0lqF84til3P+2YhIumbNTr6NDOgaXeCLapc00Cs/Ln
Gm3BWCDptsdYqT0ACFdMOk41etItJZYluGo3Y5aPCd3nMrz5184Hfh20ZnaV+7Cq
bV1o5tfAMh8lFOsxTPD3TZuhBciWhL9nkaSwuH7XhjSe
-----END CERTIFICATE-----
)=====";

// WiFiClient i_wifi_client;
WiFiClientSecure i_wifi_client;

int c_wifi_server_max_attempts = 500;

boolean i_wifi_connect()
{

    char *char_array_ssid = const_cast<char *>(state_wifi_ssid.c_str());
    char *char_array_pw = const_cast<char *>(state_wifi_pw.c_str());

    WiFi.begin(char_array_ssid, char_array_pw);
    Serial.println("[Should connect to WIFI] START");

    int c_wifi_max_fails = c_wifi_server_max_attempts;

    int wifi_fail_connect_counter = 0;

    /* waiting for WiFi connect */
    while (WiFi.status() != WL_CONNECTED and wifi_fail_connect_counter < c_wifi_max_fails)
    {
        wifi_fail_connect_counter++;
        Serial.print("AW=" + String(wifi_fail_connect_counter) + "/" + String(c_wifi_max_fails) + " ");
        delay(100);
    }

    Serial.println("\n[Should connect to WIFI] STOP");

    if (WiFi.status() == WL_CONNECTED)
    {
        i_wifi_client.setCACert(root_ca);
        return true;
    }
    else
    {
        return false;
    }
}

void i_wifi_disconnect()
{
    WiFi.disconnect(true);
    Serial.println("[Disconnect WIFI]\n");
}

boolean wifi_check_status()
{
    boolean connection_flag = i_wifi_connect();
    i_wifi_disconnect();
    return connection_flag;
}

/*
 * ####################################
 *  Register Device Section
 * ####################################
 */

struct S_WIFI_REGISTER
{
    boolean success;
    String token;
};

S_WIFI_REGISTER wifi_register_device_actor(String device_id, String secret, String serverUrl, int serverPort, int serverTimeout)
{

    char *c_wifi_server_url = const_cast<char *>(serverUrl.c_str());
    int c_wifi_server_port = serverPort;
    int c_wifi_timeout = serverTimeout;

    S_WIFI_REGISTER ret = {false, ""};

    if (i_wifi_connect())
    {
        Serial.println("Connect to server (timeout " + String(c_wifi_timeout) + ") (" + c_wifi_server_url + ") (" + String(serverPort) + ")");
        if (!i_wifi_client.connect(c_wifi_server_url, c_wifi_server_port, c_wifi_timeout))
            Serial.println("Connection failed!");
        else
        {
            Serial.println("Connected to server!");
            time_update_time_and_quota_connected();

            DynamicJsonDocument doc(1024 * 10);

            doc["id"] = device_id;
            doc["secret"] = secret;
            doc["version"] = c_product_version;

            String body = "";

            serializeJson(doc, body);

            String send_string = String("POST ") + "/v1/register" + " HTTP/1.1\r\n" +
                                 "Host: " + String(c_wifi_server_url) + ":" + String(c_wifi_server_port) + "\r\n" +
                                 "Content-Type: application/json" + "\r\n" +
                                 "Content-Length: " + body.length() + "\r\n\r\n" +
                                 body; // + "\r\n" +
                                       //  "Connection: close\r\n\r\n";

            Serial.println("Send String is '" + send_string + "'");

            i_wifi_client.print(send_string);

            int c_mail_max_fails = c_wifi_server_max_attempts;

            int mail_fail_connect_counter = 0;

            Serial.println("[Waiting for response] START");
            while (!i_wifi_client.available() and mail_fail_connect_counter < c_mail_max_fails)
            {
                mail_fail_connect_counter++;
                Serial.print("AM=" + String(mail_fail_connect_counter) + "/" + String(c_mail_max_fails) + " ");
                delay(50);
            }
            Serial.println("\n[Waiting for response] STOP");

            String line = "";
            while (i_wifi_client.available())
            {
                line += i_wifi_client.readStringUntil('\r');
            }
            Serial.print("Response '" + line + "'");

            if (line.indexOf("OK-") > 0)
            {
                ret.success = true;
                ret.token = line.substring(line.indexOf("OK-") + 3);
            }

            /* if the server disconnected, stop the client */
            if (!i_wifi_client.connected())
            {
                Serial.println();
                Serial.println("Server disconnected");
            }

            i_wifi_client.stop();
        }
    }
    else
        Serial.println("Could not send: Not connected");

    i_wifi_disconnect();

    return ret;
}

boolean wifi_register_device_gateway(String my_id, String gateway_id, String serverUrl, int serverPort, int serverTimeout, String serverDeviceToken)
{

    char *c_wifi_server_url = const_cast<char *>(serverUrl.c_str());
    int c_wifi_server_port = serverPort;
    int c_wifi_timeout = serverTimeout;

    boolean ret = false;

    if (i_wifi_connect())
    {
        Serial.println("Connect to server (timeout " + String(c_wifi_timeout) + ") (" + c_wifi_server_url + ") (" + String(serverPort) + ")");
        if (!i_wifi_client.connect(c_wifi_server_url, c_wifi_server_port, c_wifi_timeout))
            Serial.println("Connection failed!");
        else
        {
            Serial.println("Connected to server!");
            time_update_time_and_quota_connected();

            DynamicJsonDocument doc(1024 * 10);

            doc["auth-id"] = my_id;
            doc["auth-token"] = serverDeviceToken;
            doc["gateway-id"] = gateway_id;

            String body = "";

            serializeJson(doc, body);

            String send_string = String("POST ") + "/v1/gatewayregister" + " HTTP/1.1\r\n" +
                                 "Host: " + String(c_wifi_server_url) + ":" + String(c_wifi_server_port) + "\r\n" +
                                 "Content-Type: application/json" + "\r\n" +
                                 "Content-Length: " + body.length() + "\r\n\r\n" +
                                 body; // + "\r\n" +
                                       //  "Connection: close\r\n\r\n";

            Serial.println("Send String is '" + send_string + "'");

            i_wifi_client.print(send_string);

            int c_mail_max_fails = c_wifi_server_max_attempts;

            int mail_fail_connect_counter = 0;

            Serial.println("[Waiting for response] START");
            while (!i_wifi_client.available() and mail_fail_connect_counter < c_mail_max_fails)
            {
                mail_fail_connect_counter++;
                Serial.print("AM=" + String(mail_fail_connect_counter) + "/" + String(c_mail_max_fails) + " ");
                delay(50);
            }
            Serial.println("\n[Waiting for response] STOP");

            String line = "";
            while (i_wifi_client.available())
            {
                line += i_wifi_client.readStringUntil('\r');
            }
            Serial.print("Response '" + line + "'");

            if (line.endsWith("OK"))
            {
                ret = true;
            }

            /* if the server disconnected, stop the client */
            if (!i_wifi_client.connected())
            {
                Serial.println();
                Serial.println("Server disconnected");
            }

            i_wifi_client.stop();
        }
    }
    else
        Serial.println("Could not send: Not connected");

    i_wifi_disconnect();

    return ret;
}

/*
 * ####################################
 *  Send Chat Message Section
 * ####################################
 */

boolean wifi_send_chat_message(String receiver, String author, String msg, String serverUrl, int serverPort, int serverTimeout, String serverDeviceToken)
{

    char *c_wifi_server_url = const_cast<char *>(serverUrl.c_str());
    int c_wifi_server_port = serverPort;
    int c_wifi_timeout = serverTimeout;

    boolean ret = false;

    if (i_wifi_connect())
    {
        Serial.println("Connect to server (timeout " + String(c_wifi_timeout) + ") (" + c_wifi_server_url + ") (" + String(serverPort) + ")");
        if (!i_wifi_client.connect(c_wifi_server_url, c_wifi_server_port, c_wifi_timeout))
            Serial.println("Connection failed!");
        else
        {
            Serial.println("Connected to server!");
            time_update_time_and_quota_connected();

            DynamicJsonDocument doc(1024 * 10);

            doc["auth-id"] = author;
            doc["auth-token"] = serverDeviceToken;
            doc["receiver"] = receiver;
            doc["msg"] = msg;

            String body = "";

            serializeJson(doc, body);

            String send_string = String("POST ") + "/v1/writemsg" + " HTTP/1.1\r\n" +
                                 "Host: " + String(c_wifi_server_url) + ":" + String(c_wifi_server_port) + "\r\n" +
                                 "Content-Type: application/json" + "\r\n" +
                                 "Content-Length: " + body.length() + "\r\n\r\n" +
                                 body; // + "\r\n" +
                                       //  "Connection: close\r\n\r\n";

            Serial.println("Send String is '" + send_string + "'");

            i_wifi_client.print(send_string);

            int c_mail_max_fails = c_wifi_server_max_attempts;

            int mail_fail_connect_counter = 0;

            Serial.println("[Waiting for response] START");
            while (!i_wifi_client.available() and mail_fail_connect_counter < c_mail_max_fails)
            {
                mail_fail_connect_counter++;
                Serial.print("AM=" + String(mail_fail_connect_counter) + "/" + String(c_mail_max_fails) + " ");
                delay(50);
            }
            Serial.println("\n[Waiting for response] STOP");

            String line = "";
            while (i_wifi_client.available())
            {
                line += i_wifi_client.readStringUntil('\r');
            }
            Serial.print("Response '" + line + "'");

            if (line.endsWith("OK"))
            {
                ret = true;
            }

            /* if the server disconnected, stop the client */
            if (!i_wifi_client.connected())
            {
                Serial.println();
                Serial.println("Server disconnected");
            }

            i_wifi_client.stop();
        }
    }
    else
        Serial.println("Could not send: Not connected");

    i_wifi_disconnect();

    return ret;
}

/*
 * ####################################
 *  Get Chat Messages Section
 * ####################################
 */

String wifi_get_chat_messages(String myId, String serverUrl, int serverPort, int serverTimeout, String serverDeviceToken)
{

    char *c_wifi_server_url = const_cast<char *>(serverUrl.c_str());
    int c_wifi_server_port = serverPort;
    int c_wifi_timeout = serverTimeout;

    String ret = "";

    if (i_wifi_connect())
    {
        Serial.println("Connect to server (timeout " + String(c_wifi_timeout) + ") (" + c_wifi_server_url + ") (" + String(serverPort) + ")");
        if (!i_wifi_client.connect(c_wifi_server_url, c_wifi_server_port, c_wifi_timeout))
            Serial.println("Connection failed!");
        else
        {
            Serial.println("Connected to server!");
            time_update_time_and_quota_connected();

            DynamicJsonDocument doc(1024 * 10);

            doc["auth-id"] = myId;
            doc["auth-token"] = serverDeviceToken;

            String body = "";

            serializeJson(doc, body);

            String send_string = String("POST ") + "/v1/getmsgs" + " HTTP/1.1\r\n" +
                                 "Host: " + String(c_wifi_server_url) + ":" + String(c_wifi_server_port) + "\r\n" +
                                 "Content-Type: application/json" + "\r\n" +
                                 "Content-Length: " + body.length() + "\r\n\r\n" +
                                 body; // + "\r\n" +
            //  "Connection: close\r\n\r\n";

            Serial.println("Send String is '" + send_string + "'");

            i_wifi_client.print(send_string);

            int c_mail_max_fails = c_wifi_server_max_attempts;

            int mail_fail_connect_counter = 0;

            Serial.println("[Waiting for response] START");
            while (!i_wifi_client.available() and mail_fail_connect_counter < c_mail_max_fails)
            {
                mail_fail_connect_counter++;
                Serial.print("AM=" + String(mail_fail_connect_counter) + "/" + String(c_mail_max_fails) + " ");
                delay(50);
            }
            Serial.println("\n[Waiting for response] STOP");

            String line = "";
            while (i_wifi_client.available())
            {
                line += i_wifi_client.readStringUntil('\r');
            }
            Serial.print("Response '" + line + "'");

            ret = line;

            /* if the server disconnected, stop the client */
            if (!i_wifi_client.connected())
            {
                Serial.println();
                Serial.println("Server disconnected");
            }

            i_wifi_client.stop();
        }
    }
    else
        Serial.println("Could not send: Not connected");

    i_wifi_disconnect();

    return ret;
}

/*
 * ####################################
 *  Clear Chat Message Section
 * ####################################
 */

boolean wifi_clear_message(String myId, String serverUrl, int serverPort, int serverTimeout, String serverDeviceToken)
{

    char *c_wifi_server_url = const_cast<char *>(serverUrl.c_str());
    int c_wifi_server_port = serverPort;
    int c_wifi_timeout = serverTimeout;

    boolean ret = false;

    if (i_wifi_connect())
    {
        Serial.println("Connect to server (timeout " + String(c_wifi_timeout) + ") (" + c_wifi_server_url + ") (" + String(serverPort) + ")");
        if (!i_wifi_client.connect(c_wifi_server_url, c_wifi_server_port, c_wifi_timeout))
            Serial.println("Connection failed!");
        else
        {
            Serial.println("Connected to server!");
            time_update_time_and_quota_connected();

            DynamicJsonDocument doc(1024 * 10);

            doc["auth-id"] = myId;
            doc["auth-token"] = serverDeviceToken;

            String body = "";

            serializeJson(doc, body);

            String send_string = String("POST ") + "/v1/clearmsgs" + " HTTP/1.1\r\n" +
                                 "Host: " + String(c_wifi_server_url) + ":" + String(c_wifi_server_port) + "\r\n" +
                                 "Content-Type: application/json" + "\r\n" +
                                 "Content-Length: " + body.length() + "\r\n\r\n" +
                                 body; // + "\r\n" +
                                       //  "Connection: close\r\n\r\n";

            Serial.println("Send String is '" + send_string + "'");

            i_wifi_client.print(send_string);

            int c_mail_max_fails = c_wifi_server_max_attempts;

            int mail_fail_connect_counter = 0;

            Serial.println("[Waiting for response] START");
            while (!i_wifi_client.available() and mail_fail_connect_counter < c_mail_max_fails)
            {
                mail_fail_connect_counter++;
                Serial.print("AM=" + String(mail_fail_connect_counter) + "/" + String(c_mail_max_fails) + " ");
                delay(50);
            }
            Serial.println("\n[Waiting for response] STOP");

            String line = "";
            while (i_wifi_client.available())
            {
                line += i_wifi_client.readStringUntil('\r');
            }
            Serial.print("Response '" + line + "'");

            if (line.endsWith("OK"))
            {
                ret = true;
            }

            /* if the server disconnected, stop the client */
            if (!i_wifi_client.connected())
            {
                Serial.println();
                Serial.println("Server disconnected");
            }

            i_wifi_client.stop();
        }
    }
    else
        Serial.println("Could not send: Not connected");

    i_wifi_disconnect();

    return ret;
}

/*
 * ####################################
 *  Auto Sync Section
 * ####################################
 */

String wifi_auto_sync(String myId, String serverUrl, int serverPort, int serverTimeout, String serverDeviceToken)
{

    char *c_wifi_server_url = const_cast<char *>(serverUrl.c_str());
    int c_wifi_server_port = serverPort;
    int c_wifi_timeout = serverTimeout;

    String ret = "";

    if (i_wifi_connect())
    {
        Serial.println("Connect to server (timeout " + String(c_wifi_timeout) + ") (" + c_wifi_server_url + ") (" + String(serverPort) + ")");
        if (!i_wifi_client.connect(c_wifi_server_url, c_wifi_server_port, c_wifi_timeout))
            Serial.println("Connection failed!");
        else
        {
            Serial.println("Connected to server!");
            // time_update_time_and_quota_connected(); below

            DynamicJsonDocument doc(1024 * 10);

            doc["auth-id"] = myId;
            doc["auth-token"] = serverDeviceToken;

            doc["version"] = c_product_version;
            doc["battery"] = utils_get_battery();
            doc["time_before_sync"] = time_get_current_unix_time();
            time_update_time_and_quota_connected();
            doc["time_after_sync"] = time_get_current_unix_time();

            String body = "";

            serializeJson(doc, body);

            String send_string = String("POST ") + "/v1/autosync" + " HTTP/1.1\r\n" +
                                 "Host: " + String(c_wifi_server_url) + ":" + String(c_wifi_server_port) + "\r\n" +
                                 "Content-Type: application/json" + "\r\n" +
                                 "Content-Length: " + body.length() + "\r\n\r\n" +
                                 body; // + "\r\n" +
                                       //  "Connection: close\r\n\r\n";

            Serial.println("Send String is '" + send_string + "'");

            i_wifi_client.print(send_string);

            int c_mail_max_fails = c_wifi_server_max_attempts;

            int mail_fail_connect_counter = 0;

            Serial.println("[Waiting for response] START");
            while (!i_wifi_client.available() and mail_fail_connect_counter < c_mail_max_fails)
            {
                mail_fail_connect_counter++;
                Serial.print("AM=" + String(mail_fail_connect_counter) + "/" + String(c_mail_max_fails) + " ");
                delay(50);
            }
            Serial.println("\n[Waiting for response] STOP");

            String line = "";
            while (i_wifi_client.available())
            {
                line += i_wifi_client.readStringUntil('\r');
            }
            Serial.print("Response '" + line + "'");

            ret = line;

            /* if the server disconnected, stop the client */
            if (!i_wifi_client.connected())
            {
                Serial.println();
                Serial.println("Server disconnected");
            }

            i_wifi_client.stop();
        }
    }
    else
        Serial.println("Could not send: Not connected");

    i_wifi_disconnect();

    return ret;
}