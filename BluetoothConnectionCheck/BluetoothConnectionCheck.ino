
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX | TX
int throttleValue = 0;
int steeringValue = 0;
int incomingByte = 0;
String inData;
void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);  // HC-05 default speed in AT command more
  Serial.println("connected");
}

void loop()
{
  while(mySerial.available() > 7) {
    int incomingByte = mySerial.read();
    if(incomingByte == 0){
      incomingByte = mySerial.read();
      if(incomingByte == 0) {
        incomingByte = mySerial.read();
        if(incomingByte == 0){
          throttleValue = mySerial.read();
          steeringValue = mySerial.read();
        }
      }
    }
    
    
//    char recieved = mySerial.read();
//    inData += recieved;
//    if (recieved == '\n'){ 
//      Serial.print("Recieved String: ");
//     Serial.print(inData);
//    inData = ""; 
//    }
  }  
  Serial.print("Throtte: ");
  Serial.print(throttleValue);
  Serial.print(" Steering: ");
  Serial.println(steeringValue);
}
