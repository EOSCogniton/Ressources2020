function [Z_r,Z_f] = charge_long(a_x,v, m_t,xr,xf, h, W ,rho, Cz, Cz_rep,S)
%CHARGES calcule les charges sur les trains avant et arrière de la voiture
%   xr : distance CG train arrière
%   xf : distance CG train avant
%   W : empattement (wheelbase)
%   m_t : masse totale
%   Cz : costante aérodynamique
%   rho : masse volumique air
%   S : surface équivalente véhicule (plan normale x)
%   a_x ; accéleration longitudinale
%   Cz_rep : répartition aéro avant
%   v : vitesse en m/s

    g = 9.81; % m/s^2
    
    % charges statiques
    Z_0f = (xr/W)*m_t*g;
    Z_0r = (xf/W)*m_t*g;
    %charges aéros
    Z_aero_f = 1/2*Cz*rho*S* v^2 *(1-Cz_rep);
    Z_aero_r = 1/2*Cz*rho*S* v^2 *Cz_rep;
    %Transfert de charge
    dZ_f = - m_t * a_x*h/W;
    dZ_r = m_t * a_x*h/W; 
    %charge totale, prise en compte du cas ou un train se soulève
    Z_f = min(Z_0f + dZ_f + Z_aero_f , m_t*g + Z_aero_f);
    Z_r = min(Z_0r + dZ_r + Z_aero_r , m_t*g + Z_aero_r); 

end

