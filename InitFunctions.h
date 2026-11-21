#ifndef INIT_FUNCTIONS
#define INIT_FUNCTIONS

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>
#include <CoordinateData.h>
#include <string>

typedef void (*OnTouchCallback)(void);

TFT_eSPI* tft;
XPT2046_Touchscreen* touchScreen;

void InitializeDisplay();
bool InitializeTouchScreen(OnTouchCallback onTouch);
void InitializeWiFi();
std::unordered_map<std::string, Building> InitializeBuildings();

#endif