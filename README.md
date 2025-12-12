# STM32 Self-Balancing Robot - Fuzzy Logic Control

![Status](https://img.shields.io/badge/Status-Completed-green) ![Platform](https://img.shields.io/badge/Platform-STM32-blue) ![Algorithm](https://img.shields.io/badge/Control-Fuzzy%20Logic-orange)

**Two-Wheeled Self-Balancing Robot** project powered by **STM32F103C8T6** and **Fuzzy PD Controller**. The robot is capable of maintaining static balance, resisting external disturbances, and recovering quickly to the upright position.

## 🎥 Demo

![Project Demo](LINK_TO_YOUR_DEMO_GIF_HERE)

## 🛠️ Hardware

* **Microcontroller:** STM32F103C8T6 (Blue Pill)
* **Sensor:** MPU6050 (6-DOF IMU)
* **Actuator:** DC Geared Motor JGB37-520
* **Driver:** L298N Dual H-Bridge
* **Power:** LiPo Battery 4S (14.8V) - High discharge rate
* **Regulator:** LM2596 Buck Converter (14.8V to 5V)

## 🧠 Control Algorithm: Fuzzy Logic

Unlike traditional PID controllers, this project uses a **Sugeno Fuzzy Logic Controller** to handle the non-linear dynamics of the balancing robot.

### 1. Linguistic Variables & Membership Functions
We define 3 linguistic variables with normalized ranges [-1, 1]:
* **Input 1 ($e$):** Tilt Angle Error.
* **Input 2 ($\dot{e}$):** Angular Velocity (Gyro rate).
* **Output ($u$):** PWM Control Signal.

![Linguistic Variables Definition](LINK_TO_IMAGE_OF_MEMBERSHIP_FUNCTIONS_HERE)
*(Figure: Membership Functions for Error, Error_dot, and Output)*

### 2. Fuzzy Rule Base
The controller operates based on a 5x5 rule matrix (25 rules total). The diagonal arrangement ensures stability and smooth damping response.

![Fuzzy Rule Base Table](LINK_TO_IMAGE_OF_RULE_TABLE_HERE)
*(Figure: The 5x5 Fuzzy Rule Base Table)*

### 3. Rule Visualization
The surface below illustrates how the inputs ($e, \dot{e}$) map to the control output ($u$), showing the non-linear response of the controller.

![Fuzzy Surface / Rule Illustration](LINK_TO_IMAGE_OF_RULE_ILLUSTRATION_HERE)
*(Figure: Fuzzy Control Surface / Visualization of Rules)*

### 4. System Flowchart
The control loop runs inside a **10ms Timer Interrupt**:
1.  Read MPU6050.
2.  Compute Angle (Kalman/Complementary Filter).
3.  Fuzzification -> Inference -> Defuzzification.
4.  Write PWM to Motors.

![Timer Interrupt Flowchart](LINK_TO_YOUR_FLOWCHART_IMAGE_HERE)

## ⚙️ Tuning Parameters

Optimal parameters found for 4S Battery setup:

| Parameter | Value | Description |
| :--- | :--- | :--- |
| **K_e** | `0.2` | Error Scaling (Stiffness) |
| **K_e_dot** | `0.01` | Gyro Scaling (Damping) |
| **K_
