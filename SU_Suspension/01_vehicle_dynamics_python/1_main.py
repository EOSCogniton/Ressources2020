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

g =9.81 # gravité
rho=1.18 # masse volumique air

#%% CAR DATAS
#masses
m_car=215
m_pilot=75
m_wheel=6.374
m=m_car+m_pilot
ms= m - 4*m_wheel #masse suspendue

h_wheel = 0.235 #hauteur de la masse non suspendue ~ rayon du pneu
h_stat=0.35 #hauteur du centre gravité
hrc_f=0.100 #hauteur du centre de roulis avant
hrc_r=0.100 #hauteur du centre de roulis arrière

w=1.575 #wheelbase
xf=w/2 #distance centre de gravité jusqua train avant
xr= w-xf

#voies
tf=1.254
tr=1.200

#motion ratio
MR_f = 1.2
MR_r = 1.18

l = 0.205 #largeur du pneu

#%% Aero

#Les données aéros sont données pour Optimus
S= 1.14 #surface effective pour la déportance en m²
Cz= 2.13 #coefficient de portance

#répartition aéro
af = 0.5
ar = 0.5

#%% RATES

phi = np.arctan(2*hrc_f/(2*l+tf))-np.arctan(2*(hrc_f-0.05)/(2*l+tf)) #angle de roulis max


KT = 100000 #tire rate

#spring rates
Ks_f = 43800 # N/m
Ks_r = 52500 # N/m

#wheel rates
Kw_f=Ks_f/(MR_f**2) # N/m
Kw_r=Ks_r/(MR_r**2) # N/m

#ARB rates
RR = (1*pi/180)/(2.2*g) # rad/(m/s²) # desired roll rate

cs = 1.5 #coeff de sécurité pour le roulis

RR=RR/cs

dh= h_stat - (xr/w)*hrc_f - (xf/w)*hrc_r # m
ha = np.cos(np.arctan((hrc_r-hrc_f)/w))*dh

Qsf=Kw_f*tf**2/2 # Nm/rad #raideur en roulis des ressors avant
Qsr=Kw_r*tr**2/2 # Nm/rad #raideur en roulis des ressors arrière
Qs=Qsf*Qsr/(Qsf+Qsr) # Nm/rad

Qarb = ms*ha/RR - Qs # Nm/rad

MN = 0.55 # magic number répartition de raideur anti-roulis à l'avant

Qarb_f= MN*Qarb
Qarb_r= (1-MN)*Qarb

#Ride frequencies

Kr_f = Kw_f*KT/(Kw_f+KT)
Kr_r = Kw_r*KT/(Kw_r+KT)

Ff = np.sqrt(Kr_f/m*2*(w/xr))/(2*pi)
Fr = np.sqrt(Kr_r/m*2*(w/xf))/(2*pi)

#%% TIRE

corr=0.58 #scaling factor

def Fy_max(Z):
    # with 65 kPa pression
    poly=np.polyfit([0,500,800,1100,1400],[0,1500,2308,2961,3461],3)
    return corr*np.polyval(poly,Z)


def SA_max(Z):
    # with 65 kPa pression
    poly=np.polyfit([500,800,1100,1400],[8.869,7.381,7.083,6.964],4)
    return np.polyval(poly,Z)
