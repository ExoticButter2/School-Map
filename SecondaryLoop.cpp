#include <SecondaryLoop.h>
#include <Arduino.h>
#include <vector>

std::vector<void(*)()> functionsToCall;

TaskHandle_t loopTask = nullptr;
SemaphoreHandle_t functionsMutex = nullptr;

void AddFunction(void (*function)())
{
    xSemaphoreTake(functionsMutex, portMAX_DELAY);

    functionsToCall.push_back(function);

    xSemaphoreGive(functionsMutex);
}

void RemoveFunction(void (*function)())
{
    xSemaphoreTake(functionsMutex, portMAX_DELAY);

    for (auto i = functionsToCall.begin(); i != functionsToCall.end(); ++i)
    {
        if (*i == function)
        {
            functionsToCall.erase(i);
            break;
        }
    }

    xSemaphoreGive(functionsMutex);
}

void InitializeSecondaryLoop()
{
    functionsMutex = xSemaphoreCreateMutex();

    BaseType_t result = xTaskCreatePinnedToCore(SecondaryLoop, "SecondaryLoop", 30000, NULL, 1, &loopTask, 1);

    Serial.printf("Task creation: %d\n", result);
    Serial.println("Initialized secondary loop\n");
}

void SecondaryLoop(void* parameters)
{
    Serial.println("Secondary loop started\n");

    for (;;)
    {
        std::vector<void(*)()> functionsCopy = functionsToCall;

        for (const auto& function: functionsCopy)
        {
            function();
        }

        Serial.printf("Stack high watermark: %d\n", uxTaskGetStackHighWaterMark(loopTask));

        vTaskDelay(1);
    }
}