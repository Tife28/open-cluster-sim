#include "Sensors.h"
#include "Globals.h"
#include "Config.h"

void readSensors()
{
    vehicle.speed =
        map(analogRead(SPEED_SENSOR_PIN),0,1023,0,MAX_SPEED);

    vehicle.fuel =
        map(analogRead(FUEL_SENSOR_PIN),0,1023,0,MAX_FUEL);

    vehicle.temperature =
        map(analogRead(TEMP_SENSOR_PIN),
            0,1023,
            MIN_ENGINE_TEMP,
            MAX_ENGINE_TEMP);
}