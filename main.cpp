#include <InitFunctions.h>
#include <Arduino.h>
#include <TouchFunctions.h>
#include <SecondaryLoop.h>
#include <string>

void setup()
{
    Serial.begin(115200);
    InitializeWiFi();
    delay(3000);

    InitializeDisplay();

    InitializeSecondaryLoop();

    InitializeTouchScreen(OnTouch);

    std::unordered_map<std::string, Building> buildings = InitializeBuildings();
}

void loop()
{
    
}