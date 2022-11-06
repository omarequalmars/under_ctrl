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
    float PID_ctrlr_withoverflow(float error, float last_error, float last_last_error, float P, float I, float D, float saturation_limit, float T_samp){

            float ctrlaction = ctrlaction + P*(error - last_error) + I*T_samp*error + D*(error - 2*last_error + last_last_error)/T_samp;

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
    float PID_ctrlr_withoutoverflow(float error, float sumerror, float differror, float P, float I, float D, float saturation_limit, float T_samp, int clamping){
            /* error, sumerror, differror are the error, cumulative error, and error rate respectively,
            P, I, & D are the coefficients
            saturation_limit is the maximum ctrl action actuator can take
            T_samp is the sampling time
            clamping is a flag, if == 0 then it is off, otherwise it is on */

                // CTRL action is calculated as the superposition of three controllers
            float ctrlaction = P_ctrlr(error, P) + I_ctrlr(sumerror, I, T_samp) + D_ctrlr(differror, D, T_samp);
                int sat = saturated(ctrlaction,saturation_limit);
                // Clamping
                // if (saturated) => pause the integration (let sumerror be 0)
                switch (clamping){
                case 0:
                    break;
                default:
                    ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp);
                    break;
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
