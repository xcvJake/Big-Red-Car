//Pot inputs
int throttle = A0;
int steering = A1;

// Pot Values
int throttleValue = 0;
int steeringValue = 0;

void setup() {
 Serial.begin(9600);
}

void loop() {
  throttleValue = map(analogRead(throttle), 0, 1023, 0, 255);
  steeringValue = map(analogRead(steering), 0, 1023, 0, 255); 
  Serial.write(0);
  Serial.write(0);
  Serial.write(0);
  Serial.write(throttleValue);
  Serial.write(steeringValue);
  Serial.write(255);
  Serial.write(255);
  Serial.write(255);
  //Serial.print(throttleValue);
  //Serial.print(',');
 //Serial.print(steeringValue);
  //Serial.print('\n');
  delay(100);
}
