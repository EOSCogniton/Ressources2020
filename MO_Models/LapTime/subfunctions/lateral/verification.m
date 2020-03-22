%% 0- load & settings
% this verification script uses the values in the base workspace
param_file = "C:\Users\mik75\Documents\FSAEinvictus\Ressources2020\MO_Models\LapTime\test_aeroTire.mat";
load(param_file,'xr','W','xf','m_t','Tf','Tr','h','Cz','rho','S','Cz_rep', 'p_Cy1', 'p_Dy1','p_Ey1', 'p_Ey3', 'p_Ky1', 'p_Hy1', 'p_Vy1', 'q')


%% 1- tyre model : effet de la charge nominale Zo sur le modèle de pneu

% slip angle (SA) vector from 0 to 20 deg
a = [0:.2:20]/180*pi; %rad

% vecteur des charges
z = [500:3000]; %N

% vecteur des charges nominales
zo = [500 600, 700];

% tire model function
tireModel = @(Z,SA,Zo) simplifiedMFy2(Z,SA, p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q, Zo);

subplot(1,2,1); hold on; legend()
for zi = zo
    % allure de tau = y/z pour tout SA optimales pour diffèrentes charges nominales
    y_best = max( tireModel(z, a, zi), [],1); % find best y for each load
    plot(z, y_best./z, 'DisplayName', ['Zo = ' num2str(zi) ' N'])
end

subplot(1,2,2); hold on; legend()
for zi=zo
    % allure z, y classique pour differentes charges nominales
    y_500 = tireModel(500,a, zi);
    y_700 = tireModel(700,a, zi);
    plot(a, y_500, 'DisplayName', ['Fz= 500 N @ Zo= ' num2str(zi) ' N'])
    plot(a, y_700, 'DisplayName', ['Fz= 700 N @ Zo = ' num2str(zi) ' N'])
end


%% 2- verify optim solution x

% calculate the charges
a_y = x(1);
[Z_fi, Z_fe, Z_ri, Z_re] = charges(a_y, R_turn, xr, xf, W, m_t, Tf, Tr, h, Cz, rho, S, Cz_rep);

% slip angle (SA) vector from 0 to 20 deg
a = [0:.2:50]/180*pi; %rad

% complete tyre curves for all SA
Y_all = simplifiedMFy2([Z_fi, Z_fe, Z_ri, Z_re], a, p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q, Zo);
Y_fia = Y_all(:,1);
Y_fea = Y_all(:,2);
Y_ria = Y_all(:,3);
Y_rea = Y_all(:,4);

% point solution of the found optim
SA_f = x(2); SA_r = x(3);
Y_opt = simplifiedMFy2([Z_fi, Z_fe, Z_ri, Z_re], [SA_f SA_f SA_r SA_r], p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q, Zo);
Y_fi = Y_opt(1,1);
Y_fe = Y_opt(2,2);
Y_ri = Y_opt(3,3);
Y_re = Y_opt(4,4);

% plot model and optim solution for each tire
figure(); hold on; legend()
title(['a_y = ' num2str(a_y) 'm/s^2; R_{turn} = ' num2str(R_turn) 'm'])
xlabel('SA (deg)')
a = a/pi*180;
SA_f = SA_f/pi*180; SA_r = SA_r/pi*180;
ylabel('Fy (N)')

plot(a, Y_fia, 'DisplayName', ['fi, Fz=' num2str(Z_fi) 'N'])
plot(a, Y_fea, 'DisplayName', ['fe, Fz=' num2str(Z_fe) 'N'])
plot(a, Y_ria, 'DisplayName', ['ri, Fz=' num2str(Z_ri) 'N'])
plot(a, Y_rea, 'DisplayName', ['re, Fz=' num2str(Z_re) 'N'])

scatter([SA_f SA_f SA_r SA_r],[Y_fi, Y_fe, Y_ri, Y_re], 'DisplayName', 'optimal')



