float array_sum(float array[],int array_size);
float dotproduct(float array1[], float array2[],int array_size);

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
       */
    }

    float SMA_FIR_Filter(float x_0, int window_size){
       static float X[10]={0,0,0,0,0,0,0,0,0,0};
      if(window_size>10){
        window_size = 10;
        // max window size is 10 for speed in calculation
      }
     for(int i = window_size-1;i > 0;i--){
       // delaying each received input
       X[i]=X[i-1];
     }
     // saving the most recent reading
     X[0]=x_0;
     // return the moving average
    return array_sum(X,window_size)/window_size;
    /*
       This is a
              It takes a simple unweighted moving average over the readings with a max window of 10 for simplicity.
       */
    }

    float FIR_filter(float x_0, int window_size, float weights[]){
        // defining input array
        static float output;
        static int i;
        output = 0;
        static float X[5]={0,0,0,0,0};
      if(window_size>5){
        window_size = 5;
        // max window size is 10 for speed in calculation
      }
           // saving the most recent reading
      X[0]=x_0;

      output = dotproduct(X,weights,window_size);
      for(i=0;i<window_size;i++){
        X[i+1] = X[i];
      }
      return output;
    }

    float IIR_filter(float x_0,int window_size, float weights_input[], float weights_feedback[]){
        // defining input and output arrays
        static float output;
    static float X[5] = {0,0,0,0,0};
    static float Y[4] = {0,0,0,0};
    if(window_size>5){
        window_size = 5;
         // max window size is 5 for speed in calculation
    }
    X[0]=x_0;
    output = dotproduct(X,wei  ghts_input,window_size) - dotproduct(Y,weights_feedback,window_size-1);
    for(i=0;i<window_size;i++){
      if(i<(window_size-1)){
        X[i+1]=X[i];
        Y[i+1]=Y[i];
      }
      else if(i<window_size){
        X[i+1]=X[i];
      }

      Y[0]=output;
    }

    float array_sum(float array[],int array_size){
      float sum = 0;
      for(int i = 0; i < array_size; i++){
          sum += array[i];
      }
      return sum;
    }

    float dotproduct(float array1[], float array2[],int array_size){
    static float sum;
    sum = 0;
    static int i = 0;
    for(i=0;i<array_size;i++){
        sum += array1[i]*array2[i];
    }
    return sum;
    }
