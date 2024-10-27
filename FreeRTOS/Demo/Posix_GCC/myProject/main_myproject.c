#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Define the message queue
QueueHandle_t xQueue;

// Task prototypes
void vRobotTask(void *pvParameters);
void vControlUnitTask(void *pvParameters);

// Structure for the message containing component data
typedef struct {
    int id;
    char componentType[20];
} ComponentMessage;

int main_myproject(void) {
    // Create a queue capable of holding 5 messages of type ComponentMessage
    xQueue = xQueueCreate(5, sizeof(ComponentMessage));
    
    if (xQueue != NULL) {
        // Create the robot and control unit tasks
        xTaskCreate(vRobotTask, "Robot Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
        xTaskCreate(vControlUnitTask, "Control Unit Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

        // Start the FreeRTOS scheduler
        vTaskStartScheduler();
    } else {
        printf("Failed to create the queue.\n");
    }

    // Should never reach here
    for (;;);
}

void vRobotTask(void *pvParameters) {
    ComponentMessage msg;
    int componentCount = 0;

    for (;;) {
        // Prepare the message with component data
        msg.id = componentCount++;
        snprintf(msg.componentType, sizeof(msg.componentType), "Component-%d", msg.id);

        // Send the message to the queue
        if (xQueueSend(xQueue, (void *)&msg, portMAX_DELAY) == pdPASS) {
            printf("Robot Task: Sent component ID=%d, Type=%s\n", msg.id, msg.componentType);
        } else {
            printf("Robot Task: Failed to send component.\n");
        }

        // Delay to simulate time between component production
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1-second delay
    }
}

void vControlUnitTask(void *pvParameters) {
    ComponentMessage receivedMsg;

    for (;;) {
        // Wait to receive a message from the robot in the queue
        if (xQueueReceive(xQueue, &receivedMsg, portMAX_DELAY) == pdPASS) {
            // Process the received data and display it to the factory manager
            printf("Control Unit Task: Received component ID=%d, Type=%s\n", receivedMsg.id, receivedMsg.componentType);
        } else {
            printf("Control Unit Task: Failed to receive component.\n");
        }
    }
}
