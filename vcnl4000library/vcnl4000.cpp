/*
 * vcnl4000.cpp
 *
 * VCNL4000 i2c proximity/light sensor
 *
 * Written by Adafruit! Public domain.
 *
 * Datasheet: http://www.adafruit.com/datasheets/vcnl4000ps.pdf
 *
 */

#include "vcnl4000.h"

VCNL4000::VCNL4000() {
}

void VCNL4000::begin() {
	Wire.begin();

	configure();
}


void VCNL4000::configure() {
	uint8_t rev = read8(VCNL4000_PRODUCTID);

	if ((rev & 0xF0) != 0x10) {
		#if VCNL4000_DEBUG == 1
		Serial.println("VCNL4000 Sensor not found :(");
		#endif
	}

	writeLedCurrent(20); // set to 20 * 10mA = 200mA
	writeProximityAdjust(0x81);
}


void VCNL4000::writeLedCurrent(uint8_t current) {
	write8(VCNL4000_IRLED, current);
}


uint8_t VCNL4000::readLedCurrent() {
	return read8(VCNL4000_IRLED);
}


void VCNL4000::writeProximityAdjust(uint8_t adjust) {
	write8(VCNL4000_PROXINITYADJUST, adjust);
}


uint8_t VCNL4000::readProximityAdjust() {
	return read8(VCNL4000_PROXINITYADJUST);
}


uint16_t VCNL4000::readAmbientData() {
	// read ambient light!
	write8(VCNL4000_COMMAND, VCNL4000_MEASUREAMBIENT );
	
	uint16_t ambientData = 0;

	while (ambientData == 0) {
		uint8_t result = read8(VCNL4000_COMMAND);
		if (result & VCNL4000_AMBIENTREADY) {
			ambientData = read16(VCNL4000_AMBIENTDATA);
		}
		delay(10);
	}

	return ambientData;
}


uint16_t VCNL4000::readProximityData() {
	// read ambient light!
	write8(VCNL4000_COMMAND, VCNL4000_MEASUREPROXIMITY);

	uint16_t proximityData = 0;

	while (proximityData == 0) {
		uint8_t result = read8(VCNL4000_COMMAND);

		if ((result & VCNL4000_PROXIMITYREADY)) {
			proximityData = read16(VCNL4000_PROXIMITYDATA);
		}
		delay(10);
	}

	return proximityData;
}


// Read 1 byte from the VCNL4000 at 'address'
uint8_t VCNL4000::read8(uint8_t address) {
	uint8_t data;

	Wire.beginTransmission(VCNL4000_ADDRESS);
#if ARDUINO >= 100
	Wire.write(address);
#else
	Wire.send(address);
#endif
	Wire.endTransmission();

	delayMicroseconds(170);  // delay required

	Wire.requestFrom(VCNL4000_ADDRESS, 1);
	while(!Wire.available());

#if ARDUINO >= 100
	return Wire.read();
#else
	return Wire.receive();
#endif
}


// Read 2 byte from the VCNL4000 at 'address'
uint16_t VCNL4000::read16(uint8_t address) {
	uint16_t data;

	Wire.beginTransmission(VCNL4000_ADDRESS);
#if ARDUINO >= 100
	Wire.write(address);
#else
	Wire.send(address);
#endif
	Wire.endTransmission();

	Wire.requestFrom(VCNL4000_ADDRESS, 2);
	while(!Wire.available());
#if ARDUINO >= 100
	data = Wire.read();
	data <<= 8;
	while(!Wire.available());
	data |= Wire.read();
#else
	data = Wire.receive();
	data <<= 8;
	while(!Wire.available());
	data |= Wire.receive();
#endif

	return data;
}


// write 1 byte
void VCNL4000::write8(uint8_t address, uint8_t data) {
	Wire.beginTransmission(VCNL4000_ADDRESS);
#if ARDUINO >= 100
	Wire.write(address);
	Wire.write(data);  
#else
	Wire.send(address);
	Wire.send(data);  
#endif
	Wire.endTransmission();
}