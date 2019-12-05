int laserPin = 13;
int diodePin = 6;

bool val;

void setup() {             
  Serial.begin(9600);
     
  pinMode(laserPin, OUTPUT);  // Define the digital output interface pin 13 
  pinMode(diodePin,INPUT);
}

void loop() {
  digitalWrite(laserPin, HIGH); // Open the laser head

  val=digitalRead(diodePin);
  Serial.println(val);
  
  delay(1000); // Delay one second
  
  digitalWrite(laserPin, LOW); // Close the laser head

  val=digitalRead(diodePin);
  Serial.println(val);
  
  delay(1000); 
}
