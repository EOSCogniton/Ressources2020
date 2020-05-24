%Script d'étude de sensibilité sur le skidpad
addpath(genpath('.\subfunctions'))

%- Rentrez le path de votre fichier véhicule de base :
%- Attention à enregistrer le paramètre d'origine !!
Paramfile = 'C:\Users\bobau\Documents\EPSA\Ressources2020\MO_Models\LapTime\Vehicules\param_elec_continuous.mat'; %<-- à modifier

%- Rentrer le path du track :
trackfile = 'C:\Users\bobau\Documents\EPSA\Ressources2020\MO_Models\LapTime\Tracks\FSATA_track_elec.mat';
m = matfile(Paramfile,'Writable',true);

start = 1; %<-- à modifier
step = 0.2; %<-- à modifier
End = 2; %<-- à modifier

%_Init_
L = start:step:End;
T = [];
for param=L
    %noter le nom du paramètre à étudier après m. , voir le fichier
    %param.txt dans le dossier subfunctions
    % Attention si ce paramètre et relier à une relation ( ex masse
    % véhicule relié à la masse totale et à l ahauteur du COG) il faut
    % retaper la relation avec de m. devant le nom des variables
    m.Long_tire_grip = param;  %<-- à modifier
    [~,~,~,time] = LapTime(trackfile,Paramfile);
    T = [T,time(end)];
end

plot(L,T)
% Changer les titres des axes et du graphique
title('Sensitivity study of the longitudinal grip coeff')
xlabel('Longitudinal grip coeff')
ylabel('AutoX time (s)')