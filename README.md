# Footstep Power Generation Using Arduino

![Project Banner](images/prototype.jpg)

> **Piezoelectric energy harvesting system that converts mechanical pressure from human footsteps into electrical energy, monitored in real-time using Arduino Uno with LCD display.**

---

## Table of Contents

- [About the Project](#about-the-project)
- [How It Works](#how-it-works)
- [Block Diagram](#block-diagram)
- [Components Required](#components-required)
- [Circuit Diagram](#circuit-diagram)
- [Arduino Code](#arduino-code)
- [Output & Results](#output--results)
- [Applications](#applications)
- [Future Improvements](#future-improvements)
- [Project Report](#project-report)
- [License](#license)

---

## About the Project

Footstep Power Generation is an embedded systems project that demonstrates **renewable energy harvesting** from human walking motion. When a person steps on a piezoelectric tile, the mechanical pressure is converted into small bursts of AC voltage. This voltage is rectified, smoothed, and fed into an Arduino Uno, which reads and displays the generated power in real time on a 16x2 LCD screen.

This project highlights how wasted **kinetic energy** from daily human movement can be captured and utilized for low-power applications — making it a practical and eco-friendly solution for public spaces like railway stations, shopping malls, and walkways.

### Key Features

- Real-time voltage and power monitoring via Arduino
- LCD display showing live energy output
- Low-cost, easily replicable hardware setup
- Scalable design for multiple piezoelectric tiles

---

## How It Works

```
Footstep Applied
      ↓
Piezoelectric Disc (generates AC voltage)
      ↓
Bridge Rectifier (converts AC → DC)
      ↓
Capacitor (smooths and filters voltage)
      ↓
Arduino Uno (reads voltage via analog pin A0)
      ↓
LCD Display (shows voltage & power output)

```

1. **Piezoelectric Effect** — When mechanical pressure is applied to the piezo disc, it deforms and generates a small alternating voltage (typically 2V–10V per step).
2. **Rectification** — A bridge rectifier (4 diodes) converts the AC output to DC.
3. **Smoothing** — A capacitor filters out ripple and stabilizes the DC voltage.
4. **Steps and voltage Reading** — Arduino reads the steps and voltage from pin A0 (0–1023 values mapped to 0–5V).

   ```
6. **Display** — Results are shown on the I2C 16x2 LCD in real time.

---

## Block Diagram

```
[Piezo Disc] → [Bridge Rectifier] → [Capacitor] → [Arduino Uno] → [LCD Display]
                                                         ↓
                                                   [LED Indicator]
```

---

## Components Required

| Component | Specification | Quantity |
|---|---|---|
| Arduino Uno | ATmega328P, 5V | 1 |
| Piezoelectric Disc | 27mm diameter | 4–6 |
| Bridge Rectifier | IN4007 diodes | 4 |
| Capacitor | 1000µF / 25V | 1 |
| I2c 16x2 LCD Display | HD44780 compatible | 1 |
| Potentiometer | 10kΩ (for LCD contrast) | 1 |
| LED | 5mm, Red or Green | 1 |
| Resistor | 220Ω (for LED) | 1 |
| Resistor | 10kΩ (voltage divider) | 2 |
| Connecting Wires | Male-to-Male jumper | As needed |
| Breadboard | Full size | 1 |
| USB Cable | Type-A to Type-B | 1 |
| Wooden/Acrylic Base | For tile mounting | 1 |

**Estimated Cost:** ₹500 – ₹800 (approx.)

---

## Circuit Diagram

> See `circuit/schematic.png` for the full Fritzing circuit diagram.

### Pin Connections

| Arduino Pin | Connected To |
|---|---|
| A0 | Output of capacitor (via voltage divider) |
| Pin 12 | LCD RS |
| Pin 11 | LCD EN |
| Pin 5 | LCD D4 |
| Pin 4 | LCD D5 |
| Pin 3 | LCD D6 |
| Pin 2 | LCD D7 |
| Pin 8 | LED Anode (via 220Ω resistor) |
| 5V | VCC for LCD and circuit |
| GND | Common ground |

---

## Arduino Code

The full source code is available in the `src/` folder: [`src/footstep_power.ino`](src/footstep_power.ino)

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Change 0x27 to 0x3F if your LCD address is different
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sensorPin = A0;

void setup() {
  // Initialize LCD
  lcd.init();          // or lcd.begin(16, 2) with some libraries
  lcd.backlight();

  // Optional startup message
  lcd.setCursor(0, 0);
  lcd.print("FOOT STEP GENERATION");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);
}

void loop() {
  // Read raw sensor value (0–1023)
  int FOOTSTEP = analogRead(sensorPin);          // Nano analogRead uses A0–A5. [web:17][web:67]

  // Convert to voltage (optional, for nicer display)
  float voltage = FOOTSTEP * (5.0 / 1023.0);     // 0–5 V mapping. [web:65]

  // Clear and print
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FOOTSTEP : ");
  lcd.print(FOOTSTEP);

  lcd.setCursor(0, 1);
  lcd.print("V: ");
  lcd.print(voltage, 2);   // 2 decimal places

  delay(200);              // Update ~5 times per second
}
```

### How to Upload the Code

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Open `src/footstep_power.ino`
3. Go to **Tools** → **Board** → select **Arduino Uno**
4. Go to **Tools** → **Port** → select your COM port
5. Click the **Upload** button (→)

---

## Output & Results

### LCD Output Example

```
FOOTSTEP: -
V: 3.42V
```

---

## Applications

- Smart energy floors in metro stations and airports
- Self-powered street lighting and signboards
- IoT sensor nodes powered by foot traffic
- Military boot energy harvesting for field devices
- Smart homes and office corridors
- Emergency lighting in public spaces

---

## Future Improvements

- Add a **battery storage module** to store harvested energy
- Use **multiple piezo tiles** in an array for higher power output
- Add an **LCD display** for better readability

---

## Project Report

The full project report including abstract, literature review, methodology, and references is available in:
📄 [`docs/project_report.pdf`](docs/project_report.pdf)

---

**Institution:** East West Institute of Technologu
**Department:** [ECE]
**Academic Year:** 2024–2025

---

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## Acknowledgements

- [Arduino Official Documentation](https://www.arduino.cc/reference/en/)
- [Piezoelectric Energy Harvesting — Research Reference]

---

*If you found this project helpful, please give it a ⭐ on GitHub!*
