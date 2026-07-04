# OpenCluster

> Open-source Automotive Instrument Cluster Simulator

OpenCluster is an Arduino-based project that simulates the behavior of a modern automotive instrument cluster.

The project follows a modular ECU-inspired architecture and is designed for learning embedded software engineering, automotive systems, and CAN-based dashboard development.

---

## Current Features

- ECU Boot Animation
- Vehicle State Manager
- Speed, fuel and temperature simulation
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
- LEDs
- Push Buttons

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

- [x] LCD Driver
- [x] ECU Boot
- [x] Sensor Manager
- [x] Dashboard Display
- [x] Vehicle State Manager
- [x] Warning Manager
- [x] Event-Driven Display
- [x] Sound Manager
- [X] Driver Controls
- [X] Lighting Manager
- [ ] Engine Simulation
- [ ] CAN Bus Integration
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
