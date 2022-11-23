

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

    float ComplementaryFusionFilter(float readings_1, float readings_2_dot,float updated, float T_sampling, float alpha){
      updated = readings_1*alpha + (updated + readings_2_dot*T_sampling)*(1-alpha);
      return updated;
      /* 
       This is a sensor fusion filter based on the complementary filter concept
       It updates the state (readings_1) from sensor 1
       and it's derivative from sensor 2 and recursively updates the fused reading.
       It is recommended to trace the function for the best understanding.
       =======================================================
       alpha is the weight coefficient for sensor 1 (proportional to how much it is 'trusted')
       0 <= alpha <= 1
       in the extreme cases, alpha = 1 means the filter will converge to sensor 1
       and alpha = 0 means it will converge to sensor 2
       readings_1 is the reading from sensor 1
       readings_2_dot is the reading from sensor 2
       updated is the filter output
       T_sampling is self descriptive
       */
    }

    float MA_Filter(float x_1, float x_2, float x_3, int window){
      if(window==3) return (x_1+x_2+x_3)/3;
      else if(window==2) return (x_1+x_2)/2;
      /*
       This is a FIR Filter
       It takes a simple unweighted moving average over the readings with a max window of 3 for simplicity.
       In order for the filter to work, readings x_1, 2, and 3 must be accordingly delayed in the main code (I'm sorry you have to do that)
       */
    }
    
    

    
 
