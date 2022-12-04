int saturated(float ctrlaction, float satlim);

float P_ctrlr(float error, float P) {
  float ctrlaction = error * P; // calculating ctrl action based on P
  return ctrlaction;
}
float I_ctrlr(float sumerror, float I, float T_samp) {
  float ctrlaction = T_samp * sumerror * I; // calculating ctrl action based on I
  return ctrlaction;
}
float D_ctrlr(float differror, float D, float T_samp) { // calculating ctrl action based on D
  float ctrlaction = differror * D / T_samp;
  return ctrlaction;
}
float PID_ctrlr_withoverflow(float error, float P, float I, float D, float saturation_limit, float T_samp) {
  static float last_error = 0;
  static float last_last_error = 0;
  static float ctrlaction = 0;
  ctrlaction = ctrlaction + P * (error - last_error) + I * T_samp * error + D * (error - 2 * last_error + last_last_error) / T_samp;
  last_last_error = last_error;
  last_error = error;
  static int sat;
  sat = saturated(ctrlaction, saturation_limit);
  // Saturation
  // if(upper limit saturated) => limit the ctrlaction to upper limit
  // if(lower limit saturated) => limit the ctrlaction to lower limit
  switch (sat) {
    case 1:
      return saturation_limit;
    case -1:
      return -saturation_limit;
    default:
      return ctrlaction;
  }
  return ctrlaction;
}

float PID_ctrlr_withoutoverflow(float error, float P, float I, float D, float saturation_limit, float T_samp, int clamping)
{
  static float integrator_sum = 0;// integrator sum
  static float differror = 0;// error difference
  static float sumerror = 0;// cumulative error sum
  static float last_error = 0;// delayed error
  static short sat = 0;// saturation flag
  static short clamp_cond = 0;// clamping into operation
  static float ctrlaction = 0;
  // differencing the error
  differror = error - last_error;
  // delaying the error
  last_error = error;
  // saturation flag
  sat = saturated(ctrlaction, saturation_limit);// check saturated or not
  switch (clamping) {
    case 0:// if clamping is deactivated
      sumerror += error;
      ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp) + I_ctrlr(sumerror, I, T_samp);
      break;
    // if clamping is activated
    default:
      // check if it's clamping time
      
      clamp_cond = ((sat == 1) && (error > 0)) || ((sat == -1) && (error < 0));
      if (clamp_cond) {// stop integ. in clamping time
        ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp) + integrator_sum;
      }
      else {
        sumerror += error;
        integrator_sum = I_ctrlr(sumerror, I, T_samp);
        ctrlaction = P_ctrlr(error, P) + D_ctrlr(differror, D, T_samp) + integrator_sum;
      }
  }
  // Saturation
  // if(upper limit saturated) => limit the ctrlaction to upper limit
  // if(lower limit saturated) => limit the ctrlaction to lower limit
ctrlaction = sat==1 ? saturation_limit : sat==-1 ? -saturation_limit : ctrlaction;
return ctrlaction;
}

int saturated(float ctrlaction, float satlim) { // saturation status
  /* this function returns
    1 if the ctrlaction is upper-limit-saturated
    and -1 if lower-limit-saturated */
  static int flag=0;
//  if(ctrlaction>=satlim)
//    flag=1;
//
//  else if(ctrlaction<=-satlim)
//    flag=-1;
//  else
//  flag=0;
  flag= ctrlaction>=satlim? 1 : ctrlaction<=-satlim? -1 : 0;
 return flag;
}

float error(float state, float setpoint) { // calculating error
  return (setpoint - state);
}
