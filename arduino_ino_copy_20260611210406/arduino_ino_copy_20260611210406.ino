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
