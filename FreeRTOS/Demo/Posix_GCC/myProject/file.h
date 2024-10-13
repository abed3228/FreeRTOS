#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"



// Task prototypes
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

// Function that simulates writing to a file
void writeToFile(const char *data);