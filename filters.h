

    float ComplementaryFilter(float readings, float filtered, float alpha){ // Infinite Impulse Response Filter
        filtered = readings*alpha + filtered*(1-alpha);
        return filtered;
        /*

        This filter is a super basic IIR filter
        It takes an exponentially weighed moving average over the readings
        to the effect of smoothing out any ripples.
        ================================
        alpha is the MA Weight:
        alpha = 1 means the filter output will essentially be the same as the input.
        As alpha is decreased, the effective moving average window is increased
        to the effect of higher order smoothing, however note that this comes with a larger lag effect
        where the output is phase-shifted

        0 <= alpha <= 1

        */
    }

    /* Kalman Filter / Linear Quadratic Estimator

    work in progress */
    float vec_mat_2by2(float X[], float Y[][2]){
        // vector x matrix
        int i,j;
        float res=0;
            for(i=0;i<2;i++){
            for(j=0;j<2;j++){
            res += X[i]*Y[j][i];
            }
            }
        return res;
    }
    float transpose(float a[][2]){
        // matrix transpose
        float res[2][2];
            for (int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++) {
                res[j][i] = a[i][j];
            }
        }
        return res;
    }

    float sum_mat(float a[][2], float b[][2]){
        // matrix sum
    float sum[][2] = {{0,0},{0,0}};
    int i,j;

        for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            sum[i][j] = a[i][j] + b[i][j];
        }
    }
    return sum;
    }

    /*float KalmanFilter(float Current_readings, float Omega_readings, float Q, float R[][2]){
    // Declaration of model params
       float K_b =
       float K_t =
       float J =
       float B =
       float Res =
       float Ind =
    // Declaration of State transition Matrix
       float A[2][2] = {{-Res/Ind, -K_b/Ind},{K_t/J, -B/J}};
       float B[2][2] = {{1/Ind, 1/Ind},{0,0}};
       float C[2][2] = {{1,0},{0,1}};
    // Declaration of state vector
       float X[2] = {Current_readings,Omega_readings};



    }*/
