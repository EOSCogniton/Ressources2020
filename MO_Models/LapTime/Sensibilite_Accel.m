%Script d'�tude de sensibilit� sur l'accel
addpath(genpath('.\subfunctions'))
%- rentrez le path de votre fichier v�hicule de base :

Paramfile = 'C:\Users\bobau\Documents\EPSA\Ressources2020\MO_Models\LapTime\Vehicules\param_elec_continuous.mat'; %<-- � modifier

m = matfile(Paramfile,'Writable',true);

start = 1; %<-- � modifier
step = 0.1; %<-- � modifier
End = 2; %<-- � modifier

L = start:step:End;
T = [];
for param=L
    %noter le nom du param�tre � �tudier apr�s m. , voir le fichier
    %param.txt dans le dossier subfunctions
    % Attention si ce param�tre et relier � une relation ( ex masse
    % v�hicule reli� � la masse totale et � l ahauteur du COG) il faut
    % retaper la relation avec de m. devant le nom des variables
    m.Long_tire_grip = param;  %<-- � modifier
   [~,~,time] = Accelelec(75,Paramfile);
   T = [T,time];
end

plot(L,T)
% Changer les titres des axes et du graphique
title('Sensitivity study of the longitudinal grip coeff')
xlabel('Longitudinal grip coeff')
ylabel('Acc�l�ration time (s)')