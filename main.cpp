#include <InitFunctions.h>
#include <Arduino.h>
#include <TouchFunctions.h>
#include <SecondaryLoop.h>

void setup()
{
    Serial.begin(115200);
    //InitializeWiFi();
    delay(3000);

    InitializeDisplay();

    // if (!mainSprite.createSprite(20, 20))
    // {
    //     Serial.println("Failed to create sprite");
    // }

    // mainSprite.fillSprite(TFT_WHITE);

    InitializeTouchScreen(OnTouch);
    InitializeSecondaryLoop();

    // Serial.printf("Core: %d", xPortGetCoreID());
    // Serial.printf("Available PSRAM: %u", ESP.getFreePsram());
    auto buildings = InitializeBuildings();
}

void loop()
{
    
}