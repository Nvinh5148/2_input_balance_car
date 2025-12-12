# STM32 Self-Balancing Robot - Fuzzy Logic Control

![Project Banner](https://img.shields.io/badge/STM32-F103C8T6-blue) ![Algorithm](https://img.shields.io/badge/Control-Fuzzy%20Logic-orange) ![Status](https://img.shields.io/badge/Status-Completed-green)

This project involves the design and implementation of a **Two-Wheeled Self-Balancing Robot** using the **STM32F103C8T6** microcontroller and a **Fuzzy PD Controller**. The system is capable of maintaining static balance and recovering quickly from external disturbances.

##  Demo
*(Insert a link to a demo video or a GIF of the balancing robot here)*

##  Hardware

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
* **SCL**: `PB10`
* **SDA**: `PB11`
* **VCC**: 3.3V
* **GND**: GND

### L298N Driver (Timer 3 PWM)
* **IN1**: `PA6` (TIM3_CH1)
* **IN2**: `PA7` (TIM3_CH2)
* **IN3**: `PB0` (TIM3_CH3)
* **IN4**: `PB1` (TIM3_CH4)

*(Note: Encoder pins PA0, PA1, PB6, PB7 are reserved for future Position Control development)*

##  Control Algorithm

This project utilizes a **Fuzzy Logic Controller (Sugeno Model)** instead of a traditional PID controller to better handle the system's non-linearity.

### Controller Structure:
* **Input 1:** Tilt Angle Error ($e = \theta_{set} - \theta_{measure}$).
* **Input 2:** Derivative of Error ($\dot{e} \approx -Gyro_{rate}$).
* **Output:** PWM signal for motor control.

### Flowchart:
The system operates based on a **10ms** Timer Interrupt:
1. Read MPU6050 data.
2. Calculate Tilt Angle (Kalman/Complementary Filter).
3. Normalize inputs to the range $[-1, 1]$.
4. Execute Defuzzification.
5. Output PWM signal.

![Timer Interrupt Flowchart](path/to/your/flowchart_image.png)
*(Replace with your Flowchart image)*

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

![STMStudio Graph](path/to/stmstudio_result.png)
*(Impulse response graph from STMStudio)*

##  Installation & Usage

1. Clone this repository:
   ```bash
   git clone [https://github.com/your-username/stm32-balance-car-fuzzy.git](https://github.com/your-username/stm32-balance-car-fuzzy.git)
