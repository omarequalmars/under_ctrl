# Control Systems Repository

This repository contains a collection of header files and some `.c` files for testing various control systems, filters, and DC motor operation functions.

## Table of Contents
- [PID Control](#pid-control)
- [Model-Reference Adaptive Control](#model-reference-adaptive-control)
- [Filters](#filters)
- [DC Motor Operation](#dc-motor-operation)
- [Future Plans](#future-plans)
- [Important Note](#important-note)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## PID Control
[`PID.h`](PID.h) contains functions for PID control, including saturation and anti-windup features.

## Model-Reference Adaptive Control
[`MRAC.h`](MRAC.h) includes functions for Model-Reference Adaptive Control implementing the Lyapunov-rule.

## Filters
[`filters.h`](filters.h) offers functions for FIR/IIR filters.

## DC Motor Operation
[`DCMotorHBridge.h`](DCMotorHBridge.h) contains functions for operating DC Motors using H-bridges.

## Future Plans
Plans to expand this project to include additional controllers and advanced control systems for enthusiasts, students, and professionals.

## Important Note
Please read the comments inside the header files before using them in your code to understand their functionality and proper usage.

## Installation
```bash
git clone https://github.com/omarequalmars/under_ctrl.git
cd under_ctrl
