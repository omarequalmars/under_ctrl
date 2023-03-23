

float modelrefO1(float time_constant, float setpoint, float T_samp){
    static float state = 0;
    static float B_m = 1/time_constant
    static float A_m = 1/time_constant;
    static float last_setpoint = 0;
    static float a = B_m*T_samp/(2+A_m*T_samp);
    static float b = (A_m*T_samp - 2)/(A_m*T_samp + 2);
    state = a*(setpoint + last_setpoint) - b*state;
    last_setpoint = setpoint;
    return state;
}

float ImproviseAdaptOvercome(float state_real, float gain_initial, float gain_max, float learning_rate, float time_constant, float setpoint, float T_samp){
    static float gain = gain_initial;
    static float tracking_error = 0;
    static float model_error = 0;
    tracking_error = setpoint - state_real;
    model_error = state_real - modelrefO1(time_constant, setpoint, T_samp);
    gain -= T_samp*learning_rate*model_error*tracking_error;
    gain = (gain <= 0) ? 0 : gain;
    gain = (gain >= gain_max) ? gain_max : gain ;
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

float Trap(float variable, float T_samp){
    static float X = 0;
    static float X_last = 0;
    static float integral = 0;
    X = variable;
    integral += (X + X_last)*T_samp/2;
    X_last = X;
    return integral;
}

float UnderControl(float speed, float setpoint, float gain_initial, float gain_max, float learning_rate, float time_constant, float T_samp){
    static float gain = 0;
    static float tracking_err = 0;
    static float ctrlaction = 0;
    gain = ImproviseAdaptOvercome(speed, gain_initial, gain_max, learning_rate, time_constant, setpoint, T_samp);
    tracking_err = error(speed, setpoint);
    ctrlaction = PID_ctrlr_withZOH(tracking_err, gain, 0, 0, 255, T_samp, 0);
    return ctrlaction;
}

