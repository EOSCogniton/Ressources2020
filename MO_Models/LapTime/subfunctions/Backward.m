function [V,Gx,Gy,t] = Backward(V_end,Gy_end,R,D,GGV)
%def output
V = zeros(length(R)-1,1);
Gx = zeros(length(R)-1,1);
Gy = zeros(length(R)-1,1);
t = zeros(length(R)-1,1);
%init
V(end) = V_end;
Gx(end) = 0;
Gy(end) = Gy_end;
for i = length(R)-1:-1:2
    if Gx(i)==0 && V(i)==0
        disp('voiture arrétée ???')
        dt=0.1;
    elseif Gx(i)==0 && V(i)~=0
        dt = D(i+1)/V(i);
    else
        dt = (-V(i)+sqrt(V(i)^2+2*Gx(i)*D(i+1)))/Gx(i); 
    end
    t(i:end) = t(i:end) + dt;
    [V_i,Gy_i,Gx_i] = findVmin(V(i),R(i),R(i-1),GGV,dt,Gx(i),Gy(i));
    V(i-1)= V_i;
    Gy(i-1) = Gy_i;
    Gx(i-1) = Gx_i;
end
end