    int saturated(float ctrlaction, float satlim);
	float sumerror = 0;
	float last_error = 0;
	float last_last_error = 0; 
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
		
            float ctrlaction = ctrlaction + P*(error - last_error) + I*T_samp*error + D*(error - 2*last_error + last_last_error)/T_samp;
		last_last_error = last_error;
		last_error = error;
            int sat = saturated(ctrlaction,saturation_limit);
                // Saturation
                // if(upper limit saturated) => limit the ctrlaction to upper limit
                // if(lower limit saturated) => limit the ctrlaction to lower limit
                switch (sat){
                case 1:
                    return saturation_limit;
                case -1:
                    return -1*saturation_limit;
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
              // differencing the error
		differror = error - last_error;
              // delaying the error
		last_error = error;
		float ctrlaction;
              // saturation flag
                int sat = saturated(ctrlaction,saturation_limit);
              // clamping flag: ctrlr must be saturated and error must be opposite in sign to ctrlaction
		            int clamp_cond = (sat != 0)*(error*ctrlaction < 0);
               
    switch (clamping){
      // if no clamping then business as usual
      case 0:
		    sumerror += error;
		    ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp) + I_ctrlr(sumerror, I, T_samp);
		break;
    // if clamping is on
        default:
        // check for condition
		if(clamp_cond){
      // halt the error summation and calculate alternative ctrlaction
        ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp);
		} else{// business as usual
		    sumerror += error;
		    ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp) + I_ctrlr(sumerror, I, T_samp);
		}
             }
              // Saturation
                // if(upper limit saturated) => limit the ctrlaction to upper limit
                // if(lower limit saturated) => limit the ctrlaction to lower limit
                switch (sat){
                case 1:
                    return saturation_limit;
                case -1:
                    return -1*saturation_limit;
                default:
                    return ctrlaction;
                }

                return ctrlaction;
        }

        int saturated(float ctrlaction, float satlim){ // saturation status
            /* this function returns
            1 if the ctrlaction is upper-limit-saturated
            and -1 if lower-limit-saturated */

            float lower_sat = -1*satlim; // lower saturation limit
            int flag1 = ctrlaction>=satlim;
            int flag2 = ctrlaction<=lower_sat;
                if(flag1){
                    return 1; // upper saturation
            }
                else if(flag2){
                    return -1; // upper saturation
            }
        }

      float error(float state, float setpoint){ // calculating error
            return (setpoint - state);
    }
