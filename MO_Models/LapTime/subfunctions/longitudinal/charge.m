function Z = charge(a_x,v, m_t, rep, h, W ,rho, Cz, Cz_rep)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    g = 9.81; % m/s^2
    Z_0 = rep*m_t*g;
    dZ = m_t*a_x * h/W;
    Z_aero = 1/2*rho*v^2*Cz*Cz_rep; % force aero ==> charges

     % Cas ou les roues avant se soulevent
    Z =  min(Z_0+dZ+Z_aero, m_t*g+Z_aero);
end

