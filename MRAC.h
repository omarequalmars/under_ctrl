#include "PID.h"

float modelrefO1(float A_m, float B_m, float setpoint, float T_samp):
float ImproviseAdaptOvercome(float state_real, float gain_initial, float learning_rate, float A_m, float B_m, float setpoint, float T_samp);
float differentiate(float variable, float T_samp);
float UnderControl(float speed,float setpoint, float gain_initial, float gain_max, float learning_rate, float A_m, float B_m, float T_samp);

float modelrefO1(float A_m, float B_m, float setpoint, float T_samp){
    static float state_dot = 0;
    static float state = 0;
    state_dot = -state*A_m + B_m*setpoint;
    state += state_dot*T_samp;
    return state;
}

float ImproviseAdaptOvercome(float state_real, float gain_initial,float gain_max, float learning_rate, float A_m, float B_m, float setpoint, float T_samp){
    static float gain = gain_initial;
    static float tracking_error = 0;
    static float model_error = 0;
    tracking_error = setpoint - state_real;
    model_error = state_real - modelrefO1(A_m, B_m, setpoint, T_samp);
    gain -= T_samp*learning_rate*model_error*tracking_error;
    gain = (gain <= 0) ? 0 : gain;
    gain = (gain >= gain_max) ? gain_max : gain;
    return gain;
}

float NeedForSpeed(float variable, float T_samp){
    static float X = 0;
    static float X_last = 0;
    static float diff = 0;
    diff = (X - X_last)/T_samp;
    X_last = X;
    return diff;
}

float UnderControl(float speed,float setpoint, float gain_initial, float gain_max, float learning_rate, float A_m, float B_m, float T_samp){
    static float gain = 0;
    static float tracking_err = 0;
    static float ctrlaction = 0;
    gain = ImproviseAdaptOvercome(speed, gain_initial, gain_max, learning_rate, A_m, B_m, setpoint, T_samp);
    tracking_err = error(speed, setpoint);
    ctrlaction = PID_ctrlr_withTustin(tracking_err, gain, 0, 0, 255, T_samp);
    return ctrlaction;
}

