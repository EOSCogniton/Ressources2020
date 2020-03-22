%% Variables

% Carto moteur
rpm_rank = [1000 ,1500 ,2500 ,3000 ,3500 ,4000 ,5000 ,6000 ,7000 ,8000 ,8500 ,9000 ,9500 ,10000 ,10500 ,11000 ,11500 ,12000 ,13000 ,14000 ];
MAP_rank = [10 ,17 ,25 ,32 ,39 ,47 ,54 ,61 ,68 ,76 ,83 ,90 ,98 ,105 ];
injection_fuel_map =...
    [0.25 ,0.43 ,0.61 ,0.80 ,0.90 ,1.10 ,1.40 ,1.70 ,1.90 ,1.78 ,1.88 ,1.95 ,2.54 ,5.00 ;... %1
     0.25 ,0.43 ,0.61 ,0.80 ,0.90 ,1.10 ,1.40 ,1.70 ,1.90 ,1.78 ,1.88 ,1.95 ,2.54 ,5.00 ;... %2
     0.25 ,0.43 ,0.61 ,0.80 ,0.90 ,1.10 ,1.40 ,1.70 ,1.90 ,1.78 ,1.88 ,1.95 ,2.79 ,5.70 ;... %3
     0.25 ,0.43 ,0.61 ,0.80 ,0.90 ,1.10 ,1.40 ,1.70 ,1.90 ,1.78 ,2.21 ,2.30 ,5.61 ,6.50 ;... %4
     0.25 ,0.43 ,0.61 ,0.80 ,0.90 ,1.10 ,1.40 ,1.70 ,1.90 ,2.10 ,2.60 ,2.70 ,6.00 ,6.50 ;... %5
     0.25 ,0.43 ,0.61 ,0.80 ,0.90 ,1.20 ,1.50 ,1.85 ,2.20 ,2.40 ,3.20 ,3.50 ,6.00 ,7.00 ;... %6
     0.25 ,0.43 ,0.80 ,0.80 ,1.25 ,1.40 ,1.60 ,1.90 ,2.40 ,2.80 ,3.80 ,4.10 ,6.00 ,7.00 ;... %7
     0.40 ,0.47 ,0.80 ,0.90 ,1.30 ,1.40 ,1.80 ,1.70 ,2.30 ,3.60 ,4.00 ,4.20 ,5.00 ,6.00 ;... %8
     0.40 ,0.60 ,0.80 ,0.90 ,1.30 ,1.45 ,1.80 ,2.20 ,2.50 ,3.70 ,4.20 ,4.60 ,4.50 ,5.00 ;... %9
     0.40 ,0.60 ,0.80 ,0.90 ,1.32 ,1.45 ,1.90 ,2.30 ,2.90 ,3.70 ,4.30 ,5.00 ,5.12 ,5.50 ;... %10
     0.40 ,0.60 ,1.10 ,1.10 ,1.35 ,1.50 ,2.00 ,2.60 ,3.03 ,3.80 ,4.80 ,5.60 ,6.05 ,6.50 ;... %11
     0.40 ,0.60 ,1.10 ,1.10 ,1.35 ,1.55 ,2.20 ,2.71 ,3.03 ,3.80 ,4.80 ,5.60 ,6.05 ,6.50 ;... %12
     0.60 ,0.60 ,1.10 ,1.20 ,1.38 ,1.60 ,2.40 ,2.71 ,3.03 ,3.80 ,4.80 ,5.60 ,6.05 ,6.50 ;... %13
     0.60 ,0.90 ,1.10 ,1.30 ,1.40 ,1.70 ,2.40 ,3.00 ,3.59 ,4.15 ,4.70 ,6.03 ,6.51 ,7.00 ;... %14
     0.60 ,0.90 ,1.30 ,1.40 ,1.40 ,1.70 ,2.50 ,3.10 ,3.75 ,4.15 ,4.70 ,6.03 ,6.51 ,7.00 ;... %15
     0.60 ,0.90 ,1.30 ,1.40 ,1.50 ,1.70 ,2.60 ,3.20 ,3.75 ,4.15 ,4.70 ,6.03 ,6.51 ,7.00 ;... %16
     0.60 ,0.90 ,1.30 ,1.40 ,1.50 ,1.70 ,2.60 ,3.30 ,3.75 ,4.15 ,4.70 ,6.03 ,6.51 ,7.00 ;... %17
     0.60 ,0.90 ,1.30 ,1.45 ,1.50 ,1.80 ,2.70 ,3.30 ,3.75 ,4.15 ,4.85 ,6.03 ,6.51 ,7.00 ;... %18
     0.60 ,0.90 ,1.30 ,1.45 ,1.50 ,1.80 ,2.80 ,3.30 ,3.75 ,4.32 ,4.85 ,6.03 ,6.51 ,7.00 ;... %19
     0.60 ,0.90 ,1.30 ,1.45 ,1.50 ,1.80 ,2.80 ,3.30 ,3.75 ,4.32 ,4.85 ,6.03 ,6.51 ,7.00 ];   %20
    % 1_____2_____3_____4_____5_____6_____7_____8_____9_____10____11____12

