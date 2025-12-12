# Xe Tự Cân Bằng STM32 - Điều Khiển Mờ (Fuzzy Logic)

![Banner Dự Án](https://img.shields.io/badge/STM32-F103C8T6-blue) ![Algorithm](https://img.shields.io/badge/Control-Fuzzy%20Logic-orange) ![Status](https://img.shields.io/badge/Status-Completed-green)

Dự án thiết kế và thi công mô hình **Xe hai bánh tự cân bằng (Self-Balancing Robot)** sử dụng vi điều khiển **STM32F103C8T6** và thuật toán điều khiển **PD Mờ (Fuzzy PD Controller)**. Hệ thống có khả năng tự giữ thăng bằng tại chỗ và phục hồi nhanh chóng khi chịu tác động ngoại lực.

## 🎥 Demo
*(Chèn link video demo hoặc ảnh GIF xe đang cân bằng tại đây)*

## 🛠️ Phần Cứng (Hardware)

Hệ thống được thiết kế với các linh kiện chính sau:

| Linh Kiện | Chi Tiết | Ghi Chú |
| :--- | :--- | :--- |
| **Vi điều khiển** | STM32F103C8T6 (Blue Pill) | ARM Cortex-M3, 72MHz |
| **Cảm biến IMU** | MPU6050 | Gia tốc kế + Con quay hồi chuyển (6-DOF) |
| **Động cơ** | DC Geared Motor JGB37-520 | Có Encoder (Encoder chưa dùng trong v1.0) |
| **Driver Động cơ** | L298N | Mạch cầu H kép |
| **Nguồn** | Pin LiPo 4S (14.8V) | Dòng xả cao 45C |
| **Hạ áp** | LM2596 | Hạ 14.8V xuống 5V/3.3V nuôi mạch |

## 🔌 Sơ Đồ Kết Nối (Pinout)

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

*(Lưu ý: Các chân Encoder PA0, PA1, PB6, PB7 được dành riêng cho phát triển Position Control sau này)*

## 🧠 Thuật Toán Điều Khiển (Algorithm)

Dự án sử dụng bộ điều khiển **Fuzzy Logic (Mô hình Sugeno)** thay vì PID truyền thống để xử lý tốt tính phi tuyến của hệ thống.

### Cấu trúc bộ điều khiển:
* **Ngõ vào 1 (Input 1):** Sai số góc nghiêng ($e = \theta_{set} - \theta_{measure}$).
* **Ngõ vào 2 (Input 2):** Đạo hàm sai số ($\dot{e} \approx -Gyro_{rate}$).
* **Ngõ ra (Output):** Tín hiệu PWM điều khiển động cơ.

### Lưu đồ giải thuật (Flowchart):
Hệ thống hoạt động dựa trên ngắt Timer chu kỳ **10ms**:
1. Đọc dữ liệu MPU6050.
2. Tính góc nghiêng (Kalman/Complementary Filter).
3. Chuẩn hóa đầu vào về khoảng $[-1, 1]$.
4. Thực thi giải mờ (Defuzzification).
5. Xuất xung PWM.

![Flowchart Ngắt Timer](path/to/your/flowchart_image.png)
*(Thay thế bằng ảnh Flowchart phần ngắt của bạn)*

## ⚙️ Tinh Chỉnh Tham Số (Tuning)

Các tham số tối ưu được tìm ra thông qua thực nghiệm với nguồn Pin 4S:

| Tham số | Giá trị | Ý nghĩa |
| :--- | :--- | :--- |
| **K_e** | `0.2` | Hệ số chuẩn hóa sai số (Độ cứng - Proportional) |
| **K_e_dot** | `0.01` | Hệ số chuẩn hóa vận tốc góc (Giảm chấn - Derivative) |
| **K_u** | `3000` | Hệ số khuếch đại ngõ ra (Chuyển đổi sang PWM) |

## 📊 Kết Quả Thực Nghiệm

* **Cân bằng tĩnh:** Xe duy trì góc nghiêng ổn định tại $0^\circ$ (sau khi Calibrate Offset).
* **Khả năng chống nhiễu (Robustness):** * Chịu được góc lệch cưỡng bức lên tới **25°-30°**.
    * Thời gian phục hồi về vị trí cân bằng: **1-2 giây**.
    * Sử dụng tối đa công suất pin 4S để tạo moment xoắn lớn.

![Đồ thị STMStudio](path/to/stmstudio_result.png)
*(Đồ thị đáp ứng xung từ STMStudio)*

## 🚀 Hướng Dẫn Cài Đặt (Installation)

1. Clone repository này về máy:
   ```bash
   git clone [https://github.com/your-username/stm32-balance-car-fuzzy.git](https://github.com/your-username/stm32-balance-car-fuzzy.git)
