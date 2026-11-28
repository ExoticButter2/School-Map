#include "TimeHandler.h"
#include <time.h>

void SyncTime()
{
    configTime(0, 0, ntpServer1, ntpServer2);

    setenv("TZ", timeZone, 1);
    tzset();

    time_t now = 0;

    while (time(&now) < 1795867200)
    {
        delay(500);
    }
    
    Serial.println("Time synced");
}

bool SetTimeInfo(tm* timeInfo)
{
    if (!getLocalTime(timeInfo, 2000))
    {
        Serial.println("Failed to get time");
        return false;
    }

    return true;
    // char formattedTime[80];
    // strftime(formattedTime, sizeof(formattedTime), "%A, %B %d %Y %H:%M:%S", &timeInfo);
    // Serial.printf("Formatted time: %s", formattedTime);
}