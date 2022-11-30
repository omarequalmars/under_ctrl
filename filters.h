

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

    float ComplementaryFusionFilter(float readings_1, float delta_readings_2,float updated, float alpha){
      updated = readings_1*alpha + (updated + delta_readings_2)*(1-alpha);
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
    float filter[10]={0,0,0,0,0,0,0,0,0,0};
    float SMA_FIR_Filter(float x_1, int window_size){
      if(window_size>10){
        window_size = 10;
        // max window size is 10 for speed in calculation
      }
     for(int i = window_size-1;i > 0;i--){
       // delaying each received input
       filter[i]=filter[i-1];
     }
     // saving the most recent reading
     filter[0]=x_1;
     // return the moving average
    return array_sum(filter,window_size)/window_size;\
    /*
       This is a
              It takes a simple unweighted moving average over the readings with a max window of 10 for simplicity.
       */
    }
    float WMA_FIR_filter(float x_1, int window_size, float weights[]){
      if(window_size>10){
        window_size = 10;
        // max window size is 10 for speed in calculation
      }
      static float output=0;
      for(int i = window_size-1;i > 0;i--){
       // delaying each received input
       filter[i]=filter[i-1];
     }
     // saving the most recent reading
     filter[0]=x_1;
     for(int i = window_size-1;i > 0;i--){
       // delaying each received input
       output += weights[i]*filter[i];
    }
    return output;
    }
      
    
    float array_sum(float array[],int array_size){
      float sum = 0;
      for(int i = 0; i < array_size; i++){
          sum += array[i];
      }
      return sum;
    }
    
    

    
 
