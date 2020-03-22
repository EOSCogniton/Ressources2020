function [c, ceq] = constraints(x, R_turn, xr, xf, w, m, Tf, Tr, h, Cz, rho, S, Cz_rep, p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q, Zo)
%CONSTRAINTS: fonction des constraintes de l'optimisation. il s'agi tout
%simplement des deux équiations du PFD, équilibre des forces et équilibre
%des moments.
%    x =  [a_y, SA_f, SA_r]

% il n'y a pas de constraintes sous forme de disequation
c = [];

% calcul des charges et des rèactions des pneus
[Y_fi, Y_fe, Y_ri, Y_re] = reactions2(x, R_turn, xr, xf, w, m, Tf, Tr, h, Cz, rho, S, Cz_rep, p_Cy1, p_Dy1,p_Ey1, p_Ey3, p_Ky1, p_Hy1, p_Vy1, q, Zo);

% constraintes sous forme d'équation
ceq(1) = Y_fi +Y_fe + Y_ri + Y_re - m*x(1); % pfd équilibre des forces
ceq(2) = xr*(Y_ri+Y_re) - xf*(Y_fi+Y_fe);   % pfd équilibre des moments
end

