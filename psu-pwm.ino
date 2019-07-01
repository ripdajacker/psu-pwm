
void setup() {
  Serial.begin(9600);

  pinMode(5, OUTPUT);
  pinMode(A0, INPUT);

  // Start fan at 1/2 speed
  analogWrite(5, 128);
}

const uint16_t input_min = 300;
const uint16_t input_max = 400;
const uint16_t output_min = 55;
const uint16_t output_max = 210;

void loop() {
  // Read and map temperature to PWM signal
  uint16_t read = analogRead(A0);
  uint8_t writeThis = map(read, input_min, input_max, output_min, output_max);

  if (read < 100) {
    // Something is wrong, the wire likely broke, put the fan into high speed
    writeThis = output_max;
  } else if (read < input_min) {
    writeThis = output_min;
  } else if (read > input_max) {
    writeThis = output_max;
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
