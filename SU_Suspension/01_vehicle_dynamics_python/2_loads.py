
def LONGITUDINAL_LOAD_TRANSFER_f(ax):
    #for one front wheel
    h= h_stat*(w**2/(w**2 +xf*m*ax/Kw_f-xr*m*ax/Kw_r))
    return -m*ax*(h/w)/2

def LONGITUDINAL_LOAD_TRANSFER_r(ax):
    #for one rear wheel
    h= h_stat*(w**2/(w**2 +xf*m*ax/Kw_f-xr*m*ax/Kw_r))
    return m*ax*(h/w)/2

def LATERAL_LOAD_TRANSFER_fe(ay,R_corner):
    du = (xr/w)*m_wheel*ay*h_wheel/tf
    ds = (xr/w)*ms*ay*(hrc_f/tf)
    dr = (xr/w)*ms*ay*(ha/tf)*(Kw_f+2*Qarb_f/tf)/(Kw_f+Kw_r+2*(Qarb_f+Qarb_r)/tf)
    return + (du + ds + dr )

def LATERAL_LOAD_TRANSFER_fi(ay,R_corner):
    du = (xr/w)*m_wheel*ay*h_wheel/tf
    ds = (xr/w)*ms*ay*(hrc_f/tf)
    dr = (xr/w)*ms*ay*(ha/tf)*(Kw_f+2*Qarb_f/tf)/(Kw_f+Kw_r+2*(Qarb_f+Qarb_r)/tf)
    return - (du + ds + dr )


def LATERAL_LOAD_TRANSFER_re(ay,R_corner):
    du = (xf/w)*m_wheel*ay*h_wheel/tr
    ds = (xf/w)*ms*ay*(hrc_r/tr)
    dr = (xf/w)*ms*ay*(ha/tr)*(Kw_r+2*Qarb_r/tr)/(Kw_f+Kw_r+2*(Qarb_f+Qarb_r)/tr)
    return + (du + ds +dr)

def LATERAL_LOAD_TRANSFER_ri(ay,R_corner):
    du = (xf/w)*m_wheel*ay*h_wheel/tr
    ds = (xf/w)*ms*ay*(hrc_r/tr)
    dr = (xf/w)*ms*ay*(ha/tr)*(Kw_r+2*Qarb_r/tr)/(Kw_f+Kw_r+2*(Qarb_f+Qarb_r)/tr)
    return - (du + ds +dr)

def LOAD_fe(ax,ay,R_corner):
    return m*g*(xr/w)/2 + 0.5*af*0.5*Cz*rho*S*ay*R_corner + LONGITUDINAL_LOAD_TRANSFER_f(ax) + LATERAL_LOAD_TRANSFER_fe(ay,R_corner)

def LOAD_fi(ax,ay,R_corner):
    return m*g*(xr/w)/2 + 0.5*af*0.5*Cz*rho*S*ay*R_corner + LONGITUDINAL_LOAD_TRANSFER_f(ax) + LATERAL_LOAD_TRANSFER_fi(ay,R_corner)

def LOAD_re(ax,ay,R_corner):
    return m*g*(xf/w)/2 + 0.5*ar*0.5*Cz*rho*S*ay*R_corner + LONGITUDINAL_LOAD_TRANSFER_r(ax) + LATERAL_LOAD_TRANSFER_re(ay,R_corner)

def LOAD_ri(ax,ay,R_corner):
    return m*g*(xf/w)/2 + 0.5*ar*0.5*Cz*rho*S*ay*R_corner + LONGITUDINAL_LOAD_TRANSFER_r(ax) + LATERAL_LOAD_TRANSFER_ri(ay,R_corner)


ay = np.linspace(1,2.5,30)
R_corner=40

plt.clf()

plt.plot(ay,LOAD_fe(0,ay*g,R_corner),label='front exterior load')
plt.plot(ay,LOAD_fi(0,ay*g,R_corner),label='front interior load')
plt.plot(ay,LOAD_re(0,ay*g,R_corner),label='rear exterior load')
plt.plot(ay,LOAD_ri(0,ay*g,R_corner),label='rear interior load')

plt.xlabel('Acceleration (g)')
plt.ylabel('Vertical load (N)')
plt.grid(True)
plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc='lower left', ncol=2, mode="expand", borderaxespad=0.)
