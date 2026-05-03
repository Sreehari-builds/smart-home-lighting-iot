# 🔌 IoT Smart Home Lighting System

## 📖 Overview

This project presents a **Smart Home Lighting System** using Arduino with **multi-interface control**:

* 🔢 Keypad (manual control)
* 📶 Bluetooth Mobile App (wireless control)
* 📡 Ultrasonic Sensor (automatic motion-based control)

The system enables **flexible, real-time control of lighting**, combining embedded systems with IoT concepts.

---

## ⚙️ Features

* Master ON/OFF control
* Independent control of two LEDs
* Adjustable brightness (0–100%)
* Preset lighting modes (Low, Medium, High)
* Motion detection using ultrasonic sensor
* Dual control via keypad and mobile app
* Real-time synchronization between interfaces

---

## 📱 Mobile App Control

A custom Bluetooth-based mobile application is used to:

* Toggle LED1 and LED2
* Control system ON/OFF
* Adjust brightness using sliders
* Select lighting modes
* Receive real-time status updates

This provides a **user-friendly interface** for remote operation.

---

## 🧠 Working Principle

* The **keypad** allows direct physical interaction with the system.
* The **Bluetooth module (HC-05)** communicates with a mobile app for wireless control.
* The **ultrasonic sensor** detects nearby motion (≤ 40 cm) and activates lighting automatically.
* The Arduino processes inputs from all interfaces and updates the system accordingly.

---

## 🔌 Hardware Components

* Arduino Uno
* 4×4 Keypad
* HC-05 Bluetooth Module
* Ultrasonic Sensor (HC-SR04)
* 2 LEDs
* Resistors
* Jumper wires

---

## 🔗 Pin Configuration

| Device Pin | Arduino Pin                |
| ---------- | -------------------------- |
| R1         | 2                          |
| R2         | 8                          |
| R3         | 4                          |
| R4         | A3                         |
| C1         | 12                         |
| C2         | 13                         |
| C3         | A1                         |
| C4         | A2                         |
| VCC        | 5V                         |
| GND        | GND                        |
| TRIG       | 7                          |
| ECHO       | 6                          |
| LED1       | 9                          |
| LED2       | 3                          |
| TX         | 10                         |
| RX         | 11 *(via voltage divider)* |

---

## 🎮 Controls

### Keypad Controls

| Key | Function                          |
| --- | --------------------------------- |
| *   | Master ON                         |
| 0   | Master OFF                        |
| 1   | Toggle LED1                       |
| 2   | Toggle LED2                       |
| 4/5 | Decrease/Increase LED1 brightness |
| 3/6 | Decrease/Increase LED2 brightness |
| 7   | Low Mode                          |
| 8   | Medium Mode                       |
| 9   | High Mode                         |
| #   | Toggle Ultrasonic Mode            |

---

### 📶 Bluetooth Commands (App Communication)

* `L1_ON`, `L1_OFF`
* `L2_ON`, `L2_OFF`
* `SYS_ON`, `SYS_OFF`
* `B1_x` → LED1 brightness (0–100)
* `B2_x` → LED2 brightness (0–100)
* `M1`, `M2`, `M3` → Modes

---

## 🛠️ Setup Instructions

1. Connect components as per pin configuration
2. Upload the Arduino code
3. Power the circuit
4. Pair HC-05 with your mobile phone
5. Open the mobile app
6. Control lights using app or keypad

---

## 🚀 Future Improvements

* WiFi-based IoT control (ESP8266 / ESP32)
* Voice assistant integration
* Energy-efficient automation
* Dedicated Android/iOS app with UI enhancements

---

## 👨‍💻 Author

**Sreehari P**

---

## 📌 Conclusion

This project demonstrates a **hybrid smart lighting system** combining manual control, wireless communication, and automation. It highlights key IoT concepts such as real-time control, sensor integration, and user-friendly interfaces.

---
