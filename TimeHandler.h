#ifndef TIME_HANDLER
#define TIME_HANDLER

#include <Arduino.h>
#include <time.h>

const inline char* timeZone = "CET-1CEST,M3.5.0,M10.5.0/3";

void SyncTime();
bool SetTimeInfo(tm* timeInfo);

const inline char* ntpServer1 = "pool.ntp.org";
const inline char* ntpServer2 = "time.nist.gov";

#endif