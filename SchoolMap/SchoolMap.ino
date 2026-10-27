#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>
#include <SPI.h>

#define TS_CLK (int8_t)42
#define TS_DIN (int8_t)41
#define TS_DOUT (int8_t)40
#define TS_CS (int8_t)39
#define TS_IRQ (int8_t)38

TFT_eSPI tft;
SPIClass touchScreenSpi(VSPI);

void setup()
{
    Serial.begin(115200);
    touchScreenSpi.begin(TS_CLK, TS_DIN, TS_DOUT, TS_CS);
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