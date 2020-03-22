%% load params in workspace
param_file =  '';
load(param_file)

%pas de calcul de la simu
step = 0.01; 

% peut etre une putian de bonne idée de découper la dynamique du véhicule
% du modèle de moteur et de la simulation elle meme


%% initialisaton de variables
dsim = 0; % distance parcourue
v = 0; % vitesse du vehicule
tsim = -step; % temps
j = 0; % Numero du point de fonctionnement du moteur
t_acc = 0; % Temps
V_acc = v; % Vitesse
Gx = 0; % Acceleration en g
RPM_acc = r_pat; % Regime moteur
C = 0; % Couple
d_acc = 0; % Distance
E = 1; % Embrayage 1=debraye, 0=embraye
Adh = 1; % Risque de patinage des pneus
Ch_ar = rep*m_t*g;

%% calcul preliminaire pour quoi faire ?
n = t_pas/step; % Nombre de pas necessaire au passage de rapport ==> comment ça ?

% c'est quoi u ??
u = n;

% Rapport engagé optimal selon la vitesse du véhicule
k = 6; % Rapport engagé
for gear=1:5
    if 0 < shift_Speed(6-gear) % ==> vecteur shit_speed??
        k = 6-gear; % Rapport engage
    end
end

% c'est quoi ça ??
Ke = 1;
k = 1;

% what the fuck ??
b = coeff_roul*2/D_wheel; % Decalage du point d'appui (m)
c_roul = m_t*g*b; % Resistance au roulement (N.m)

% inerties de rotatin, justement cas la on n'est pas à l'equilibre 
J_trans = m_t*D_wheel^2/4; % Inertie equivalente des masses en translation (kg.m²)
J_eq = J_trans + J_rot; % Inertie totale (kg.m²)


%% Simulation ==> petite description de l'algo non ?
while dsim < D_max  
    
    % intération ==> initialisation pipeau à -step ?!
    tsim = tsim+step;
    
    % on rajoute quelque chose
    t_acc = [t_acc tsim];
    Ke = [Ke k]; % Memoire du rapport engage
    r = v/(k_p*K(k)*k_f*D_wheel*pi/60); % Calcul du regime moteur 
    
    % Prise en compte du patinage de l'embrayage
    if k == 1
        if r < r_pat
            E = [E, 1]; % Patinage
        else
            E = [E,0]; % Pas de patinage
        end
        r = max(r,r_pat); % ==> le patinage est lié au pneu et pas au regime moteur non ??
    else
        E = [E,0];
    end
    RPM_acc = [RPM_acc r];
    
    % Acceleration
    if (u < n) || (r > r_rupteur) % Changement de rapport
        a=0; % Acceleration nulle si changement de rapport
        C = [C, 0]; % Memoire couple aux roues
        Gx = [Gx,0]; % Memoire acceleration
        Adh = [Adh, 0]; % Pas de risque de patinage des pneus
        Ch_ar = [Ch_ar rep*m_t*g];
    else     % Pas de changement de rapport 
        F_deportance_essieu_arr = 1/2*rho*v^2*Cz*Cz_rep; % force aero 
        F_trainee = 1/2*rho*v^2*Cx;
        c_k = interp1(rmot,cmot,r)*pertes/(k_p*K(k)*k_f); % Couple a la roue au rapport engage (m.kg)
        a_ang = (c_k-c_roul)/J_eq; % Acceleration angulaire des roues arrieres
        
        % Charge sur l'essieu arrière avec prise en compte du transfert de
        % masse ==> charges.m
        C_ar = rep*m_t*g+m_t*a_ang*(D_wheel/2)*h/W + F_deportance_essieu_arr; 
        
        % Cas ou les roues avant se soulevent
        if C_ar > m_t*g+ F_deportance_essieu_arr 
            C_ar = m_t*g+ F_deportance_essieu_arr;
        end
        
        % Couple maximum transmissible ==> modèle de pneu 
        c_trans_ar = Long_tire_grip*C_ar*D_wheel/2; 
        
        % Risque de patinage des pneus
        if c_k > c_trans_ar
            Adh = [Adh,1];
            c_k = c_trans_ar; % Prise en compte de la limite d'adherence des pneus
            a_ang = (c_k-c_roul)/J_eq; % Acceleration angulaire des roues arrieres
            C_ar = rep*m_t*g+m_t*a_ang*(D_wheel/2)*h/W + F_deportance_essieu_arr; % Charge sur l'essieu arrière avec prise en compte du transfert de masse
            % non_influence_de_k_f
        else
            Adh = [Adh, 0];
        end
        
        
        C = [C, c_k]; % Memoire du couple aux roues
        Ch_ar =[Ch_ar C_ar];
        a = a_ang*D_wheel/2 - F_trainee / (m_t); % Acceleration du vehicule en m/s² non_influence_de_k_f
        Gx = [Gx,a]; % Memoire acceleration en m/s²
    end
    v = v + a*step; % Vitesse du vehicule
    V_acc = [V_acc v]; % Memoire de la vitesse
    dsim = dsim + v*step; % Distance parcourue
    d_acc = [d_acc, dsim]; % Memoire de la distance
    r = v/(k_p*K(k)*k_f*D_wheel*3.14/60); % Calcul du regime moteur
    % Changement de rapport
    % Changement au rupteur
    if (r > r_rupteur) && (u >n) && (k<6) && (k<k_max)
        k = k+1;
        u=0;
        % Changement de rapport pour optimiser le couple
    elseif (k<k_max) && (u >n) && (v*3.6>shift_Speed(k))
        k = k+1;
        u=0;        
    end
    u = u+1;
end

%remove double
L = [];
for i=2:length(V_acc)
    if V_acc(i-1)==V_acc(i)
        L = [L i];
    end
end

idx = 1:length(V_acc);
idx = setdiff(idx,L);
V_acc = V_acc(idx);
Gx = Gx(idx);
time = tsim;
