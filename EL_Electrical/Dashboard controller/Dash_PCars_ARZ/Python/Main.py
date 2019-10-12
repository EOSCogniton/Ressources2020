import serial
import time

import carseour
import carseour.definitions


'''
Config()
Serial()
Game()
'''

## Init

def Config():
    
    try:
        global game
        game = carseour.live()
    
        global gamedef
        gamedef=carseour.definitions
    
    except:
        print("Config exception raised")
        time.sleep(20)
        
        Config()
    
    return True

def Serial():
    
    global ArduinoSerial
    
    try :
        ArduinoSerial=serial.Serial(
            "COM9", 
            baudrate=115200, 
            parity=serial.PARITY_ODD,
            stopbits=1,
            bytesize=8)
    
    except:
        
        if ArduinoSerial.is_open:
            return ArduinoSerial.is_open
        
        else:
            return "Serial expection raised : try manually"
        
    return ArduinoSerial.is_open

## MAJ_Variables

'''
ID :

01 : Gear
02 : Speed

05 : RPM
06 : RPM_Bar

11 : Boost
12 : E_Temp
13 : Fuel
14 : T_Temp

20 : Lap
21 : Delta - _ Delta +

30 : Best Lap
31 : Last Lap
32 : Delta Last Lap
33 : Current Lap

40 : Pedal

'''
    
def MAJ_Gear(Gear):
    ''' Gear est un entier '''
    if Gear==-1:
        Gear="R"
    elif Gear==0:
        Gear="N"
    else:
        Gear=str(Gear)
    return "01_"+Gear

def MAJ_RPM():
    ''' RPM_Bar : Led_Bar Shift Mode Led'''
    Led_Bar=game.mRpm/(game.mMaxRPM+1)
    
    Shift=0
    if Led_Bar>=0.95:
        Shift="100"
    else:
        Shift="000"
    
    Led_Bar=min(max(round(100/0.45*(Led_Bar-0.5)),0),99)
    
    Mode=1
    # A modif avec le Gamemode
    
    Led_Strip=0
    if Led_Bar>=16:
        Led_Strip=1
    if Led_Bar>=32:
        Led_Strip=2
    if Led_Bar>=48:
        Led_Strip=3
    if Led_Bar>=64:
        Led_Strip=4
    if Led_Bar>=80:
        Led_Strip=5
    
    RPM_Bar="06_"+str(Led_Bar)+"_"+Shift+"_"+str(Mode)+"_"+str(Led_Strip)
    return RPM_Bar

def MAJ_Boost(Boost):
    '''Boost : Boost_Bar Boost_Val'''
    if Boost<10:
        return "11_0"+str(Boost)+"_"+str(Boost)
    return "11_"+str(min(99,Boost))+"_"+str(Boost)

def MAJ_E_Temp(E_Temp):
    '''E_Temp : E_Temp_Val E_Temp_Bar'''
    if E_Temp<10:
        return "12_  "+str(E_Temp)+"_"+str(E_Temp-50)
    if E_Temp<100:
        return "12_ "+str(E_Temp)+"_"+str(E_Temp-50)
    return "12_"+str(E_Temp)+"_"+str(max(E_Temp-50,0))

def MAJ_Fuel(D_Fuel):
    Fuel_Value=round(game.mFuelCapacity*game.mFuelLevel,1)
    Fuel=str(Fuel_Value)
    if Fuel_Value<10:
        Fuel=" "+str(Fuel_Value)
    if Fuel_Value<1:
        Fuel="  "+str(Fuel_Value)
    if Fuel_Value==0:
        Fuel=" 0.0"
    Fuel="13_"+Fuel
    if (Current_Lap()<2):
        return Fuel+"_--"
    if D_Fuel<0:
        return Fuel+"_PIT"
    return Fuel+"_"+str(D_Fuel)

def T_Temp(Temp):
    if Temp<100:
        return "0"+str(Temp)
    return str(Temp)

