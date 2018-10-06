#ifndef DEFS_H
#define DEFS_H

// Meant for a 2-pin 2-color LED wired across 1 and 2
// Color = anode
// Codes:
//  Red = resevior needs water
//  Green = resevior has water
//  Blink = want to pump now
//  Solid = want to pump soon
//  Off = idle / all good
#define LED_GREEN 2
#define LED_RED 3

#define PIEZO 4
#define PUMP 5

#define POWER_SOIL 6
#define POWER_WATER 7

#define TRIM_WATER_THRESH A0
#define TRIM_PUMP_TIME A1
#define SENSOR_SOIL A7
#define SENSOR_WATER A6

#define BEEP_INTERVAL 5L * 60L * 1000L
#define SOIL_INTERVAL 60L * 60L * 1000L
#define LED_INTERVAL 500
#define PUMP_TIME_MIN 1000
#define PUMP_TIME_MAX 10000
#define SOAK_TIME 5000
#define MIN_BEEPS 5

// Determined experimentally
#define WATER_LOW_THRESHOLD 600
#define WATER_EMPTY_THRESHOLD 550

enum LEDColor {
  RED,
  GREEN,
  DARK
};

enum WaterLevel {
  WATER_EMPTY,    // pump not submersed
  WATER_LOW,      // pump submersed but resevior isn't full
  WATER_READY     // water above resevior sensor
};

enum WaterTask {
  WATER_START,    // soil needs water
  WATER_CONTINUE, // keep pumping if started - currently unused
  WATER_STOP      // stop adding water
};

#endif

