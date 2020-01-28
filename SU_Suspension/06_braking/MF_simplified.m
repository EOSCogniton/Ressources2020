%% tire TIR parameters
p_cx1 = 1.786;
p_dx1 = 2.688;
p_dx2 = -2.720E-001;
p_kx1 = +8.125E+001;
p_kx2 = -2.025E+001;
p_kx3 = +5.000E-001;

%% pure longitudinal MF simplified
F_z = 1800; %N

C_x = p_cx1;
df_z = 0; %(Fz - F_z0)/F_z0;
u_x = p_dx1 +p_dx2*df_z;
D_x = u_x * F_z;

eps= 0.001;
K_x = F_z*(p_kx1+p_kx2*df_z)*exp(p_kx3*df_z);

B_x = K_x/(C_x*D_x+eps);

%% plot line

SR =  linspace(-0.2, 0.2);
F_x = D_x * sin(C_x * atan(B_x * SR));

figure()
plot(SR,F_x)