
void loop() 
{
  turnOnSteppers();
  displayLCD("Printing........"); 
  go2FirstCell(); 

   Serial.print("\n\n");
   lcd.clear();
   
   punchChar();
  
};// end loop


void go2StartPos()
{
  digitalWrite(enPinA,LOW);
  bool leftTempVar = digitalRead(switchA1) ; 
  while (!leftTempVar)
  {
    moveLeft(1); 
    leftTempVar = digitalRead(switchA1) ; 
    if (leftTempVar) digitalWrite(enPinA,HIGH); 
  }
  digitalWrite(enPinB,LOW);
  bool downTempVar = digitalRead(switchB1) ; 
  while (!downTempVar)
  {
    moveDown(1); 
    downTempVar = digitalRead(switchB1) ; 
    if (downTempVar) digitalWrite(enPinB,HIGH); 
  }
};

void go2FirstCell()
{
  moveUp(startY); 
  moveRight(startX);
}

void pause()
{while (true) {}; }


void punchChar() 
{
  for (int i = 0; i < inputLength-1 ; i++) 
  {
    Serial.print("i = :"); 
    Serial.print(i); 
    Serial.print("\n"); 
    
    char tempChar = inputCharArray[i]; //store one character of user input
    Serial.print("tempChar :" ); 
    Serial.print(tempChar); 
    Serial.print("\n");
    
    int *tempBrailleArray ;
    tempBrailleArray = char2BrailleArray(tempChar); //convert character to binary array eqivalent

    Serial.print("tempBrailleArray :" );
    
    lcd.setCursor(0,0);
    lcd.print("printing: "); 
    lcd.setCursor(10,0); 
    lcd.print(tempChar); 
    
    for(int foo = 0; foo < 6; foo ++)
    {
          Serial.print(tempBrailleArray[foo]); 
    }
    Serial.print("\n"); 
    
    for (int j = 0; j < 6; j++)
    {
      bool tempBit = tempBrailleArray[j]; //extract a single bit in jth element from binary array
      
      switch (j) 
      {
      case 0:
        // statements
        punchNoPunch(tempBit); 
        moveRight(nextDot);
        delay(50);  
        break;
      case 1:
      punchNoPunch(tempBit); 
      moveRight(nextDot); 
      delay(50); 
        // statements
        break;
      case 2:
        // statements
        punchNoPunch(tempBit); 
        moveDown(nextDot);
        delay(50); 
        break;
      case 3:
        // statements
        punchNoPunch(tempBit); 
        moveLeft(nextDot);
        delay(50); 
        break;
      case 4:
        // statements
        punchNoPunch(tempBit); 
        moveLeft(nextDot);
        delay(50); 
        break;
      case 5:
        // statements
        punchNoPunch(tempBit);
        moveDown(nextCell);
        delay(50); 
        Serial.println("moving to next letter");
        break;
      default:
        // statements
        break;
      }

    } // end j loop

Serial.print("\n");

    if (i == 29) 
    {moveRight(nextBottomCell);
    moveUp(  30*nextDot + 30*nextCell);
    }
     
    
   } // end i loop  

  Serial.println(" "); 
  Serial.println("Printing Complete ");
   lcd.setCursor(0,0); 
   lcd.print("Complete..........."); 
  setLinearPos(0);
  go2StartPos();
  pause();
} // end function
