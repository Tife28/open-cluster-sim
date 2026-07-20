---
title: Software
nav_order: 5
---

# 💻 Software Design

OpenCluster follows a modular software architecture inspired by the design principles used in modern automotive embedded systems.

Rather than placing all application logic inside a single `loop()` function, the project separates functionality into independent modules. Each module is responsible for a single aspect of the system, making the codebase easier to understand, maintain, and extend.

---

# Design Philosophy

The software is built around four key principles:

- **Modularity** — Each component has a clearly defined responsibility.
- **Maintainability** — Features can be modified without affecting unrelated modules.
- **Scalability** — The architecture supports future expansion, including CAN Bus communication and additional ECUs.
- **Readability** — Code is organized to make navigation and debugging straightforward.

---

# Software Architecture

![Software Architecture](assets/diagrams/architecture.png)

The application follows a layered architecture where data flows from user inputs to the dashboard display through several dedicated modules.

---

# Project Structure

```text
OpenCluster
│
├── src/
│   ├── main.cpp
│   ├── VehicleData.cpp
│   ├── VehicleState.cpp
│   ├── WarningManager.cpp
│   ├── DisplayManager.cpp
│   └── InputManager.cpp
│
├── include/
│   ├── VehicleData.h
│   ├── VehicleState.h
│   ├── WarningManager.h
│   ├── DisplayManager.h
│   └── InputManager.h
│
├── docs/
├── assets/
└── README.md
```

> The exact project structure may evolve as new features are added.

---

# Core Modules

## VehicleData

The `VehicleData` module acts as the central data model for the application.

It stores all information describing the current state of the simulated vehicle, including:

- Speed
- Engine RPM
- Fuel Level
- Engine Temperature
- Warning Flags
- Indicator Status

Rather than passing variables between modules, all components read from and write to this shared data model.

---

## Input Manager

The Input Manager reads user inputs and converts them into vehicle parameters.

Current responsibilities include:

- Reading potentiometer values
- Processing button inputs
- Updating the VehicleData model

Future versions may include CAN Bus message reception as an additional input source.

---

## Vehicle State Manager

The Vehicle State Manager controls the overall operating mode of the dashboard.

Current states include:

- Booting
- Ready
- Driving

Future versions may include:

- Sleep
- Diagnostics
- Shutdown
- Maintenance Mode

Using a state machine keeps system behaviour predictable and easier to extend.

---

## Warning Manager

The Warning Manager continuously evaluates vehicle parameters to determine whether driver alerts should be activated.

Current warning conditions include:

- Low Fuel
- High Engine Temperature
- Overspeed

Separating warning logic into its own module allows new warning types to be added without affecting the rest of the application.

---

## Display Manager

The Display Manager is responsible for updating the dashboard.

Responsibilities include:

- Formatting display information
- Updating LCD values
- Displaying warning messages
- Minimizing unnecessary screen refreshes

Keeping display logic isolated from application logic improves maintainability and makes future display upgrades easier.

---

# Data Flow

The software follows a simple one-way flow of information.

```text
Driver Input
      │
      ▼
Input Manager
      │
      ▼
VehicleData
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
LCD Dashboard
```

This structure keeps each module focused on a single responsibility while reducing coupling between components.

---

# Software Design Decisions

Several architectural decisions were made during development.

### Shared Data Model

Instead of passing numerous variables between modules, OpenCluster stores vehicle information inside a central `VehicleData` structure.

This improves readability and simplifies future feature development.

---

### Modular Components

Each subsystem performs one specific task.

Examples include:

- Input processing
- Warning detection
- Dashboard rendering

This makes debugging and testing significantly easier.

---

### Layered Processing

Every module processes information before handing it to the next stage.

This mirrors the layered processing found in many embedded automotive systems.

---

# Scalability

The current architecture was intentionally designed to support future expansion.

Planned additions include:

- CAN Bus communication
- Virtual ECU simulation
- FreeRTOS task scheduling
- CAN FD support
- UDS diagnostics
- Automotive cybersecurity modules

These features can be integrated with minimal changes to the existing architecture because of the project's modular design.

---

# Summary

OpenCluster's software architecture prioritizes clarity, maintainability, and scalability over complexity.

By separating responsibilities into dedicated modules and using a shared vehicle data model, the project provides a solid foundation for future development while reflecting many of the design principles used in real automotive embedded systems.
