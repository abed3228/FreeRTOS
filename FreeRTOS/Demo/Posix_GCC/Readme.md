# Smart Factory Control System Using FreeRTOS Message Queue

This exercise demonstrates the use of a FreeRTOS-based Message Queue for data transfer between two tasks: one that writes data to the queue (Robot) and one that reads from it (Control Unit).

## Overview

In this smart factory scenario, we have a **Production Robot** and a **Control Unit**. The robot is responsible for producing components and sending information about each component to the control unit. The control unit then receives the information, analyzes the component, and displays it to the factory manager.

The robot sends details of each new component it produces, such as the **ID number** and **component type**, to the control unit. The control unit waits for messages from the robot and displays the relevant information to the manager. A **Message Queue** mechanism is used for efficient communication between these two tasks.

## Objectives

- Demonstrate inter-task communication using a FreeRTOS Message Queue.
- Simulate a smart factory environment with a production robot that generates component data and a control unit that processes this data.

## Task Descriptions

### Message Queue

The **message queue `xQueue`** is created with the capacity to hold up to 5 messages. Each message is a `ComponentMessage` structure that contains the **component ID** and **component type**.

### Robot Task (`vRobotTask`)

The robot task simulates the production of components. Each new component has a unique ID and a type (e.g., "Component-0", "Component-1"). The robot sends this information to the message queue using `xQueueSend()`. The task waits one second before producing the next component to simulate time between productions.

### Control Unit Task (`vControlUnitTask`)

The control unit waits for a message from the robot using `xQueueReceive()`. After receiving a message, it prints the component details for the factory manager. The task uses `portMAX_DELAY` to wait indefinitely for a message in the queue (non-blocking behavior that waits until a message arrives).

## Expected Output

The output from running this system should look something like this:

Robot Task: 
Sent component ID=0, Type=Component-0 Control 
Unit Task: 
Received component ID=0, Type=Component-0 
Robot Task: Sent component ID=1, Type=Component-1 Control 
Unit Task: Received component ID=1, Type=Component-1 ...


## Implementation Notes

- **Robot Task (`vRobotTask`)**: Responsible for generating and sending component information.
- **Control Unit Task (`vControlUnitTask`)**: Receives and displays component information.
- **Message Queue (`xQueue`)**: Facilitates data transfer between tasks.

## How to Run

1. Set up a FreeRTOS environment on your development platform.
2. Compile and upload the code to your embedded system.
3. Observe the output on the serial monitor to track the messages sent and received.

This README should help you understand and run the smart factory control system project based on FreeRTOS message queues.
