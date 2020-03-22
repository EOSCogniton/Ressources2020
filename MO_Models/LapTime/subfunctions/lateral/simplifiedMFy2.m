function [Y] = simplifiedMFy2(Z,SA, p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q, Zo)
%UNTITLED3 schramm Hiller Baldini chapter . section
%   Z (N) charge normale
%   SA (rad) slip angle 
%   q (real) scaling factor bench to road (Calspan TTC 0.6)
%   Zo (N) charge nominale

eps = 1e-3; % avoid singularity

C_y = p_Cy1; % (>=0)

mu_y = p_Dy1;
D_y = mu_y*Z;

E_y = p_Ey1*(1-p_Ey3); % (<=1)

K_y = p_Ky1*Zo; %*sin(p_Ky4*atan(Z/Zo/p_Ky2));

B_y = K_y./(C_y.*D_y +eps);

S_Hy = p_Hy1;

S_Vy = Z*p_Vy1;

SA = SA + S_Hy;
Y= q .*D_y.*sin(C_y.*atan(B_y.*SA'-E_y.*(B_y.*SA'-atan(B_y.*SA')))) + S_Vy;

end

