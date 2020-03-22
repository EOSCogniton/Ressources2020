%% Test

%Test de la fonction fe_to_ftHz
x = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26];
log_fe = [1,5,12,13,13,14,13,12,9,2,-10,-12,-13,-10,-5,0,1,2,2,4,5,6,6,5,3,0,0];
plot(x,log_fe,"g")
hold on
plot(fe_to_ftHz(x,10,100),fe_to_ftHz(log_fe,10,100),"k");
hold on
plot(fe_to_ftHz(x,10,35),fe_to_ftHz(log_fe,10,35),"b");
hold on
plot(fe_to_ftHz(x,10,3),fe_to_ftHz(log_fe,10,3),"r");
hold on
plot(fe_to_ftHz(x,10,1),fe_to_ftHz(log_fe,10,1),"m");
legend("10 Hz","100 Hz","35 Hz","3 Hz","1 Hz")

interp2(MAP_rank, rpm_rank, injection_fuel_map,30,5000)
