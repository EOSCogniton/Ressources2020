
def LONGITUDINAL_LOAD_TRANSFER_f(ax):
    #for one front wheel
    h= h_stat*(w**2/(w**2 +xf*m*ax/Kw_f-xr*m*ax/Kw_r))
    return -m*ax*(h/w)/2

def LONGITUDINAL_LOAD_TRANSFER_r(ax):
    #for one rear wheel
    h= h_stat*(w**2/(w**2 +xf*m*ax/Kw_f-xr*m*ax/Kw_r))
    return m*ax*(h/w)/2

def LATERAL_LOAD_TRANSFER_fe(ay,R_corner):
    return (xr/w)*m*ay*(h_stat/tf)*(Kw_f+2*Qarb_f/tf)/(Kw_f+Kw_r+2*(Qarb_f+Qarb_r)/tf)

def LATERAL_LOAD_TRANSFER_fi(ay,R_corner):
    return -(xr/w)*m*ay*(h_stat/tf)*(Kw_f+2*Qarb_f/tf)/(Kw_f+Kw_r+2*(Qarb_f+Qarb_r)/tf)

def LATERAL_LOAD_TRANSFER_re(ay,R_corner):
    return (xf/w)*m*ay*(h_stat/tr)*(Kw_r+2*Qarb_r/tr)/(Kw_r+Kw_f+2*(Qarb_r+Qarb_f)/tr)

def LATERAL_LOAD_TRANSFER_ri(ay,R_corner):
    return  -(xf/w)*m*ay*(h_stat/tr)*(Kw_r+2*Qarb_r/tr)/(Kw_r+Kw_f+2*(Qarb_r+Qarb_f)/tr)

def LOAD_fe(ax,ay,R_corner):
    return m*g*(xr/w)/2 + 0.5*af*0.5*Cz*rho*S*ay*R_corner + LONGITUDINAL_LOAD_TRANSFER_f(ax) + LATERAL_LOAD_TRANSFER_fe(ay,R_corner)

def LOAD_fi(ax,ay,R_corner):
    return m*g*(xr/w)/2 + 0.5*af*0.5*Cz*rho*S*ay*R_corner + LONGITUDINAL_LOAD_TRANSFER_f(ax) + LATERAL_LOAD_TRANSFER_fi(ay,R_corner)

def LOAD_re(ax,ay,R_corner):
    return m*g*(xf/w)/2 + 0.5*ar*0.5*Cz*rho*S*ay*R_corner + LONGITUDINAL_LOAD_TRANSFER_r(ax) + LATERAL_LOAD_TRANSFER_re(ay,R_corner)

def LOAD_ri(ax,ay,R_corner):
    return m*g*(xf/w)/2 + 0.5*ar*0.5*Cz*rho*S*ay*R_corner + LONGITUDINAL_LOAD_TRANSFER_r(ax) + LATERAL_LOAD_TRANSFER_ri(ay,R_corner)