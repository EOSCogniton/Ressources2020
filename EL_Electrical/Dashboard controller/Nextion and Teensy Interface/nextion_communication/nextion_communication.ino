#include <string.h>

char id="t3";
char texte="Bonjour";
void setup(){
  Serial.begin(9600);
}

void Nextion_EndMessage(){
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void Nextion_SendText(char txtid,char txt){
  Serial.print(txtid+".txt=");
  Serial.print("\"");
  Serial.print(txt);
  Serial.print("\"");
  Nextion_EndMessage();
}

void Nextion_SendVal(char valid,float val){
  Serial.print(valid+".val=");
  Serial.print(val);
  Nextion_EndMessage();
}

void loop(){
  Nextion_SendText(id,texte);
}

