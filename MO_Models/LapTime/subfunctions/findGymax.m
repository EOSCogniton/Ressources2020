%% Constant turn Model
    % Ce programme donne une estimation de l'acc�leration lat�rale maximale
    % lors d'un virage de rayon constant en fonction des param�tres de la voiture et des pneus
    % Input :   - global : Vehicle_file step
    %           - Turn radius (R_turn)
    %           - Turn angle  (A_turn)

    %Output :   - vectors of speed, time and distance
    
    %Hypothesis :   - tire always at the slip limit
    %               - no suspensions (wtf ?)
 
%% Algo

% Le but du programme est de calculer l'acc�l�ration lat�rale amax � laquelle
% l'�quilibre de la voiture est rompu, c'est-�-dire l'�quilibre en force et en moment.
% La fonction FORCE donne le bilan des forces selon la direction parall�le au rayon du
% virage, amax_force est l'accel�ration a telle que FORCE(a)=0, ce qui correspond au cas
% ou les 2 trains de la voiture d�rapent simultan�ment.
% La fonction torque donne le bilan des moments autour de l'axe vertical,
% amax_force est l'accel�ration a telle que TORQUE(a)=0, ce qui correspond au
% cas ou un des trains de la voiture d�rape (train avant ou arri�re).
% On choisit le minimum de ces deux valeurs et on obtient l'acc�l�ration maximale telle
% que la voiture ne d�rape pas

function [amax,V_turn] = findGymax(R_turn,param_file)
%import parameters :
load(param_file,'xr','W','xf','m_t','g','Tf','Tr','h','Cz','rho','S','FZ','FY','Cz_rep')

% Searching for the maximal lateral acceleration for this turn : 
options = optimset('Algorithm','Levenberg-Marquardt','Display','off');

f1 = @(x) force(x,xr, W, xf, m_t, g, Tf, Tr, h, Cz, rho, S, R_turn, FZ,FY,Cz_rep);
f2 = @(x) force_f(x,xr, W, m_t, g, Tf, h, Cz, rho, S, R_turn, FZ,FY,Cz_rep);
f3 = @(x) force_r(x, W, xf, m_t, g, Tf, Tr, h, Cz, rho, S, R_turn, FZ,FY,Cz_rep);


x1 = fsolve(f1,2000,options) ;
x2 = fsolve(f2,2000,options) ;
x3 = fsolve(f3,2000,options) ;
amax = min([abs(x1) abs(x2) abs(x3)]);

%Calcul of the speed associated with this lateral acceleration
V_turn = sqrt(amax*abs(R_turn));
%V_turn = V_turn*3.6; % speed conversion 
end
%% Functions

%force d'adh�rence lat�rale du pneu en fonction de la charge
function [y] = Y(z,FZ,FY)
    y = interp1(FZ,FY,z,'linear','extrap');
end


function [F] = force(a,xr, W, xf, m_t, g, Tf, Tr, h, Cz, rho, S, R_turn, FZ,FY,Cz_rep)
    Zfe=(xr/W)*m_t*g/2 + 1/4*Cz*rho*S*abs(a)*abs(R_turn)*(1-Cz_rep) + (xr/W)*m_t/Tf*a*h ;
    Zfi=(xr/W)*m_t*g/2 + 1/4*Cz*rho*S*abs(a)*abs(R_turn)*(1-Cz_rep) - (xr/W)*m_t/Tf*a*h ;
    Zre=(xf/W)*m_t*g/2 + 1/4*Cz*rho*S*abs(a)*abs(R_turn)*Cz_rep + (xf/W)*m_t/Tr*a*h ;
    Zri=(xf/W)*m_t*g/2 + 1/4*Cz*rho*S*abs(a)*abs(R_turn)*Cz_rep - (xf/W)*m_t/Tr*a*h ;
    F = Y(Zfe,FZ,FY)+Y(Zfi,FZ,FY)+Y(Zre,FZ,FY)+Y(Zri,FZ,FY) - m_t*a;
end


function [F_f] = force_f(a,xr, W, m_t, g, Tf, h, Cz, rho, S, R_turn, FZ,FY,Cz_rep)

    Zfe=(xr/W)*m_t*g/2 + 1/4*Cz*rho*S*abs(a)*abs(R_turn)*(1-Cz_rep) + (xr/W)*m_t/Tf*a*h ;
    Zfi=(xr/W)*m_t*g/2 + 1/4*Cz*rho*S*abs(a)*abs(R_turn)*(1-Cz_rep) - (xr/W)*m_t/Tf*a*h ;
    F_f = Y(Zfe,FZ,FY)+Y(Zfi,FZ,FY) - (xr/W)*m_t*a ;
end


function [F_r] = force_r(a, W, xf, m_t, g, Tf, Tr, h, Cz, rho, S, R_turn, FZ,FY,Cz_rep)

    Zre=(xf/W)*m_t*g/2 + 1/4*Cz*rho*S*abs(a)*(abs(R_turn)+max(Tf,Tr))*Cz_rep + (xf/W)*m_t/Tr*a*h ;
    Zri=(xf/W)*m_t*g/2 + 1/4*Cz*rho*S*abs(a)*(abs(R_turn)+max(Tf,Tr))*Cz_rep - (xf/W)*m_t/Tr*a*h ;
    F_r = Y(Zre,FZ,FY)+Y(Zri,FZ,FY) - (xf/W)*m_t*a ;
end 