#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Wed Nov  6 21:42:28 2019 @author(s): MSO
durée de vie roulement (S)71910 ACD/P4A par la norme ISO 281:2007
"""
from math import cos,pi

Dw = 6.35 #mm
D2 = 67.12 #mm
d2 = 57.1 #mm
Dpw = (D2 + d2)/2
a = 25 #deg

bm = 1.3

print("Table 2: ", Dw*cos(a)/Dpw)

#%%
fc = 55.5
i = 1
Z= 25

Cr = bm * fc * (i * cos(a))**0.7 *Z**(2/3) * Dw

#%%

Fa = 0.5e3 #N
Fr = 4e3 #N
print("Table 3: ", Fa/Fr)
X = 1
Y = 0

Pr = X*Fr + Y*Fa

#%%

L10 = (Cr/Pr)**3 *1e6 #revs

n_end = 3 *4 * 2 + 3
tot_km = n_end * 22
D_wheel = 470 #mm
tot_rev = tot_km *1e6 / (pi*D_wheel)
print("L10/tot_rev: ", L10/tot_rev)