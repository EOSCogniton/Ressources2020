function [Y_fi, Y_fe, Y_ri, Y_re] = reactions2 (x, R_turn)
% x =  [a_y, SA_f, SA_r]
% calcul des réactions
[Z_fi, Z_fe, Z_ri, Z_re] = charges(x(1), R_turn);
Y_fi = simplifiedMFy(Z_fi, x(2));
Y_fe = simplifiedMFy(Z_fe, x(2));
Y_ri = simplifiedMFy(Z_ri, x(3));
Y_re = simplifiedMFy(Z_re, x(3));
end
