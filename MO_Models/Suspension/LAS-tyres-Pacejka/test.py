#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Tue May 14 09:18:22 2019 @author(s): MSO
1 - search key to acces the fit coeff in the glossary.
2 - access the fit structure (matlab)
3 - plot the model with f89 function
"""

#%% 1 - search the glossary to get a key
from search_graph import searchUpLow

query = [
    #test
    "C",  #type
    "8",  #round

    #tire
    "C",  #make
    "B",  #model
    "13", #rim diameter
    "7",  #rim width

    #physics
    "12f", #pressure
    "20",  #speed
    "100", #load (FZ)

    #geometry
    "0",  #camber
#        "0"  #toe
]

ans = searchUpLow(query)
print("upper:{}\nlower:{}".format(ans[1],ans[0]))

#%% 2 - read the fit coeffs from the matlab structure
import scipy.io as sio # to read the matlab structure with fit coeff
from numpy import array

allFitCoeff = sio.loadmat('dataFit/R8_Corner_Pacejka_89.mat')
coeff_Fy = array(allFitCoeff[ans[0]]['FY'][0][0][0,:])
coeff_Fy
