#include "filters.h"
#include <stdio.h>


void main(){

    int i = 0; // just a counter
    float array[100]; // array of readings

    float filtered=0;

    float T_sampling = 0.05;

    float P[3][3] = {{0,0,0},{0,0,0},{0,0,0};
    float Q_process = 0.1;



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


}
