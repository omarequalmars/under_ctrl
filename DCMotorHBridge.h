

void MoveitMoveit(int PulseWidth, int direction, int A_channel, int B_channel, int INPUT_PIN){
    if (fabs(PulseWidth)<=255){
        PulseWidth = 255;
    }
    if(direction==1){ // CCW
        digitalWrite(A_channel,1);
        digitalWrite(B_channel,0);
        digitalWrite(INPUT_PIN,PulseWidth);

    if(direction==0){
        digitalWrite(A_channel,0);
        digitalWrite(B_channel,1);
        digitalWrite(INPUT_PIN,PulseWidth);
    }
    }
}

void rampspeed(int INPUT_PIN){
    for(int i=0;i<255;i+=50){
        digitalWrite(INPUT_PIN,i);
    }
    }