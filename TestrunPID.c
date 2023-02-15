
#include "filters.h"
#include <stdio.h>
#include "fdacoefs.h"

void main(){
    float array[2000];
    float filteroutput;
    array[0]=1;
    for(int i =0;i<2000;i++){
        array[i+1]=0;
        filteroutput = FIR_filter(array[i],BL,B);
        printf("%f : %f : %f\n", i*0.005, array[i], filteroutput);
    }


}
