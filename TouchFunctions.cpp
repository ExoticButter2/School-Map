#include <TouchFunctions.h>
#include <InitFunctions.h>

void DragScreen(int x, int y)
{
    
}

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

    tft->fillScreen(TFT_WHITE);
    //mainSprite.fillRect(pixelX, pixelY, 10, 10, TFT_RED);
    tft->fillCircle(10, 10, 10, TFT_RED);

    // ulong elapsedTime = micros() - initialTime;
    // Serial.printf("%luHz\n", 1000000UL / elapsedTime); // in seconds
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