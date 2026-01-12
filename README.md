# 🌤️ Smart Clothes Drying System (Blynk IoT)

## 📌 Giới thiệu
**Phơi đồ thông minh sử dụng Blynk** là hệ thống IoT giúp **tự động thu vào / phơi ra quần áo** dựa trên điều kiện thời tiết và điều khiển từ xa qua điện thoại.

Hệ thống giúp:
- Tránh quần áo bị ướt khi trời mưa
- Tiết kiệm thời gian và công sức
- Điều khiển và giám sát mọi lúc, mọi nơi

---

## ⚙️ Chức năng chính

### 🔹 1. Tự động theo thời tiết
- Phát hiện **mưa** bằng cảm biến mưa
- Phát hiện **ánh sáng** bằng cảm biến LDR
- Tự động:
  - Thu quần áo vào khi trời mưa
  - Phơi ra khi trời nắng

### 🔹 2. Điều khiển từ xa qua Blynk
- Điều khiển hệ thống bằng **ứng dụng Blynk**
- Các chức năng:
  - Thu đồ
  - Phơi đồ
  - Bật / tắt chế độ tự động
- Hiển thị trạng thái hệ thống theo thời gian thực

### 🔹 3. Điều khiển động cơ
- Sử dụng động cơ DC / Servo
- Điều khiển thông qua relay hoặc driver động cơ
- Chuyển động ổn định, dễ triển khai thực tế

---

## 📱 Giao diện Blynk
- Nút điều khiển (Button Widget)
- Hiển thị trạng thái (LED Widget)
- Chế độ Auto / Manual
- Kết nối WiFi

---

## 🧰 Phần cứng sử dụng
- ESP8266 / ESP32
- Cảm biến mưa
- Cảm biến ánh sáng (LDR)
- Relay module / Motor Driver
- Động cơ DC / Servo
- Nguồn cấp

---

## 💻 Phần mềm & Công nghệ
- Ngôn ngữ: **C/C++ (Arduino IDE)**
- Nền tảng IoT: **Blynk**
- Giao tiếp: **WiFi**
- Môi trường phát triển: **Arduino IDE**
