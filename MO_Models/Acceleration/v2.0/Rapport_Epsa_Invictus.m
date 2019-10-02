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

figure(1)
plot([-5 5],[0,0],'k:','linewidth',3)
hold on
plot([1 1],[-100,100],'k:','linewidth',2)
hold on
plot([2 2],[-100,100],'k:','linewidth',2)
hold on
plot([3 3],[-100,100],'k:','linewidth',2)
hold on
p1=plot(1:length(CL),[0,VariazioneCL],'b','linewidth',2);
hold on
p2=plot(1:length(CX),[0,VariazioneCX],'r','linewidth',2);
hold on
p3=plot(1:length(E),[0,VariazioneE],'g','linewidth',2);
hold on
plot(1:length(CL),[0,VariazioneCL],'b.','Markersize',30)
hold on
plot(1:length(CX),[0,VariazioneCX],'r.','Markersize',30)
hold on
plot(1:length(E),[0,VariazioneE],'g.','Markersize',30)
hold on
grid on
ylabel('Variation w.r.t. Standard Configuration [%]')
xlabel('Configuration:   1-Standard        2-Steered wheels        3-Low Drag')
ylim([-40,15])
xlim([0.5,3.5])
title('Coefficient variation with different configuration')
grid on 
grid minor
set(gca,'xtick',[-1:1:4])
set(gca,'ytick',[-100:5:100])
legend([p1,p2,p3],'-CL','CX','Aerodynamic Efficiency','Location','northwest')

%%




figure(2)
for i=1:length(CL)
plot(V,Lift(rho,A,CL(i),V),'linewidth',2)
hold on
end
plot(V,LNoAero(rho,Aop,CLop,V),'linewidth',2)
hold on
title('-Lift at various speed and configuration')
xlabel('V [Km/h]')
ylabel('-L [N]')
grid on
grid minor
legend('Standard Configuration','Steered wheels','Low Drag Configuration','No Aero. Package','Location','northwest')



figure(3)
for i=1:length(CX)
plot(V,Drag(rho,A,CX(i),V),'linewidth',2)
hold on
end
plot(V,DNoAero(rho,Aop,CXop,V),'linewidth',2)
hold on
title('Drag at various speed and configuration')
xlabel('V [Km/h]')
ylabel('D [N]')
grid on
grid minor
legend('Standard Configuration','Steered wheels','Low Drag Configuration','No Aero. Package','Location','northwest')