delta_tps = 10; %intervalle de temps (en ms) entre 2 relevés de TPS pour appliquer le Throtle Transcient
throttle_turn_off = 100; % pourcentage pédale au-dessus duquel le tip in est désactivé
tip_in_tab =... % 0-1500 ; 1500-3000 ; 3000-5000 ; 5000 et +
    [3, 5, 5, 5 ;... %variation pédale à détecter
     100, 40, 20, 20 ;... % variation d'injection (en %)
     30, 50, 10, 20]; %durée (en nombre de tours moteur)
tip_out_tab =... % 0-1500 ; 1500-3000 ; 3000-5000 ; 5000 et +
    [40, 40, 10, 5 ;... % variation pédale à détecter
     1, 2, 3, 3 ;... % variation d'injection (en %)
     1, 1, 1, 1]; % durée (en nombre de tours moteur)

air_temp_comp =... % compensation par rapport à la température plenum
    [-10, -5,  0, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 90,100,110,115,116,120 ;... % échelle de température
     14 , 12, 10,  6,  5,  3,  1, -1, -2, -4, -7,-10,-12,-15,-17,-19,-21,-22,-23,-23]; % compensation pourcentage temps d'injection

water_temp_comp =... % compensation par rapport à la température moteur
    [  0, 10, 20, 30, 40, 45, 50, 55, 60, 70, 80, 85, 90, 95,100,105,110,112,115,120 ;... % échelle de température
       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  9, 10, 15, 18]; % compensation pourcentage temps d'injection

% Données

fe = 10; % Fréquence d'échantillonage
ft = 100; % Fréquence de traitement
rpm = []; % data rpm
MAP = []; %data Manifold Air Pressure
debit_inj = 3.9; %en ml/s


% Rafinement du modèle

flag_tip_in = true; %activation de la prise en compte du tip in ou non
flag_tip_out = false; %activation de la prise en compte du tip out ou non
if flag_tip_in || flag_tip_out
    TPS = []; %data du Throtle Position Sensor
end

flag_air_comp = false; % activation de la compensation en température admission
if flag_air_comp
    temp_plenum = []; % data de la température plenum
end

flag_water_comp = false; % activation de la compensation en température moteur
if flag_water_comp
    temp_water = []; % data de la température plenum
end

%% Execution

%Execution de la cartographie sur les data
rpm_ft = fe_to_ftHz (rpm, fe, ft);
MAP_ft = fe_to_ftHz (MAP, fe, ft);
tours_ft = tours_moteurs (rpm_ft,ft);
inj_time_ft = log_to_inj (rpm_ft, MAP_ft, tours_ft, ft, injection_fuel_map, rpm_rank, MAP_rank);

