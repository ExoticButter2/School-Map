#include <InitFunctions.h>
#include <SPI.h>
#include <Secrets.h>
#include <DisplaySettings.h>
#include <TouchScreenPinout.h>
#include <WiFi.h>
#include <User_Setups/Setup21_ILI9488.h>

OnTouchCallback onTouchCallbackFunction = nullptr;

void InitializeDisplay(TFT_eSPI& tft)
{
    tft.init();
    tft.setRotation(DISPLAY_ROTATION);

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
}

XPT2046_Touchscreen* InitializeTouchScreen(OnTouchCallback onTouch)
{
    onTouchCallbackFunction = onTouch;

    SPIClass touchScreenSpi(VSPI);

    XPT2046_Touchscreen* touchScreen = new XPT2046_Touchscreen(TS_CS);

    if (!touchScreenSpi.begin(TS_CLK, TS_DOUT, TS_DIN, TS_CS))
    {
        Serial.println("Failed to initialize touch screen SPI");
    }

    if (!touchScreen->begin(touchScreenSpi))
    {
        Serial.println("Failed to initialize touch screen");
    }

    touchScreen->setRotation(TOUCH_ROTATION);
    touchScreen->setThresholds(TOUCH_THRESHOLD);

    return touchScreen;
}

void InitializeWiFi()
{
    int status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED)
    {
        status = WiFi.begin(WIFI_SSID, WIFI_Password);
        delay(10000);
    }

    while (!Serial)
    {

    }

    Serial.println("Connected to WiFi");
}

std::unordered_map<std::string, Building> InitializeBuildings()
{
    std::unordered_map<std::string, Building> buildings;

    return buildings;
}