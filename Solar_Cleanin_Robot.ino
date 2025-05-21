#include <SoftwareSerial.h>

// Motor pins
const int enA = 2;
const int in1 = 3;
const int in2 = 4;
const int enB = 5;
const int in3 = 6;
const int in4 = 7;

int command = 0;

// Cleaning system
const int cleanen = 10;
const int watermotor = 11;
const int brushmotor = 12;

// Ultrasonic pins
const int trigPin = 8;
const int echoPin = 9;

// Bluetooth serial (use pins other than 0 and 1)
SoftwareSerial mySerial(0, 1); // RX, TX (change pins to any free ones on your board)

// Flags
bool blockForward = false;

void setup() {
  // Motor setup
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Cleaning system setup
  pinMode(cleanen, OUTPUT);
  analogWrite(cleanen, 200);
  pinMode(watermotor, OUTPUT);
  pinMode(brushmotor, OUTPUT);

  // Ultrasonic setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Serial ports
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  // Stop if obstacle detected
  if (distance > 12 && (command == 'F' || command == 'f')) {
    stop();
  }

  // Process Bluetooth command
  if (mySerial.available() > 0) {
    command = mySerial.read();
    Serial.print("Command: ");
    Serial.println((char)command);
    executeCommand(command);
  }

  delay(10);
}

void executeCommand(int command) {
  switch (command) {
    case 'F': case 'f': forward(); break;
    case 'B': case 'b': backward(); break;
    case 'L': case 'l': left(); break;
    case 'R': case 'r': right(); break;
    case 'W': case 'w': water(); break;
    case 'Z': case 'z': brush(); break;
    case 'T': case 't': brushStop(); break;
    case 'S': case 's': stop(); break;
  }

  Serial.flush();
  delay(10);
}

// Movement functions
void forward() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(enA, 130); analogWrite(enB, 130);
}

void backward() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(enA, 130); analogWrite(enB, 130);
}

void left() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(enA, 130); analogWrite(enB, 130);
}

void right() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(enA, 130); analogWrite(enB, 130);
}

void stop() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  analogWrite(enA, 0); analogWrite(enB, 0);
}

void brushStop() {
  analogWrite(cleanen, 0);
  digitalWrite(watermotor, LOW);
  digitalWrite(brushmotor, LOW);
}

// Ultrasonic distance function
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void water() {
  analogWrite(cleanen, 200);
  digitalWrite(watermotor, HIGH);
}

void brush() {
  analogWrite(cleanen, 200);
  digitalWrite(brushmotor, HIGH);
}