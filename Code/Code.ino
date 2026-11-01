 
#include <SoftwareSerial.h> 
  
const uint8_t BT_RX = 2;   // Arduino D2 <- HC-05 TXD 
const uint8_t BT_TX = 3;   // Arduino D3 -> HC-05 RXD (via 1k/2k divider) 
  
const uint8_t ENA = 5;     // left motor group speed (PWM) 
const uint8_t IN1 = 8;     // left group direction 
const uint8_t IN2 = 9; 
const uint8_t IN3 = 10;    // right group direction 
const uint8_t IN4 = 11; 
const uint8_t ENB = 6;     // right motor group speed (PWM) 
  
const uint8_t SPEED = 200; // PWM duty, 0-255 
  
SoftwareSerial bluetooth(BT_RX, BT_TX); 
  
// dirL/dirR: 1 = forward, -1 = backward, 0 = stop 
void drive(int8_t dirL, int8_t dirR, uint8_t speed) { 
  digitalWrite(IN1, dirL > 0); 
  digitalWrite(IN2, dirL < 0); 
  digitalWrite(IN3, dirR > 0); 
  digitalWrite(IN4, dirR < 0); 
  analogWrite(ENA, dirL != 0 ? speed : 0); 
  analogWrite(ENB, dirR != 0 ? speed : 0); 
} 
  
void moveForward()  { drive( 1,  1, SPEED); } 
void moveBackward() { drive(-1, -1, SPEED); } 
void turnLeft()     { drive(-1,  1, SPEED); }  // spin left in place 
void turnRight()    { drive( 1, -1, SPEED); }  // spin right in place 
void stopMotors()   { drive( 0,  0, 0); } 
  
void setup() { 
  pinMode(ENA, OUTPUT); 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  pinMode(ENB, OUTPUT); 
  stopMotors(); 
  bluetooth.begin(9600);   // HC-05 default data-mode baud rate 
} 
  
void loop() { 
  if (bluetooth.available() > 0) { 
    char cmd = toupper(bluetooth.read()); 
    switch (cmd) { 
      case 'F': moveForward();  break; 
      case 'B': moveBackward(); break; 
      case 'L': turnLeft();     break; 
      case 'R': turnRight();    break; 
      case 'S': stopMotors();   break; 
      default:  break;         // ignore any other character 
    } 
  } 
}