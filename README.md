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
[`MRAC.h`](MRAC.h) includes functions for Model-Reference Adaptive Control implementing the Lyapunov-rule, using a first-order system as the reference model.

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
```
## Examples
- Classical PID Position Control example
```bash
#include "PID.h"
#define K_p 1.0
#define K_i 10.0
#define K_d 0.1
#define sampling_time 0.005
#define max_PWM 255
#define anti_windup_on 1
#define anti_windup_off 0

#define in1 3
#define in2 4
#define PWM_pin A0

void main(){
float position_setpoint = 10.0
float position_actual, error_signal;
position_actual = readdata();
error_signal = error(position_actual, position_setpoint);
PWM = PID_ctrlr_withZOH(error_signal, K_p, K_i, K_d, max_PWM, sampling_time, anti_windup_on);
MoveitMoveit(PWM, in1, in2, PWM_pin);
```
- MRAC-PI Speed Control Example
```bash
#include "MRAC.h"
#define sampling_time 0.005
#define max_PWM 255
#define anti_windup_on 1
#define anti_windup_off 0

#define in1 3
#define in2 4
#define PWM_pin A0

void main(){
float position_setpoint = 10.0
float position_actual, error_signal;
position_actual = readdata();
error_signal = error(position_actual, position_setpoint);
PWM = ```bash
#include "PID.h"
#define K_init_both 1.0
#define K_integralmax 10.0
#define K_proportionalmax 0.1
#define learning_rate 0.1
#define reference_time_constant 0.01
#define sampling_time 0.005
#define max_PWM 255
#define anti_windup_on 1
#define anti_windup_off 0

#define in1 3
#define in2 4
#define PWM_pin A0

void main(){
float speed_setpoint = 10.0
float speed_actual, error_signal;
speed_actual = readdata();
PWM = UnderControl(speed_actual, speed_setpoint, K_init_both, K_proportionalmax, K_integralmax, learning_rate, reference_time_constant, sampling_time);
MoveitMoveit(PWM, in1, in2, PWM_pin);
```



