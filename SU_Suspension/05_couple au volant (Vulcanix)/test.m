clear
close all

%Calcule de la force exercée pae une main sur le volant

alpha=78; %angle du bras de levier dans le porte moyeu, en °
P = 280*9.81; %poids en N
T = 0.8*P/4; %force tangentielle sur une roue
Rv = 0.27/2; %Rayon du volant (en metre)
Lc = 0.017; %chasse (en metre)
dm = 0.06*sin(alpha*pi/180); %bras de levier du porte moyeu (en mètre)
dc = 0.08; %debattement de la cremaillere (en mètre/tour)
theta = (0:0.01:pi/2);%angles du volant

Fv = 0*theta;

for i=1:length(theta)
    Fv(i) = (Lc*T*dc*f(theta(i)))/(pi*dm*Rv*2);
end

figure;
plot(theta*180/pi,Fv);
title("Evolution de la force exercée par une main en fonction de l'angle du volant")
xlabel('angle du volant (en radian)')
ylabel('Force exercée sur le volant (en N)')

% t=0:0.01:2*pi;
% ff=0*t;
% for i=1:length(ff)
%     ff(i)=f(t(i));
% end
% figure
% plot(t,ff)

function [fv] = f(t)
    a = 40*pi/180 ;
    fv = cos(a)*(1 + tan(t)^2)/(1 + cos(a)^2*tan(t)^2);
end

