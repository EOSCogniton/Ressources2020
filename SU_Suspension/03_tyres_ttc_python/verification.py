#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Tue May 14 10:31:48 2019 @author(s): MSO
plot the f89 function using already loaded variablres
"""

from f89 import f89
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator 


# FIGURE
fig, ax = plt.subplots()
fig.suptitle('mean in camber and toe')

# x - label 
ax.set_xlabel("SA")
ax.xaxis.set_major_locator(MultipleLocator(2))
#ax.xaxis.set_minor_locator(MultipleLocator(1))

# y - label
ax.set_ylabel('Fy')
ax.yaxis.set_major_locator(MultipleLocator(500))
#ax.xaxis.set_minor_locator(MultipleLocator(1))


Fy = f89(coeff_Fy, SA)
plt.plot(SA, Fy, '.-g')
plt.plot(SA, f89(coeff_Fy_lo, SA), '.-b')
plt.plot(SA, f89(coeff_Fy_up, SA), '.-r')