#ifndef TYPES_H
#define TYPES_H

enum VehicleState
{
    BOOTING,
    READY,
    DRIVING
};

enum WarningType
{
    ENGINE_HOT,
    LOW_FUEL,
    OVER_SPEED
};

struct VehicleData
{
    int speed;
    int fuel;
    int temperature;

    bool lowFuel;
    bool engineHot;
    bool overSpeed;

    bool headlights;
    bool leftIndicator;
    bool rightIndicator;

    bool leftButton;
    bool rightButton;
    bool hazardButton;
    bool lightButton;
};

#endif