#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>  
#include <LiquidCrystal.h>
#include <MFRC522>

#define RS  23
#define E   22
#define D4  21
#define D5  19
#define D6  18
#define D7  5


LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup() {
    lcd.begin(16, 2);  
    lcd.print("furrula");
}

void loop() {
}
