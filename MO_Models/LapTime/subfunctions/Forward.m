function [V,Gx,Gy,t] = Forward(V_start,Gx_start,Gy_start,R,D,GGV)
%---Init---
V = zeros(length(R),1);
Gx = zeros(length(R),1);
Gy = zeros(length(R),1);
t = zeros(length(R),1);
V(1) = V_start;
Gx(1) = Gx_start;
Gy(1) = Gy_start;

%---Loop--
for i = 2:length(R)
    %dt Computation
    if Gx(i-1)==0 && V(i-1)==0
        disp('voiture arrétée ???')
        dt=0.1;
    elseif Gx(i-1)==0 && V(i-1)~=0
        dt = D(i)/V(i-1);
    else
        dt = (-V(i-1)+sqrt(V(i-1)^2+2*Gx(i-1)*D(i)))/Gx(i-1); 
    end
    %fill t vector
    if i==2
        t(1) = dt;
    else
        t(i-1) = t(i-2)+dt;
    end
    % Velocity computation
    V(i) = V(i-1) +dt*Gx(i-1);
    % find Gy
    if abs(R(i))==150 %if radius saturated
        Gy(i) = 0;   
    else %if turn
        Gy(i) = abs(V(i)^2/R(i)); %Steady state hypothesis    
    end
    %find Gx
    Gx(i) = findGxmax(abs(Gy(i)),V(i),GGV);
end
%Remove first value
V = V(2:end);
Gy = Gy(2:end);
Gx = Gx(2:end);
end