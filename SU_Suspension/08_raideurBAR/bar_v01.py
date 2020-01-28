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
p_max = 2 *deg #rad
m = np.linspace(200, 350) #kg
h_1 = 195e-3 #m
a_y = 2.2 #g m/s^2

# repartition
a = np.linspace(30e-2, 70e-2)

# tire
k_t = 550 *lbf_in #N/m
t_F = 1240e-3 #m
t_R = 1200e-3 #m

# shock front
k_sF = 250 *lbf_in #N/m
s_F = 440e-3 #m

# shock rear
k_sR = 250 *lbf_in #N/m
s_R = 200e-3 #m

# ARB front
#k_bF = np.linspace(50e3, 170e3) #N/m
s_bF = 440e-3 #m

# ARB rear
#k_bR = np.linspace(150e3, 170e3) #N/m
s_bR = 500e-3 #m

#%% calculus

k_0F = (2/(k_sF*s_F**2) + 2/(k_t*t_F**2))**-1
k_0R = (2/(k_sR*s_R**2) + 2/(k_t*t_R**2))**-1

M, A = np.meshgrid(m, a)

k_p =  M*g * h_1 * (a_y/(p_max)+1)

k_bF = 2/s_bF**2 * (A*k_p - k_0F)

k_bR = 2/s_bR**2 * ((1-A)*k_p - k_0R)

#%% plot
fig = plt.figure(); pos = gridspec.GridSpec(1, 1)[0]
ax0 = fig.add_subplot(pos)

fig.suptitle('a_y = 2.2 g, phi_max = 2 deg, h_1 = 195 mm, bar stiffness in N/mm (front is red)')

#ax0.plot(m, fk_p(a), label='{} g'.format(str(a)))

cs = ax0.contour(m, a, k_bF*1e-3, levels=np.arange(0,300,5) , colors='r')
ax0.clabel(cs , inline=1, fmt='%1.0f')

cs = ax0.contour(m, a, k_bR*1e-3, levels = np.arange(0,300,5), colors='b')
ax0.clabel(cs , inline=1, fmt='%1.2f')


ax0.set_xlabel('total mass [kg]')
ax0.set_ylabel('% front roll stiffness')
ax0.legend()
ax0.grid(which="minor")

#x-ticks
ax0.xaxis.set_major_locator(ticker.MultipleLocator(10))
ax0.xaxis.set_minor_locator(ticker.MultipleLocator(2))
#y-ticks
ax0.yaxis.set_major_locator(ticker.MultipleLocator(5e-2))
ax0.yaxis.set_minor_locator(ticker.MultipleLocator(1e-2))

#%% save
plt.savefig(filename='bar.pdf', format='pdf')
