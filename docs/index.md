---
title: Home
nav_order: 1
---

# 🚗 OpenCluster

> **Behind every dashboard is software. This project explores it.**

OpenCluster is an embedded systems project inspired by the architecture of modern automotive instrument clusters. It simulates how an Electronic Control Unit (ECU) collects, processes, and presents vehicle information to the driver while emphasizing modular software design and automotive engineering principles.

Designed as both a learning platform and a foundation for future automotive cybersecurity research, OpenCluster bridges the gap between embedded programming and real-world vehicle electronics.

---

## Why OpenCluster?

Every time you glance at a vehicle's dashboard, dozens of Electronic Control Units (ECUs) have already exchanged hundreds of messages to determine what should be displayed.

Speed.

Fuel level.

Engine temperature.

Warning indicators.

Gear position.

Most drivers never think about the software making those decisions.

OpenCluster was built to explore that software.

Rather than recreating an entire vehicle, the project focuses on one of its most recognizable components—the instrument cluster—while applying engineering practices commonly found in production automotive software.

---

## Project Objectives

OpenCluster aims to:

- Learn modern embedded software architecture
- Simulate the behavior of an automotive instrument cluster
- Build modular and maintainable embedded software
- Explore state-machine driven system design
- Prepare for CAN Bus integration
- Create a foundation for future automotive cybersecurity research

---

## Current Features

- 🚗 Vehicle startup sequence
- 📊 Speed simulation
- 🔄 RPM simulation
- ⛽ Fuel level monitoring
- 🌡 Engine temperature monitoring
- ⚠ Intelligent warning management
- 📺 LCD dashboard interface
- 🧩 Modular software architecture

---

## Technology Stack

### Programming

- C++
- Arduino Framework

### Hardware

- Arduino Uno
- 16×2 I2C LCD
- LEDs
- Push Buttons

### Development Tools

- Arduino IDE
- Git
- GitHub
- Tinkercad

---

## System Overview

```text
               Driver Inputs
                     │
                     ▼
              Vehicle Data Model
                     │
                     ▼
          Vehicle State Manager
                     │
                     ▼
            Warning Manager
                     │
                     ▼
             Display Manager
                     │
                     ▼
          Instrument Cluster LCD
```

Each module has a single responsibility, making the project easier to understand, extend, and maintain.

---

## Documentation

This documentation walks through the project from both an embedded systems and automotive engineering perspective.

| Section | Description |
|----------|-------------|
| 🏗 Architecture | Overall system architecture and module interactions |
| ✨ Features | Dashboard capabilities and implemented functionality |
| 🔧 Hardware | Components, wiring, and electronics |
| 💻 Software | Project structure and code organization |
| 🚦 State Machine | Vehicle operating states and transitions |
| ⚠ Warning Manager | Warning detection and handling logic |
| 🛣 Roadmap | Planned improvements and future milestones |

---

## Future Direction

OpenCluster is intended to evolve beyond a dashboard simulator into a more complete automotive software platform.

Future development includes:

- CAN Bus communication
- CAN FD support
- STM32 implementation
- FreeRTOS integration
- Virtual ECU communication
- UDS diagnostics
- Automotive cybersecurity demonstrations

---

## Engineering Philosophy

This project is built around a simple idea:

> **Understand complex automotive systems by building simplified versions of them.**

Every new feature is designed not only to function correctly but also to reflect the design principles used in real automotive embedded systems.

---

## Explore the Documentation

Whether you're interested in embedded software, automotive electronics, or cybersecurity, I hope this project provides useful insights into how modern vehicle dashboards are designed and implemented.

Welcome to OpenCluster.
