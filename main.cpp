#include <InitFunctions.h>
#include <Arduino.h>
#include <TouchFunctions.h>

void setup()
{
    Serial.begin(115200);
    //InitializeWiFi();

    InitializeDisplay();

    //delay(5000);

    // if (!mainSprite.createSprite(20, 20))
    // {
    //     Serial.println("Failed to create sprite");
    // }

    // mainSprite.fillSprite(TFT_WHITE);

    InitializeTouchScreen(OnTouch);
    auto buildings = InitializeBuildings();
}

void loop()
{
    
}