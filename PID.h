    int saturated(float ctrlaction, float satlim);
    
    float P_ctrlr(float error, float P){
            float ctrlaction = error*P; // calculating ctrl action based on P
            return ctrlaction;
    }
    float I_ctrlr(float sumerror, float I, float T_samp){
            float ctrlaction = T_samp*sumerror*I; // calculating ctrl action based on I
            return ctrlaction;
        }
    float D_ctrlr(float differror, float D, float T_samp){ // calculating ctrl action based on D
            float ctrlaction = differror*D/T_samp;
            return ctrlaction;
        }
    float PID_ctrlr_withoverflow(float error, float P, float I, float D, float saturation_limit, float T_samp){
		static float last_error = 0;
        static float last_last_error = 0; 
        static float ctrlaction = 0;
            ctrlaction = ctrlaction + P*(error - last_error) + I*T_samp*error + D*(error - 2*last_error + last_last_error)/T_samp;
		last_last_error = last_error;
		last_error = error;
            static int sat;
            sat = saturated(ctrlaction,saturation_limit);
                // Saturation
                // if(upper limit saturated) => limit the ctrlaction to upper limit
                // if(lower limit saturated) => limit the ctrlaction to lower limit
                switch (sat){
                case 1:
                    return saturation_limit;
                case -1:
                    return -saturation_limit;
                default:
                    return ctrlaction;
                }
                return ctrlaction;
    }
    
    float PID_ctrlr_withoutoverflow(float error, float P, float I, float D, float saturation_limit, float T_samp, int clamping){
            /* error, sumerror, differror are the error, cumulative error, and error rate respectively,
            P, I, & D are the coefficients
            saturation_limit is the maximum ctrl action actuator can take
            T_samp is the sampling time
            clamping is a flag, if == 0 then it is off, otherwise it is on */
            // static local variables 
            static float integrator_sum = 0;// integrator sum
            static float diff_error = 0;// error difference
            static float sumerror = 0;// cumulative error sum
	        static float last_error = 0;// delayed error
            static int sat = 0;// saturation flag
            static int clamp_cond = 0;// clamping into operation

            // differencing the error
		differror = error - last_error;
              // delaying the error
		last_error = error;
        //
		static float ctrlaction;
              // saturation flag
        sat = saturated(ctrlaction,saturation_limit);
    switch (clamping){
      // if no clamping then business as usual
        case 0:
		    sumerror += error;
		    ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp) + I_ctrlr(sumerror, I, T_samp);
		break;
        // if clamping is activated
        default:
        // check if it's clamping time
        clamp_cond = (((sat == 1) && error > 0) || ((sat == -1) && error < 0));
        break;
    }
		switch(clamp_cond){
      // halt the error summation and calculate ctrlaction
      case 1:
        ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp) + integrator_sum;
        break;
		// business as usual
        default:
		    sumerror += error;
            integrator_sum = I_ctrlr(sumerror, I, T_samp);
		    ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp) + integrator_sum;
		}
              // Saturation
                // if(upper limit saturated) => limit the ctrlaction to upper limit
                // if(lower limit saturated) => limit the ctrlaction to lower limit
                switch (sat){
                case 1:
                    return saturation_limit;
                case -1:
                    return -saturation_limit;
                default:
                    return ctrlaction;
                }

        }

        int saturated(float ctrlaction, float satlim){ // saturation status
            /* this function returns
            1 if the ctrlaction is upper-limit-saturated
            and -1 if lower-limit-saturated */
            static float lower_sat;
            lower_sat = -satlim; // lower saturation limit
            static int flag1;
            flag1 = ctrlaction>=satlim;
            static int flag2;
            flag2 = ctrlaction<=lower_sat;
                if(flag1){
                    return 1; // upper saturation
            }
                else if(flag2){
                    return -1; // upper saturation
            }else{
                return 0;
            }
        }

      float error(float state, float setpoint){ // calculating error
            return (setpoint - state);
    }
