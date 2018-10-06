#include "defs.h"
#include "music.h"

WaterLevel water_level() {
  digitalWrite(POWER_WATER, HIGH);
  int val = analogRead(SENSOR_WATER);
  digitalWrite(POWER_WATER, LOW);

  if ( val < WATER_EMPTY_THRESHOLD )
    return WATER_EMPTY;

  if ( val < WATER_LOW_THRESHOLD )
    return WATER_LOW;

  return WATER_READY;
}

int soil_level() {
  digitalWrite(POWER_SOIL, HIGH);
  delay(1);
  int soil = analogRead(SENSOR_SOIL);
  digitalWrite(POWER_SOIL, LOW);

  // This sensor reports low voltage for high moisture
  return 1023 - soil;
}

WaterTask water_task(int soil) {
  if ( soil < analogRead(TRIM_WATER_THRESH) )
    return WATER_START;
    
  return WATER_STOP;
}

unsigned pump_time()
{ return map(analogRead(TRIM_PUMP_TIME), 0, 1023, PUMP_TIME_MIN, PUMP_TIME_MAX); }

void beep() {
  tone(PIEZO, 2000, 50);
}

void led(LEDColor color) {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  if ( color == RED )
    digitalWrite(LED_RED, HIGH);

  if ( color == GREEN )
    digitalWrite(LED_GREEN, HIGH);
}

void pump(bool on) {
  digitalWrite(PUMP, on ? HIGH : LOW);
}

void wait_for_water() {
  // Must be above low mark. This is to avoid cycling where after pumping some
  // water flows back into the resevior and registers above the empty mark.
  unsigned long start, now;
  unsigned beeps = 0;
  bool needed_water = false;

  for ( start = 0, now = millis(); water_level() != WATER_READY; now = millis() ) {
    needed_water = true;
    if ( now - start >= BEEP_INTERVAL || beeps < MIN_BEEPS ) {
      beep();
      beeps++;
      start = now;
    }

    led(RED);
    delay(LED_INTERVAL);
    led(DARK);
    delay(LED_INTERVAL);
  }
  if ( needed_water )
    play_song(&its_raining_tacos);
}

void pump_water(int soil) {
  unsigned long start = millis();
  unsigned long now, led_start = 0;
  bool led_on = false;

  pump(true);
  for ( now = millis(); now - start < pump_time(); now = millis() ) {
    if ( water_task(soil) == WATER_STOP ) // for instant trim feedback
      break;

    if ( now - led_start >= LED_INTERVAL ) {
      led_start = now;
      led(led_on ? DARK : GREEN);
      led_on = !led_on;
    }
  }

  pump(false);
}

void let_soak() {
  led(GREEN);
  delay(SOAK_TIME);
  led(DARK);
}

// Built and coded using resistive sensors.
// Use capacitive sensors for better polling and longer life.
void loop() {
  static unsigned long last_read = 0;
  static int soil = 0;
  unsigned long now = millis();

  // done with a delay-less loop for instant trim feedback
  // without polling the sensor constantly and killing it
  if ( now - last_read >= SOIL_INTERVAL || last_read == 0 ) {
    soil = soil_level();
    last_read = millis();
  }

  if ( water_task(soil) == WATER_START ) {
    while ( water_task(soil) != WATER_STOP ) {
      wait_for_water();
      pump_water(soil);
      let_soak();
      soil = soil_level();
    }
  }
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(POWER_WATER, OUTPUT);
  pinMode(POWER_SOIL, OUTPUT);
  pinMode(TRIM_WATER_THRESH, INPUT);
  pinMode(TRIM_PUMP_TIME, INPUT);
  pinMode(SENSOR_WATER, INPUT);
  pinMode(SENSOR_SOIL, INPUT);

  // wire_test();
  play_song(&happy_birthday);
}

void wire_test() {
  delay(1000);
  led(RED);
  delay(1000);
  led(GREEN);
  delay(1000);
  led(DARK);
  delay(1000);
  pump(true);
  delay(1000);
  pump(false);
  delay(1000);
  beep();

  Serial.begin(9600);
  while ( true ) {
    Serial.print("water thresh: ");
    Serial.println(analogRead(TRIM_WATER_THRESH));

    Serial.print("pump time: ");
    Serial.println(analogRead(TRIM_PUMP_TIME));

    Serial.print("sensor soil: ");
    Serial.println(soil_level());

    digitalWrite(POWER_WATER, HIGH);
    int water = analogRead(SENSOR_WATER);
    digitalWrite(POWER_WATER, LOW);

    Serial.print("sensor water: ");
    Serial.println(water);

    delay(1000);
  }
}

