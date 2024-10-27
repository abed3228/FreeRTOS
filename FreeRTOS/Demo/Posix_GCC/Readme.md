# Advanced Smart Factory Production Line Management Using FreeRTOS

This project aims to design an automated system for managing an advanced smart factory production line using FreeRTOS. The factory includes four main components: a **Production Machine**, a **Conveyor Belt**, an **Inspection Station**, and a **User Interface**. Each component communicates efficiently with others, while tasks are managed with FreeRTOS features to optimize the process.

## Factory Components

1. **Production Machine** – Responsible for producing new items.
2. **Conveyor Belt** – Transports items from the machine to the inspection station.
3. **Inspection Station** – Checks the quality of items to ensure they meet standards.
4. **User Interface** – Provides feedback to managers on production status, including the number of items produced and whether they passed inspection.

## Constraints and Requirements

- Each component must operate concurrently, allowing for efficient multitasking.
- The **Production Machine** has high priority to maximize item production, while the **Inspection Station** has lower priority as it can operate at a slower rate.
- **Mutex** and **Binary Semaphore** are used to synchronize tasks, preventing conflicts (e.g., the conveyor should not transport items while the machine is still producing).
- A **Counting Semaphore** is used to limit the number of items on the conveyor.
- The **User Interface** reports production and inspection status through a **Message Queue**.

## Objectives

- Implement concurrent tasks for each factory component using FreeRTOS.
- Use **Preemptive Priority-Based Scheduling** to prioritize tasks, allowing high-priority tasks like item production to run first, without monopolizing resources.
- Use **Round-Robin Scheduling** for tasks of equal priority.
- Use `pdMS_TO_TICKS()` to convert defined times to FreeRTOS ticks.
- Synchronize operations between the machine and conveyor with a **Binary Semaphore**.
- Control the number of items on the conveyor with a **Counting Semaphore**.
- Use a **Mutex** to ensure synchronized access to the User Interface.
- Enable inter-task communication via a **Message Queue**.

This setup ensures smooth system operation where items are produced, inspected, and reported in an organized manner with proper timing and synchronization.

## Solution Explanation

### Tasks

1. **vMachineTask** – Simulates item production. After each item is produced, it releases a binary semaphore for the conveyor and a counting semaphore to update the inspection station.
2. **vConveyorBeltTask** – Executes after the machine releases a binary semaphore, simulating the item transfer on the conveyor.
3. **vInspectionStationTask** – Waits for the counting semaphore, then inspects the item.
4. **vUserInterfaceTask** – Receives messages from the message queue and displays them for the user. A mutex is used to prevent simultaneous access by multiple tasks.

### Synchronization

- **Binary Semaphore**: Synchronizes between item production and conveyor movement.
- **Counting Semaphore**: Limits the number of items on the conveyor, synchronizing production and inspection.
- **Mutex**: Ensures synchronized access to the User Interface, preventing data conflicts.

### Scheduling

- **Preemptive Priority-Based Scheduling**: High-priority tasks, like production, run before lower-priority tasks, such as inspection.
- **Round-Robin Scheduling**: Operates among tasks of equal priority (e.g., inspection and user interface).

### Time Conversion with `pdMS_TO_TICKS`

Each task's delay time is specified in milliseconds, converted to FreeRTOS ticks with `pdMS_TO_TICKS()`.

## Expected Output

When running this code on a FreeRTOS-enabled system, the following console output is expected:

Production Machine: Producing an item... Conveyor Belt: Moving an item... Inspection Station: Inspecting item... User Interface: Item Produced User Interface: Item on Conveyor User Interface: Item Inspected

This output indicates that items are produced, transferred, inspected, and each stage is reported in real-time to the user interface.

## How to Run

1. Set up a FreeRTOS environment on your development platform.
2. Compile and upload the code to your embedded system.
3. Use the console to monitor the production line's progress and the user interface updates.

This README provides an overview and setup instructions for simulating an automated smart factory production line using FreeRTOS multitasking, semaphore synchronization, and message queues.
