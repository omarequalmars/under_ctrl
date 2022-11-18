

void MoveitMoveit(int PulseWidth, int A_channel, int B_channel, int INPUT_PIN){
    if (fabs(PulseWidth)>=255){
        PulseWidth = 255;
    }
    if(PulseWidth < 0){ // CCW
        digitalWrite(A_channel,1);
        digitalWrite(B_channel,0);
        digitalWrite(INPUT_PIN,PulseWidth);

    if(PulseWidth > 0{
        digitalWrite(A_channel,0);
        digitalWrite(B_channel,1);
        digitalWrite(INPUT_PIN,PulseWidth);
    }
    }
}

void rampspeed( int increment, int delay_time, int A_channel, int B_channel,int INPUT_PIN){
    for(int i=0;i<255;i+=increment){
        MoveitMoveit(i, A_channel, B_channel, INPUT_PIN);
	delay(delay_time);
    }
    }