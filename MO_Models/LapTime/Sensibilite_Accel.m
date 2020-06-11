%Script d'étude de sensibilité sur l'accel
addpath(genpath('.\subfunctions'))
%- rentrez le path de votre fichier véhicule de base :

Paramfile = 'C:\Users\bobau\Documents\EPSA\Ressources2020\MO_Models\LapTime\Vehicules\param_elec_continuous.mat'; %<-- à modifier

m = matfile(Paramfile,'Writable',true);

start = 1; %<-- à modifier
step = 0.1; %<-- à modifier
End = 2; %<-- à modifier

L = start:step:End;
T = [];
for param=L
    %noter le nom du paramètre à étudier après m. , voir le fichier
    %param.txt dans le dossier subfunctions
    % Attention si ce paramètre et relier à une relation ( ex masse
    % véhicule relié à la masse totale et à l ahauteur du COG) il faut
    % retaper la relation avec de m. devant le nom des variables
    m.Long_tire_grip = param;  %<-- à modifier
   [~,~,time] = Accelelec(75,Paramfile);
   T = [T,time];
end

plot(L,T)
% Changer les titres des axes et du graphique
title('Sensitivity study of the longitudinal grip coeff')
xlabel('Longitudinal grip coeff')
ylabel('Accélération time (s)')