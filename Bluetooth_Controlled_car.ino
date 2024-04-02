//this is code is writen by Engr Imran. You can edit the pin modes according to your schamatics diagram

#include <SoftwareSerial.h>

const int enA = A1;
const int in1 = 2; 
const int in2 = 4;  
const int enB = A2; 
const int in3 = 7;  
const int in4 = 8; 
const int l1 = 10;
const int l2 = 11;
const int l3 = 12;
const int l4 = 13;

SoftwareSerial mySerial(0, 1); // RX, Tx

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available() > 0) {
    
     Serial.println(mySerial.read());

     int command = mySerial.read();  // Read the command character
     Serial.println(command);
     
     executeCommand(command);
  }
}

void executeCommand(int command) {

  // Serial.println(command);

  if (command == 70 || command == 102){ // F or f
    forward();
  }
  else if(command == 66 || command == 98){ // B or b
    backward();
  }
  else if(command == 82 || command == 114){ // R or r
    right();
  }
  else if(command == 76 || command == 108){ // L or l
    left();
  }
  else if(command == 83 || command == 115){ // S or s
    stop();
  }
  
  Serial.flush();
}

void front()
{
  digitalWrite(l1, HIGH);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, LOW);
  digitalWrite(l4, LOW);
}
void back()
{
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(l3, HIGH);
  digitalWrite(l4, HIGH);
}
void Left()
{
  digitalWrite(l1, HIGH);
  digitalWrite(l2, LOW);
  digitalWrite(l3, HIGH);
  digitalWrite(l4, LOW);
  delay(100);
  digitalWrite(l1, HIGH);
  digitalWrite(l2, LOW);
  digitalWrite(l3, HIGH);
  digitalWrite(l4, LOW);
}
void Right()
{
  digitalWrite(l1, LOW);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, LOW);
  digitalWrite(l4, HIGH);
  delay(100);
  digitalWrite(l1, LOW);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, LOW);
  digitalWrite(l4, HIGH);
}
void forward() {
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void backward() {
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void left() {
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void right() {
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void stop() {
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
