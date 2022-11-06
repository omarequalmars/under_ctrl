
titlesize = 15;
labelsize = 10;
legendsize = 13;
% declaring system parametes
K = 0.1;
B = 0.01;
L = 0.01;
J = 0.001;
Res = 1;
P = 0.01;
% declaring state space matrices
A = ([-Res/L , -K/L;K/J, -B/J]);
B = ([1/L 1/L;0 0]);
C = [1 0; 0 P];
D = [0 0;0 0];
% constructing state space model
sys = ss(A,B,C,D,'Inputname', {'Armature Voltage', 'Noise'}, 'Outputname', {'Armature Current','Linear Speed'});
% constructing simulation
% time
t = 0:0.01:10;
% PWM and voltage
PWM = 255;
V_in = PWM*(12/255)*ones(size(t));
% input noise
noise_input = rand(size(t));
% combined input
total_in = [V_in;noise_input];
% simulating system
y = lsim(sys,total_in,t);
% fishing out the results
current = y(:,1);
omega = y(:,2);
% covariance matrices
Q = 0.1;
R = [1 0;
     0 0.1];
 % making a Kalman Filter
 [kalmf,L,P] = kalman(sys,Q,R);
 new_outs = kalmf(:,1);
 % simulating kalman filter
 y_new = lsim(new_outs,V_in,t);
 % fishing out the outputs
 Armature_Current_est = y_new(:,1);
 Omega_est = y_new(:,2);

 %plotting for comparison
subplot(2,1,1)
plot(t, omega)
hold on
plot(t, Omega_est)
title(['Speed response at ' num2str(PWM/255) ' Duty cycle'],'Fontsize',titlesize,'FontWeight', 'Bold');
ylabel('\omega in m/s','Fontsize',labelsize,'FontWeight', 'Bold');
xlabel('time/ s','Fontsize',labelsize,'FontWeight', 'Bold');
legend('Raw Speed','Filtered Speed')
grid on

subplot(2,1,2)
plot(t, current)
hold on 
plot(t, Armature_Current_est)
title(['Current response at ' num2str(PWM/255) ' Volts'],'Fontsize',titlesize,'FontWeight', 'Bold');
ylabel('I_a in Amps','Fontsize',labelsize,'FontWeight', 'Bold');
xlabel('time/ s','Fontsize',labelsize,'FontWeight', 'Bold');
legend('Raw Current', 'Filtered Current')
grid on
