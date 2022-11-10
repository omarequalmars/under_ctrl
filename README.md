// This repo consists mainly of several header files along with some .c files for testing

PID.h is a header files containing a family of functions relating to PID control, mainly culminating in complete PID function with saturation and anti-windup features

filters.h is a work in progress, which will be a family of functions relating to implementation of different filters for data processing.
The TestrunXXX files are test files that generate fake data to test various features on.

The goal is to expand the filters header file into a library for real-time sensor data processing, such as Weighted moving averages and such.
In the future, it is possible that this project is expanded to include functions for other controllers and bring advanced control system to both enthusiasts', students', and professionals' fingertips.
