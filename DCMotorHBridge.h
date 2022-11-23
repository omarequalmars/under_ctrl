

void MoveitMoveit(int PulseWidth, int A_channel, int B_channel, int INPUT_PIN){
  int pulse_mag = fabs(PulseWidth);
  // Saturate output at 255
    if (pulse_mag>=255){
        pulse_mag = 255;
    }
    
    // decide directions based on PWM sign
    if(PulseWidth < 0){ // CCW
        digitalWrite(A_channel,HIGH);
        digitalWrite(B_channel,LOW);
        digitalWrite(INPUT_PIN,pulse_mag);
    }
    else if(PulseWidth > 0){ // CW
        digitalWrite(A_channel,LOW);
        digitalWrite(B_channel,HIGH);
        digitalWrite(INPUT_PIN,pulse_mag);
    }
    
}

float currentscale(int bits){
    float V_0 = 2.5;
    float voltage = bits*5/1023.0;
    float current = ((voltage-V_0)/0.185);
    return current;
}

float NeedForSpeed(int pulses, float Pulses_per_rev, float T_sampling){
  float Speed;
  Speed = 2.0*pulses/(Pulses_per_rev*T_sampling);
  return Speed;
}
