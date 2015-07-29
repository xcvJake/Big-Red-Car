
int throttleValue = 100;
int steeringValue = 100;
int disconnectCounter = 0;

int steeringPot = A0;
int leftLimitSwitch = 10;
int rightLimitSwitch = 11;
int pwmMOSFET = 6;

void setup() 
{
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  //Motors
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  //Steering
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  //PWM Mosfet
  TCCR0B = TCCR0B & 0b11111000 | 0x02;
  pinMode(pwmMOSFET, OUTPUT);
  
  //Limit Switches
  pinMode(leftLimitSwitch, INPUT);
  digitalWrite(leftLimitSwitch, HIGH); 
  pinMode(rightLimitSwitch, INPUT);
  digitalWrite(rightLimitSwitch, HIGH);
}

void loop()
{
  //Get Values from the serial port from the remote
  //change to an if statement for disconnection protection
  if(Serial.available() > 7) {
    int incomingByte = Serial.read();
    if(incomingByte == 0){
      incomingByte = Serial.read();
      if(incomingByte == 0) {
        incomingByte = Serial.read();
        if(incomingByte == 0){
          throttleValue = Serial.read();
          steeringValue = Serial.read();
          disconnectCounter = 0; //Connection Re-established. 
        }
      }
    }
  } else {
    //Bluetooth Disconnect TimeOut Counter
    if (disconnectCounter < 2000) {
      disconnectCounter++;
    } else { 
      disconnectCounter = 2001;
    }
    //When counter has exceeded 7, turn off the motors completely, lost connection
  }  
  

  
  
  
  
  if (disconnectCounter > 2000) { //BLUETOOTH DISCONNECTED
    //Disable Vehicle
    //Turn Everything off
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      analogWrite(pwmMOSFET, 0);
  } else { //Things are fine set the motors and steering     
    //Speed Control
    if (throttleValue > 160){ //Go Backwards
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
      digitalWrite(2, HIGH);
      digitalWrite(4, HIGH);
      int pwmValue = 255 - map(throttleValue, 160, 255, 0, 255);
      analogWrite(pwmMOSFET, pwmValue);
      
    } else if (throttleValue < 70){//GO Forwards
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH);
      int tempThrottle = 70 - throttleValue;
      int pwmValue = 255 - map(tempThrottle, 0, 70, 0, 255);
      analogWrite(pwmMOSFET, pwmValue);
      
    } else { //Stop the motors
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      analogWrite(pwmMOSFET, 255);
      
    }
    
    //Direction Control
    if (steeringValue > 160) { //GO Left 
      if(digitalRead(leftLimitSwitch) == LOW){//Turn Steering Left
          digitalWrite(12, LOW);
          digitalWrite(8, LOW);
          digitalWrite(13, HIGH);
          digitalWrite(9, HIGH);
      } else { //Turn Steering off
          digitalWrite(12, LOW);
          digitalWrite(13, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, LOW);
      }
    } else if (steeringValue < 70 ) { //GO Right
      if(digitalRead(rightLimitSwitch) == LOW) {//Turn Steering Right
          digitalWrite(13, LOW);
          digitalWrite(9, LOW);
          digitalWrite(12, HIGH);
          digitalWrite(8, HIGH);
      } else { //Turn Steering off
          digitalWrite(12, LOW);
          digitalWrite(13, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, LOW);
      }
    } else { //GO Straight
          digitalWrite(12, LOW);
          digitalWrite(13, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, LOW);      
    }
    }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
}
