%% load params in workspace
param_file =  'C:\Users\mik75\Documents\FSAEinvictus\Ressources2020\MO_Models\LapTime\param_test.mat';
load(param_file)

D_max = 200; % m

%pas de calcul de la simu
step = 0.01; 

% peut etre une putian de bonne idée de découper la dynamique du véhicule
% du modèle de moteur et de la simulation elle meme


%% initialisaton de variables
d = 0; % distance parcourue
v = 0; % vitesse du vehicule
tsim = 0; % temps
j = 0; % Numero du point de fonctionnement du moteur
tt = 0; % Temps
fig_v = figure(2); % Vitesse
Gx = 0;% Acceleration en g
fig_r = figure(3); % memoire Regime moteur
cc = 0; % memoire Couple aux roues 
dd = 0; % Distance
ee = 1; % Embrayage 1=debraye, 0=embraye
Adh = 1; % Risque de patinage des pneus
ZZ = rep*m_t*g;

% Rapport engagé optimal selon la vitesse du véhicule
%k = 6; % Rapport engagé
%for gear=1:5
%    if 0 < shift_Speed(6-gear) 
%        k = 6-gear; % Rapport engage
%    end
%end

k = 1;  % rapport vourant, 1 départ
fig_k = figure(1);

% what the fuck ??
b = coeff_roul*2/D_wheel; % Decalage du point d'appui (m) ==> bras
c_roul = m_t*g*b; % Resistance au roulement (N.m)

% inerties de rotation, justement cas la on n'est pas à l'equilibre 
J_trans = m_t*D_wheel^2/4; % Inertie equivalente des masses en translation (kg.m²)
J_eq = J_trans + J_rot; % Inertie totale (kg.m²)

% Nombre de pas necessaire au passage de rapport ==> comment ça ?
n = t_pas/step;
u = n; % c'est quoi u ??



%% Simulation ==> petite description de l'algo non ?
while d < D_max  
    
    % on rajoute quelque chose
    tt = [tt tsim]; % memoire t_acc 
    figure(fig_k), scatter(tsim, k) % Memoire du rapport engage ==> appena fatto 
    
    % Calcul du regime moteur à partir de ls vitesse
    % ?? on vien de le calculer 
    r = v/(k_p*K(k)*k_f*D_wheel*pi/60); % rpm

    % Prise en compte du patinage de l'embrayage
    r = min(r,r_pat);
    e = 0 +(k==1)*(r<r_pat);
    ee = [ee, e];
    
    % Prise en compte du patinage de l'embrayage
    %if k == 1
    %    if r < r_pat
    %        ee = [ee, 1]; % Patinage
    %    else
%             ee = [ee,0]; % Pas de patinage
%         end
%         r = max(r,r_pat);
%     else
%         ee = [ee,0];
%     end

    % update memoire regime moteur 
    figure(fig_r), scatter(tsim, r);
    
    % Acceleration
    if (u < n) || (r > r_rupteur) % Changement de rapport en cours
        a_x=0; % Acceleration nulle si changement de rapport
        cc = [cc, 0]; % Memoire couple aux roues
        Gx = [Gx,0]; % Memoire acceleration
        Adh = [Adh, 0]; % Memoire risque de patinage des pneus
        ZZ = [ZZ rep*m_t*g];
    else     % Pas de changement de rapport 
        
        c_k = interp1(rmot,cmot,r)*pertes/(k_p*K(k)*k_f); % Couple a la roue au rapport engage (m.kg)==> moteur
        a_ang = (c_k-c_roul)/J_eq; % Acceleration angulaire des roues arrieres
        
        % Charge sur l'essieu arrière avec prise en compte du transfert de masse ==> charges.m
        Z = charge(a_ang*(D_wheel/2),v, m_t, rep, h, W ,rho, Cz, Cz_rep);

        % Couple maximum transmissible ==> modèle de pneu 
        c_amm = Long_tire_grip*Z*D_wheel/2; 
        
        % Risque de patinage des pneus
        if c_k > c_amm
            Adh = [Adh,1]; % Memoire adhérence
            c_k = c_amm; % Prise en compte de la limite d'adherence des pneus
            a_ang = (c_k-c_roul)/J_eq; % Acceleration angulaire des roues arrieres
            Z = charge(a_ang*(D_wheel/2),v, m_t, rep, h, W ,rho, Cz, Cz_rep); % ==> log 
        else
            Adh = [Adh, 0];
        end
        
        
        cc = [cc, c_k]; % Memoire du couple aux roues
        ZZ =[ZZ Z];
        
        % PFD - Acceleration du vehicule en m/s² non_influence_de_k_f
        F_trainee = 1/2*rho*v^2*Cx; % aero
        a_x = a_ang*D_wheel/2 - F_trainee / (m_t); 
        
        Gx = [Gx,a_x]; % Memoire acceleration en m/s²
    end
    
    v = v + a_x*step; % Vitesse du vehicule
    figure(fig_v), scatter(tsim, v); % Memoire de la vitesse
    d = d + v*step; % Distance parcourue par la simulation
    dd = [dd, d]; % Memoire de la distance
    r = v/(k_p*K(k)*k_f*D_wheel*pi/60); % Calcul du regime moteur
    
    % Changement de rapport ou changement au rupteur
    if (r > r_rupteur) && (u >n) && (k<6) && (k<k_max)
        k = k+1;
        u=0;
        % Changement de rapport pour optimiser le couple
    elseif (k<k_max) && (u >n) && (v*3.6>shift_Speed(k))
        k = k+1;
        u=0;        
    end
    
    % a sert à quoi cette variable ???
    u = u+1;
    
    % intération temps
    tsim = tsim+step;
end

%remove double
L = [];
for i=2:length(vv)
    if vv(i-1)==vv(i)
        L = [L i];
    end
end

idx = 1:length(vv);
idx = setdiff(idx,L);
vv = vv(idx);
Gx = Gx(idx);
time = tsim;
