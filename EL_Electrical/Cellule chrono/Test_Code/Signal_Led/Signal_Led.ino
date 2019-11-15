void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(3, OUTPUT);
  pinMode(4,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(3,HIGH);
  bool SGN=digitalRead(4);
  Serial.println(SGN);
  delay(1000);
}
