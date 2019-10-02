#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Tue May 14 09:18:22 2019 @author(s): MSO
mu en fonction de Fz et Vitesse
"""
# glossary file is a global variable loaded in the search_graph library

#%% 1 - search the glossary for available Fz values with a valid query
from search_graph import searchNext, searchCombi, loadGlossary

loadGlossary('glossary/brake.json')

query = [# comment values to remove them from the query
    #test
    "B",  #type
    "8",  #round

    #tire
    "C",  #make
    "B",  #model
    "10", #rim diameter
    "7",  #rim width

    #physics
    "12f", #pressure
    "25",  #speed
    "100", #load (FZ)

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
allFitCoeff = sio.loadmat('dataFit/R8_Brake_Pacejka_89.mat')
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
        c = allFitCoeff[k]['FX'][0][0][0]     
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


# FIGURE
fig, ax = plt.subplots()
fig.suptitle('mean in camber and toe')

# x - label 
ax.set_xlabel("SL(deg)")
ax.xaxis.set_major_locator(MultipleLocator(2))
#ax.xaxis.set_minor_locator(MultipleLocator(1))

# y - label
ax.set_ylabel('Fx(N)')
#ax.yaxis.set_major_locator(MultipleLocator(1000))
#ax.xaxis.set_minor_locator(MultipleLocator(1))

SA = linspace(-12,12) # deg 

for i, f in enumerate(Fz):
    Fy = f89(coeff_Fy[i], SA)
    plt.plot(SA,Fy)
    
#%% 4 - get maximum point for the skidpad model
from scipy.constants import g, lb
Fy_max = []
for i, f in enumerate(Fz):
    m = max(f89(coeff_Fy[i], SA))
    Fy_max.append(m)

# convert to SI metric units
# fitted data is already in SI
Fz = Fz*lb*g #N  


# FIGURE
fig, ax = plt.subplots()
fig.suptitle('max Fx for a given Fz')

# x - label 
ax.set_xlabel("Fz (N)")

# y - label
ax.set_ylabel('Fx(N)')

plt.plot(Fz,Fy_max,'.')
    
