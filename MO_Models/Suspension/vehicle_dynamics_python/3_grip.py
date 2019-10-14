
def GRIP_fe(ax,ay,R_corner):
    return Fy_max(LOAD_fe(ax,ay,R_corner))

def GRIP_fi(ax,ay,R_corner):
    return Fy_max(LOAD_fi(ax,ay,R_corner))

def GRIP_re(ax,ay,R_corner):
    return Fy_max(LOAD_re(ax,ay,R_corner))

def GRIP_ri(ax,ay,R_corner):
    return Fy_max(LOAD_ri(ax,ay,R_corner))


def GRIP_f(ay,R_corner):
    return GRIP_fe(0,ay,R_corner)+GRIP_fi(0,ay,R_corner)

def GRIP_r(ay,R_corner):
    return GRIP_re(0,ay,R_corner)+GRIP_ri(0,ay,R_corner)

def GRIP_total(ay,R_corner):
    return GRIP_f(ay,R_corner) + GRIP_r(ay,R_corner)

#%% PLOT
    


R_corner = 0

ay=np.linspace(1,2.5,50)
r=np.linspace(0,50,50)
AY, R = np.meshgrid(ay, r)

Ff = GRIP_fe(0,AY*g,R)+GRIP_fi(0,AY*g,R)
Fr = GRIP_re(0,AY*g,R)+GRIP_ri(0,AY*g,R)

Ffreq = m*AY*g*(xr/w)
Frreq = m*AY*g*(xf/w)

gripf=GRIP_fe(0,ay*g,R_corner)+GRIP_fi(0,ay*g,R_corner)
gripr=GRIP_re(0,ay*g,R_corner)+GRIP_ri(0,ay*g,R_corner)

#grip = gripr + gripf


plt.figure(1)

plt.clf()

plt.plot(ay,gripf,label='front Fy',color='blue',linestyle='solid')
plt.plot(ay,m*ay*g*(xr/w),label='required front Fy',color='blue',linestyle='dashed')

plt.plot(ay,gripr,label='rear Fy',color='red',linestyle='solid')
plt.plot(ay,m*ay*g*(xf/w),label='required rear Fy',color='red',linestyle='dashed')


plt.legend(loc='upper left',borderaxespad=0.1)
plt.xlabel('Lateral acceleration (g)')
plt.ylabel('Lateral force (N)')
plt.grid(True)


plt.figure(2)

plt.clf()

plt.plot(ay,LOAD_fe(0,ay*g,R_corner)/g,label='front exterior load')
plt.plot(ay,LOAD_fi(0,ay*g,R_corner)/g,label='front interior load')
plt.plot(ay,LOAD_re(0,ay*g,R_corner)/g,label='rear exterior load')
plt.plot(ay,LOAD_ri(0,ay*g,R_corner)/g,label='rear interior load')

plt.xlabel('Acceleration (g)')
plt.ylabel('Vertical load (kg)')
plt.grid(True)
plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc='lower left', ncol=2, mode="expand", borderaxespad=0.)

plt.figure(3)

plt.clf()

plt.plot(ay,GRIP_fe(0,ay*g,R_corner)/g,label='front exterior grip')
plt.plot(ay,GRIP_fi(0,ay*g,R_corner)/g,label='front interior grip')
plt.plot(ay,GRIP_re(0,ay*g,R_corner)/g,label='rear exterior grip')
plt.plot(ay,GRIP_ri(0,ay*g,R_corner)/g,label='rear interior grip')

plt.xlabel('Acceleration (g)')
plt.ylabel('Vertical load (kg)')
plt.grid(True)
plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc='lower left', ncol=2, mode="expand", borderaxespad=0.)


plt.figure(4)

plt.clf()
cont=plt.contour(AY, R, Ff-Ffreq,10)
plt.clabel(cont)
plt.xlabel('Lateral acceleration (g)')
plt.ylabel('Corner radius (m)')

plt.figure(5)

plt.clf()
cont=plt.contour(AY, R, Fr-Frreq,10)
plt.clabel(cont)
plt.xlabel('Lateral acceleration (g)')
plt.ylabel('Corner radius (m)')

plt.figure(6)

plt.clf()
cont=plt.contour(AY, R, Fr+Ff-Frreq-Ffreq,10)
plt.clabel(cont)
plt.xlabel('Lateral acceleration (g)')
plt.ylabel('Corner radius (m)')
plt.grid(True)

plt.show()
