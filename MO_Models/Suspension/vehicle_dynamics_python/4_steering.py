# -*- coding: utf-8 -*-

#%% GRIP


def GRIP_f(ay,R_corner):
    return GRIP_fe(0,ay,R_corner)+GRIP_fi(0,ay,R_corner)

def GRIP_r(ay,R_corner):
    return GRIP_re(0,ay,R_corner)+GRIP_ri(0,ay,R_corner)

def GRIP_total(ay,R_corner):
    return GRIP_f(ay,R_corner) + GRIP_r(ay,R_corner)

#%% RESOLUTION
    

def slip_angles(r):
    def griptotal(a):
        return GRIP_total(a,r) - m*a
    def gripf(a):
        return GRIP_f(a,r) - (xr/w)*m*a
    def gripr(a):
        return GRIP_r(a,r) - (xf/w)*m*a

    amax = min(fsolve(griptotal,g) , fsolve(gripf,g) , fsolve(gripr,g))
    SA_fe=SA_max(LOAD_fe(0,amax,r))
    SA_fi=SA_max(LOAD_fi(0,amax,r))
    return [SA_fe[0],SA_fi[0]]

def steering_angle_e(r):
    q=0.7
    return 0.95*slip_angles(r)[0] + np.arctan(w*q/(r+max(tf,tr)/2))*180/pi

def steering_angle_i(r):
    q=0.7
    return 0.95*slip_angles(r)[1] + np.arctan(w*q/(r-max(tf,tr)/2))*180/pi


radius=np.linspace(3,35,100)
safe= [slip_angles(r)[0] for r in radius]
safi= [slip_angles(r)[1] for r in radius]

thetae=[steering_angle_e(r) for r in radius]
thetai=[steering_angle_i(r) for r in radius]

ackermane=[180/pi*np.arctan((1/(tf/w+1/np.tan(theta*pi/180)))) for theta in thetai]


plt.figure(1)
plt.clf()
plt.plot(radius,safe,label='front exterior tire')
plt.plot(radius,safi,label='front interior tire')
plt.xlabel('Corner radius (m)')
plt.ylabel('Optimum slip angle (°)')
plt.grid(True)
plt.legend()

plt.figure(2)
plt.clf()
plt.plot(radius,thetae,label='front exterior tire')
plt.plot(radius,thetai,label='front interior tire')
plt.xlabel('Corner radius (m)')
plt.ylabel('Steering angle (°)')
plt.grid(True)
plt.legend()

plt.figure(3)
plt.clf()
plt.plot(thetai,thetai,label='parallel')
plt.plot(thetai,ackermane,label='ackerman')
plt.plot(thetai,thetae,label='desired geometry')
plt.legend()
plt.xlabel('Interior steering angle (°)')
plt.ylabel('Exterior steering angle (°)')
plt.grid(True)


plt.show()