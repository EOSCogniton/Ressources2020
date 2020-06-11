function [eff] = get_efficency(rpm,c,efficiency)
eff = 0.8;
for Z =1:efficiency.Znb
    if Z==1
        data = efficiency.Z1;
    elseif Z==2
        data = efficiency.Z2;
    elseif Z==3
        data = efficiency.Z3;
    elseif Z==4
        data = efficiency.Z4;
    elseif Z==5
        data = efficiency.Z5;
    elseif Z==6
        data = efficiency.Z6;
    end
    if inpolygon(rpm,c,data(:,1),data(:,2))
        eff = data(1,3)/100;
        break 
    end
end
end

