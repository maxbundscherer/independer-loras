#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

WebServer i_ota_server(80);

/*
 * Login page
 */

const char *i_ota_loginIndex =
    "<form name='loginForm'>"
    "<table width='20%' bgcolor='#a800ab' align='center'>"
    "<tr>"
    "<td colspan=2>"
    "<center><font size=4><b>Independer Update Login Page</b></font></center>"
    "<br>"
    "</td>"
    "<br>"
    "<br>"
    "</tr>"
    "<td>Username:</td>"
    "<td><input type='text' size=25 name='userid'><br></td>"
    "</tr>"
    "<br>"
    "<br>"
    "<tr>"
    "<td>Password:</td>"
    "<td><input type='Password' size=25 name='pwd'><br></td>"
    "<br>"
    "<br>"
    "</tr>"
    "<tr>"
    "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
    "</tr>"
    "</table>"
    "</form>"
    "<script>"
    "function check(form)"
    "{"
    "if(form.userid.value=='admin' && form.pwd.value=='updateindepender')"
    "{"
    "window.open('/serverIndex')"
    "}"
    "else"
    "{"
    " alert('Error Password or Username')/*displays error message*/"
    "}"
    "}"
    "</script>";

/*
 * Server Index Page
 */

const char *i_ota_serverIndex =
    "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
    "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
    "<input type='file' name='update'>"
    "<input type='submit' value='Update'>"
    "</form>"
    "<div id='prg'>progress: 0%</div>"
    "<script>"
    "$('form').submit(function(e){"
    "e.preventDefault();"
    "var form = $('#upload_form')[0];"
    "var data = new FormData(form);"
    " $.ajax({"
    "url: '/update',"
    "type: 'POST',"
    "data: data,"
    "contentType: false,"
    "processData:false,"
    "xhr: function() {"
    "var xhr = new window.XMLHttpRequest();"
    "xhr.upload.addEventListener('progress', function(evt) {"
    "if (evt.lengthComputable) {"
    "var per = evt.loaded / evt.total;"
    "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
    "}"
    "}, false);"
    "return xhr;"
    "},"
    "success:function(d, s) {"
    "console.log('success!')"
    "},"
    "error: function (a, b, c) {"
    "}"
    "});"
    "});"
    "</script>";

/*
 * setup function
 */
void i_ota_setup(String ssid, String password, String host)
{

    // Connect to WiFi network
    char ssid_char[ssid.length() + 1];
    ssid.toCharArray(ssid_char, ssid.length() + 1);

    char password_char[password.length() + 1];
    password.toCharArray(password_char, password.length() + 1);

    Serial.println("Conntect to '" + String(ssid_char) + "' '" + ssid + "'");

    WiFi.begin(ssid_char, password_char);
    Serial.println("");

    WiFi.setSleep(false);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Updated");

    /*use mdns for host name resolution*/
    char host_char[host.length() + 1];
    host.toCharArray(host_char, host.length() + 1);
    if (!MDNS.begin(host_char))
    { // http://esp32.local
        Serial.println("Error setting up MDNS responder!");
        while (1)
        {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");
    /*return index page which is stored in serverIndex */
    i_ota_server.on("/", HTTP_GET, []()
                    {
    i_ota_server.sendHeader("Connection", "close");
    i_ota_server.send(200, "text/html", i_ota_loginIndex); });
    i_ota_server.on("/serverIndex", HTTP_GET, []()
                    {
    i_ota_server.sendHeader("Connection", "close");
    i_ota_server.send(200, "text/html", i_ota_serverIndex); });
    /*handling uploading firmware file */
    i_ota_server.on(
        "/update", HTTP_POST, []()
        {
    i_ota_server.sendHeader("Connection", "close");
    i_ota_server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart(); },
        []()
        {
            HTTPUpload &upload = i_ota_server.upload();
            if (upload.status == UPLOAD_FILE_START)
            {
                Serial.printf("Update: %s\n", upload.filename.c_str());
                if (!Update.begin(UPDATE_SIZE_UNKNOWN))
                { // start with max available size
                    Update.printError(Serial);
                }
            }
            else if (upload.status == UPLOAD_FILE_WRITE)
            {
                /* flashing firmware to ESP*/
                if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
                {
                    Update.printError(Serial);
                }
            }
            else if (upload.status == UPLOAD_FILE_END)
            {
                if (Update.end(true))
                { // true to set the size to the current progress
                    Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
                }
                else
                {
                    Update.printError(Serial);
                }
            }
        });
    i_ota_server.begin();
}

void i_ota_loop(void)
{
    i_ota_server.handleClient();
    delay(1);
}

void ota_start()
{
    i_ota_setup(state_wifi_ssid, state_wifi_pw, state_wifi_hostname);
    while (1)
    {
        i_ota_loop();
    }
}