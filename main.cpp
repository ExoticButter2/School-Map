#include <DragFunctions.h>
#include <TFTPinLayout.h>
#include <InitFunctions.h>
#include <Arduino.h>

TFT_eSPI tft;
TFT_eSprite mainSprite(&tft);

SPIClass touchScreenSpi(VSPI);

XPT2046_Touchscreen* touchScreen;

void OnTouch()
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

    // ulong elapsedTime = micros() - initialTime;
    // Serial.printf("%luHz\n", 1000000UL / elapsedTime); // in seconds
}

void setup()
{
    Serial.begin(115200);
    InitializeWiFi();

    TFT_eSPI tft = InitializeDisplay();

    // if (!mainSprite.createSprite(20, 20))
    // {
    //     Serial.println("Failed to create sprite");
    // }

    // mainSprite.fillSprite(TFT_WHITE);

    InitializeTouchScreen(OnTouch);


}

void loop()
{
    
}