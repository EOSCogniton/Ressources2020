#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Tue May 14 09:18:22 2019 @author(s): MSO
1 - search the glossary for available Fz values with a valid query
2 - calculate the model mean in camber and toe
3 - plot and verify data
4 - get points for the skidpad model
"""
# glossary file is a global variable loaded in the search_graph library
from search_graph import loadGlossary
loadGlossary('glossary/corner.json')

#%% 1 - search the glossary for available Fz values with a valid query
from search_graph import searchNext, searchCombi

query = [# comment values to remove them from the query
    #test
    "C",  #type
    "8",  #round

    #tire
    "H",  #make
    "H",  #model
    "10", #rim diameter
    "7",  #rim width

    #physics
    "12f", #pressure
    "45",  #speed
#    "100", #load (FZ)

    #geometry
#    "0",  #camber
#    "0"   #toe
]

ans = searchNext(query)
print(ans)

#%% 2 - calculate the coeffs mean in camber and toe
import scipy.io as sio #to read the matlab structure with fit coeff
from numpy import array, empty, append, vstack, mean

# load the data coeffs
allFitCoeff = sio.loadmat('dataFit/R8_Corner_Pacejka_89.mat')
# get available Fx from fitted test data
availableFz = searchNext(query)
# result variables
Fz = array([])
coeff_Fy = empty(6)
# loop to calculate the mean
for fz in availableFz:
    # get all the combinations keys
    keys = searchCombi([*query,fz])
    # store the Fz
    Fz = append(Fz, float(fz))  # imperial system
    # get the associated coefficients
    coeff = empty(6)
    for k in keys:
        c = allFitCoeff[k]['FY'][0][0][0]     
        coeff = vstack((coeff,c))
    # remove the zero line
    coeff = coeff[1:]
    # mean the coeffs 
    fy = array([mean(coeff[:,i]) for i in range(6)])
    # store the coeffs for giver Fz
    coeff_Fy = vstack((coeff_Fy,fy))

# remove zero line
coeff_Fy  = coeff_Fy[1:]

#%% 3 - plot and verify data
from f89 import f89# pacejka '89 model function
from numpy import linspace
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator 
from scipy.constants import g, lb, mph, kmh


# FIGURE
fig, ax = plt.subplots()

# tire information in the title
title = "test: {}{}, tire:{}{}{}{}, pression:{} psi, speed:{:.1f} km/h\
        \n mean in camber and toe".format(
        query[0], query[1],  #test
        *query[2:6],  #tire
        query[6],  # pression
        float(query[7])*mph/kmh,  # speed
        )
fig.suptitle(title)

# x - label 
ax.set_xlabel("SA (deg)")
ax.xaxis.set_major_locator(MultipleLocator(2))
#ax.xaxis.set_minor_locator(MultipleLocator(1))

# y - label
ax.set_ylabel('Fy (N)')
ax.yaxis.set_major_locator(MultipleLocator(500))
#ax.xaxis.set_minor_locator(MultipleLocator(1))

SA = linspace(-12,12) # deg 

for i, f in enumerate(Fz):
    Fy = f89(coeff_Fy[i], SA)
    ax.plot(SA,Fy, label="Fz:{:.1f} N".format(f*lb*g))

ax.legend()
    
#%% 4 - get points for the skidpad model
from scipy.constants import g, lb
Fy_max = []
Fy_SA = []
sa = -0.9 #deg
for i, f in enumerate(Fz):
    # max points
    m = max(f89(coeff_Fy[i], SA))
    Fy_max.append(m)
    # for a given SA
    n = f89(coeff_Fy[i], sa)
    Fy_SA.append(n)

# convert to SI metric units
# fitted data is already in SI
Fz = Fz*lb*g #N  

# FIGURE
fig, ax = plt.subplots()
fig.suptitle('Fy for a given Fz')

# x - label 
ax.set_xlabel("Fz (N)")
#ax.xaxis.set_major_locator(MultipleLocator(500))

# y - label
ax.set_ylabel('Fy(N)')
#ax.yaxis.set_major_locator(MultipleLocator(500))

# max plots
ax.plot(Fz,Fy_max,'.', label="max Fy for any SA")
ax.plot(Fz,Fy_SA,'.', label="SA:{} deg".format(sa))

ax.legend()

print("max friction coefficient:{:.2f}".format(max(Fy_SA/Fz)))
