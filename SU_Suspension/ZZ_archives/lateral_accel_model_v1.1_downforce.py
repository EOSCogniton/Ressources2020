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

R_skidpad= 15.25/2   # rayon du skid pad en m
g= 9.81  # accélération de la pesanteur en m/s²
m_pilot= 75 # masse du pilot en kg
k_pilot= 0.3 

#%% CAR DATAS


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

#%% RESOLUTION EN FONCTION DE LA DOWNFORCE

# Le but du programme est de calculer l'accélération latérale amax à laquelle
# le train dérape. amax est donc l'accélération à la limite
# du glissement, c'est à dire lorsque la force centrifuge égale la
# somme des forces d'adhérences des pneus intérieur et extérieur.
# La fonction PHI donne la somme totale des forces dans la direction
# latérale (y) en fonction de l'accélération latérale pour les deux trains de
# la voiture (avant et arrière), on recherche donc amax tel que PHI(amax)=0


h= 0.3 # hauteur de centre de gravité en m
t= 1.3 # voie de la voiture en m
m = 205 # masse de la voiture en kg

DF=np.linspace(0,500,100)
ACC=[]
TIME=[]

Aodg=10

for L in DF:
    def FORCE(a):
            Ze = m*g/4 + m*a*h/t/2 + L/2    # charge sur le pneu extérieur
            Zi = m*g/4 - m*a*h/t/2 + L/2    # charge sur le pneu intérieur
            return 2*(Ze*µy(Ze)+Zi*µy(Zi))-m*a
    amax=fsolve(FORCE,Aodg)
    ACC.append(amax/g)
    TIME.append(2*pi*sqrt((R_skidpad+track/2)/amax))
        
#%% PLOT

import matplotlib.pyplot as plt

plt.clf()

plt.subplot(2, 1, 1)
plt.plot(DF, ACC)
plt.title('Accélération latérale et temps au skid pad en fonction de la déportance')
plt.ylabel('Accélération latérale (g)')

plt.subplot(2, 1, 2)
plt.plot(DF, TIME)
plt.xlabel('Déportance (N)')
plt.ylabel('Temps au skid-pad (s)')

plt.show()
