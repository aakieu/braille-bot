//////////////////////////////////////////////// Initialization  ///////////////////////////////////////////////////////////////
void initArduino()
{
  // Define motors as outputs 
  pinMode(pulsePinA,OUTPUT); 
  pinMode(dirPinA,OUTPUT);
  pinMode(enPinA,OUTPUT);
  pinMode(pulsePinB,OUTPUT); 
  pinMode(dirPinB,OUTPUT);
  pinMode(enPinB,OUTPUT);
  // Define switches as inputs 
  pinMode(switchA1,INPUT); 
  pinMode(switchA2,INPUT); 
  pinMode(switchB1,INPUT); 
  pinMode(switchB2,INPUT);
}

//////////////////////////////////////////////// LCD  ///////////////////////////////////////////////////////////////

void displayLCD (String tempString)
{
  lcd.print(tempString);
  lcd.setCursor(0,0); //Set starting position for LCD disaply
  delay(100);
 };



//////////////////////////////////////////////// Linear Servo  ///////////////////////////////////////////////////////////////
 void setLinearPos(int pos) 
{ // Sets the position of the the linear servo
  // 0: Fully retracted 
  // 180: Fully extended 
  linearServo.write(pos); 
};
 
void punchDot() 
{ setLinearPos(punchPos);  
  delay(1500); 
  setLinearPos(upPos); 
  delay(500);
  }

