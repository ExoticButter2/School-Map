#include <InitFunctions.h>

OnTouchCallback onTouchCallbackFunction = nullptr;

TFT_eSPI InitializeDisplay()
{
    TFT_eSPI tft;
    tft.init();
    tft.setRotation(DISPLAY_ROTATION);

    pinMode(DISPLAY_LED, OUTPUT);
    digitalWrite(DISPLAY_LED, HIGH);

    return tft;
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

void InitializeRooms()
{

}