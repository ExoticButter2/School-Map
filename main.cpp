#include "InitFunctions.h"
#include <Arduino.h>
#include "TouchFunctions.h"
#include "SecondaryLoop.h"
#include "WebuntisHandler.h"
#include "Secrets.h"
#include <string>
#include "TimeHandler.h"
#include <ArduinoJson.h>

void setup()
{
    Serial.begin(115200);
    delay(500);

    InitializeWiFi(WIFI_SSID, WIFI_Password);

    SyncTime();

    if (ConnectClientToUntis())
    {
        if (AuthenticateUntis(Webuntis_User, Webuntis_Password))
        {
            String timeTableString = GetTimeTableToday();
            JsonDocument timeTableJson;

            deserializeJson(timeTableJson, timeTableString);

            LogoutUntis();
        }
        
        client.stop();
        Serial.println("Ended connection");
    }
    // delay(3000);

    // InitializeDisplay();

    // InitializeSecondaryLoop();

    // InitializeTouchScreen(OnTouch);

    // std::unordered_map<std::string, Building> buildings = InitializeBuildings();
}

void loop()
{
    
}