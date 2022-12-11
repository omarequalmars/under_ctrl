
#include "Adafruit_VL53L0X.h"
#include "Timer2_OVF.h"
#include "filters.h"
#include "DCMotorHBridge.h"
#include "PID.h"
#define channel_A_Motor_1 2
#define channel_B_Motor_1 4
#define enable_A 5
#define in1 6
#define in2 7
#define ir1 3
#define ir2 8
#define T_Samp 0.005
#define F_samp 1/T_Samp
#define Pulses_per_cm 100.7
#define alpha_fusion 0.05
//-----------------------
#define clamp_on 1
#define clamp_off 0
#define p 1
#define i 0
#define d 0
#define setpoint 50
#define saturation 255

unsigned int  pulses = 0;
unsigned int  pulses_samp = 0;
unsigned int  prev_pulses = 0;
int  delta_pulses = 0;
float fused_dist = 0;
void Pulses();
float Dist_Measure();
const int ledPin = 13;
volatile byte state = LOW;
float Dist_samp = 0;
float Dist_read = 0;
float err = 0;
float ctrl_action = 0;
float filter1 = 0;
float current = 0;
float current_sampled = 0;
int ir_1;
int ir_2;

void imcominghome(int IR_sig, int in1, int in2, int enable_A);
VL53L0X_RangingMeasurementData_t measure;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
void setup() {
  Serial.begin(115200);
  pinMode(channel_A_Motor_1, INPUT);
  pinMode(channel_B_Motor_1, INPUT);
  pinMode(ir1, INPUT);
  pinMode(enable_A, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  //attachInterrupt(digitalPinToInterrupt(channel_A_Motor_1), pls_stop, FALLING);
  attachInterrupt(digitalPinToInterrupt(channel_A_Motor_1), Pulses, RISING);
  while (! Serial) {
    delay(1);
  }
  if (!lox.begin()) {
    while (1);
  }
  cli();//stop interrupts
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2 = 177; //255-((16*10^6)/(PreSc*F_samp))
  TCCR2A |= 0;// turn on Normal mode
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Set CS22,CS21,CS20 bits for 1024 prescaler
  TIMSK2 |= (1 << TOIE2);  // enable timer Overflow interrupt
  sei();//allow interrupts
}


void loop() {
  Dist_read = Dist_Measure();
  current = currentscale();
  MoveitMoveit(-255, in1, in2, enable_A);
}
float Dist_Measure() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data

    //Serial.print("Distance (cm): "); Serial.println(measure.RangeMilliMeter/10);

  } else {
    measure.RangeMilliMeter = Dist_samp;
  }
  return measure.RangeMilliMeter / 10;
}
void Pulses() {
  static unsigned int ENCB;
  ENCB = digitalRead(channel_B_Motor_1);
  if (ENCB > 0) {
    pulses++;
  }
  else {
    pulses--;
  }
}
ISR(TIMER2_OVF_vect) {
  Dist_samp = Dist_read;
  pulses_samp = pulses;
  current_sampled = current;
  delta_pulses = pulses_samp - prev_pulses;
  fused_dist = ComplementaryFusionFilter(Dist_samp, delta_pulses / Pulses_per_cm, fused_dist, alpha_fusion);

  Serial.print(fused_dist);
  Serial.print(" ,");
  Serial.println(current_sampled);
  prev_pulses = pulses_samp;
  TCNT2 = 177;
}
void imcominghome(int IR_sig, int A_channel, int B_channel, int INPUT_PIN) {
  while (IR_sig) {
    MoveitMoveit(180, A_channel, B_channel, INPUT_PIN);

  }
}
