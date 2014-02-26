// Example sketch for talking to the VCNL4000 i2c proximity/light sensor
// Written by Adafruit! Public domain.
// To use: Connect VCC to 3.3-5V (5V is best if it is available), GND to
//         ground, SCL to i2c clock (on classic arduinos, Analog 5), SDA
//         to i2c data (on classic arduinos Analog 4). The 3.3v pin is
//         an ouptut if you need 3.3V
// This sensor is 5V compliant so you can use it with 3.3 or 5V micros

// You can pick one up at the Adafruit shop: www.adafruit.com/products/466

#include <Wire.h>
#include "vcnl4000.h"

VCNL4000 vcnl;

void setup() {
	Serial.begin(9600);
	Serial.println("VCNL");
	vcnl.begin();

	Serial.print("IR LED current = ");
	Serial.print(vcnl.readLedCurrent());
	Serial.println(" mA");

	Serial.print("Proximity adjustment register = ");
	Serial.println(vcnl.readProximityAdjust(), HEX);
}

void loop() {
	Serial.print("Ambient = ");
	Serial.print(vcnl.readAmbientData());
	Serial.print("\t\tProximity = ");
	Serial.println(vcnl.readProximityData());
	delay(100);
}