function [c, ceq] = constraints(x, R_turn, xr, xf, w, m, Tf, Tr, h, Cz, rho, S, Cz_rep, p_Cy1, p_Dy1, p_Ky1, q)
%UNTITLED9 Summary of this function goes here
%   Detailed explanation goes here
c = [];

% x =  [a_y, SA_f, SA_r]

% calcul des charges
[Y_fi, Y_fe, Y_ri, Y_re] = reactions2(x, R_turn, xr, xf, w, m, Tf, Tr, h, Cz, rho, S, Cz_rep, p_Cy1, p_Dy1, p_Ky1, q);

ceq(1) = Y_fi +Y_fe + Y_ri + Y_re - m*x(1);
ceq(2) = xr*(Y_ri+Y_re) - xf*(Y_fi+Y_fe);
end

