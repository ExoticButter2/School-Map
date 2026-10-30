#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>
#include <SPI.h>
#include <DragFunctions.h>
#include <WiFi.h>
#include <Secrets.h>

#define TS_CLK 42
#define TS_DIN 41
#define TS_DOUT 40
#define TS_CS 39
#define TS_IRQ 38

#define DISPLAY_LED (int8_t) 18
#define DISPLAY_CS (int8_t) 4
#define DISPLAY_RESET (int8_t) 15
#define DISPLAY_DC (int8_t) 5
#define DISPLAY_MISO (int8_t) 20 // SDO pin
#define DISPLAY_MOSI (int8_t) 45 // SDI pin
#define DISPLAY_SCLK (int8_t) 21

const int16_t TOUCH_THRESHOLD = 400.0F;

TFT_eSPI tft;
TFT_eSprite mainSprite(&tft);

SPIClass touchScreenSpi(VSPI);

XPT2046_Touchscreen* touchScreen;

void InitializeRoomsAndWiFi()
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

void OnTouch(ulong initialTime)
{
    uint16_t x, y;
    uint8_t z;

    Serial.println("Touch detected");
    touchScreen->readData(&x, &y, &z);

    int pixelX = map(x, 200, 3800, 0, 320);
    int pixelY = map(y, 200, 3800, 0, 480);

    Serial.print("x: ");
    Serial.print(pixelX);
    Serial.print("y: ");
    Serial.print(pixelY);
    Serial.print("z: ");
    Serial.print(z);

    TS_Point point = touchScreen->getPoint();

    Serial.print("Get point: ");
    Serial.print("X: ");
    Serial.print(point.x);
    Serial.print("Y: ");
    Serial.print(point.y);
    Serial.print("Z: ");
    Serial.print(point.z);

    tft.fillScreen(TFT_WHITE);
    //mainSprite.fillRect(pixelX, pixelY, 10, 10, TFT_RED);
    mainSprite.fillCircle(10, 10, 10, TFT_RED);

    mainSprite.pushSprite(pixelX, pixelY);

    ulong elapsedTime = micros() - initialTime;
    Serial.printf("%luHz\n", 1000000UL / elapsedTime); // in seconds
}

void setup()
{
    Serial.begin(115200);
    InitializeRoomsAndWiFi();

    Serial.println("Initializing TFT..");
    tft.init();
    tft.setRotation(0);

    if (!mainSprite.createSprite(20, 20))
    {
        Serial.println("Failed to create sprite");
    }

    mainSprite.fillSprite(TFT_WHITE);

    touchScreen = new XPT2046_Touchscreen(TS_CS);

    if (!touchScreenSpi.begin(TS_CLK, TS_DOUT, TS_DIN, TS_CS))
    {
        Serial.println("Failed to initialize touch screen SPI");
    }

    if (!touchScreen->begin(touchScreenSpi))
    {
        Serial.println("Failed to initialize touch screen");
    }

    touchScreen->setRotation(2);
    touchScreen->setThresholds(TOUCH_THRESHOLD);

    Serial.println("Initialized TFT successfully");
    pinMode(DISPLAY_LED, OUTPUT);
    digitalWrite(DISPLAY_LED, HIGH);

    delay(3000);
    Serial.printf("PSRAM size: %d\n", ESP.getPsramSize());
}

void loop()
{
    
}