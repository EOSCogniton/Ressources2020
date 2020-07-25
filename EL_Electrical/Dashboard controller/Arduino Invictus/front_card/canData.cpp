#include <FlexCAN.h>

FlexCAN CANbus(500000);

//definition of a object which is specific to the library
static CAN_message_t msg,stmsg;


// All the values that have to be multiplied
float Lambda, Kph, Volts, FuelConHR, AdvanceDeg, Inject, FuelConKM, CamAdv, CamTarg, CamPWM, Cam2Adv, Cam2Targ, Cam2PWM;

int H_PIN, N_PIN, L_PIN, C_PIN, W_PIN, G_PIN;
int T_Time = 1000;

void setup() {
  
  CANbus.begin();
  
  }

void receive() {
  
  CANbus.read(msg);
  switch(msg.id){    

    case 0x1008:
    
      logRaceCap = msg.buf[0];
      break;
      
    case 0x1002:
      
      Gear = msg.buf[0];
      ErrMotored = msg.buf[1];
      break;
      
    case 0x2000:
    
      Rpm = msg.buf[0]+256*msg.buf[1];
      TPS = msg.buf[2]+256*msg.buf[3];
      W_Temp = msg.buf[4]+256*msg.buf[5];
      A_Temp = msg.buf[6]+256*msg.buf[7];
      break;
      
      
    case 0x2001:

      MAPKpa = msg.buf[0]+256*msg.buf[1];
      Lambda = msg.buf[2]+256*msg.buf[3];
      Kph = msg.buf[4]+256*msg.buf[5];
      O_Press = msg.buf[6]+256*msg.buf[7];
      
      Lambda *= 0.001;
      Kph *= 0.1;
      break;
            
    
    case 0x2002:

      F_Press = msg.buf[0]+256*msg.buf[1];
      O_Temp = msg.buf[2]+256*msg.buf[3];
      Volts = msg.buf[4]+256*msg.buf[5];
      FuelConHR = msg.buf[6]+256*msg.buf[7];
      
      Volts *= 0.1;
      FuelConHR *= 0.1;
      break;
           
    case 0x2003:

      Gear = msg.buf[0]+256*msg.buf[1];
      AdvanceDeg = msg.buf[2]+256*msg.buf[3];
      Inject = msg.buf[4]+256*msg.buf[5];
      FuelConKM = msg.buf[6]+256*msg.buf[7];
      
      AdvanceDeg *= 0.1;
      Inject *= 0.01;
      FuelConKM *= 0.1;      
      break;
          
    case 0x2004:

      Ana1 = msg.buf[0]+256*msg.buf[1];
      Ana2 = msg.buf[2]+256*msg.buf[3];
      Ana3 = msg.buf[4]+256*msg.buf[5];
      CamAdv = msg.buf[6]+256*msg.buf[7];

      CamAdv *= 0.1;
      break;
          
    case 0x2005:

      CamTarg = msg.buf[0]+256*msg.buf[1];
      CamPWM = msg.buf[2]+256*msg.buf[3];
      CrankErr = msg.buf[4]+256*msg.buf[5];
      CamErr = msg.buf[6]+256*msg.buf[7];

      CamTarg *= 0.1;
      CamPWM *= 0.1;
      break;
          
    case 0x2006:

      Cam2Adv = msg.buf[0]+256*msg.buf[1];
      Cam2Targ = msg.buf[2]+256*msg.buf[3];
      Cam2PWM = msg.buf[4]+256*msg.buf[5];
      Ext5v = msg.buf[6]+256*msg.buf[7];

      Cam2Adv *= 0.1;
      Cam2Targ *= 0.1;
      Cam2PWM *= 0.1;
      break;
      
    case 0x2007:

      InjDutyCycle = msg.buf[0]+256*msg.buf[1];
      LambdaPIDTarg = msg.buf[2]+256*msg.buf[3];
      LambdaPIDAdj = msg.buf[4]+256*msg.buf[5];  
      ECU = msg.buf[6]+256*msg.buf[7] 
      break;     
    }
 
  }

void sendData() {
  Switch_H=digitalRead(Homing_button);
  Switch_N=digitalRead(Neutre_button);
  Switch_L=digitalRead(Log_switch);
  Switch_C=digitalRead(LaunchControl_button);
  Switch_W=digitalRead(WD_Switch);


  byte Modif[8]={0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  byte Null[8]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  tmillis=millis();
  if(tmillis>(T_D_Millis+T_Time)){ // Envoie discret de période T_Time

    T_D_Millis=millis();
  
    if(Switch_H==0){
        stmsg.id = 0x1001;
        stmsg.buf = Null;
    }
    if(Switch_H==1){
        stmsg.id = 0x1001;
        stmsg.buf = Modif;
    }

    if(Switch_N==0){
        stmsg.id = 0x1002;
        stmsg.buf = Null;
    }
    if(Switch_N==1){
        stmsg.id = 0x1002;
        stmsg.buf = Modif;
    }
  
    if(Switch_L==0){
        stmsg.id = 0x1003;
        stmsg.buf = Null;
    }
    if(Switch_L==1){
        stmsg.id = 0x1003;
        stmsg.buf = Modif;
    }

    if(Switch_C==0){
        stmsg.id = 0x1004;
        stmsg.buf = Null;
    }
    if(Switch_C==1){
        stmsg.id = 0x1004;
        stmsg.buf = Modif;
    }
  
    if(Switch_W==0){
        stmsg.id = 0x1005;
        stmsg.buf = Null;
    }
    if(Switch_W==1){
        stmsg.id = 0x1005;
        stmsg.buf = Modif;
    }

    if(Switch_G==0){
        stmsg.id = 0x1006;
        stmsg.buf = Null;
    }
    if(Switch_G==1){
        stmsg.id = 0x1006;
        stmsg.buf = Modif;
    }
  }
}  
