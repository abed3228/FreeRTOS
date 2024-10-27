#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


// Semaphores
SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xCountingSemaphore;

// Task prototypes
void vProductionTask(void* pvParameters);
void vPackagingTask(void* pvParameters);
void vTransportTask(void* pvParameters);

int main_project(void)
{
    // Create binary semaphore (for transferring component to packaging)
    xBinarySemaphore = xSemaphoreCreateBinary();

    // Create counting semaphore (for limiting number of components in transport)
    xCountingSemaphore = xSemaphoreCreateCounting(5, 0); // Up to 5 components in transport

    if (xBinarySemaphore != NULL && xCountingSemaphore != NULL)
    {
        // Create tasks
        xTaskCreate(vProductionTask, "Production Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
        xTaskCreate(vPackagingTask, "Packaging Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
        xTaskCreate(vTransportTask, "Transport Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

        // Start the FreeRTOS scheduler
        vTaskStartScheduler();
    }
    else
    {
        printf("Failed to create semaphores.\n");
    }

    // Should never reach here
    for (;;)
        ;
}

void vProductionTask(void* pvParameters)
{
    for (;;)
    {
        // Produce a component
        printf("Production Task: Producing a component...\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1-second delay to simulate production time

        // Signal that the component is ready for packaging
        xSemaphoreGive(xBinarySemaphore);
        printf("Production Task: Component ready for packaging.\n");

        // Small delay to allow smooth Round-Robin scheduling
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vPackagingTask(void* pvParameters)
{
    for (;;)
    {
        // Wait for the binary semaphore from the production station
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY))
        {
            // Package the component
            printf("Packaging Task: Packaging the component...\n");
            vTaskDelay(pdMS_TO_TICKS(800)); // 800ms delay for packaging

            // Transfer the component to transport (release counting semaphore)
            xSemaphoreGive(xCountingSemaphore);
            printf("Packaging Task: Component ready for transport.\n");
        }

        // Small delay to allow smooth Round-Robin scheduling
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vTransportTask(void* pvParameters)
{
    for (;;)
    {
        // Wait for the counting semaphore to transport a component
        if (xSemaphoreTake(xCountingSemaphore, portMAX_DELAY))
        {
            // Transport the component to the warehouse
            printf("Transport Task: Transporting component to the warehouse...\n");
            vTaskDelay(pdMS_TO_TICKS(1200)); // 1.2-second delay for transport

            printf("Transport Task: Component delivered to warehouse.\n");
        }

        // Small delay to allow smooth Round-Robin scheduling
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

