#%% LATERAL ACCELERATION MODEL
# Ce programme donne une estimation de l'accéleration latérale maximale 
# en fonction des paramètres de la voiture et des pneus

#%% TOOLS

from scipy.optimize import fsolve
import numpy as np
from math import pi, sqrt

#%% GENERAL DATAS

# ! ! ! k désigne ici le rapport hauteur du centre de gravité sur voie
# (c'est la grandeur qui compte dans le transfert de charge)

R_skidpad=15.25/2   # rayon du skid pad en m
g=9.81  # accélération de la pesanteur en m/s²
m_pilot=95 # masse du pilot en kg
k_pilot=0.3 
track=1.3 # ordre de grandeur de la voie de la voiture en m


#%% TIRE DATAS

# Donnees extraites des modeles de GTE

# Pour du 13"
FZ=np.array([50,100,150,250,350])*g*0.453592 #0.453592 = conversion lbs en kg
FY=np.array([647.54,1296.98,1918.52,2904.13,3756.80])*0.453592

µ=FY/FZ
µ_poly=np.polyfit(FZ,µ,2)

#coefficient de friction latéral du pneu en fonction de la charge (selon l'axe y)
def µy(z):
    return np.polyval(µ_poly,z)


#%% RESOLUTION

# Le but du programme est de calculer l'accélération latérale amax à laquelle
# le train dérape. amax est donc l'accélération à la limite
# du glissement, c'est à dire lorsque la force centrifuge égale la
# somme des forces d'adhérences des pneus intérieur et extérieur.
# La fonction PHI donne la somme totale des forces dans la direction
# latérale (y) en fonction de l'accélération latérale pour les deux trains de
# la voiture (avant et arrière), on recherche donc amax tel que PHI(amax)=0

MASS=np.linspace(200,250,200)        #liste des masses
K=np.linspace(0.05,0.8,200)             #liste des rapports hauteur C.G. / voie
ACC=np.zeros([len(MASS),len(K)])
TIME=np.zeros([len(MASS),len(K)])

Aodg=10    #une accélération en ordre de grandeur pour initier la fonction fsolve qui trouve le zéro de PHI

for i in range(len(MASS)):
    for j in range(len(K)):
        def PHI(a):
            m = MASS[i]+m_pilot
            k = (MASS[i]/m)*K[j]+(m_pilot/m)*k_pilot
            Ze = m*g/4 + m*a*k/2    # charge sur le pneu extérieur
            Zi = m*g/4 - m*a*k/2    # charge sur le pneu intérieur
            return 2*(Ze*µy(Ze)+Zi*µy(Zi))-m*a
        amax=fsolve(PHI,Aodg)
        ACC[i,j] = amax/g
        TIME[i,j]=2*pi*sqrt((R_skidpad+track/2)/amax)



#%% PLOT

import matplotlib.pyplot as plt

plt.clf()
cont=plt.contour(MASS, K, TIME,30)
plt.clabel(cont)
plt.xlabel('Masse (kg)')
plt.ylabel('Rapport h/t')
plt.show()
