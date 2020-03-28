function [V,Gx,Gy,t] = Backward(V_end,Gy_end,R,D,GGV)
%---Init---
V = zeros(length(R)-1,1);
Gx = zeros(length(R)-1,1);
Gy = zeros(length(R)-1,1);
t = zeros(length(R)-1,1);
V(end) = V_end;
Gx(end) = 0;
Gy(end) = Gy_end;

for i = length(R)-1:-1:2
    %dt Computation
    if Gx(i)==0 && V(i)==0
        disp('voiture arrétée ???')
        dt=0.1;
    elseif Gx(i)==0 && V(i)~=0
        dt = D(i+1)/V(i);
    else
        dt = (-V(i)+sqrt(V(i)^2+2*abs(Gx(i))*D(i+1)))/abs(Gx(i));
    end
    %fill t vector
    t(i:end) = t(i:end) + dt;
    
    % Velocity computation
    V(i-1) = V(i) - dt*Gx(i);
    % find Gy
    if abs(R(i))==150 %if radius saturated
        Gy(i-1) = 0;   
    else %if turn
        Gy(i-1) = abs(V(i-1)^2/R(i)); %Steady state hypothesis    
    end
    %find Gx
    Gx(i-1) = findGxmin(abs(Gy(i-1)),V(i-1),GGV);
    
end
end