#include <stdio.h>
#include <unistd.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "file.h"

// Mutex definition
SemaphoreHandle_t xMutex;

void main_myproject(void)
{

    // Create the mutex
    xMutex = xSemaphoreCreateMutex();

    // Create tasks
    xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, (void *)xMutex, 2, NULL);
    xTaskCreate(vTask2, "Task 2", configMINIMAL_STACK_SIZE, (void *)xMutex, 2, NULL);

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here
    for (;;)
        ;
}
