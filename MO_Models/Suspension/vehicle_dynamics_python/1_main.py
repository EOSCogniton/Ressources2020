# -*- coding: utf-8 -*-
"""
Created on Fri Oct 11 14:33:24 2019

@author: Martin Kawczynski
"""
import numpy as np
import matplotlib.pyplot as plt
from math import pi
from scipy.optimize import fsolve, fmin

#PHYSICS

g =9.81
rho=1.18

#%% CAR DATAS

m_car=215
m_pilot=75
m_wheel=6.374
m=m_car+m_pilot
ms= m - 4*m_wheel

h_stat=0.35
hrc_f=0.090
hrc_r=0.106

w=1.575
xf=0.785
xr= w-xf

tf=1.254
tr=1.200

MR_f = 1.2
MR_r = 1.18

#%% Aero

#Les données aéros sont données pour Optimus
S= 1.14 #surface effective pour la déportance en m²
Cz= 2.13 #coefficient de portance

af = 0.5
ar = 0.5
#%% RATES

KT = 100000 #tire rate

#spring rates
Ks_f = 43800 # N/m
Ks_r = 52500 # N/m

#wheel rates
Kw_f=Ks_f/(MR_f**2) # N/m
Kw_r=Ks_r/(MR_r**2) # N/m

#ARB rates
RR = (2*pi/180)/(2*g) # rad/(m/s²) # desired roll rate
dh= h_stat - (xr/w)*hrc_f - (xf/w)*hrc_r # m

Qsf=Kw_f*tf**2/2 # Nm/rad
Qsr=Kw_r*tr**2/2 # Nm/rad
Qs=Qsf*Qsr/(Qsf+Qsr) # Nm/rad

Qarb = ms*dh/RR - Qs # Nm/rad

MN = 0.6 # magic number

Qarb_f= MN*Qarb
Qarb_r= (1-MN)*Qarb

#Ride frequencies

Kr_f = Kw_f*KT/(Kw_f+KT)
Kr_r = Kw_r*KT/(Kw_r+KT)

Ff = np.sqrt(Kr_f/m*2*(w/xr))/(2*pi)
Fr = np.sqrt(Kr_r/m*2*(w/xf))/(2*pi)

#%% TIRE

corr=0.483 #scaling factor

def Fy_max(Z):
    # with 65 kPa pression
    poly=np.polyfit([500,800,1100,1400],[1500,2308,2961,3461],3)
    return corr*np.polyval(poly,Z)


def SA_max(Z):
    # with 65 kPa pression
    poly=np.polyfit([500,800,1100,1400],[8.869,7.381,7.083,6.964],4)
    return np.polyval(poly,Z)
