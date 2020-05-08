

rmot = rmot_s/100;
cmot = cmot_s;
plot(rmot,cmot,'--',"DisplayName",'without power limit')
title('Motor curb for motor EMRAX 228 CC')

Pmax = 80000; % Maximum power from the accumulator (W)
econ = 0.97; % electrical efficiency of the controller
emot = 0.9; % electrical efficiency of the motor

Cmax = Pmax*econ*emot.*ones(length(rmot),1)./(rmot*2*pi/60);

id_max_case = (Cmax<cmot);
cmot = id_max_case.*Cmax + (1-id_max_case).*cmot;

hold on
plot(rmot,cmot,"DisplayName",'with power limit')
xlabel('Motor Speed (rpm)')
ylabel('Motor Torque (N.m)')
legend
