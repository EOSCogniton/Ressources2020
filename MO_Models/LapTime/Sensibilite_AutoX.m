%Script d'�tude de sensibilit� sur le skidpad
addpath(genpath('.\subfunctions'))

%- Rentrez le path de votre fichier v�hicule de base :
%- Attention � enregistrer le param�tre d'origine !!
Paramfile = 'C:\Users\bobau\Documents\EPSA\Ressources2020\MO_Models\LapTime\Vehicules\param_elec_continuous.mat'; %<-- � modifier

%- Rentrer le path du track :
trackfile = 'C:\Users\bobau\Documents\EPSA\Ressources2020\MO_Models\LapTime\Tracks\FSATA_track_elec.mat';
m = matfile(Paramfile,'Writable',true);

start = 1; %<-- � modifier
step = 0.2; %<-- � modifier
End = 2; %<-- � modifier

%_Init_
L = start:step:End;
T = [];
for param=L
    %noter le nom du param�tre � �tudier apr�s m. , voir le fichier
    %param.txt dans le dossier subfunctions
    % Attention si ce param�tre et relier � une relation ( ex masse
    % v�hicule reli� � la masse totale et � l ahauteur du COG) il faut
    % retaper la relation avec de m. devant le nom des variables
    m.Long_tire_grip = param;  %<-- � modifier
    [~,~,~,time] = LapTime(trackfile,Paramfile);
    T = [T,time(end)];
end

plot(L,T)
% Changer les titres des axes et du graphique
title('Sensitivity study of the longitudinal grip coeff')
xlabel('Longitudinal grip coeff')
ylabel('AutoX time (s)')