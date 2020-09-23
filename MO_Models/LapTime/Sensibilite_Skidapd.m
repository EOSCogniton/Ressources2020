%Script d'étude de sensibilité sur le skidpad
addpath(genpath('.\subfunctions'))

%- Rentrez le path de votre fichier véhicule de base :
%- Attention à enregistrer le paramètre d'origine !!
Paramfile = 'C:\Users\bobau\Documents\EPSA\Ressources2020\MO_Models\LapTime\Vehicules\param_elec_continuous.mat'; %<-- à modifier

m = matfile(Paramfile,'Writable',true);

start = 0.3; %<-- à modifier
step = 0.05; %<-- à modifier
End = 0.7; %<-- à modifier

%_Init_
R_skidpad = 8;
L = start:step:End;
T = [];
for param=L
    %noter le nom du paramètre à étudier après m. , voir le fichier
    %param.txt dans le dossier subfunctions
    % Attention si ce paramètre et relier à une relation ( ex masse
    % véhicule relié à la masse totale et à l ahauteur du COG) il faut
    % retaper la relation avec de m. devant le nom des variables
    m.q = param;  %<-- à modifier
    [~,V_skidpad] = findGymax(R_skidpad,Paramfile);
    time = (2*pi*R_skidpad)/V_skidpad;
    T = [T,time];
end

plot(L,T)
% Changer les titres des axes et du graphique
title('Sensitivity study of the longitudinal grip coeff')
xlabel('Longitudinal grip coeff')
ylabel('Skidpad time (s)')