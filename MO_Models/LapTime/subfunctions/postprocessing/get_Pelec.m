function [P,E,c_m,rpm] = get_Pelec(V,Gx,t,paramfile,Lapnb,regen)
%output :   P : Instant battery electrical power (W)
%           E : Total power used during endurance (J)
load(paramfile)
b = coeff_roul*2/D_wheel; % Decalage du point d'appui (m)
c_roul = m_t*g*b; % Resistance au roulement (N.m)
m_rot = J_rot/(D_wheel/2)^2;%masse équivalente des inerties en rotations
m_eq = m_rot + m_t;
eff_cont = 0.97;

c_m = zeros(length(V),1);
P = c_m;
V = V/3.6;
rpm = V/(k_f*D_wheel*pi/60);
for id=1:length(V)
   
   F_trainee = 1/2*rho*V(id)^2*Cx;   
   c_m(id) = ((Gx(id)*m_eq+F_trainee)*(D_wheel/2)+c_roul)/pertes*k_f;
   
   eff_motor = get_efficency(rpm(id),abs(c_m(id)),efficiency);
   P(id) = (rpm(id)*2*pi/60)*c_m(id)/eff_motor/eff_cont;
   if P(id)<0
       P(id)=0.3*P(id)*regen;
       c_m(id) = c_m(id)*regen;
   end
end

E = trapz(t,P)*Lapnb;
end



