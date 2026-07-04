#include "Vehicle.h"
#include "Globals.h"
#include "Config.h"

void processVehicleState()
{
    vehicle.lowFuel =
        vehicle.fuel <= LOW_FUEL_LEVEL;

    vehicle.engineHot =
        vehicle.temperature >= HIGH_ENGINE_TEMP;

    vehicle.overSpeed =
        vehicle.speed >= OVERSPEED_LIMIT;

    currentState =
        (vehicle.speed == 0) ? READY : DRIVING;
}