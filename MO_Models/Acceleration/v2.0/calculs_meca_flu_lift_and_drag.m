clear all
close all
clc

% Je n'ai pas eu assez de temps pour mettre l'aile anterieure en
% configuration low-drag. Il faul lancer une procede d'optimization pour
% calculer l'angle d'attaque des profils meilleur pour reduire le drag. ça a été faite
% seulement pour l'aile arriere, l'aile anteireure reste pour l'instant en
% configuration max appui.

 %Drag= Positif si opposé au sens de marche du vehicule
 %Lift= Positif vers le bas

rho=1.18415; %Masse Volumique air 
A=1.139;     %Aire de reference avec paquet aero


CX=[1.268,  1.38,   0.800]; % CX Configuration standard(Deportance max), CX Roues Braquées, CX Configuration(Aile arriere ouverte) 
CL=[2.238,  2.13,  1.490]; % CL Configuration standard(Deportance max), CL Roues Braquées, CL Configuration(Aile arriere ouverte) 

E=CL./CX;              % Efficacite aerodynamique

CXop=0.8393;           % CX Optimus sans paquet aero
CLop=-0.2014;          % CL Optimus sans paquet aero 

Aop=0.8437;            %Aire de reference sans paquet aero

V=linspace(0,120,1000);

%Drag et Lift sans paquet aero
DNoAero=@(rho,Aop,CXop,V) 0.5.*Aop.*rho.*CXop.*(V./3.6).^2; %Approximation CX= constante (Peu variable)
LNoAero=@(rho,Aop,CLop,V) 0.5.*Aop.*rho.*CLop.*(V./3.6).^2; %Approximation CL= constante (Peu variable)

%Drag et Lift avec paquet aero
Drag=@(rho,A,CX,V) 0.5.*A.*rho.*CX.*(V./3.6).^2; %Approximation CX= constante (Peu variable)
Lift=@(rho,A,CL,V) 0.5.*A.*rho.*CL.*(V./3.6).^2; %Approximation CL= constante (Peu variable)

for i=2:length(CL)
VariazioneCL(i-1)=(CL(i)-CL(1))./CL(1).*100;
end

for i=2:length(CX)
VariazioneCX(i-1)=(CX(i)-CX(1))./CX(1).*100;
end

for i=2:length(E)
VariazioneE(i-1)=(E(i)-E(1))./E(1).*100;
end

%%

Lift_config = [];
for i=1:length(CL)
Lift_config = [Lift_config ; Lift(rho,A,CL(i),V)];
end

vitesse_voiture_aero = V.*(1/3.6); % vitesse (m/s)
Lift_standard_config = Lift_config(1,:);
Lift_steering_wheels_config = Lift_config(2,:);
Lift_low_drag_config = Lift_config(3,:);
Lift_no_aero = LNoAero(rho,Aop,CLop,V);

Drag_config = [];
for i=1:length(CX)
Drag_config = [Drag_config ; Drag(rho,A,CX(i),V)];
end

Drag_standard_config = Drag_config(1,:);
Drag_steering_wheels_config = Drag_config(2,:);
Drag_low_drag_config = Drag_config(3,:);
Drag_no_aero = DNoAero(rho,Aop,CXop,V);