def MAJ_T_Temp():
    '''
    Tyre Temp :
    Front_Left : round(game.mTyreTemp[0])
    Front_Right: round(game.mTyreTemp[1])
    Rear_Left  : round(game.mTyreTemp[2])
    Rear_Right : round(game.mTyreTemp[3])
    '''
    FL=T_Temp(round(game.mTyreTemp[0]))
    FR=T_Temp(round(game.mTyreTemp[1]))
    RL=T_Temp(round(game.mTyreTemp[2]))
    RR=T_Temp(round(game.mTyreTemp[3]))
    return "14_"+FL+"_"+FR+"_"+RL+"_"+RR

def Current_Lap():
    N_Lap=0
    for player in game.standing():
        if player["name"]=="arthur.rodriguez":
            N_Lap=player['lap']
    return N_Lap

def MAJ_Current_Lap():
    N_Lap=Current_Lap()
    if N_Lap==game.mLapsInEvent:
        return "20_Final"
    if N_Lap>game.mLapsInEvent:
        return "20_Ended"
    return "20_"+str(N_Lap)+"/"+str(game.mLapsInEvent)

def MAJ_Delta(Time):
    if Time<10:
        Time="0"+str(Time)
    else :
        Time=str(Time)
    while len(Time)<6:
        Time=Time+"0"
    return Time[0:7]

def MAJ_Delta():
    
    # Init
    D_Prev,D_Suiv=0,0
    
    # D_Prev
    if game.mSplitTimeAhead==-1:
        D_Prev="=00.000"
    else:
        D_Prev="-"+MAJ_Delta(round(game.mSplitTimeAhead,3))
    
    # D_Suiv
    if game.mSplitTimeBehind==-1:
        D_Suiv="=00.000"
    else:
        D_Suiv="+"+MAJ_Delta(round(game.mSplitTimeBehind,3))
    
    return "21_"+D_Prev+"_"+D_Suiv

def Time(Time):
    Min=Time//60
    Sec=round(Time-60*Min,3)
    if Sec<10:
        Time=str(int(Min))+":0"+str(Sec)
    else:
        Time=str(int(Min))+":"+str(Sec)
    while len(Time)<8:
        Time=Time+"0"
    return Time[0:9]

def MAJ_Last_Lap_Time(Lap_Invalid):
    
    # Init
    B_Lap=game.mBestLapTime
    L_Lap=game.mLastLapTime # Rouge ou Blanc ? # Fait    
    D_Last=L_Lap-B_Lap # Rouge ou Vert # Fait
        
    # B_Lap
    if B_Lap==-1.0:
        B_Lap="30_2_--:--.---"
    else:
        ''' Best Lap : Color Time
            Violet=0 , Vert=1'''
        B_Lap=Time(B_Lap)
        Color=1
        B_Lap="30_"+str(Color)+"_"+B_Lap
    
    # L_Lap
    if L_Lap==-1.0:
        return (B_Lap, "31_2_--:--.---", "32_2_00:00.000")
    ''' Last Lap : Color Time
        Blanc=2 , Rouge=4'''
    L_Lap=Time(L_Lap)
    Color=2
    if Lap_Invalid==1:
        Color=4
    L_Lap="31_"+str(Color)+"_"+L_Lap
    
    # D_Last
    ''' Last Lap : Color Time
        Vert=1 , Rouge=4'''

    Color=1
    if D_Last==0:
        D_Last="32_2_=0.000"
    else:
        if D_Last>0:
            Color=4
        if D_Last<10:
            D_Last="0"+str(round(abs(D_Last),3))
        else:
            D_Last=str(round(abs(D_Last),3))
        if Color==4:
            D_Last="_+"+D_Last
        else:
            D_Last="_-"+D_Last
        while len(D_Last)<7:
            D_Last=D_Last+"0"
        D_Last="32_"+str(Color)+D_Last
    
    return (B_Lap, L_Lap, D_Last)

def MAJ_Current_Lap_Time(Lap_Invalid):
    ''' Current Lap : Time
        Blanc=2 , Rouge=4'''
    C_Lap=game.mCurrentTime # Rouge ou Blanc ? # Fait
    if C_Lap==-1:
        return "33_2_00:00.000"
    C_Lap=Time(C_Lap)
    Color=2
    if Lap_Invalid==1:
        Color=4
    C_Lap="33_"+str(Color)+"_"+C_Lap
    return C_Lap

