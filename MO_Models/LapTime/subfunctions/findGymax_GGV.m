function [amax,V_turn] = findGymax_GGV(R_turn,GG    V)
options = optimset('Algorithm','Levenberg-Marquardt','Display','off');
fun = @(x) tosolve(x,R_turn,GGV);
V_turn = fsolve(fun,20,options);
amax = V_turn^2/R_turn;

end

function Y = tosolve(X,R_turn,GGV)
% X=V
    V_GGV = GGV(:,4);
    Gy_GGV = GGV(:,3);
    if X<0
        Y=10^5; %on évite les vitesse négatives du solveur
    else
        Y = interp1(V_GGV,Gy_GGV,X,'linear','extrap')-X^2/R_turn;
    end

end
