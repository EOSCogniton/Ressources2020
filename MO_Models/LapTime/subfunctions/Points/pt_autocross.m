function [pt_auto] = pt_autocross(Tbest,Tteam)
%Calcul saison 2020
Tmax=1.25*Tbest;
pt_auto=4.5+95.5*(Tmax/Tteam-1)/0.25;

if pt_auto <4.5
    pt_auto=4.5;
end

end

