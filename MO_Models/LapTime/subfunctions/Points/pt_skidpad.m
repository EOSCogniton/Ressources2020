function [pt_skid] = pt_skidpad(Tbest,Tteam)
%Calcul saison 2020
Tmax=1.25*Tbest;
pt_skid=3.5+71.5*((Tmax/Tteam)^2-1)/0.5625;

if pt_skid<3.5
    pt_skid=3.5;
end

end

