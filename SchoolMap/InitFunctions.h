#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>
#include <SPI.h>
#include <Secrets.h>
#include <DisplaySettings.h>
#include <PinLayout.h>
#include <WiFi.h>

typedef void (*OnTouchCallback)(void)

TFT_eSPI InitializeDisplay();
XPT2046_Touchscreen InitializeTouchScreen();
void InitializeWiFi();
void InitializeRooms();