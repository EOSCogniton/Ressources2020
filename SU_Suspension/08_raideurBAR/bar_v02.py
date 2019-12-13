#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Sun Nov 24 01:14:52 2019 @author(s): MSO
raideur barre anti roulis
"""

import numpy as np

from matplotlib import gridspec
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

g = 9.807 #m/s^2
deg = np.pi/180 #rad
lbf_in = g * 1e3 /55.997 #N/m


#%% constants
s_sF = 270e-3 #m
k_sF=43818 #N/m
u_sF=473e-3 #m/rad
s_tF=627e-3 #m
k_tF=90000 #N/m
s_bF=245e-3 #m
u_bF = 6.56e-3*180/np.pi #m/rad
s_sR=340e-3 #N
k_sR=43818 #N/m
u_sR=505e-3 #m/rad
s_tR=600e-3 #m
k_tR=90000 #N/m
s_bR=228e-3 #m
u_bR = 6.8e-3*180/np.pi #m/rad
h_1 = 195e-3 #m

#%%
p_max = 2 *deg #rad
m = np.linspace(250, 350) #kg
a = np.linspace(0.4,0.6)
a_y = 2.2 #g m/s^2

#%% raideurs statiques
k_spF = 2*s_sF*k_sF*u_sF
k_tpF = 2*s_tF**2*k_tF
k_0pF = (1/k_spF+1/k_tpF)**-1

k_spR = 2*s_sR*k_sR*u_sR
k_tpR = 2*s_tR**2*k_tR
k_0pR = (1/k_spR+1/k_tpR)**-1

#%% calculus

M, A = np.meshgrid(m, a)

k_p =  M*g * h_1 * (a_y/(p_max)+1)

k_bpF = A * k_p #Nm/rad
k_bF = k_bpF/(2*s_bF*u_bF)

k_bpR = (1-A) *k_p 
k_bR = k_bpR/(2*s_bR*u_bR)

#%% plot A FAIRE
fig = plt.figure(); pos = gridspec.GridSpec(1, 1)[0]
ax0 = fig.add_subplot(pos)

fig.suptitle('a_y = 2.2 g, phi_max = 2 deg, h_1 = 195 mm \nbar stiffness in N/mm (front is red)')

#ax0.plot(m, fk_p(a), label='{} g'.format(str(a)))

cs = ax0.contour(m, a, k_bF*1e-3, levels=np.arange(0,300,10) , colors='r')
ax0.clabel(cs , inline=1, fmt='%1.0f')

cs = ax0.contour(m, a, k_bR*1e-3, levels = np.arange(0,300,10), colors='b')
ax0.clabel(cs , inline=1, fmt='%1.2f')


ax0.set_xlabel('total mass [kg]')
ax0.set_ylabel('% front roll stiffness')
ax0.legend()
ax0.grid(which="minor")

#x-ticks
ax0.xaxis.set_major_locator(ticker.MultipleLocator(10))
ax0.xaxis.set_minor_locator(ticker.MultipleLocator(5))
#y-ticks
ax0.yaxis.set_major_locator(ticker.MultipleLocator(10e-2))
ax0.yaxis.set_minor_locator(ticker.MultipleLocator(2e-2))

#%% save
plt.savefig(filename='bar_v02.pdf', format='pdf')
