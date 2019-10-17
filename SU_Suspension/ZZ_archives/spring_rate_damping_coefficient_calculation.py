# -*- coding: utf-8 -*-
"""
Created on Sun Sep 29 20:29:51 2019

@author: Martin Kawczynski
"""
#%% TOOLS

import numpy as np
import matplotlib.pyplot as plt
from math import pi

g=9.81
#%% CAR DATAS

m_car=212
m_pilot=75
m_wheel=6.374
m=m_car+m_pilot

h_stat=0.35

w=1.600
xf=0.800
xr= w-xf

ms_f= (m_car + m_pilot - 4*m_wheel)*(xr/w)/2
ms_r= (m_car + m_pilot - 4*m_wheel)*(xf/w)/2

fs_f=2.00
fs_r=2.20

Kw_f= 4*pi**2*fs_f**2*ms_f
Kw_r= 4*pi**2*fs_r**2*ms_r

#%% LOW SPEED GRAPH

vl=[0.050,0.100,0.150,0.200]
Fl=[100,240,375,480]

Cl = np.polyfit(vl,Fl,1)[0]

#%% HIGH SPEED GRAPH

vh=[0.075,0.150]
Fh=[300,350]

Ch = np.polyfit(vh,Fh,1)[0]

#%% RESOLUTION MOTION RATIO

xi=0.69

C0_f=4*pi*ms_f*fs_f
C0_r=4*pi*ms_r*fs_r

MR_f = (Cl/(C0_f*xi))**(1/2)
MR_r = (Cl/(C0_r*xi))**(1/2)

#%% SPRINGRATES

Ks_f=MR_f**2*Kw_f
Ks_r=MR_r**2*Kw_r

print('front spring rate =',Ks_f)
print('rear spring rate =',Ks_r)

def LOAD_TRANSFER(ax):
    #pour une roue
    h= h_stat*(w**2/(w**2 +xf*m*ax/Kw_f-xr*m*ax/Kw_r))
    Zr= m*g*(xf/w)/2 + m*ax*(h/w)/2
    Zf= m*g*(xr/w)/2 - m*ax*(h/w)/2
    return [Zf,Zr]

def WHEEL_DISPLACEMENT(ax):
    df=LOAD_TRANSFER(ax)[0]/Kw_f
    dr=LOAD_TRANSFER(ax)[1]/Kw_r
    return [df,dr]

def SPRING_DISPLACEMENT_f(ax):
    return WHEEL_DISPLACEMENT(ax)[0]/MR_f

def SPRING_DISPLACEMENT_r(ax):
    return WHEEL_DISPLACEMENT(ax)[1]/MR_r



#%% PLOT

A=np.linspace(-3,2,50)
Ds_f=(SPRING_DISPLACEMENT_f(A*g)-SPRING_DISPLACEMENT_f(0))*1000
Ds_r=(SPRING_DISPLACEMENT_r(A*g)-SPRING_DISPLACEMENT_r(0))*1000

plt.clf()
plt.plot(A,Ds_f,label='Front spring displacement')
plt.plot(A,Ds_r,label='Rear spring displacement')
plt.xlabel('Acceleration (g)')
plt.ylabel('Spring displacement (mm)')
plt.grid(True)
plt.legend()
plt.show()