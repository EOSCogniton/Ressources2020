function plot_efficiency(efficiency)

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
    plot([data(:,1);data(1,1)],[data(:,2);data(1,2)],"DisplayName",cat(2,num2str(data(1,3)),'%'))
    hold on
end
legend
title("efficiency map")
xlabel(" Motor speed (rpm)")
ylabel("Motor Torque (N.m)")
end