def Pedal(Value):
    Value=round(Value)
    if Value<10:
        return "00"+str(Value)
    if Value<100:
        return "0"+str(Value)
    return str(Value)
    

def MAJ_Pedal():
    Disp="40_"
    Disp=Disp+Pedal(100*game.mThrottle)+"_"
    Disp=Disp+Pedal(100*game.mBrake)+"_"
    Disp=Disp+Pedal(100*game.mClutch)+"_"
    Disp=Disp+Pedal(abs(100*game.mSteering))
    return Disp




## Send

def Send(Msg):
    ''' Msg est une chaine de caractères '''
    Msg=Msg+"!"
    
    print(Msg)
    
    ArduinoSerial.write(Msg.encode("utf-8"))
    
    time.sleep(0.008) # 0.02 est OK
    
    return

## Global code

def Init():
    
    # Boost
    Boost=0
    Boost_B=Boost
    Send(MAJ_Boost(Boost))
    
    # E_Temp
    E_Temp=round(game.mWaterTempCelsius)
    E_Temp_B=E_Temp
    Send(MAJ_E_Temp(E_Temp))
    
    # Fuel
    Fuel=game.mFuelLevel
    Fuel_L_B=Fuel
    Fuel_B=MAJ_Fuel(-1)
    Send(Fuel_B)
    
    # T_Temp
    T_Temp=MAJ_T_Temp()
    T_Temp_B=T_Temp
    Send(T_Temp)
    
    # Lap
    Lap=Current_Lap()
    Lap_B=Lap
    Send(MAJ_Current_Lap())
    
    return

def Game():
    
    # Config
    Config()
    Serial()
    
    # Init
    Gear_B,Gear=0,0
    Boost_B,Boost=0,0
    E_Temp_B,E_Temp=0,0
    Fuel_B,Fuel_L_B,Fuel,D_Fuel="13",-1,-1,-1
    T_Temp_B,T_Temp="14","14"
    Lap_B,Lap=-1,-1
    Lap_Invalid=0
    
    Init()
    
    # Code
    while True:        
        # Gear
        Gear=game.mGear
        if Gear!=Gear_B:
            Gear_B=Gear
            Send(MAJ_Gear(Gear))
        
        # Speed
        Send("02_"+str(int(game.mSpeed*3.6)))

        # RPM
        Send("05_"+str(int(game.mRpm)))
        Send(MAJ_RPM())
        
        # Boost
        Boost=round(game.mBoostAmount)
        if Boost!=Boost_B:
            Boost_B=Boost
            Send(MAJ_Boost(Boost))
        
        # E_Temp
        E_Temp=round(game.mWaterTempCelsius)
        if E_Temp!=E_Temp_B:
            E_Temp_B=E_Temp
            Send(MAJ_E_Temp(E_Temp))
        
        # Fuel
        if MAJ_Fuel(D_Fuel)!=Fuel_B:
            Fuel_B=MAJ_Fuel(D_Fuel)
            Send(Fuel_B)
        
        # T_Temp
        T_Temp=MAJ_T_Temp()
        if T_Temp!=T_Temp_B:
            T_Temp_B=T_Temp
            Send(T_Temp)
        
        # Fuel
        # Current_Lap
        # Last_Lap_Time
        if Current_Lap()>Lap_B:
            Fuel=round(game.mFuelCapacity*game.mFuelLevel,1)
            D_Fuel=round(Fuel_L_B-Fuel,1)
            Fuel_L_B=Fuel
            
            Lap_B=Current_Lap()
            Send(MAJ_Current_Lap())
            
            L_L_Time=MAJ_Last_Lap_Time(Lap_Invalid)
            Send(L_L_Time[0])
            Send(L_L_Time[1])
            Send(L_L_Time[2])
        
        # Delta
        Send(MAJ_Delta())
        
        # Current_Lap_Time
        Lap_Invalid=game.mLapInvalidated
        Send(MAJ_Current_Lap_Time(Lap_Invalid))
        
        # Pedal
        Send(MAJ_Pedal())
        
    return
    
# Game()