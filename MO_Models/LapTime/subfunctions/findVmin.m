function [V,Gy,Gx] = findVmin(Vp,r,rp,GGV,dt,Gxp,Gyp)
%This function take the radius turn of the car at a given moment as input
%and find the speed of the car using the GGV diagramm.
%le p après une variable signifie précédent, le s signifie suivant.
if abs(r)==150
    Gy = 0;
    Gx = interp1(GGV(:,4),GGV(:,2),Vp,'linear','extrap');
    V = Vp - dt*Gxp;
else
        V = Vp - dt*Gxp;
%        ddr = (rp+rs-2*r)/(2*dt);
        Gy = abs(V^2/r);
        Gx = findGxmin(abs(Gy),V,GGV);
%     dr = (r-rp)/dt;
%     ddr = (rp+rs-2*r)/(2*dt);
%     dthetap = Vp/r;
%     options = optimset('Algorithm','Levenberg-Marquardt','Display','off');
%     fun = @(X) tosolve(X,ddr,r,dr,dt,dthetap,GGV);
%     X = fsolve(fun,[Gyp,Gxp,Vp],options);
%     Gy = X(1);
%     Gx = X(2);
%     V = X(3)*r;
end
end

function F = tosolve(X,ddr,r,dr,dt,dthetap,GGV)
%where X(1) = Gy
%      X(2) = Gx
%      X(3) = dtheta
    F(1) = X(1) - ddr-X(3)^2*r;
    F(2) = X(2) - 2*X(3)*dr + (X(3) - dthetap)/dt*r;
    F(3) = X(2) - findGxmin(X(1),X(3)*r,GGV);
end

