# Smart Factory Robotic Production Line Control Using FreeRTOS

This project demonstrates the management of a robotic production line in a smart and advanced factory using FreeRTOS. The production line consists of multiple stations: **Production**, **Packaging**, and **Transport**. Each station handles a different part of the process, and the factory operates efficiently through task scheduling and organization. For correct timing, the factory uses a FreeRTOS-based Round-Robin scheduling system.

## Factory Stations

1. **Production Station** – Responsible for producing components; each component waits for approval to move to the next station.
2. **Packaging Station** – Packages the component once it's ready.
3. **Transport Station** – Transfers the packaged components to the warehouse.

## Round-Robin Scheduling

In this factory setup, multiple stations operate sequentially in a fair and ordered manner using **Round-Robin Scheduling**. Each station runs for a set period and then relinquishes its resources to the next station.

## Semaphores

To manage the process, we use the following semaphores:

- **Binary Semaphore** – Used to approve the transfer of components from the production to the packaging station.
- **Counting Semaphore** – Ensures the number of components transported is limited by the conveyor's capacity.

## Objectives

- Manage multiple tasks in a real-time system.
- Use Round-Robin Scheduling to allow fair resource allocation.
- Implement delays with `pdMS_TO_TICKS()` for accurate timing.
- Control transitions between stations using binary and counting semaphores.

## Code Explanation

### Multitasking

There are three distinct tasks:

- **Production Task (`vProductionTask`)**: Simulates component production.
- **Packaging Task (`vPackagingTask`)**: Simulates the packaging process.
- **Transport Task (`vTransportTask`)**: Simulates the transfer process to the warehouse.

### Round-Robin Scheduling

Each task is created with the same priority (priority level 1), enabling Round-Robin scheduling by FreeRTOS. Each task operates for a set period and then releases resources for other tasks to proceed.

### `pdMS_TO_TICKS()`

Whenever a task needs to delay itself to simulate the time required for production, packaging, or transport, we use `pdMS_TO_TICKS()` to convert milliseconds to FreeRTOS-compatible ticks.

### Binary Semaphore

The binary semaphore `xBinarySemaphore` is used to synchronize between the production and packaging stations. When a component is ready, the production station releases the semaphore, allowing the packaging station to begin its process only after acquiring it.

### Counting Semaphore

The counting semaphore `xCountingSemaphore` limits the number of components that can be transported simultaneously. When a component is packaged, the packaging station releases the counting semaphore, and the transport station takes it to move the component.

## Expected Output

During the execution, the console output should resemble the following:

Production Task: Producing a component... Production Task: Component ready for packaging. Packaging Task: Packaging the component... Packaging Task: Component ready for transport. Transport Task: Transporting component to the warehouse... Transport Task: Component delivered to warehouse.

The component follows an orderly process through the three stations, with Round-Robin scheduling ensuring fair and efficient resource allocation. Semaphores synchronize transitions, and `pdMS_TO_TICKS()` controls timing accurately.

## How to Run

1. Set up a FreeRTOS environment on your development platform.
2. Compile and upload the code to your embedded system.
3. Monitor the console output to track the component's progress through the production line.

This README serves as a guide for setting up and understanding the project code, simulating a smart factory production line using FreeRTOS, Round-Robin scheduling, and semaphore-based synchronization.
