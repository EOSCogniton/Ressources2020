function pt = pt_calcul(event,Tbest,Tteam)
%Calcul saison 2020
%event should be 'Accel', 'Skidpad' or 'AutoX'

if strcmp(event,'Accel')
    if Tteam<Tbest 
        pt = 75;
    else
        Tmax=1.5*Tbest;
        pt=3.5+71.5*(Tmax/Tteam-1)/0.5;
        if pt <3.5
            pt=3.5;
        end
    end
elseif strcmp(event,'Skidpad')
    if Tteam<Tbest 
        pt = 75;
    else
        Tmax=1.25*Tbest;
        pt=3.5+71.5*((Tmax/Tteam)^2-1)/0.5625;
        if pt<3.5
            pt=3.5;
        end
    end
elseif strcmp(event,'AutoX')
    if Tteam<Tbest 
        pt = 100;
    else
        Tmax=1.25*Tbest;
        pt=4.5+95.5*(Tmax/Tteam-1)/0.25;
        if pt <4.5
            pt=4.5;
        end
        end
else
    pt=0;
end
end