function [pt_acc] = pt_accel(Tbest,Tteam)
%Calcul saison 2020
Tmax=1.5*Tbest;
pt_acc=3.5+71.5*(Tmax/Tteam-1)/0.5;

if pt_acc <3.5
    pt_acc=3.5;
end

end

