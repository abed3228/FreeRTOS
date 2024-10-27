#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

// Definitions
#define ITEM_COUNT 5
#define INSPECTION_DELAY pdMS_TO_TICKS(1000) // Delay at the inspection station (in milliseconds)
#define PRODUCTION_DELAY pdMS_TO_TICKS(500)  // Delay at the production machine (in milliseconds)
#define BELT_DELAY pdMS_TO_TICKS(700)        // Delay on the conveyor belt (in milliseconds)

// Semaphores and queues
SemaphoreHandle_t xBinarySemaphore;
SemaphoreHandle_t xCountingSemaphore;
SemaphoreHandle_t xMutex;
QueueHandle_t xMessageQueue;

// Task prototypes
void vMachineTask(void *pvParameters);
void vConveyorBeltTask(void *pvParameters);
void vInspectionStationTask(void *pvParameters);
void vUserInterfaceTask(void *pvParameters);

int main_myproject(void)
{
    // Create binary semaphore
    xBinarySemaphore = xSemaphoreCreateBinary();

    // Create counting semaphore with ITEM_COUNT capacity
    xCountingSemaphore = xSemaphoreCreateCounting(ITEM_COUNT, 0);

    // Create mutex to protect reporting
    xMutex = xSemaphoreCreateMutex();

    // Create message queue
    xMessageQueue = xQueueCreate(10, sizeof(char *));

    // Create tasks
    xTaskCreate(vMachineTask, "Machine Task", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(vConveyorBeltTask, "Conveyor Belt Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vInspectionStationTask, "Inspection Station Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vUserInterfaceTask, "User Interface Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    for (;;)
        ;
}

void vMachineTask(void *pvParameters)
{
    for (;;)
    {
        // Produce an item
        printf("Production Machine: Producing an item...\n");
        vTaskDelay(PRODUCTION_DELAY);

        // Release binary semaphore for the conveyor belt
        xSemaphoreGive(xBinarySemaphore);

        // Release counting semaphore, indicating a new item on the conveyor belt
        xSemaphoreGive(xCountingSemaphore);

        // Send message to the queue for the user interface
        char *message = "Item Produced";
        xQueueSend(xMessageQueue, &message, portMAX_DELAY);
    }
}

void vConveyorBeltTask(void *pvParameters)
{
    for (;;)
    {
        // Wait for the binary semaphore from the production machine
        xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
        printf("Conveyor Belt: Moving an item...\n");
        vTaskDelay(BELT_DELAY);

        // Send message to the queue for the user interface
        char *message = "Item on Conveyor";
        xQueueSend(xMessageQueue, &message, portMAX_DELAY);
    }
}

void vInspectionStationTask(void *pvParameters)
{
    for (;;)
    {
        // Wait for the counting semaphore
        xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
        printf("Inspection Station: Inspecting item...\n");
        vTaskDelay(INSPECTION_DELAY);

        // Send message to the queue for the user interface
        char *message = "Item Inspected";
        xQueueSend(xMessageQueue, &message, portMAX_DELAY);
    }
}

void vUserInterfaceTask(void *pvParameters)
{
    char *receivedMessage;

    for (;;)
    {
        // Wait for a message from the queue
        if (xQueueReceive(xMessageQueue, &receivedMessage, portMAX_DELAY))
        {
            // Protected access to reporting via mutex
            xSemaphoreTake(xMutex, portMAX_DELAY);
            printf("User Interface: %s\n", receivedMessage);
            xSemaphoreGive(xMutex);
        }
    }
}
