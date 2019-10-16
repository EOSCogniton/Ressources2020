/***************************************************************
  @file: nextion_communication
  @author: Raphaël Viudès(RVS)
     for Ecurie Piston Sport Auto
      at Ecole Centrale de Lyon
  @description: countains all the functions that permit an update of
  the values displayed on the screen
  @functions: setGear(char gear)
                    Updates the gear display on the screen according to
                    char gear(e.g. N,1,2,3,..)
              setOilTemp(int oilTemp)
                    Updates the display of oil temperature in Celsius degrees
              setVoltage(int voltage)
                    Updates the battery voltage(in diciVolts)
              setRPM(int RPM)
                    Updates the RPM display
              setLaunch(bool launch_active)
                    Changes display depending on launch control activation: screen
                    turns green if launch control is active, else it turns normal
              nextion_endMessage()
                    Sends a message which has to be sent at the end of each communication
                    with Nextion (it's a protocol)
              changePage(int page)
                    Changes the display page
              updateDisplay(..)
                    Supposed to be called while changing page or restarting the screen
****************************************************************/

void setup(){
  Serial.begin(9600);
}

void changePage(int page){
  Serial.print("Page ");
  Serial.print(page);
}

void updateDisplay(int page,char gear,int oilTemp, float voltage){
  if(page==1){
    setGear(gear);
    setOilTemp(oilTemp);
    setVoltage(voltage);
    setLaunch(launch);
  }
  if(page==2){
    setGear(gear);
    setOilTemp(oilTemp);
    setVoltage(voltage);
    setRMP(rpm);
    setLaunch(launch);
  }
}

void setGear(char gear){
  Serial.print("gear.txt=");
  Serial.print("\"");
  Serial.print(gear);
  Serial.print("\"");
  nextion_endMessage();
}

void setOilTemp(int oilTemp){
  Serial.print("oil_temp.val=");
  Serial.print(oilTemp);
  nextion_endMessage();
}

void setVoltage(int voltage){
  Serial.print("voltage.val=");
  Serial.print(voltage);
  nextion_endMessage();
}

void setRPM(int RPM){
  Serial.print("rpm.val=");
  Serial.print(RPM);
  nextion_endMessage();
}

void setLaunch(bool launch_active){
  if(launch_active){
    Serial.print("launch_state.val=");
    Serial.print(1);
    nextion_endMessage();
    //The screen turns green if launch control is active
    Serial.print("display_pro.bco=");
    Serial.print(1441);
    nextion_endMessage();
    //Font backgrounds turn green too
    Serial.print("oil_temp.bco=");
    Serial.print(1441);
    nextion_endMessage();
    Serial.print("voltage.bco=");
    Serial.print(1441);
    nextion_endMessage();
    Serial.print("gear.bco=");
    Serial.print(1441);
    nextion_endMessage();
    //Font colors turn black
    Serial.print("oil_temp.pco=");
    Serial.print(0);
    nextion_endMessage();
    Serial.print("voltage.pco=");
    Serial.print(0);
    nextion_endMessage();
    Serial.print("gear.pco=");
    Serial.print(0);
    nextion_endMessage();
  }
  else{
    Serial.print("launch_state.val=");
    Serial.print(0);
    nextion_endMessage();
    //The screen turns black if launch control is inactive
    Serial.print("display_pro.bco=");
    Serial.print(4258);
    nextion_endMessage();
    //Font backgrounds turn black
    Serial.print("oil_temp.bco=");
    Serial.print(4258);
    nextion_endMessage();
    Serial.print("voltage.bco=");
    Serial.print(4258);
    nextion_endMessage();
    Serial.print("gear.bco=");
    Serial.print(4258);
    nextion_endMessage();
    //Font colors turn white
    Serial.print("oil_temp.pco=");
    Serial.print(65535);
    nextion_endMessage();
    Serial.print("voltage.pco=");
    Serial.print(65535);
    nextion_endMessage();
    Serial.print("gear.pco=");
    Serial.print(65535);
    nextion_endMessage();
    }
}

void nextion_endMessage(){
  //This message must be sent as a confirmation of the end of the message
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}
