function [Z_fi, Z_fe, Z_ri, Z_re] = charges(a_y, R_turn, xr, xf, w, m, Tf, Tr, h, Cz, rho, S, Cz_rep)
%CHARGES calcule les charges sur chaque pneu de la voiture
%   xr : distance CG train arrière
%   xf : distance CG train avant
%   w : empattement (wheelbase)
%   m : masse totale
%   Cz : costante aérodynamique
%   rho : masse volumique air
%   S : surface équivalente véhicule (plan normale x)
%   a_y ; accéleration latérale
%   R_turn : rayon nominale du virage
%   Cz_rep : répartition aéro avant
%   Tf : voie (track) avant (front)
%   Tr : voie arrière

g = 9.81; %m/s

% charges statiques
Z_0f = (xr/w)*m*g/2;
Z_0r = (xf/w)*m*g/2;

% charge aéro
Z_aero_f = 1/4*Cz*rho*S* abs(a_y)*abs(R_turn) *(1-Cz_rep);
Z_aero_r = 1/4*Cz*rho*S* abs(a_y)*abs(R_turn) *Cz_rep;

% transfert de charge
dZ_f = (xr/w)*m * a_y*h/Tf;
dZ_r = (xf/w)*m * a_y*h/Tr; 

% charge pneus (front / rear) (internal / external)
Z_fe = Z_0f + dZ_f + Z_aero_f; 
Z_fi = Z_0f - dZ_f + Z_aero_f;

Z_re = Z_0r + dZ_r + Z_aero_r;
Z_ri = Z_0r - dZ_r + Z_aero_r;

end

