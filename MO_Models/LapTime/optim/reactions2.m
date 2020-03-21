function [Y_fi, Y_fe, Y_ri, Y_re] = reactions2 (x, R_turn, xr, xf, w, m, Tf, Tr, h, Cz, rho, S, Cz_rep, p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q)
%REACTIONS-2: utilise la fonction CHARGES et calcule la réacion laterale
%des pneus en utilisant le modèle de pneu
% x =  [a_y, SA_f, SA_r]

% calcul des charges
[Z_fi, Z_fe, Z_ri, Z_re] = charges(x(1), R_turn,  xr, xf, w, m, Tf, Tr, h, Cz, rho, S, Cz_rep);

% calcul des réactions latérales des pneus 
Y_fi = simplifiedMFy2(Z_fi, x(2), p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q);
Y_fe = simplifiedMFy2(Z_fe, x(2), p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q);
Y_ri = simplifiedMFy2(Z_ri, x(3), p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q);
Y_re = simplifiedMFy2(Z_re, x(3), p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q);
end
