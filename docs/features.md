---
title: Features
nav_order: 3
---

# ✨ Features

OpenCluster simulates the core functionality of a modern automotive instrument cluster. Each feature is designed to represent a subsystem commonly found in production vehicles while maintaining a modular and extensible software architecture.

---

# Dashboard Overview

The dashboard provides the driver with essential vehicle information and system feedback.

Current capabilities include:

- Vehicle startup sequence
- Speed monitoring
- Engine RPM monitoring
- Fuel level monitoring
- Engine temperature monitoring
- Intelligent warning management
- LCD dashboard display
- Modular software architecture

---

# Vehicle Startup Sequence

Upon power-up, OpenCluster performs a simulated vehicle boot process before entering normal operation.

The startup sequence provides a more realistic user experience by mimicking the initialization behavior of a modern digital instrument cluster.

### Highlights

- Simulated system initialization
- Smooth transition into driving mode
- Foundation for future self-diagnostics

---

# Speed Simulation

Vehicle speed is simulated using analog input and displayed on the dashboard in real time.

The speed value is continuously updated and serves as an input for other modules, including the Warning Manager.

### Current Functionality

- Real-time speed updates
- Dashboard display
- Overspeed detection support

### Future Improvements

- CAN Bus speed messages
- Cruise control simulation
- Speed limiter functionality

---

# Engine RPM Simulation

OpenCluster simulates engine revolutions per minute (RPM), allowing the dashboard to display engine activity similar to a real vehicle.

### Current Functionality

- Real-time RPM updates
- Dashboard display
- Foundation for future engine simulations

### Future Improvements

- Gear-dependent RPM calculation
- Idle speed simulation
- Rev limiter behavior

---

# Fuel Level Monitoring

Fuel level is continuously monitored and displayed on the dashboard.

When fuel drops below the configured threshold, the Warning Manager generates a low-fuel alert.

### Current Functionality

- Fuel percentage display
- Low fuel detection

### Future Improvements

- Fuel consumption model
- Estimated driving range
- Refueling simulation

---

# Engine Temperature Monitoring

The dashboard monitors simulated engine temperature and detects overheating conditions.

This feature demonstrates how embedded software can continuously evaluate sensor values and react to abnormal operating conditions.

### Current Functionality

- Temperature display
- High temperature warning

### Future Improvements

- Warm-up simulation
- Cooling system behavior
- Fan activation logic

---

# Warning Management

OpenCluster includes a centralized Warning Manager responsible for evaluating vehicle conditions and notifying the driver.

Current warning conditions include:

- Low Fuel
- High Engine Temperature
- Overspeed

The warning system is designed so additional warning types can be added without affecting other modules.

---

# LCD Dashboard Interface

Vehicle information is presented through a 16×2 I2C LCD, providing a compact simulation of an automotive instrument cluster.

Displayed information includes:

- Speed
- RPM
- Fuel level
- Engine temperature
- Active warning messages

The display module only refreshes when values change, reducing unnecessary updates and improving responsiveness.

---

# Modular Software Design

OpenCluster separates functionality into dedicated software modules rather than placing all logic inside a single application loop.

Benefits include:

- Easier maintenance
- Better readability
- Improved scalability
- Simplified debugging
- Cleaner code organization

This architecture also prepares the project for future migration to STM32 and FreeRTOS.

---

# Current Limitations

OpenCluster is currently a software simulation and does not yet communicate with real automotive ECUs.

The following features are planned for future releases:

- CAN Bus communication
- Virtual ECU network
- CAN FD support
- UDS diagnostics
- FreeRTOS task scheduling
- Automotive cybersecurity demonstrations

---

# Summary

OpenCluster demonstrates how a modular embedded application can simulate the behavior of an automotive instrument cluster while providing a strong foundation for future expansion into vehicle networking, embedded operating systems, and automotive cybersecurity.
