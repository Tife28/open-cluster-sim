#include "Config.h"
#include "Globals.h"
#include "Sensors.h"
#include "Vehicle.h"
#include "DriverControls.h"
#include "WarningManager.h"
#include "Display.h"
#include "Lighting.h"
#include "Sound.h"
#include "Boot.h"

void setup()
{
    bootSequence();
}

void loop()
{
    readSensors();

    readDriverControls();

    processVehicleState();

    processDriverControls();

    updateWarnings();

    updateSound();

    updateLighting();

    updateDisplayScheduler();

    drawDisplay();
}