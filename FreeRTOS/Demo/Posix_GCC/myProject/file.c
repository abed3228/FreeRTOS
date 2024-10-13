#include "file.h"

void vTask1(void *pvParameters)
{
    for (;;)
    {
        // Try to take the mutex to write to the file
        if (xSemaphoreTake((SemaphoreHandle_t)pvParameters, portMAX_DELAY))
        {
            // Write to the file
            writeToFile("Task1\n");
            printf("Task 1 wrote to the file.\n");

            // Release the mutex after writing
            xSemaphoreGive((SemaphoreHandle_t)pvParameters);
        }
    }
}

void vTask2(void *pvParameters)
{
    for (;;)
    {
        // Try to take the mutex to write to the file
        if (xSemaphoreTake((SemaphoreHandle_t)pvParameters, portMAX_DELAY))
        {
            // Write to the file
            writeToFile("Task2\n");
            printf("Task 2 wrote to the file.\n");

            // Release the mutex after writing
            xSemaphoreGive((SemaphoreHandle_t)pvParameters);
        }
    }
}

void writeToFile(const char *data)
{
    FILE *file = fopen("output.txt", "a"); // Open the file in append mode
    if (file != NULL)
    {
        fprintf(file, "%s", data); // Write the data to the file
        fflush(file);
        fclose(file); // Close the file
    }
    else
    {
        printf("Failed to open the file.\n");
    }
}
