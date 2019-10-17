# -*- coding: utf-8 -*-
"""
Created on Sun Sep 22 22:20:23 2019

@author: Martin Kawczynski
"""

#%% TOOLS

from scipy.optimize import fsolve, fmin
import numpy as np
from math import pi, sqrt
import matplotlib.pyplot as plt

#%% Input

aero='oui'

#%% GENERAL DATAS

g= 9.81  # accélération de la pesanteur en m/s²
rho = 1.18415 # masse volumique de l'air en kg/m³
m_pilot= 75 # masse du pilot en kg
h_pilot= 0.3 # hauteur de centre de gravité du pilote en m


#%% CAR DATAS

m_car= 200
h_car= 0.3

tf= 1.236     # voie avant (en m)
tr= 1.165    # voie arrière (en m)

w= 1.600    # empattement (en m)
xf = 0.8        # distance entre le train avant et le C.G.
xr = w - xf     # distance entre le train arrière et le C.G.

Kf= 6000 #raideur suspension avant en N/m
Kr= 6600  #raideur suspension arrière en N/m

lf= 56000  #raideur anti-roulis avant
lr= 50000  #raideur anti-roulis arrière

## Aero

#Les données aéros sont données pour Optimus
S= 1.14 #surface effective pour la déportance en m²
CZ= 2.13 #coefficient de portance
m_packaero= 15
h_aero= 0.4

if aero == 'oui':
    m_aero=m_packaero
    Cz=CZ
else:
    m_aero=0
    Cz=0

m= m_car + m_pilot + m_aero
h= (m_car*h_car + h_pilot*m_pilot + m_aero*h_aero)/m

#%% TIRE DATAS
corr=0.483


def Fy_max(Z):
    # pour une pression de 65 kPa
    poly=np.polyfit([500,800,1100,1400],[1500,2308,2961,3461],3)
    return corr*np.polyval(poly,Z)


def SA_max_f(Z):
    # pour une pression de 65 kPa
    poly=np.polyfit([500,800,1100,1400],[8.869,7.381,7.083,6.964],4)
    return np.polyval(poly,Z)


#%% LOAD TRANSFER
    

def NORMAL_LOAD(a,R_corner):
    Zfe=(xr/w)*m*g/2 + 1/8*Cz*rho*S*a*R_corner + (xr/w)*m*a*(h/tf)*(Kf+2*lf/tf)/(Kf+Kr+2*(lf+lr)/tf)
    Zfi=(xr/w)*m*g/2 + 1/8*Cz*rho*S*a*R_corner - (xr/w)*m*a*(h/tf)*(Kf+2*lf/tf)/(Kf+Kr+2*(lf+lr)/tf)
    Zre=(xf/w)*m*g/2 + 1/8*Cz*rho*S*a*R_corner + (xf/w)*m*a*(h/tr)*(Kr+2*lr/tr)/(Kf+Kr+2*(lf+lr)/tr)
    Zri=(xf/w)*m*g/2 + 1/8*Cz*rho*S*a*R_corner - (xf/w)*m*a*(h/tr)*(Kr+2*lr/tr)/(Kf+Kr+2*(lf+lr)/tr)
    return [Zfe,Zfi,Zre,Zri]

#%% GRIP

def GRIP_total(a,R_corner):
    [Zfe,Zfi,Zre,Zri]=NORMAL_LOAD(a,R_corner)
    return Fy_max(Zfe)+Fy_max(Zfi)+Fy_max(Zre)+Fy_max(Zri)

def GRIP_f(a,R_corner):
    [Zfe,Zfi,Zre,Zri]=NORMAL_LOAD(a,R_corner)
    return Fy_max(Zfe)+Fy_max(Zfi)

def GRIP_r(a,R_corner):
    [Zfe,Zfi,Zre,Zri]=NORMAL_LOAD(a,R_corner)
    return Fy_max(Zre)+Fy_max(Zri)

#%% RESOLUTION
    

def slip_angles(r):
    def griptotal(a):
        return GRIP_total(a,r) - m*a
    def gripf(a):
        return GRIP_f(a,r) - (xr/w)*m*a
    def gripr(a):
        return GRIP_r(a,r) - (xf/w)*m*a

    amax = min(fsolve(griptotal,g) , fsolve(gripf,g) , fsolve(gripr,g))
    [Zfe,Zfi,Zre,Zri]=NORMAL_LOAD(amax,r)
    SA_fe=SA_max_f(Zfe)
    SA_fi=SA_max_f(Zfi)
    SA_re=SA_max_f(Zre)
    SA_ri=SA_max_f(Zri)
    return [SA_fe[0],SA_fi[0],SA_re[0],SA_ri[0]]

def steering_angle_e(r):
    q=0.7
    return 0.95*slip_angles(r)[0] + np.arctan(w*q/(r+max(tf,tr)/2))*180/pi

def steering_angle_i(r):
    q=0.7
    return 0.95*slip_angles(r)[1] + np.arctan(w*q/(r-max(tf,tr)/2))*180/pi

radius=np.linspace(3,25,100)
safe= [slip_angles(r)[0] for r in radius]
safi= [slip_angles(r)[1] for r in radius]
sare= [slip_angles(r)[2] for r in radius]
sari= [slip_angles(r)[3] for r in radius]

thetae=[steering_angle_e(r) for r in radius]
thetai=[steering_angle_i(r) for r in radius]

plt.clf()

plt.figure(1)
plt.plot(radius,safe,label='front exterior tire')
plt.plot(radius,safi,label='front interior tire')
plt.xlabel('Corner radius (m)')
plt.ylabel('Optimum slip angle (°)')
plt.grid(True)
plt.legend()

plt.figure(2)
plt.plot(radius,thetae,label='front exterior tire')
plt.plot(radius,thetai,label='front interior tire')
plt.xlabel('Corner radius (m)')
plt.ylabel('Steering angle (°)')
plt.grid(True)
plt.legend()

plt.figure(3)
plt.plot(thetai,thetae)
plt.xlabel('Interior steering angle (°)')
plt.ylabel('Exterior steering angle (°)')
plt.grid(True)


plt.show()