# SolveCore | DIY Cubing Timer

A high-performance, beginner-friendly speedcubing timer built for the Wemos D1 Mini (ESP8266). This project delivers a professional Stackmat experience using capacitive touch sensors and a 20x4 LCD.

---

## Hardware Requirements

* **Microcontroller:** Wemos D1 Mini (or any ESP8266)
* **Display:** 20x4 I2C LCD Module (LiquidCrystal_I2C)
* **Sensors:** 2x TTP223 Capacitive Touch Modules (or copper foil pads)
* **Button:** 1x Tactile Push Button (for Resets)
* **Power:** Micro-USB or 5V Battery



---

## Wiring Pinout

| Component      | Wemos Pin | I2C/Type      |
|----------------|-----------|---------------|
| **LCD VCC** | 5V        | Power         |
| **LCD GND** | G         | Ground        |
| **LCD SDA** | D2        | I2C Data      |
| **LCD SCL** | D1        | I2C Clock     |
| **Left Pad** | D5        | Digital Input |
| **Right Pad** | D6        | Digital Input |
| **Reset Btn** | D7        | Input Pullup  |

---

## Features

- **LCD UI:** Clean layout with dedicated zones for PB, Ao5, and Scrambles.
- **Capacitive Touch:** Zero-latency start/stop logic using skin contact.
- **WCA Scrambler:** Generates a random 20 move scramble after every solve.
- **Session Stats:**
    - **PB:** Tracks your fastest solve of the current session.
    - **Ao5:** Calculates your Average of 5.

---

## How To Use

1. **Arming:** Place both hands on the pads. Wait for the READY progress bar to fill.
2. **Starting:** Lift your hands to start the timer.
3. **Stopping:** Touch either pad (or both) to stop the clock instantly.
4. **Review:** Your time will be displayed for 2 seconds before the next scramble appears.
5. **Resetting:** Hold the Reset Button (D7) to clear your PB and Average.

---

## Setup Instructions

1. **Library:** Open the Arduino IDE Library Manager and install LiquidCrystal_I2C.
2. **Board:** Go to Tools > Board and select LOLIN(WEMOS) D1 R2 & mini.
3. **Upload:** Copy the provided code, hit upload, and enjoy.

> **Note:** The scrambler uses the A0 pin to generate randomness. Leave this pin disconnected for the best results.
