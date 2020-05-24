%Script d'�tude de sensibilit� sur le skidpad
addpath(genpath('.\subfunctions'))

%- Rentrez le path de votre fichier v�hicule de base :
%- Attention � enregistrer le param�tre d'origine !!
Paramfile = 'C:\Users\bobau\Documents\EPSA\Ressources2020\MO_Models\LapTime\Vehicules\param_elec_continuous.mat'; %<-- � modifier

m = matfile(Paramfile,'Writable',true);

start = 0.3; %<-- � modifier
step = 0.05; %<-- � modifier
End = 0.7; %<-- � modifier

%_Init_
R_skidpad = 8;
L = start:step:End;
T = [];
for param=L
    %noter le nom du param�tre � �tudier apr�s m. , voir le fichier
    %param.txt dans le dossier subfunctions
    % Attention si ce param�tre et relier � une relation ( ex masse
    % v�hicule reli� � la masse totale et � l ahauteur du COG) il faut
    % retaper la relation avec de m. devant le nom des variables
    m.q = param;  %<-- � modifier
    [~,V_skidpad] = findGymax(R_skidpad,Paramfile);
    time = (2*pi*R_skidpad)/V_skidpad;
    T = [T,time];
end

plot(L,T)
% Changer les titres des axes et du graphique
title('Sensitivity study of the longitudinal grip coeff')
xlabel('Longitudinal grip coeff')
ylabel('Skidpad time (s)')