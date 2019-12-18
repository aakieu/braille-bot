// LIBRARIES
#include <Servo.h>
#include <Wire.h> //Wire library
#include <LiquidCrystal_I2C.h> //Liquid crystal library
// Create Servo Object 
Servo linearServo;  // create servo object to control a servo
//Create LCD Object
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
// LCD displays uses 4 pins on the arduino board. 
// VCC --> VCC  (purple)
// GND --> GND (blue)
// SDA --> A4 (gray) 
// SCL --> A5 (white)

// Motor A : X-axis motor 
const int pulsePinA = 10;   // Pulse Pin [attach to PWM pin to control speed] 
const int dirPinA = 9;    // Dir+ Pin
const int enPinA = 8;     // En+
// Motor B : Y-axis motor
const int pulsePinB = 5;   // Pulse Pin [attach to PWM pin to control speed]
const int dirPinB = 6;    // Dir+ Pin
const int enPinB = 7;     // En+
// linear servo
const int linearPin = 3;


// safety switches
const int switchA1 = A0;  // left switch 
const int switchA2 = A1;  // right switch 
const int switchB1 = A2;  // top switch 
const int switchB2 = A3;  // bottom switch

// user input 
const byte numChars = 100;
char inputCharArray[numChars]; // an array to store the received data

boolean newData = false;

// motor positions
const int startY = 12480;
const int startX = 6045;
const int nextDot = 112;
const int nextCell = 170;
const int nextBottomCell = 458;

const int upPos = 80; 
const int punchPos = 155;

int inputLength = 0;


//////////////////////////////// SETUP() ///////////////////////////////////////////////////////////////
void setup() {
  // Put code here to run once:
   Serial.begin(9600);


  // Initialize Arduino pins
  initArduino(); 

  // Initialize LCD
  lcd.begin(16,2); 

  // Initialize Linear servo 
  linearServo.attach(linearPin);  // attaches the servo on pin 3 to the servo object

  // Start with motors off 
  digitalWrite(enPinA,HIGH); // enable pin is active-low;
  digitalWrite(enPinB,HIGH); // enable pin is active-low;

  // fully retract linear servo 
  setLinearPos(0);
  delay(1000); 

  displayLCD("Starting...........");
  Serial.println(" Returning motors to default position...");
  delay(2000);
  //go2StartPos(); // while loop inside, motors will be off after  
  Serial.println(" Motors in start position");
  displayLCD("Ready for Input");
  Serial.println("Ready for Input");


  takeUserInput(); 
  displayUserInput();
  displayLengthOfArray();
  displayUserInput2();
  
};
