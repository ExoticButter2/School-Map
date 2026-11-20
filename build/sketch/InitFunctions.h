#line 1 "C:\\Users\\maksi\\OneDrive\\Documents\\GitHub\\School-Map\\SchoolMap\\InitFunctions.h"
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>
#include <SPI.h>
#include <Secrets.h>
#include <DisplaySettings.h>
#include <TFTPinLayout.h>
#include <WiFi.h>

typedef void (*OnTouchCallback)(void);

TFT_eSPI InitializeDisplay();
XPT2046_Touchscreen* InitializeTouchScreen(OnTouchCallback onTouch);
void InitializeWiFi();
void InitializeRooms();