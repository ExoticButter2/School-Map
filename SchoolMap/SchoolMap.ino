#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup()
{
    Serial.begin(115200);
    Serial.println("Initializing TFT..");
    tft.init();

    Serial.println("Initialized TFT successfully");
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);

    int flagColorHeight = TFT_HEIGHT / 3;

    tft.fillRect(0, 0, TFT_WIDTH, flagColorHeight, TFT_WHITE);
    tft.fillRect(0, flagColorHeight, TFT_WIDTH, flagColorHeight, TFT_GREEN);
    tft.fillRect(0, flagColorHeight * 2, TFT_WIDTH, flagColorHeight, TFT_RED);

    delay(5000);
    Serial.println("Print after 5 seconds of initialization");
}

void loop()
{
    
}