void testServo(){
  setLinearPos(0); 
  delay(2000); 
  setLinearPos(100);
  delay(2000); 
}

 //////////////////////////////////////////////// Stepper Motors  ///////////////////////////////////////////////////////////////
 void rotateClockWiseA(int numPulse){
  // left towards x axis 
  digitalWrite(dirPinA,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < numPulse; x++) {
    digitalWrite(pulsePinA,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(pulsePinA,LOW); 
    delayMicroseconds(500); 
  }
};

void rotateCounterClockWiseA( int numPulse){
  // right towards x axis 
  digitalWrite(dirPinA,LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < numPulse; x++) {
    digitalWrite(pulsePinA,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(pulsePinA,LOW); 
    delayMicroseconds(500); 
  }
};


void rotateClockWiseB(int numPulse){
  // up (+y axis)
    digitalWrite(dirPinB,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation 
  for(int x = 0; x < numPulse; x++) {
    digitalWrite(pulsePinB,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(pulsePinB,LOW); 
    delayMicroseconds(500); 
  }
};


void rotateCounterClockWiseB(int numPulse){
  // down (-y axis)
  digitalWrite(dirPinB,LOW); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation 
  for(int x = 0; x < numPulse; x++) {
    digitalWrite(pulsePinB,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(pulsePinB,LOW); 
    delayMicroseconds(500); 
  }
};


void moveUp( int numPulse){
  // +y direction (up)
  rotateClockWiseB(numPulse);   
};


void moveDown(int numPulse){
  // -y direction (down)
  rotateCounterClockWiseB(numPulse); 
};


void moveRight(int numPulse){
  // +x direction (right)
  rotateCounterClockWiseA(numPulse); 
};


void moveLeft(int numPulse){
  // -x direction (left) 
  rotateClockWiseA(numPulse);  
};


void testSteppers()
{
  int testPulse = 800;
  moveUp(testPulse);
  delay(1000);
  moveUp(testPulse);
  delay(1000);
  moveDown(testPulse);
  delay(1000);
  moveDown(testPulse);
  delay(1000);
  moveRight(testPulse);
  delay(1000);
  moveRight(testPulse);
  delay(1000);
  moveLeft(testPulse);
  delay(1000);
  moveLeft(testPulse);
  delay(1000);
}

void turnOnSteppers()
{
  digitalWrite(enPinA,LOW); // enable pin is active-low;
  digitalWrite(enPinB,LOW); // enable pin is active-low;
}


void turnOffSteppers()
{
  digitalWrite(enPinA,HIGH); // enable pin is active-low;
  digitalWrite(enPinB,HIGH); // enable pin is active-low;
}





//////////////////////////////////////////////// Switches  ///////////////////////////////////////////////////////////////
void testSwitch()
{
  bool sw1 = digitalRead(switchA1); 
  bool sw2 = digitalRead(switchA2);
  bool sw3 = digitalRead(switchB1);
  bool sw4 = digitalRead(switchB2);
  Serial.print("sw1: ");
  Serial.print(sw1); 
  Serial.print("\t");
  Serial.print("sw2: ");
  Serial.print(sw2); 
  Serial.print("\t");
  Serial.print("sw3: ");
  Serial.print(sw3); 
  Serial.print("\t");
  Serial.print("sw4: ");
  Serial.print(sw4); 
  Serial.print("\t");
  Serial.print("\n");
}

//////////////////////////////////////////////// User Input  ///////////////////////////////////////////////////////////////
void takeUserInput()
{
  while (!newData)
  {inputLength = recvWithEndMarker(); }
}


void displayUserInput() 
{
 if (newData == true) 
 {
 Serial.print("Input Data:  ");
 Serial.println(inputCharArray);
 newData = false;
 }
}

void displayUserInput2()
{
  Serial.print("\n"); 
  for (int i = 0; i < inputLength ; i++)
 {
  Serial.print(" i = : "); 
  Serial.print(i); 
  Serial.print(" \t"); 
  Serial.print(inputCharArray[i]);
    Serial.print(" \n"); 
 }
}


void  displayLengthOfArray()
  {
    Serial.print("Length Of Input: "); 
    Serial.print(inputLength); 
    Serial.print("\n");
  }


int recvWithEndMarker() 
{
 static byte index = 0;
 int tempIndex = 0; 
 char endMarker = '\n';
 char currentChar;
 
 // if (Serial.available() > 0) {
 while (Serial.available() > 0 && newData == false) 
 {
  currentChar = Serial.read();
  
  if (currentChar != endMarker)
  {
    inputCharArray[index] = currentChar;
    index++;
    
    if (index >= numChars) {index = numChars - 1;} 
  }
 
  else 
  { 
    inputCharArray[index] = '\0'; // terminate the string
    tempIndex = index; 
    index = 0;
    newData = true;
    return tempIndex ;
  }
 }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void punchNoPunch(bool bitIsOne)
{
  if (bitIsOne)
  {
   punchDot();
   Serial.println("punch");
  }
  else Serial.println("no punch");
}
      
 void punchCell() 
 {
  int punchCellDelay = 50;
  punchDot();
  //delay(punchCellDelay);
   
  moveRight(nextDot);
  delay(punchCellDelay);
  punchDot();
  //delay(punchCellDelay);
  
  moveRight(nextDot);
  delay(punchCellDelay);
  punchDot();
  //delay(punchCellDelay);
 
  /////////////////////////////////////////////////////////
  moveDown(nextDot);
  delay(punchCellDelay);
  punchDot();
  //delay(punchCellDelay);
 
  moveLeft(nextDot);
  delay(punchCellDelay);
 punchDot();
 //delay(punchCellDelay);
  moveLeft(nextDot);
  delay(punchCellDelay);
  punchDot();
  //delay(punchCellDelay);
 }


//////////////////////////////////////////////// char2BrailleArray()  ///////////////////////////////////////////////////////////////
int * char2BrailleArray(char myChar)
{ 
  switch (myChar) 
  {
  case 'a':
    // statements
    static int a[6] = {1, 0, 0, 0, 0, 0};
    return a; 
    break;
    
  case 'b':
    // statements
    static int b[6] = {1, 1, 0, 0, 0, 0};
    return b; 
    break;

    case 'c':
    // statements
    static int c[6] = {1, 0, 0, 0, 0, 1};
    return c; 
    break;

    case 'd':
    // statements
    static int d[6] = {1, 0, 0, 0, 1, 1};
    return d; 
    break; 
    
    case 'e':
    // statements
    static int e[6] = {1, 0, 0, 0, 1, 0};
    return e; 
    break;   

    case 'f':
    // statements
    static int f[6] = {1, 1, 0, 0, 0, 1};
    return f; 
    break; 

    case 'g':
    // statements
    static int g[6] = {1, 1, 0, 0, 1,1 };
    return g; 
    break; 

    case 'h':
    // statements
    static int h[6] = {1, 1, 0, 0, 1,0};
    return h; 
    break;

    case 'i':
    // statements
    static int i[6] = {0, 1, 0, 0, 0, 1};
    return i; 
    break;

    case 'j':
    // statements
    static int j[6] = {0, 1, 0, 0, 1, 1};
    return j; 
    break; 

    case 'k':
    // statements
    static int k[6] = {1, 0, 1, 0, 0, 0};
    return k; 
    break; 

    case 'l':
    // statements
    static int l[6] = {1, 1, 1, 0, 0, 0};
    return l; 
    break; 

    case 'm':
    // statements
    static int m[6] = {1, 0, 1, 0, 0,1};
    return m; 
    break; 

    case 'n':
    // statements
    static int n[6] = {1, 0, 1, 0, 1, 1};
    return n; 
    break; 

    case 'o':
    // statements
    static int o[6] = {1, 0, 1, 0, 1, 0};
    return o; 
    break; 

    case 'p':
    // statements
    static int p[6] = {1, 1, 1, 0, 0, 1};
    return p; 
    break; 

    case 'q':
    // statements
    static int q[6] = {1, 1, 1, 0, 1, 1};
    return q; 
    break; 

    case 'r':
    // statements
    static int r[6] = {1, 1, 1, 0, 1, 0};
    return r; 
    break; 

    case 's':
    // statements
    static int s[6] = {0, 1, 1, 0, 0, 1};
    return s; 
    break; 

    case 't':
    // statements
    static int t[6] = {0, 1, 1, 0, 1, 1};
    return t; 
    break; 

    case 'u':
    // statements
    static int u[6] = {1, 0, 1, 1, 0, 0};
    return u; 
    break; 

    case 'v':
    // statements
    static int v[6] = {1, 1, 1, 1, 0, 0};
    return v; 
    break; 

    case 'w':
    // statements
    static int w[6] = {1, 0, 0, 1, 1, 1};
    return w; 
    break; 

    case 'x':
    // statements
    static int x[6] = {1, 0, 1, 1, 0, 1};
    return x; 
    break; 

    case 'y':
    // statements
    static int y[6] = {1, 0, 1, 1, 1, 1};
    return y; 
    break;                                                 

    case 'z':
    // statements
    static int z[6] = {1, 0, 1, 1, 1, 0};
    return z; 
    break;

    case '#':
    // statements
    static int lb[6] = {0, 0, 1, 1, 1, 1};
    return lb; 
    break;

    case '0':
    // statements
    static int zero[6] = {0, 1, 0, 0, 1, 1};
    return zero; 
    break; 

    case '1':
    // statements
    static int one[6] = {1, 0, 0, 0, 0, 0};
    return one; 
    break; 

    case '2':
    // statements
    static int two[6] = {1, 1, 0, 0, 0, 0};
    return two; 
    break; 

    case '3':
    // statements
    static int three[6] = {1, 0, 0, 0, 0, 1};
    return three; 
    break; 

    case '4':
    // statements
    static int four[6] = {1, 0, 0, 0, 1, 1};
    return four; 
    break; 

    case '5':
    // statements
    static int five[6] = {1, 0, 0, 0, 1, 0};
    return five; 
    break; 

    case '6':
    // statements
    static int six[6] = {1, 1, 0, 0, 0, 1};
    return six; 
    break; 

    case '7':
    // statements
    static int seven[6] = {1, 1, 0, 0, 1, 1};
    return seven; 
    break; 

    case '8':
    // statements
    static int eight[6] = {1, 1, 0, 0, 1, 0};
    return eight; 
    break;                            

    case '9':
    // statements
    static int nine[6] = {0, 1, 0, 0, 0, 1};
    return nine; 
    break;

    case ' ':
    // statements
    static int space[6] = {0, 0, 0, 0, 0, 0};
    return space; 
    break;
   
  default:
    // statements
    break;}
 
 };
  
