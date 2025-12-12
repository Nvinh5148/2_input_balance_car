# STM32 Self-Balancing Robot - Fuzzy Logic Control

![Project Banner](https://img.shields.io/badge/STM32-F103C8T6-blue) ![Algorithm](https://img.shields.io/badge/Control-Fuzzy%20Logic-orange) ![Status](https://img.shields.io/badge/Status-Completed-green)

This project involves the design and implementation of a **Two-Wheeled Self-Balancing Robot** using the **STM32F103C8T6** microcontroller and a **Fuzzy PD Controller**. The system is capable of maintaining static balance and recovering quickly from external disturbances.

##  Real Hardware Implementation

The physical model is constructed using a 2-layer acrylic chassis to ensure stability and organized wiring.

### 1. Wiring Diagram
The complete connection schematic including the power block, central processing unit, and motor driver.

<img width="585" height="368" alt="image" src="https://github.com/user-attachments/assets/04720585-705c-46c4-bacb-b083bd7e396f" />


### 2. Finished Model
The heavy components (Battery, Motors) are placed on the bottom layer to lower the center of gravity, while the control circuits (STM32, L298N) are mounted on the top layer.

<img width="894" height="670" alt="image" src="https://github.com/user-attachments/assets/c16c8d33-3fa4-4895-952d-1b89b0d769ff" />


The system is built using the following main components:

| Component | Detail | Note |
| :--- | :--- | :--- |
| **Microcontroller** | STM32F103C8T6 (Blue Pill) | ARM Cortex-M3, 72MHz |
| **IMU Sensor** | MPU6050 | Accelerometer + Gyroscope (6-DOF) |
| **Motors** | DC Geared Motor JGB37-520 | Equipped with Encoder (Not used in v1.0) |
| **Motor Driver** | L298N | Dual H-Bridge Module |
| **Power Source** | LiPo 4S Battery (14.8V) | High discharge rate (45C) |
| **Buck Converter** | LM2596 | Steps down 14.8V to 5V/3.3V for logic |

##  Pinout & Wiring

### MPU6050 (I2C2)
* **SCL**: `PB8`
* **SDA**: `PB9`
* **VCC**: 3.3V
* **GND**: GND

### L298N Driver (Timer 3 PWM)
* **IN1**: `PA6` (TIM3_CH1)
* **IN2**: `PA7` (TIM3_CH2)
* **IN3**: `PB0` (TIM3_CH3)
* **IN4**: `PB1` (TIM3_CH4)

*(Note: Encoder pins PA0, PA1, PB6, PB7 are reserved for future Position Control development)*

##  Control Algorithm (Fuzzy Logic)

This project utilizes a **Fuzzy Logic Controller (Sugeno Model)** to better handle the system's non-linearity compared to a traditional PID controller.

### 1. Linguistic Variables & Membership Functions
The controller defines inputs and outputs using linguistic variables normalized to the range $[-1, 1]$.

* **Input 1: Error ($e$)**: Tilt angle error.
    * Sets: `NB`, `NS`, `ZE`, `PS`, `PB` (Trapezoidal/Triangular).
* **Input 2: Error_dot ($\dot{e}$)**: Angular velocity (Gyro).
    * Sets: `NB`, `NS`, `ZE`, `PS`, `PB` (Trapezoidal/Triangular).
* **Output: Control Signal ($u$)**: PWM duty cycle factor.
    * Sets: `NB`, `NM`, `NS`, `ZE`, `PS`, `PM`, `PB` (Sugeno Constants).
    * 
*(Image illustrating the Membership Functions for e, edot, and u)*

<img width="434" height="341" alt="image" src="https://github.com/user-attachments/assets/4aecd96e-e1c0-4176-8197-05a04247a543" />
<img width="396" height="159" alt="image" src="https://github.com/user-attachments/assets/e3dab52b-4019-4fd5-baa6-f81c9def3066" />

### 2. Fuzzy Rule Base (5x5 Matrix)
The system uses a set of 25 rules based on a diagonal structure to ensure stability and smooth damping.

| $\dot{e}$ \ $e$ | NB | NS | ZE | PS | PB |
| :---: | :---: | :---: | :---: | :---: | :---: |
| **NB** | NB | NB | NM | NS | ZE |
| **NS** | NB | NM | NS | ZE | PS |
| **ZE** | NM | NS | ZE | PS | PM |
| **PS** | NS | ZE | PS | PM | PB |
| **PB** | ZE | PS | PM | PB | PB |


### 4. Controller Flowchart
The control loop operates on a **10ms** Timer Interrupt:
1. Read MPU6050 data.
2. Calculate Tilt Angle (Kalman/Complementary Filter).
3. Normalize inputs to $[-1, 1]$.
4. **Fuzzification -> Inference -> Defuzzification**.
5. Output PWM signal.

##  Tuning Parameters

Optimal parameters were determined through experimental tuning with a 4S LiPo battery:

| Parameter | Value | Description |
| :--- | :--- | :--- |
| **K_e** | `0.2` | Error Scaling Factor (Stiffness - Proportional) |
| **K_e_dot** | `0.01` | Error_dot Scaling Factor (Damping - Derivative) |
| **K_u** | `3000` | Output Gain (PWM Conversion) |

##  Experimental Results

* **Static Balance:** The robot maintains a stable tilt angle at $0^\circ$ (after Offset Calibration).
* **Robustness:**
    * Withstands forced tilt angles up to **25°-30°**.
    * Recovery time to equilibrium: **1-2 seconds**.
    * Utilizes maximum power from the 4S battery to generate high torque.

<img width="843" height="606" alt="image" src="https://github.com/user-attachments/assets/e8bca19a-274d-41b8-9e7b-57f1de9a36c5" />

*(Impulse response graph from STMStudio)*

##  References & Credits

Special thanks to the open-source community. This project utilizes the following libraries:

* **[qlibs](https://github.com/kmilo17pet/qlibs)** by *kmilo17pet*: Used for the **qFIS (Fuzzy Inference System)** engine implementation.
* **[MPU6050](https://github.com/leech001/MPU6050)** by *leech001*: Used for MPU6050 I2C communication and **Kalman Filter** algorithm.

##  Author

* **Name:** [Nguyen Vinh]
* **University:** Ho Chi Minh City University of Technology (HCMUT)

---
*If you find this project useful, please give it a ⭐!*
