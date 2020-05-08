function GGV = makeGGV(param_file,V_vector)
%This function create the GGV matrix :
% - 1 column : Gx max (Accel) for Gy=0
% - 2 column : Gx min (Break) for Gy=0
% - 3 column : Gy max for Gx=0
% - 4 column : V
% - 5 column : Radius corresponding to V and Gy


%---Speed init--
GGV = zeros(14,5);
GGV(:,4) = V_vector;

%---Acceleration---
addpath('longitudinal');
load(param_file,'type_engine')
if strcmp(type_engine,'Combustion')    
    [V_acc,Gx_acc,~] = Accel(200,param_file);
else
    [V_acc,Gx_acc,~] = Accelelec(200,param_file);
end
GGV(:,1) = interp1(V_acc,Gx_acc,GGV(:,4),'linear','extrap');

%---Breaking---
% load(param_file,'m_t','g','rho','S','Cz','Cx','Long_tire_grip_brake')
% GGV(:,2) = (-(m_t*g+1/2*rho*S*Cz*(GGV(:,4)).^2)*Long_tire_grip_brake-1/2*rho*S*Cx*(GGV(:,4)).^2)/m_t;
[Gx_break,V_break] = Braking(max(V_vector),param_file);
GGV(:,2) = interp1(V_break,Gx_break,GGV(:,4),'linear','extrap');

%---Lateral and Radius---
addpath('lateral')
Gy = zeros(15,1);
V_Gy = zeros(15,1);
i=1;
for r = 1:10:150
    [Gy(i),V_Gy(i)] = findGymax(r,param_file);
    if Gy(i)<1 %Debug
        Gy = Gy(1:i-1);
        V_Gy = V_Gy(1:i-1);
        break
    end
    i=i+1;
end
GGV(:,3) = interp1(V_Gy,Gy,GGV(:,4),'linear','extrap');
r = 1:10:150;
GGV(:,5) = interp1(V_Gy,r,GGV(:,4),'linear','extrap');
end

