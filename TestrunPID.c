
#include "PID.h"
#include "filters.h"
#include <stdio.h>

void main(){
    int i = 0; // just a counter
    float array[100]; // array of readings

    float filtered=0;

    float err = 0;
    float ctrlaction = 0;

    float setpoint = 6;
    float satlim = 60;
    float P = 15, I = 1, D = 0;
    float sumerror=0, differror;
    float last_err = 0;
    int sat = 0;
    float T_sampling = 0.05;

    float alpha = 1; // complementary filter weight

    // reading generation

    for(i=0;i<100;i++){
        if(i<30){
        array[i]=i;
        }
        else if(i<=60){
        array[i]=30-i;
        }
        else if(i>60){
           array[i]= (float) i/6;
        }
    }
    printf("timestamp :: error : sumerror : error rate : CTRLaction\n");
    for(i=0;i<100;i++){ // action loop (void loop in Arduino/ESP)
         // filtering readings to remove noise
        filtered=ComplementaryFilter(array[i],filtered,alpha);
        // saving last error reading for differentiation
        last_err = err;
         // calculating error
        err = error(filtered,setpoint);
         // cumulative sum of errors
        sumerror += err;
         // error rate
        differror = err - last_err;
         // ctrlr below
        ctrlaction = PID_ctrlr_withoutoverflow(err,sumerror,differror,P,I,D,satlim,T_sampling,1);

        sat = saturated(ctrlaction,satlim); // saturation flag
        printf("%.2f ms :: %.2f : %.2f : %.2f : %.3f \n",i*T_sampling*1000,err,sumerror,differror, ctrlaction);
    }






}
