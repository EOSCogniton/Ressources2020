#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Sat Nov 23 13:30:31 2019 @author(s): MSO
calcule raideur des amortisseurs 
"""

import numpy as np

from matplotlib import gridspec
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

k_s1 = 250 #lbf_in
k_s2 = 300 #lbf_in
k_t = 550 #lbf_in

m = np.linspace(200, 300)
nu_1 = 1/(2*np.pi)*(4/m *(1/k_s1+1/k_t)**-1 *175.13)**(1/2)
nu_2 = 1/(2*np.pi)*(4/m *(1/k_s2+1/k_t)**-1 *175.13)**(1/2)

#%% plot

fig = plt.figure(); pos = gridspec.GridSpec(1, 1)[0]
ax0 = fig.add_subplot(pos)

#fig.suptitle('mesure horizontale')


ax0.plot(m, nu_1, color='blue', label='250 lbf/in')
ax0.plot(m, nu_2, color='red', label='300 lbf/in')

ax0.set_ylabel('frequency [Hz]')
ax0.set_xlabel('suspended mass [kg]')
ax0.legend()
ax0.grid()

#x-ticks
ax0.xaxis.set_major_locator(ticker.MultipleLocator(10))
ax0.xaxis.set_minor_locator(ticker.MultipleLocator(2))
#y-ticks
ax0.yaxis.set_major_locator(ticker.MultipleLocator(0.2))
ax0.yaxis.set_minor_locator(ticker.MultipleLocator(0.1))

#%% save
plt.savefig(filename='freq.pdf', format='pdf')
