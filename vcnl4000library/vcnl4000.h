/*
 * vcnl4000.h
 *
 * VCNL4000 i2c proximity/light sensor
 *
 * Written by Adafruit! Public domain.
 *
 * Datasheet: http://www.adafruit.com/datasheets/vcnl4000ps.pdf
 *
 */

#ifndef VCNL4000_h
#define VCNL4000_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "Wire.h"

#define VCNL4000_DEBUG 0

// the i2c address
#define VCNL4000_ADDRESS 0x13

// commands and constants
#define VCNL4000_COMMAND 0x80
#define VCNL4000_PRODUCTID 0x81
#define VCNL4000_IRLED 0x83
#define VCNL4000_AMBIENTPARAMETER 0x84
#define VCNL4000_AMBIENTDATA 0x85
#define VCNL4000_PROXIMITYDATA 0x87
#define VCNL4000_SIGNALFREQ 0x89
#define VCNL4000_PROXINITYADJUST 0x8A

#define VCNL4000_3M125 0
#define VCNL4000_1M5625 1
#define VCNL4000_781K25 2
#define VCNL4000_390K625 3

#define VCNL4000_MEASUREAMBIENT 0x10
#define VCNL4000_MEASUREPROXIMITY 0x08
#define VCNL4000_AMBIENTREADY 0x40
#define VCNL4000_PROXIMITYREADY 0x20

class VCNL4000 {
	public:
		VCNL4000();
		void begin();
		void configure();
		void writeLedCurrent(uint8_t current);
		uint8_t readLedCurrent();
		void writeProximityAdjust(uint8_t adjust);
		uint8_t readProximityAdjust();
		uint16_t readAmbientData(void);
		uint16_t readProximityData(void);

	private:
		uint8_t read8(uint8_t address);
		uint16_t read16(uint8_t address);
		void write8(uint8_t address, uint8_t data);

};

#endif