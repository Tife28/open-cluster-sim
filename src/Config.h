#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

const byte SPEED_SENSOR_PIN = A0;
const byte FUEL_SENSOR_PIN  = A1;
const byte TEMP_SENSOR_PIN  = A2;

const byte BUZZER_PIN = 8;

const byte LEFT_LED_PIN   = 2;
const byte RIGHT_LED_PIN  = 3;
const byte ENGINE_LED_PIN = 4;
const byte FUEL_LED_PIN   = 5;
const byte HIGH_LED_PIN   = 6;

const byte LEFT_BUTTON_PIN   = 9;
const byte RIGHT_BUTTON_PIN  = 10;
const byte HAZARD_BUTTON_PIN = 11;
const byte LIGHT_BUTTON_PIN  = 12;

const int MAX_SPEED = 200;
const int MAX_FUEL = 100;

const int MIN_ENGINE_TEMP = 20;
const int MAX_ENGINE_TEMP = 120;

const int LOW_FUEL_LEVEL = 15;
const int HIGH_ENGINE_TEMP = 105;
const int OVERSPEED_LIMIT = 120;

#endif