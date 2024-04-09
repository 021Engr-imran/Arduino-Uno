#include <LiquidCrystal.h>
#include <Servo.h>

const byte latchPin = 2;    // Pin connected to Pin 5 of 74HC595 (Latch)
const byte dataPin  = 3;    // Pin connected to Pin 6 of 74HC595 (Data)
const byte clockPin = 4;    // Pin connected to Pin 7 of 74HC595 (Clock)
const int buttonPinA0 = A0; // Button pin A0
const int buttonPinA1 = A1; // Button pin A1
const int buttonPinA2 = A2; // Button pin A2
const int speakerPin = 10;  // Speaker pin

int pos = 0;
int brightness = 0;
int seconds = 0;
LiquidCrystal lcd_1(12, 11, 8, 7, 6, 5);
Servo servo_9;

unsigned long previousMillis = 0;     // Store the last time the LED was updated
unsigned long previousServoMillis = 0; // Store the last time the servo was updated
unsigned long previousButtonMillis = 0; // Store the last time buttons were checked
const long interval = 500;            // Interval at which to update LED (milliseconds)
const long servoInterval = 15;        // Interval at which to update servo (milliseconds)
const long buttonInterval = 10;       // Interval at which to check button (milliseconds)
const long speakerInterval = 100;     // Interval at which to play tone (milliseconds)

void setup() {
  pinMode(latchPin, OUTPUT);   // Set shift registers pins to output
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(buttonPinA0, INPUT);
  pinMode(buttonPinA1, INPUT);
  pinMode(buttonPinA2, INPUT);
  pinMode(speakerPin, OUTPUT);
  
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD
  lcd_1.print("hello world!"); // Print a message to the LCD
  
  servo_9.attach(9, 500, 2500); // Attach servo motor
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Check button presses
  if (currentMillis - previousButtonMillis >= buttonInterval) {
    previousButtonMillis = currentMillis;

    if (digitalRead(buttonPinA0) == HIGH) {
      tone(speakerPin, 440, 100); // Play tone A4 (440 Hz)
    }
    if (digitalRead(buttonPinA1) == HIGH) {
      tone(speakerPin, 494, 100); // Play tone B4 (494 Hz)
    }
    if (digitalRead(buttonPinA2) == HIGH) {
      tone(speakerPin, 523, 100); // Play tone C5 (523 Hz)
    }
  }

  // Update LED display
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time LED was updated

    int numbers[10] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 24};
    static int i = 0; // Static variable to remember the index

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numbers[i]);
    digitalWrite(latchPin, HIGH);

    i = (i + 1) % 10; // Move to the next index, wrapping around if necessary

    lcd_1.setCursor(0, 1);
    lcd_1.print(seconds); // Print the number of seconds since reset
    seconds++;
  }

  // Update servo position
  if (currentMillis - previousServoMillis >= servoInterval) {
    previousServoMillis = currentMillis;

    if (pos <= 180) {
      servo_9.write(pos);
      pos++;
    } else {
      pos = 0;
    }
  }

  // Update for Leds
  if ((currentMillis / 500) % 2 == 0) {
    analogWrite(1, brightness);
    brightness = (brightness + 5) % 256; // Increment brightness
  } else {
    analogWrite(1, 0); // Turn off LED
  }
}