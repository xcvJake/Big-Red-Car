

int incomingByte = 0;

void setup() {
  // put your setup code here, to run once:
  //Motors
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
//Steering
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
                if(incomingByte == 119){ // w pressed
                  digitalWrite(2, LOW);
                  digitalWrite(4, LOW);
                  digitalWrite(3, HIGH);
                  digitalWrite(5, HIGH);
                  Serial.println("Forward");
                } else if ( incomingByte == 115) { //s pressed
                  digitalWrite(3, LOW);
                  digitalWrite(5, LOW);
                  digitalWrite(2, HIGH);
                  digitalWrite(4, HIGH);
                  Serial.println("Reverse");
                } else if (incomingByte == 97 ) { //a pressed
                  digitalWrite(6, LOW);
                  digitalWrite(8, LOW);
                  digitalWrite(7, HIGH);
                  digitalWrite(9, HIGH);
                  Serial.println("Left");
                } else if (incomingByte == 100 ) { //d pressed
                  digitalWrite(7, LOW);
                  digitalWrite(9, LOW);
                  digitalWrite(6, HIGH);
                  digitalWrite(8, HIGH);
                  Serial.println("Right");
                } else { // You Pressed wrong, shut everything off
                  digitalWrite(2, LOW);
                  digitalWrite(3, LOW);
                  digitalWrite(4, LOW);
                  digitalWrite(5, LOW);
                  digitalWrite(6, LOW);
                  digitalWrite(7, LOW);
                  digitalWrite(8, LOW);
                  digitalWrite(9, LOW);
                  Serial.println("wrong input: press w, a, s, or d ");
                }
        }
}
