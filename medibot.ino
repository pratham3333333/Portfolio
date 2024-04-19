#include <SoftwareSerial.h>  // Include SoftwareSerial library for Bluetooth
#include <Servo.h>

Servo myServo;
Servo myServo1;

// Define pins for HC-05 Bluetooth module
#define BT_RX 10
#define BT_TX 11
#define RX_PIN 0
#define buzzerPin 13 // Replace with your actual buzzer pin

SoftwareSerial BTSerial(BT_RX, BT_TX);  // Create a SoftwareSerial object for communication
/*
   Left Motor
*/
// IN 1
#define LM_IN1    2  
// IN 2
#define LM_IN2    4
/*
   Right Motor
*/
// IN 3
#define RM_IN3    5
// IN 4
#define RM_IN4    7
// Define byte values for movement commands
#define FWD_BYTE   1  // Byte value for forward
#define BWD_BYTE   2  // Byte value for backward
#define LFT_BYTE   3  // Byte value for left
#define RGT_BYTE   4  // Byte value for right
#define STP_BYTE   5  // Byte value for stop
#define patient_BTYE 6
#define patient2_BTYE 7 
#define Servo_BTYE 10
#define Servo1_BTYE 11


int motorSpeed = 80;
void setup() {
  myServo.attach(9);
  myServo1.attach(12);
  myServo.write(0);   // Set servo to 0 degrees
  myServo1.write(180); 
  pinMode(buzzerPin, OUTPUT);

  // Set motor pins as outputs for controlling direction
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }

  // Initialize serial communication with HC-05 at 9600 baud rate
  BTSerial.begin(9600);
  // Start serial communication for debugging purposes 
  Serial.begin(9600);
  Serial.println("Starting Bluetooth control...");
}

void loop() {
    if (Serial.available() > 0) {
    // Read data from EM-18 module (12-character ID)
    String rfidData = Serial.readString(); // Read as a string
    const String validCard1 = "400034E0FF6B";
    const String validCard2 = "1D00FE99D9A3";
    // Combine RFID data with additional text
    if (rfidData == validCard1) {
  // Valid card 1
    String combinedData = "Room-1:Reached";
    Serial.println(combinedData);
     BTSerial.write(combinedData.c_str());
}
else if (rfidData == validCard2) {
  // Valid card 2
  String combinedData = "Room-2: Reached ";
  Serial.println(combinedData);
  BTSerial.write(combinedData.c_str());
}
}
  if (BTSerial.available()) {
    int command = BTSerial.read();  // Read a byte from Bluetooth

    // Control movement based on received byte value
    switch (command) {
      case FWD_BYTE:
        go_Forward();
        break;
      case BWD_BYTE:
        go_Backward();
        break;
      case LFT_BYTE:
        go_Left();
        break;
      case RGT_BYTE:
        go_Right();
        break;
      case STP_BYTE:
        go_Stop();
        break;
      case patient_BTYE:
        go_patient1();    
        break;  
      case patient2_BTYE:
        go_patient2();    
        break;  
      case Servo_BTYE:
        go_Servo();    
        break;
      case Servo1_BTYE:
        go_Servo1();    
        break; 
      default:
        Serial.println("Unknown command received!");  // Handle unknown commands 
    }   
  }
  
}

// Movement control functions for the robot
void go_Forward() {
  digitalWrite(LM_IN1, HIGH);
  digitalWrite(LM_IN2, LOW);
  digitalWrite(RM_IN3, HIGH);
  digitalWrite(RM_IN4, LOW);
  Serial.println("Going Forward");  // Print to serial for debugging }

void go_Backward() {
  digitalWrite(LM_IN1, LOW);
  digitalWrite(LM_IN2, HIGH);
  digitalWrite(RM_IN3, LOW);
  digitalWrite(RM_IN4, HIGH);
  Serial.println("Going Backward");  // Print to serial for debugging ()
}

void go_Left() {
  digitalWrite(LM_IN1, LOW);
  digitalWrite(LM_IN2, HIGH);
  digitalWrite(RM_IN3, HIGH);
  digitalWrite(RM_IN4, LOW);
  
  
  Serial.println("Going Left");  // Print to serial for debugging ()
}

void go_Right() {
  digitalWrite(LM_IN1, HIGH);
  digitalWrite(LM_IN2, LOW);
  digitalWrite(RM_IN3, LOW);
  digitalWrite(RM_IN4, HIGH);
  Serial.println("Going Right");  // Print to serial for debugging 
}

void go_Stop() {
  digitalWrite(LM_IN1, LOW);
  digitalWrite(LM_IN2, LOW);
  digitalWrite(RM_IN3, LOW);
  digitalWrite(RM_IN4, LOW);
  Serial.println("Stopping");  // Print to serial for debugging 
}
void go_Servo(){
 tone(buzzerPin, 1000); // Generate a 1kHz tone
delay(1000);             // Wait for 0.5 seconds
noTone(buzzerPin);       // Stop the tone
delay(1000);   
       // Wait for 1 second 
  myServo.write(90);   // Set servo to 0 degrees
  delay(5000);  
  tone(buzzerPin, 1000); // Generate a 1kHz tone
delay(1000);             // Wait for 0.5 seconds
noTone(buzzerPin);       // Stop the tone
delay(1000);  
myServo.write(0);  // Set servo to 90 degrees
delay(4000);    
}
void go_Servo1(){
tone(buzzerPin, 1000); // Generate a 1kHz tone
delay(1000);             // Wait for 0.5 seconds
noTone(buzzerPin);       // Stop the tone
delay(1000);         // Wait for 1 second
  myServo1.write(90); 
  delay(5000);  

  tone(buzzerPin, 1000); // Generate a 1kHz tone
delay(1000);             // Wait for 0.5 seconds
noTone(buzzerPin);       // Stop the tone
delay(1000);    // Set servo to 0 degrees
  myServo1.write(180);  // Set servo to 90 degrees
  delay(6000);    
}
//Room 1
void go_Patient1(){
  go_Forward();
  delay(4000);
  go_Stop();
  delay(1000);
  go_Left();
  delay(1600);
  go_Stop();
  delay(500);
  go_Forward();
  delay(1000);
  go_Stop();
  go_Servo1();
  go_Stop();
  go_Backward();
  delay(1000);
  go_Stop();
  delay(500);
  go_Right();
  delay(1600);
  go_Stop();
  go_Backward();
  delay(4000);
  go_Stop();
}
//Room 2
void go_Patient2(){
  go_Forward();
  delay(4000);
  go_Stop();
  delay(1000);
  go_Right();
  delay(1000);
  go_Stop();
  delay(500);
  go_Forward();
  delay(2000);
  go_Stop();
  go_Servo();
  go_Stop();
  delay(2000);
  go_Backward();
  delay(1500);
  go_Stop();
  delay(500);
  go_Left();
  delay(1000);
  go_Stop();
  go_Backward();
  delay(4000);
  go_Stop();


    // Call the stop function to halt the car
}
