#include "InitFunctions.h"
#include <Arduino.h>
#include "TouchFunctions.h"
#include "SecondaryLoop.h"
#include "WebuntisHandler.h"
#include "Secrets.h"
#include <string>

void setup()
{
    Serial.begin(115200);
    delay(500);

    InitializeWiFi(WIFI_SSID, WIFI_Password);

    if (ConnectClientToUntis())
    {
        if (AuthenticateUntis(Webuntis_User, Webuntis_Password))
        {
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