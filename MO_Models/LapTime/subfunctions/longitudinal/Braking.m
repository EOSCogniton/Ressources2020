function [Gxf,V,Fsat] = Braking(Vinit,param_file)

%---Parameters---
dt=0.01; %pas de calcul de la simu
load(param_file,'m_t','xr','xf', 'h', 'W' ,'rho','Cx', 'Cz', 'Cz_rep','D_wheel','Long_tire_grip_brake','x_brf','S')
x_brf = 0.75;
%---Init---
Gx = 0; 
V = Vinit+20/3.6;
Fsat = [];

while V(end)>-5
    %--Charges--
    [Z_r,Z_f] = charge_long(Gx(end),V(end), m_t,xr,xf, h, W ,rho, Cz, Cz_rep,S);
    
    %--Couple max transmissible--
    C_fmax = Long_tire_grip_brake*Z_f*(D_wheel/2);
    C_rmax = Long_tire_grip_brake*Z_r*(D_wheel/2);
    
    %Qui glisse en premier ?
    if C_fmax/x_brf  > C_rmax/(1-x_brf )
        C_r = C_rmax;
        C_f = C_rmax/(1-x_brf )*x_brf ;
        Fsat = [Fsat 0];
    else
        Fsat = [Fsat 1];
        C_f = C_fmax;
        C_r = C_fmax/x_brf *(1-x_brf );
    end
    
    %--Accel--
    Gx_i = -((C_r + C_f)/(D_wheel/2)+1/2*Cx*rho*S* V(end)^2)/m_t;
    Gx = [Gx Gx_i];
    
    %--Vitesse--
    V = [V V(end)+Gx_i*dt];
end

%Filtrage des données (utile en cas d'instabilité)
Gxf = movmean(Gx,10);

idx = (V>0 & V<=Vinit);
V = V(idx);
Gxf = Gxf(idx);

end

