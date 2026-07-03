# OpenCluster

> Open-source Automotive Instrument Cluster Simulator

OpenCluster is an Arduino-based project that simulates the behavior of a modern automotive instrument cluster.

The project follows a modular ECU-inspired architecture and is designed for learning embedded software engineering, automotive systems, and CAN-based dashboard development.

---

## Current Features

- ECU Boot Animation
- Vehicle State Manager
- Speed Simulation
- Fuel Simulation
- Engine Temperature Simulation
- Warning Manager
- Event-driven LCD Updates
- Audible Warning System
- Modular Firmware Architecture

---

## Hardware

- Arduino Uno
- 16×2 I²C LCD (MCP23008)
- Passive Buzzer
- Potentiometers
- LEDs (Upcoming)
- Push Buttons (Upcoming)

---

## Roadmap

### v0.1
- LCD Driver

### v0.2
- ECU Boot Animation

### v0.3
- Sensor Manager

### v0.4
- Warning Manager

### v0.5
- Event-driven Display

### v0.6
- Sound Manager

### v0.7
- Driver Controls

### v0.8
- Lighting Manager

### v0.9
- Engine Simulation

### v1.0
- Instrument Cluster Simulator

---

## Project Architecture

```
Sensors
      │
Driver Controls
      │
Vehicle Manager
      │
Warning Manager
      │
├── Display Manager
├── Sound Manager
└── Lighting Manager
```

---

## License

MIT
