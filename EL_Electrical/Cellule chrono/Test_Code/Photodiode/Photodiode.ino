

bool val;

void setup() {             
  Serial.begin(9600);
     
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
}

void loop() {

  val=digitalRead(5);
  Serial.print("Pin 5 : ");
  Serial.println(val);

  val=digitalRead(6);
  Serial.print("Pin 6 : ");
  Serial.println(val);
  
  delay(1000); // Delay one second
}
