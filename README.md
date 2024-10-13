# Task Synchronization with Mutex

This project demonstrates how to synchronize two tasks that write to a file using a mutex to prevent simultaneous access. The tasks write alternately to a text file while ensuring proper locking and releasing of the mutex to avoid conflicts.

## Objective

The objective of this exercise is to create two tasks:
- **Task1** writes the word `"Task1"` to a file.
- **Task2** writes the word `"Task2"` to the same file.

Each task writes to the file alternately, using a **mutex** to prevent simultaneous access that could lead to incorrect writing.

## Code Explanation

### Mutex
- The **mutex** `xMutex` is created at the start of the program to synchronize access to the file.
- Each task acquires the mutex using `xSemaphoreTake()` before writing to the file.
- After the task completes the write operation, it releases the mutex using `xSemaphoreGive()` to allow the other task to proceed.

### Tasks
- The tasks `vTask1` and `vTask2` write the words `"Task1"` and `"Task2"` to the file `output.txt` alternately.
- Each task ensures mutual exclusion by acquiring the mutex before writing and releasing it after the write operation.

### Function: `writeToFile`
The `writeToFile` function:
1. Opens the file `output.txt` in append mode.
2. Writes the provided data (either `"Task1"` or `"Task2"`).
3. Closes the file after writing.

If the file cannot be opened, an error message is printed to the console.

### Delays
- Each task introduces a **1-second delay** (1000ms) between each write operation using `vTaskDelay()`. 
- This delay allows the tasks to operate alternately, providing time for each task to write to the file.

## Result

When running this program, the output in the `output.txt` file will look like this:

Task1 
Task2 
Task1 
Task2


The tasks write alternately to the file, and the **mutex** ensures that they do not write to the file at the same time.

## How to Run

1. Clone the repository.
2. Build and run the project in your preferred environment.
3. The output file `output.txt` will show the alternating writes from Task1 and Task2.

## License
This project is licensed under the MIT License.
