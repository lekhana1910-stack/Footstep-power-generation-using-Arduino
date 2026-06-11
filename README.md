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
- LED indicator that glows when sufficient voltage is generated
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
      ↓
LED Indicator (glows above threshold voltage)
```

1. **Piezoelectric Effect** — When mechanical pressure is applied to the piezo disc, it deforms and generates a small alternating voltage (typically 2V–10V per step).
2. **Rectification** — A bridge rectifier (4 diodes) converts the AC output to DC.
3. **Smoothing** — A capacitor filters out ripple and stabilizes the DC voltage.
4. **ADC Reading** — Arduino reads the analog voltage from pin A0 (0–1023 values mapped to 0–5V).
5. **Calculation** — Voltage and estimated power are calculated using the formula:
   ```
   Voltage (V) = analogRead(A0) × (5.0 / 1023.0)
   Power (W)   = V² / R   (where R = load resistance in ohms)
   ```
6. **Display** — Results are shown on the 16x2 LCD in real time.

---

## Block Diagram

```
[Piezo Disc] → [Bridge Rectifier] → [Capacitor] → [Arduino Uno] → [LCD Display]
                                                         ↓
                                                   [LED Indicator]
```

> See `circuit/block_diagram.png` for the visual block diagram.

---

## Components Required

| Component | Specification | Quantity |
|---|---|---|
| Arduino Uno | ATmega328P, 5V | 1 |
| Piezoelectric Disc | 27mm diameter | 4–6 |
| Bridge Rectifier | IN4007 diodes | 4 |
| Capacitor | 1000µF / 25V | 1 |
| 16x2 LCD Display | HD44780 compatible | 1 |
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
#include <LiquidCrystal.h>

// LCD pin configuration
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int piezoPin = A0;     // Analog input from piezo circuit
const int ledPin = 8;        // LED indicator pin
const float R_load = 100.0;  // Load resistance in ohms

void setup() {
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  lcd.print("Footstep Power");
  lcd.setCursor(0, 1);
  lcd.print("  Generation  ");
  delay(2000);
  lcd.clear();
}

void loop() {
  int rawValue = analogRead(piezoPin);
  float voltage = rawValue * (5.0 / 1023.0);
  float power = (voltage * voltage) / R_load;

  // Display voltage
  lcd.setCursor(0, 0);
  lcd.print("Volt: ");
  lcd.print(voltage, 2);
  lcd.print(" V  ");

  // Display power
  lcd.setCursor(0, 1);
  lcd.print("Power:");
  lcd.print(power * 1000, 1);
  lcd.print(" mW ");

  // LED glows if voltage exceeds threshold
  if (voltage > 1.5) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(500);
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

### Observed Readings

| Number of Steps | Voltage Generated | Power Output |
|---|---|---|
| 1 step | 1.2V – 2.5V | 14 mW – 62 mW |
| 5 steps | 2.0V – 3.5V | 40 mW – 122 mW |
| 10 steps | 2.8V – 4.2V | 78 mW – 176 mW |
| 20 steps | 3.5V – 4.8V | 122 mW – 230 mW |

> Results may vary based on piezo disc quality, tile pressure, and load resistance.

### LCD Output Example

```
Volt: 3.42 V
Power: 116.9 mW
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
- Integrate **IoT (ESP8266/ESP32)** to monitor output on a mobile app
- Use **multiple piezo tiles** in an array for higher power output
- Add an **OLED display** for better readability
- Implement **MPPT (Maximum Power Point Tracking)** for efficiency
- Design a **custom PCB** to replace the breadboard for durability

---

## Project Report

The full project report including abstract, literature review, methodology, and references is available in:
📄 [`docs/project_report.pdf`](docs/project_report.pdf)

---

## Team Members

| Name | Role |
|---|---|
| [Your Name] | Hardware & Circuit Design |
| [Team Member 2] | Arduino Programming |
| [Team Member 3] | Documentation & Testing |

**Institution:** [Your College Name]
**Department:** [Electronics / ECE / EEE]
**Academic Year:** 2024–2025

---

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## Acknowledgements

- [Arduino Official Documentation](https://www.arduino.cc/reference/en/)
- [Piezoelectric Energy Harvesting — Research Reference]
- Our project guide **[Mentor Name]** for valuable support and guidance

---

*If you found this project helpful, please give it a ⭐ on GitHub!*
