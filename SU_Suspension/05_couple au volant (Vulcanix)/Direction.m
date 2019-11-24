%Dimensionnement de la direction :

%Données :
a = 40*pi/180 ; %angle du cardan (en radian)
b = 15*pi/180 ; % angle du volant (en radian)
hc = 0.61 ; %hauteur du chassis (en metre)
D = 0.08 ; %Distance horizontale entre l'axe de pivot et la cremaillere (en metre)
d = 0.265 ; %diametre du volant (en metre)
l1 = tan(b)*d + 0.02 + 0.01 + 0.02 ;
db = cos(b)*d/2 ;
%Offset :
ov = 0.01 ; %vertical 
oh = 0.03 ; %horizontal

%Equations :
l2 = (hc - db - l1*sin(b))/sin(a+b) ;
h = l2*cos(a+b) + cos(b)*(l1-tan(b)*d) - D

%On prend en compte l'offset au niveau du volant :
l2_new = (hc - db - ov - l1*sin(b))/sin(a+b) ;
h_new = l2_new*cos(a+b) + cos(b)*(l1-tan(b)*d) + oh - D

ecart = h_new - h

%Dimensionnement de la chasse :
P = 280; %poids 
T = 0.8*P/4; %force tangentielle sur une roue
Dv = [0.023 0.025 0.027]; %diametre du volant (en metre)
Lc = 0.075; %chasse (en metre)
dm = 0.07; %bras de levier du porte moyeu
dc = 0.09; %debattement de la cremaillere
theta = [0:0.1:pi/2];%angle du volant

Fv1 = 1:length(theta);
Fv2 = 1:length(theta);
Fv3 = 1:length(theta);

for i=1:length(theta)
    Fv1(i) = (Lc*T*dc*f(theta(i)))/(pi*dm*0.115);
end

for i=1:length(theta)
    Fv2(i) = (Lc*T*dc*f(theta(i)))/(pi*dm*0.125);
end

for i=1:length(theta)
    Fv3(i) = (Lc*T*dc*f(theta(i)))/(pi*dm*0.135);
end

figure;
plot(theta*180/pi,Fv1,theta*180/pi,Fv2,theta*180/pi,Fv3);
% title("Evolution de la force exercée par une main en fonction de l'angle du volant")
% xlabel('angle du volant (en radian)')
% ylabel('Force exercée sur le volant (en N)')
title("Evolution of the force applied on the steering wheel")
xlabel('Steering wheel angle (Deg)')
ylabel('Force of one hand on the steering wheel (N)')


function [fv] = f(t)
    a = 40*pi/180 ;
    fv = cos(a)*(1 + tan(t)^2)/(1 + cos(a)^2*tan(t)^2);
end

