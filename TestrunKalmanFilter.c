#include "filters.h"
#include <stdio.h>

float print_mat(float Y[][2]);

void main(){


    float X[2] = {2,3};
    float Y[2][2] = {{2,3},{5,7}};
    float Z[2][2] = {{12,5},{4,9}};
    float W[2][2] = {{0,0},{0,0}};


}

float print_mat(float Y[][2]){
 for(int i=0;i<2;i++){
            printf("%f \n");
        for(int j=0;j<2;j++){
            printf("%f,", Y[i][j]);
        }
    }
}
