

    float ComplimentaryFilter(float readings, float filtered, float alpha){ // Infinite Impulse Response Filter
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

    float ComplimentaryFusionFilter(float readings_1, float readings_2_dot,float updated, float T_sampling, float alpha){
      updated = readings_1*alpha + (updated + readings_2_dot*T_sampling)*(1-alpha);
      return updated;
    }

    
 
