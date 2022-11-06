

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
    float KalmanFilter(float readings, float P[][2], float Q_process, float R_process, float T_sampling){
        float  y, S, KF_out;
        float K_0, K_1, K_2;

        P[0][0] += ;
        P[0][1] += ;
        P[0][2] += ;
        P[1][0] += ;
        P[1][1] += ;
        P[1][2] += ;

        y = ;
        S = P[0][0] + R_process;
        K_0 = P[0][0]/S;
        K_1 = P[1][1]/S;
        K_2 = P[2][2]/S;


        KF_out += K_0*y



    }
