

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);

    pinMode(A1,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(A1,HIGH);
  
   int Sel=digitalRead(A0);
   Serial.println(Sel);

   delay(1000);
}
