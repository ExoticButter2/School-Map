#include <InitFunctions.h>
#include <SPI.h>
#include <Secrets.h>
#include <DisplaySettings.h>
#include <TouchScreenPinout.h>
#include <WiFi.h>
#include <User_Setups/Setup21_ILI9488.h>
#include <SecondaryLoop.h>

OnTouchCallback onTouchCallbackFunction = nullptr;

TFT_eSPI* tft;
XPT2046_Touchscreen* touchScreen;

void InitializeDisplay()
{
    tft = new TFT_eSPI();

    tft->init();
    tft->setRotation(DISPLAY_ROTATION);

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
}

bool InitializeTouchScreen(OnTouchCallback onTouch)
{
    onTouchCallbackFunction = onTouch;

    SPIClass touchScreenSpi(VSPI);

    touchScreen = new XPT2046_Touchscreen(TS_CS);

    if (!touchScreenSpi.begin(TS_CLK, TS_DOUT, TS_DIN, TS_CS))
    {
        Serial.println("Failed to initialize touch screen SPI");
        return false;
    }

    if (!touchScreen->begin(touchScreenSpi))
    {
        Serial.println("Failed to initialize touch screen");
        return false;
    }

    touchScreen->setRotation(TOUCH_ROTATION);
    touchScreen->setThresholds(TOUCH_THRESHOLD);

    AddFunction(&CheckForTouch);

    return true;
}

void CheckForTouch()
{
    if (touchScreen->touched())
    {
        if (onTouchCallbackFunction != nullptr)
        {
            onTouchCallbackFunction();
        }
    }
}

void InitializeWiFi()
{
    int status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED)
    {
        status = WiFi.begin(WIFI_SSID.c_str(), WIFI_Password.c_str());
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