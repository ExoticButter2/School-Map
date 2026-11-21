#include <SecondaryLoop.h>
#include <functional>
#include <Arduino.h>

std::vector<void(*)()> functionsToCall;
TaskHandle_t loopTask;

void AddFunction(void (*function)())
{
    functionsToCall.push_back(function);
}

void RemoveFunction(void (*function)())
{
    for (int i = 0; i < functionsToCall.size(); i++)
    {
        const auto& possibleMatch = functionsToCall[i];

        if (possibleMatch == function)
        {
            functionsToCall.erase(functionsToCall.begin() + i);
            
        }
    }
}

void InitializeSecondaryLoop()
{
    xTaskCreatePinnedToCore(SecondaryLoop, "SecondaryLoop", 10000, NULL, 1, &loopTask, 0);
    Serial.println("Initialized secondary loop");
}

void SecondaryLoop(void* parameters)
{
    for (;;)
    {
        for (const auto& function: functionsToCall)
        {
            function();
        }
    }
}