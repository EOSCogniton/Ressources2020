*version 9.1 597976086
u 266
U? 7
X? 4
R? 9
V? 7
C? 5
? 6
DSTM? 3
@libraries
@analysis
.DC 0 0 0 0 1 1
+ 0 0 V2
+ 0 4 1
+ 0 5 4
+ 0 6 0.1
.TRAN 1 0 0 0
+0 0ns
+1 3s
.OP 0 
.STMLIB test1.stl
+ D:\EPSA\STUF2019\EL - Electrical\Autre\BSPD\Pspice\test1.stl
@targets
@attributes
@translators
a 0 u 13 0 0 0 hln 100 PCBOARDS=PCB
a 0 u 13 0 0 0 hln 100 PSPICE=PSPICE
a 0 u 13 0 0 0 hln 100 XILINX=XILINX
@setup
unconnectedPins 0
connectViaLabel 0
connectViaLocalLabels 0
NoStim4ExtIFPortsWarnings 1
AutoGenStim4ExtIFPorts 1
@index
pageloc 1 0 5478 
@status
n 0 118:09:06:23:16:52;1538860612 e 
s 0 118:09:06:23:05:14;1538859914 e 
c 118:09:06:23:16:46;1538860606
*page 1 0 970 720 iA
@ports
port 202 GND_ANALOG 510 90 h
port 47 GND_ANALOG 390 230 h
port 246 GND_ANALOG 730 170 h
port 259 GND_ANALOG 550 210 h
port 261 GND_ANALOG 270 180 h
@parts
part 65 c 350 220 v
a 0 u 13 0 0 35 hln 100 VALUE=10n
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C2
a 0 ap 9 0 15 0 hln 100 REFDES=C2
part 226 7474 630 130 h
a 0 sp 11 0 40 80 hln 100 PART=7474
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DIP14
a 0 s 0:13 0 0 0 hln 100 GATE=A
a 0 a 0:13 0 0 0 hln 100 PKGREF=U6
a 0 ap 9 0 40 8 hln 100 REFDES=U6A
part 244 R 730 170 v
a 0 sp 0 0 0 10 hlb 100 PART=R
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 15 35 hln 100 VALUE=500k
a 0 a 0:13 0 0 0 hln 100 PKGREF=R7
a 0 ap 9 0 15 0 hln 100 REFDES=R7
part 201 VDC 510 50 h
a 1 u 13 0 -11 18 hcn 100 DC=5V
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 a 0:13 0 0 0 hln 100 PKGREF=V5
a 1 ap 9 0 24 7 hcn 100 REFDES=V5
part 224 7404 570 150 h
a 0 sp 11 0 40 40 hln 100 PART=7404
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DIP14
a 0 s 0:13 0 0 0 hln 100 GATE=A
a 0 a 0:13 0 0 0 hln 100 PKGREF=U5
a 0 ap 9 0 28 8 hln 100 REFDES=U5A
part 248 R 550 210 v
a 0 sp 0 0 0 10 hlb 100 PART=R
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 15 35 hln 100 VALUE=500k
a 0 a 0:13 0 0 0 hln 100 PKGREF=R8
a 0 ap 9 0 15 0 hln 100 REFDES=R8
part 260 VPULSE 270 140 h
a 1 u 0 0 0 0 hcn 100 V1=0
a 1 u 0 0 0 0 hcn 100 V2=5
a 1 u 0 0 0 0 hcn 100 TD=0.1s
a 1 u 0 0 0 0 hcn 100 TF=0.01s
a 1 u 0 0 0 0 hcn 100 PW=0.3s
a 1 u 0 0 0 0 hcn 100 TR=0.01s
a 0 a 0:13 0 0 0 hln 100 PKGREF=V6
a 1 ap 9 0 20 10 hcn 100 REFDES=V6
part 45 R 390 130 v
a 0 u 13 0 15 35 hln 100 VALUE=1000k
a 0 sp 0 0 0 10 hlb 100 PART=R
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R3
a 0 ap 9 0 15 0 hln 100 REFDES=R3
part 46 c 390 220 v
a 0 u 13 0 5 30 hln 100 VALUE=1m
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C1
a 0 ap 9 0 15 0 hln 100 REFDES=C1
part 44 555D 440 140 h
a 0 sp 11 0 66 100 hlb 100 PART=555D
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DIP8
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=X2
a 1 ap 9 0 70 8 hln 100 REFDES=X2
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
a 1 s 13 0 300 95 hrn 100 PAGENO=1
part 196 nodeMarker 300 140 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 4 22 hlb 100 LABEL=3
part 242 nodeMarker 720 130 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=R7:2
a 0 a 0 0 4 22 hlb 100 LABEL=5
part 193 nodeMarker 550 150 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=U5A:A
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 4 22 hlb 100 LABEL=1
@conn
w 49
a 0 up 0:33 0 0 0 hln 100 V=
s 490 210 490 230 48
s 490 230 390 230 50
a 0 up 33 0 440 229 hct 100 V=
s 390 220 390 230 214
s 350 220 350 230 66
s 350 230 390 230 68
w 64
a 0 up 0:33 0 0 0 hln 100 V=
s 350 160 440 160 218
a 0 up 33 0 350 189 hct 100 V=
s 350 190 350 160 217
w 229
a 0 up 0:33 0 0 0 hln 100 LVL=
s 620 150 630 150 227
a 0 up 33 0 625 149 hct 100 LVL=
w 112
a 0 up 0:33 0 0 0 hln 100 V=
s 440 180 390 180 57
s 390 170 390 180 62
s 440 170 390 170 60
a 0 up 33 0 415 159 hct 100 V=
s 390 130 390 170 52
s 390 180 390 190 59
w 241
a 0 up 0:33 0 0 0 hln 100 LVL=
a 0 up 0:33 0 0 0 hln 100 V=
s 690 130 720 130 240
a 0 up 33 0 715 129 hct 100 LVL=
a 0 up 33 0 710 129 hct 100 V=
s 720 130 730 130 247
w 72
a 0 up 0:33 0 0 0 hln 100 V=
a 0 up 0:33 0 0 0 hln 100 LVL=
s 540 150 550 150 125
a 0 up 33 0 560 149 hct 100 V=
s 550 150 570 150 225
a 0 up 33 0 560 149 hct 100 LVL=
s 550 150 550 170 255
w 262
a 0 up 0:33 0 0 0 hln 100 V=
s 440 140 350 140 113
a 0 up 33 0 350 134 hct 100 V=
s 350 140 300 140 238
s 350 40 350 140 236
s 300 140 270 140 197
s 620 40 350 40 234
s 620 130 620 40 232
s 630 130 620 130 230
w 258
a 0 up 0:33 0 0 0 hln 100 LVL=
a 0 up 0:33 0 0 0 hln 100 V=
s 510 50 450 50 203
s 450 50 450 90 205
s 390 90 420 90 75
a 0 up 33 0 450 84 hct 100 V=
s 450 90 490 90 207
s 490 90 490 110 76
s 440 150 420 150 117
a 0 up 0:33 0 405 159 hct 100 V=
s 420 90 450 90 265
s 420 150 420 90 263
@junction
j 440 180
+ p 44 DISCHARGE
+ w 112
j 440 170
+ p 44 THRESHOLD
+ w 112
j 390 130
+ p 45 1
+ w 112
j 390 170
+ w 112
+ w 112
j 390 90
+ p 45 2
+ w 258
j 490 110
+ p 44 VCC
+ w 258
j 490 210
+ p 44 GND
+ w 49
j 390 230
+ s 47
+ w 49
j 510 90
+ s 202
+ p 201 -
j 510 50
+ p 201 +
+ w 258
j 450 90
+ w 258
+ w 258
j 390 180
+ w 112
+ w 112
j 350 220
+ p 65 1
+ w 49
j 440 160
+ p 44 CONTROL
+ w 64
j 350 190
+ p 65 2
+ w 64
j 620 150
+ p 224 Y
+ w 229
j 630 150
+ p 226 CLK
+ w 229
j 630 130
+ p 226 D
+ w 262
j 440 140
+ p 44 TRIGGER
+ w 262
j 300 140
+ p 196 pin1
+ w 262
j 350 140
+ w 262
+ w 262
j 690 130
+ p 226 Q
+ w 241
j 730 130
+ p 244 2
+ w 241
j 730 170
+ s 246
+ p 244 1
j 720 130
+ p 242 pin1
+ w 241
j 540 150
+ p 44 OUTPUT
+ w 72
j 550 150
+ p 193 pin1
+ w 72
j 570 150
+ p 224 A
+ w 72
j 550 170
+ p 248 2
+ w 72
j 550 210
+ s 259
+ p 248 1
j 270 140
+ p 260 +
+ w 262
j 270 180
+ s 261
+ p 260 -
j 390 190
+ p 46 2
+ w 112
j 390 220
+ p 46 1
+ w 49
j 440 150
+ p 44 RESET
+ w 258
j 420 90
+ w 258
+ w 258
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
