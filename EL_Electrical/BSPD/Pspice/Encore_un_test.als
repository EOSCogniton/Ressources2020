* Schematics Aliases *

.ALIASES
V_V3            V3(+=$N_0001 -=0 )
R_R13           R13(1=$N_0003 2=$N_0002 )
R_R14           R14(1=$N_0005 2=$N_0004 )
X_U6A           U6A(CLRbar=$N_0001 D=10s CLK=$N_0006 PREbar=$N_0001 Q=OUT
+  Qbar=$N_0007 PWR=$G_DPWR GND=$G_DGND )
X_U7A           U7A(A=10s B=500ms Y=$N_0006 PWR=$G_DPWR GND=$G_DGND )
X_U10A          U10A(A=IN B=$N_0008 Y=10s PWR=$G_DPWR GND=$G_DGND )
X_U11A          U11A(A=$N_0009 B=$N_0010 Y=500ms PWR=$G_DPWR GND=$G_DGND )
X_X1            X1(GND=0 TRIGGER=$N_0011 OUTPUT=$N_0008 RESET=IN
+  CONTROL=$N_0012 THRESHOLD=$N_0003 DISCHARGE=$N_0003 VCC=$N_0002 )
C_C8            C8(1=0 2=$N_0013 )
R_R12           R12(1=IN 2=$N_0011 )
C_C4            C4(1=0 2=$N_0011 )
C_C3            C3(1=0 2=$N_0014 )
R_R11           R11(1=$N_0009 2=$N_0014 )
X_U5A           U5A(A=IN Y=$N_0009 PWR=$G_DPWR GND=$G_DGND )
X_X2            X2(GND=0 TRIGGER=$N_0014 OUTPUT=$N_0010 RESET=$N_0015
+  CONTROL=$N_0013 THRESHOLD=$N_0005 DISCHARGE=$N_0005 VCC=$N_0004 )
C_C5            C5(1=0 2=$N_0003 )
C_C7            C7(1=0 2=$N_0005 )
C_C6            C6(1=0 2=$N_0012 )
V_V4            V4(+=$N_0002 -=0 )
V_V5            V5(+=$N_0004 -=0 )
X_U12A          U12A(A=$N_0009 Y=$N_0015 PWR=$G_DPWR GND=$G_DGND )
R_OUT           OUT(1=0 2=OUT )
U_DSTM1          DSTM1(PIN1=IN )
_    _(10s=10s)
_    _(OUT=OUT)
_    _(500ms=500ms)
_    _(IN=IN)
_    _($G_DGND=$G_DGND)
_    _($G_DPWR=$G_DPWR)
.ENDALIASES