%Application (si activé) des correctifs température et tip in/out
if flag_tip_in || flag_tip_out || flag_air_temp || flag_water_temp
    correction_ft = zeros(1,length(rpm_ft));
    if flag_tip_in || flag_tip_out
        tps_ft = fe_to_ftHz (TPS, fe, ft);
        if flag_tip_in
            correction_ft = log_to_tip (tps_ft, ft, rpm_ft, tours_ft, tip_in_tab, delta_tps, throttle_turn_off);
        end
        if flag_tip_out
            correction_ft = correction_ft + log_to_tip(tps_ft, ft, rpm_ft, tours_ft, tip_out_tab, delta_tps, throttle_turn_off);
        end
    end

    if flag_air_temp
        temp_plenum_ft = fe_to_ftHz(temp_plenum, fe, ft);
        correction_ft = correction_ft + log_to_temp_comp(air_temp_comp, temp_plenum_ft);
    end

    if flag_water_temp
        temp_water_ft = fe_to_ftHz(temp_water, fe, ft);
        correction_ft = correction_ft + log_to_temp_comp(water_temp_comp, temp_water_ft);
    end
    correction_ft = correction_ft/100 + 1;
    inj_time_ft = inj_time_ft .* correction_ft; %application des corrections au temps d'injection
end



%calcul de la consommation
time_inj = sum(inj_time_ft); %temps d'injection total en ms
consommation = time_inj/1000*debit_inj/1000


%% Fonctions

function log_ft = fe_to_ftHz (log_fe,fe,ft)
%Convertit la table log_fe de fréquence d'échantillonnage fe en table de
%fréquence ft
if fe == ft
    log_ft = log_fe;
elseif (ft > fe) && (mod(ft,fe) == 0)
    log_ft = interp(log_fe,ft/fe);
elseif (ft < fe) && (mod(fe,ft) == 0)
    log_ft = downsample(log_fe,fe/ft);
else
    ke = 1;
    te = 0;
    tt = 0;
    kt = 1;
    deltatt = 1/ft;
    deltate = 1/fe;
    tm = (length(log_fe)-1)*deltate;
    if fe < ft
        log_ft = zeros(1,floor(length(log_fe)*ft/fe));
    else 
        log_ft = zeros(1,floor(length(log_fe)*fe/ft));
    end
    while (tt<=tm) && (te<=tm)
        if te == tt
            log_ft(kt) = log_fe(ke);
            ke = ke + 1;
            kt = kt + 1;
            te = te + deltate;
            tt = tt + deltatt;
        elseif te > tt
            log_ft(kt) = interp1([te-deltate,te],[log_fe(ke-1),log_fe(ke)],tt);
            tt = tt + deltatt;
            kt = kt + 1;
        else
            te = deltate + te;
            ke = ke + 1;
        end
    end
    while kt <= length(log_ft)
        log_ft(kt) = log_fe(length(log_fe));
        kt = kt + 1;
    end
end
end

function tours = tours_moteurs (rpm,ft)
N = length(rpm);
tours = zeros(1,N);
rps = rpm/60/ft;
for k = 2:N
    tours(k) = tours(k-1) + (rps(k-1) + rps(k))/2;
end
end

function inj_ft = log_to_inj (rpm_ft, MAP_ft, tours_ft, injection_fuel_map, rpm_rank, MAP_rank)
N = length(rpm_ft);
inj_ft = zeros(1,N);
for k = 2:N
    a = floor(2*tours_ft(k-1));
    b = floor(2*tours_ft(k));
    inj_ft(k) = (b-a)*interp2(MAP_rank, rpm_rank, injection_fuel_map, MAP_ft(k), rpm_ft(k));
end
end

function tip_ft = log_to_tip (tps_ft, ft, rpm_ft, tours_ft, tip_in_tab, delta_tps, throttle_turn_off)
N = length(tps_ft);
percent_tip = 1000/delta_tps/ft * tip_in_tab(1,:);
tip_ft = zeros(1,N);
for k = 2:N
    rpm = rpm_ft(k);
    if rpm < 1500
        colonne = 1;
    elseif rpm < 3000
        colonne = 2;
    elseif rpm < 5000
        colonne = 3;
    else
        colonne = 4;
    end
    if ((tps_ft(k)-tps_ft(k-1)) > percent_tip(colonne)) && (tps_ft(k) < throttle_turn_off)
        tour = k;
        tip_ft(k) = tip_in_tab(2,colonne);
        while (tours_ft(tour+1) - tours_ft(k)) < tip_in_tab (3,colonne)
            tour = tour + 1;
            tip_ft(tour) = tip_in_tab(2,colonne);
        end
    end
end
end

function temp_comp = log_to_temp_comp (tab_temp_comp, temp_ft)
temp_comp = interp1(tab_temp_comp(1,:), tab_temp_comp(2,:), temp_ft(k));
end
