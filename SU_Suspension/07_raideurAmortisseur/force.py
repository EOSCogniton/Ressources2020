#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Sat Nov 23 14:44:23 2019 @author(s): MSO
force amortisseurs avec spring ratio
"""

import numpy as np
import pandas as pd

from matplotlib import gridspec
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

k_s1 = 250 #lbf/in
k_s2 = 300 #lbf/in

k_t = 550 #lbf/in

lbf_in = 9.807/55.997 #N/mm

#%% read data

data = pd.read_csv("bumpAV.csv", header=0, sep=";")
z_wheel = data.values[:,0] #mm
z_spring = data.values[:,7] #mm
print(z_wheel)

#%% raideur

F_0 = k_s1*lbf_in *z_spring
F_1 = (1/k_s1 +1/k_t)**-1*lbf_in *z_spring
F_2 = (1/k_s2 +1/k_t)**-1*lbf_in *z_spring

#%% plot
fig = plt.figure(); pos = gridspec.GridSpec(1, 1)[0]
ax0 = fig.add_subplot(pos)

#fig.suptitle('mesure horizontale')

#ax0.plot(z_wheel, F_0, color='black', label='250 lbf/in, k_t = 0')
ax0.plot(z_wheel, F_1, color='blue', label='250 lbf/in')
ax0.plot(z_wheel, F_2, color='red', label='300 lbf/in')

#legend
ax0.set_ylabel('spring force [N]')
ax0.set_xlabel('wheel travel [mm]')
ax0.legend()
ax0.grid(which='minor')


# x-ticks
ax0.xaxis.set_major_locator(ticker.MultipleLocator(10))
ax0.xaxis.set_minor_locator(ticker.MultipleLocator(1))
# y-ticks
ax0.yaxis.set_major_locator(ticker.MultipleLocator(200))
ax0.yaxis.set_minor_locator(ticker.MultipleLocator(50))


#%%

plt.savefig(filename='force.pdf', format='pdf')