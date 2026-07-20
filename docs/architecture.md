---
title: System Architecture
nav_order: 2
---

# 🏗 System Architecture

OpenCluster follows a modular software architecture inspired by the layered design commonly found in automotive embedded systems.

Rather than placing all application logic inside a single `loop()` function, responsibilities are separated into independent modules. This approach improves readability, simplifies maintenance, and makes it easier to extend the system as new features are introduced.

---

# Architecture Overview

```text
                User Inputs
                     │
                     ▼
              Input Processing
                     │
                     ▼
              Vehicle Data Model
                     │
                     ▼
          Vehicle State Manager
                     │
         ┌───────────┴───────────┐
         ▼                       ▼
 Warning Manager          Display Manager
         │                       │
         └───────────┬───────────┘
                     ▼
            Instrument Cluster LCD
```

The application follows a one-way data flow where each layer performs a specific task before passing information to the next component.

---

# Design Principles

The project is built around several software engineering principles commonly used in embedded systems.

## Single Responsibility

Each module has one clearly defined responsibility.

For example:

- VehicleData stores the current vehicle information.
- WarningManager evaluates warning conditions.
- DisplayManager handles dashboard rendering.

This separation reduces coupling between modules and improves maintainability.

---

## Data-Driven Design

The dashboard display does not calculate vehicle information directly.

Instead, every module reads from a shared VehicleData structure.

```text
VehicleData

Speed

RPM

Fuel

Temperature

Indicators

Warnings
```

This allows multiple modules to access the same information without duplicating logic.

---

## State-Based Behaviour

Vehicle behaviour changes depending on the current operating state.

Examples include:

- Boot sequence
- Ready state
- Driving mode
- Warning conditions

Using a state machine keeps system behaviour predictable while reducing unnecessary conditional logic.

---

# Core Modules

## Vehicle Data

The Vehicle Data module acts as the central source of truth for the entire application.

It stores:

- Speed
- Engine RPM
- Fuel Level
- Engine Temperature
- Indicator Status
- Warning Flags

Every other software component interacts with this shared data model.

---

## Vehicle State Manager

Responsible for determining the overall operating state of the dashboard.

Examples include:

- Booting
- Ready
- Driving

Future versions may include additional states such as Sleep, Diagnostics, and Shutdown.

---

## Warning Manager

The Warning Manager continuously monitors vehicle parameters.

Current warning conditions include:

- Low Fuel
- High Engine Temperature
- Overspeed

When a condition is detected, warning flags are updated and the dashboard responds accordingly.

---

## Display Manager

The Display Manager converts internal vehicle data into information displayed on the LCD.

Responsibilities include:

- Updating dashboard values
- Showing warning messages
- Managing screen refreshes
- Preventing unnecessary display updates

Keeping display logic isolated from application logic simplifies future display upgrades.

---

# Benefits of the Architecture

The modular design provides several advantages.

- Easier debugging
- Improved readability
- Better scalability
- Cleaner code organization
- Simplified testing
- Easier migration to STM32 and RTOS platforms

---

# Future Evolution

The current architecture was intentionally designed to support future expansion.

Planned additions include:

- CAN Bus interface
- ECU simulation
- FreeRTOS task scheduling
- CAN FD support
- UDS diagnostics
- Automotive cybersecurity modules

The goal is for OpenCluster to evolve from a dashboard simulator into a small automotive software platform.
