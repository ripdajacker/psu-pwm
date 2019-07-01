
void setup() {     
  Serial.begin(9600);  

  pinMode(5, OUTPUT);     
  pinMode(A0, INPUT);

  // Start fan at 1/2 speed
  analogWrite(5, 128);
}


void loop() {
  // Read and map temperature to PWM signal
  uint16_t read = analogRead(A0);
  uint8_t writeThis =  map(read, 300, 400, 55, 210);

  if(read < 100 ) {
    // Something is wrong, the wire likely broke
    writeThis = 210;
  } 
 
  if(read < 300) {
    writeThis = 55;    
  } else if(read > 400) {
    writeThis = 210;
  }

  // Output PWM signal
  analogWrite(5, writeThis);

  Serial.print("Read: ");
  Serial.print(read);
  Serial.print(" Write: ");
  Serial.println(writeThis);

  // Wait some time before checking again
  delay(50);
}
