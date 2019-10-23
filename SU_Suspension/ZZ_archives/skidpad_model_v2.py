#%% SKID PAD MODEL
# Ce programme donne une estimation de l'accéleration latérale maximale
# et du temps au skid-pad
# en fonction des paramètres de la voiture et des pneus

#%% TOOLS

from scipy.optimize import fsolve
import numpy as np
from math import pi, sqrt
#from score_skidpad_fsata import score

#%% Input

aero='oui'
tire= '10'

#%% GENERAL DATAS

R_skidpad= 15.25/2   # rayon du skid pad en m
g= 9.81  # accélération de la pesanteur en m/s²
rho = 1.18415 # masse volumique de l'air en kg/m³
m_pilot= 75 # masse du pilot en kg
h_pilot= 0.3 # hauteur de centre de gravité du pilote en m

#%% CAR DATAS

m_car= 200
h_car= 0.3

tf= 1.236     # voie avant (en m)
tr= 1.165    # voie arrière (en m)

w= 1.675    # empattement (en m)
xf = 0.8        # distance entre le train avant et le C.G.
xr = w - xf     # distance entre le train arrière et le C.G.


## Aero

#Les données aéros sont données pour Optimus
S= 1.14 #surface effective pour la déportance en m²
CZ= 2.13 #coefficient de portance
m_packaero= 15
h_aero= 0.4

if aero == 'oui':
    m_aero=m_packaero
    Cz=CZ
else:
    m_aero=0
    Cz=0

m= m_car + m_pilot + m_aero
h= (m_car*h_car + h_pilot*m_pilot + m_aero*h_aero)/m


#%% TIRE DATAS

# Donnees extraites des modeles de GTE

# Le coefficient q est un coeff donné par les testeurs de pneus: ils estiment
# qu'une vraie piste adhère q fois moins que leur banc d'essai (il valait 2/3 au début)

q=0.483

FZ=np.array([0,667.233,444.822,1112.055,222.411,1556.877])

## Pneus 10" pour un slip angle de -1.6°
#FY=np.array([0,620.662,460.466,876.499,274.269,765.804])*2/3
#
## Pneus 13" pour un slip angle de -1.6°
#FY=np.array([0,923.995,714.693,1111.856,420.092,1114.576])*2/3

#Pneus 10" pour un slip angle optimal
FY_10=np.array([0,1519.182,1073.523,2320.305,583.316,1923.809])*q

#Pneus 13" pour un slip angle optimal
FY_13=np.array([0,1783.995,1233.106,2692.902,676.343,3363.065])*q

m_10 = 12.750 # différence de masse entre la configuration 13" et 10"

if tire=='10':
    FY=FY_10
    m = m - m_10
else:
    FY=FY_13
    m = m


Y_poly=np.polyfit(FZ,FY,4)

# force d'adhérence latérale du pneu en fonction de la charge
def Y(z):
    return np.polyval(Y_poly,z)


#%% RESOLUTION

# Le but du programme est de calculer l'accélération latérale amax à laquelle
# l'équilibre de la voiture est rompu, c'est-à-dire l'équilibre en force et en moment.
# La fonction FORCE donne le bilan des forces selon la direction parallèle au rayon du
# virage, amax_force est l'accelération a telle que FORCE(a)=0, ce qui correspond au cas
# ou les 2 trains de la voiture dérapent simultanément.
# La fonction torque donne le bilan des moments autour de l'axe vertical,
# amax_force est l'accelération a telle que TORQUE(a)=0, ce qui correspond au
# cas ou un des trains de la voiture dérape (train avant ou arrière).
# On choisit le minimu de ces deux valeurs et on obtient l'accélération maximale telle
# que la voiture ne dérape pas

def FORCE(a):
    Zfe=(xr/w)*m*g/2 + 1/8*Cz*rho*S*a*(R_skidpad+max(tf,tr)) + (xr/w)*m*a*h/tf
    Zfi=(xr/w)*m*g/2 + 1/8*Cz*rho*S*a*(R_skidpad+max(tf,tr)) - (xr/w)*m*a*h/tf
    Zre=(xf/w)*m*g/2 + 1/8*Cz*rho*S*a*(R_skidpad+max(tf,tr)) + (xf/w)*m*a*h/tr
    Zri=(xf/w)*m*g/2 + 1/8*Cz*rho*S*a*(R_skidpad+max(tf,tr)) - (xf/w)*m*a*h/tr
    return Y(Zfe)+Y(Zfi)+Y(Zre)+Y(Zri) - m*a

def FORCE_f(a):
    Zfe=(xr/w)*m*g/2 + 1/8*Cz*rho*S*a*(R_skidpad+max(tf,tr)) + (xr/w)*m*a*h/tf
    Zfi=(xr/w)*m*g/2 + 1/8*Cz*rho*S*a*(R_skidpad+max(tf,tr)) - (xr/w)*m*a*h/tf
    return Y(Zfe)+Y(Zfi) - (xr/w)*m*a

def FORCE_r(a):
    Zre=(xf/w)*m*g/2 + 1/8*Cz*rho*S*a*(R_skidpad+max(tf,tr)) + (xf/w)*m*a*h/tr
    Zri=(xf/w)*m*g/2 + 1/8*Cz*rho*S*a*(R_skidpad+max(tf,tr)) - (xf/w)*m*a*h/tr
    return Y(Zre)+Y(Zri) - (xf/w)*m*a

amax = min(fsolve(FORCE,g)[0] , fsolve(FORCE_f,g)[0] , fsolve(FORCE_r,g)[0])
acc = amax/g
time=2*pi*sqrt((R_skidpad+max(tf,tr)/2)/amax)

print(fsolve(FORCE,g)[0] , ',' , fsolve(FORCE_f,g)[0] , ',' , fsolve(FORCE_r,g)[0])
print('accélération:',acc,'g')
print('temps au skid pad:',time,'s')
print('score au skid-pad:',score(time))