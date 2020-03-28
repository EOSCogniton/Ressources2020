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
a = 0; % a_x acceleration longitudinale
t = 0; % temps de la simulation
j = 0; % Numero du point de fonctionnement du moteur
tt = 0; % memoire Temps
vv = v; % memoire Vitesse
aa = a; % memoire de a_x --> le mettre en g pour le GGV
rr = 0; % memoire Regime moteur
cc = 0; % memoire Couple aux roues 
dd = d; % memoire Distance
ee = 1; % Embrayage 1=debraye, 0=embraye
Adh = 1; % Risque de patinage des pneus
ZZ = rep*m_t*g; % memoire charge

% Rapport engagé optimal selon la vitesse du véhicule
%k = 6; % Rapport engagé
%for gear=1:5
%    if 0 < shift_Speed(6-gear) 
%        k = 6-gear; % Rapport engage
%    end
%end

k = 1;  % rapport vourant, 1 départ
kk = k; % memoire rapport engagé

% what the fuck --> constante paramètres 
b = coeff_roul*2/D_wheel; % Decalage du point d'appui (m) ==> bras
c_roul = m_t*g*b; % Resistance au roulement (N.m)

% inerties de rotation, --> const para mètres
J_trans = m_t*D_wheel^2/4; % Inertie equivalente des masses en translation (kg.m²)
J_eq = J_trans + J_rot; % Inertie totale (kg.m²)

% Nombre de pas necessaire au passage de rapport ==> comment ça ?
%n = t_pas/step;
%u = n; % c'est quoi u ??



%% Simulation
while d < D_max  

    % Prise en compte du patinage de l'embrayage
    r = max(rr(end),r_pat);
   % rr = [rr r]; % memoire regime moteur
    e = 0 +(k==1)*(r<r_pat);
    ee = [ee, e]; % memoire patinage
   
%     % Acceleration
%     if (u < n) || (r > r_rupteur) % Changement de rapport en cours
%         a_x=0; % Acceleration nulle si changement de rapport
%         cc = [cc, 0]; % Memoire couple aux roues
%         Gx = [Gx,0]; % Memoire acceleration
%         Adh = [Adh, 0]; % Memoire risque de patinage des pneus
%         ZZ = [ZZ rep*m_t*g];
%     else     % Pas de changement de rapport 
%        
        % Couple a la roue au rapport engage (m.kg)==> moteur
        c_k = interp1(rmot,cmot,r)*pertes/(k_p*K(k)*k_f); 
        % Acceleration angulaire des roues arrieres
        %a_ang = (c_k-c_roul)/J_eq; 
        
        % calcule charges avec a_x de la boucle précedente
        Z = charge(aa(end), v, m_t, rep, h, W ,rho, Cz, Cz_rep);
        ZZ =[ZZ Z];
        
        % Couple maximum transmissible ==> modèle de pneu 
        c_amm = Long_tire_grip*Z*D_wheel/2; 
        
%         % Risque de patinage des pneus
%         if c_k > c_amm
%             Adh = [Adh,1]; % Memoire adhérence
%             c_k = c_amm; % Prise en compte de la limite d'adherence des pneus
%             a_ang = (c_k-c_roul)/J_eq; % Acceleration angulaire des roues arrieres
%             Z = charge(a_ang*(D_wheel/2),v, m_t, rep, h, W ,rho, Cz, Cz_rep); % ==> log 
%         else
%             Adh = [Adh, 0];
%         end

        % le pneu peu glisser 
        c_k = min(c_k, c_amm);
        cc = [cc, c_k]; % Memoire du couple aux roues
        
        % maj acceleration angulaire 
        a_ang = (c_k-c_roul)/J_eq;
        
        % PFD - maj a_x
        F_trainee = 1/2*rho*v^2*Cx; % aero
        a_x = a_ang*D_wheel/2 - F_trainee / (m_t); 
        aa = [aa a_x]; % Memoire acceleration en m/s²
%     end
    
    % maj vitesse du vehicule
    v = v + a_x*step; 
    vv = [vv v]; % Memoire de la vitesse
    
    % maj distance parcourue par la simulation
    d = d + v*step; 
    dd = [dd, d]; % Memoire de la distance
    
    % maj rapport de vitesse engagé
    r = v/(k_p*K(k)*k_f*D_wheel*pi/60); % Calcul du regime moteur
    rr = [rr r];
    
    k = k+ (((r > r_rupteur) || (v*3.6>shift_Speed(k)))  && (k<k_max));
    kk = [kk k]; % Memoire du rapport engage 

    % intération temps
    t = t+step;
    tt = [tt t]; % memoire t_acc 
end

%% remove double
L = [];
for i=2:length(vv)
    if vv(i-1)==vv(i)
        L = [L i];
    end
end

idx = 1:length(vv);
idx = setdiff(idx,L);
vv = vv(idx);
aa = aa(idx);
time = t;
