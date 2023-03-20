This repo consists mainly of several header files along with some .c files for testing

PID.h is a header files containing a family of functions relating to PID control, mainly culminating in a complete PID function with saturation and anti-windup features.

MRAC.h is a header file containing functions for Model-Reference Adaptive Control implementing the MIT-rule

Note: please read comments inside the header files before using them in your code, it is important for your project to know how these functions work and how to correctly use them

filters.h is a work in progress, which will be a family of functions relating to the implementation of different filters for data processing.

The TestrunXXX files are test files that generate fake data to test various features on, ex. TestRunPID.c is a file testing the PID function, meant to simulate a void loop in an Arduino/ESP. In the future there will be a series of different Testrun files for development and demonstration of different functionalities.

DCMotorHBridge.h is a header file containing a family of functions commonly used in the operation of DC Motors using H-bridges

The goal is to expand the filters header file into a library for real-time sensor data processing, such as Weighted moving averages and such.
In the future, it is possible that this project is expanded to include functions for other controllers and bring advanced control system to both enthusiasts', students', and professionals' fingertips.
