

void MoveitMoveit(int PulseWidth, int A_channel, int B_channel, int INPUT_PIN){

  // Saturate output at 255
    if (PulseWidth>=255){
        PulseWidth = 255;
    }else if(PulseWidth<=-255){
      PulseWidth = -255;
    }
    // decide directions based on PWM sign
    if(PulseWidth > 0){ 
      // if command is positive, go CCW/CW
        digitalWrite(A_channel,HIGH);
        digitalWrite(B_channel,LOW);
        digitalWrite(INPUT_PIN,pulse_mag);
    }
    else if(PulseWidth < 0){ 
      // if it switches signs, go the other way
        digitalWrite(A_channel,LOW);
        digitalWrite(B_channel,HIGH);
        digitalWrite(INPUT_PIN,pulse_mag);
    }
    
}

float currentscale(){// ACS712 current sensor ==> ADC scaling
    static int bits;
    bits = analogRead(A0);
    bits -= 512;
    
    float voltage = bits*5/512.0;// map the bits to volts
    float current = (voltage/0.185);// take the difference from the ZCV and divide by the sensitivity
    return current;
}


