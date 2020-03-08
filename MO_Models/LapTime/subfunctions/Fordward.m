function [V,Gx,Gy,t] = Fordward(V_start,Gx_start,Gy_start,R,D,GGV)
%def output
V = zeros(length(R),1);
Gx = zeros(length(R),1);
Gy = zeros(length(R),1);
t = zeros(length(R),1);
%init
V(1) = V_start;
Gx(1) = Gx_start;
Gy(1) = Gy_start;

for i = 2:length(R)
    if Gx(i-1)==0 && V(i-1)==0
        disp('voiture arrétée ???')
        dt=0.1;
    elseif Gx(i-1)==0 && V(i-1)~=0
        dt = D(i)/V(i-1);
    else
        dt = (-V(i-1)+sqrt(V(i-1)^2+2*Gx(i-1)*D(i)))/Gx(i-1); 
    end
    if i==2
        t(1) = dt;
    else
        t(i-1) = t(i-2)+dt;
    end
    [V_i,Gy_i,Gx_i] = findVmax(V(i-1),R(i),R(i-1),GGV,dt,Gx(i-1),Gy(i-1));
    V(i)= V_i;
    Gy(i) = Gy_i;
    Gx(i) = Gx_i;
end
V = V(2:end);
Gy = Gy(2:end);
Gx = Gx(2:end);
end