#include "Keyboard.h"
#include <Keypad.h>
#include <Wire.h>
//This code is for the keyboard that is directly connected to the computer via USB, the other keyboard units will have a writer.ino file
const byte ROWS = 2; // two rows
const byte COLS = 2; // two columns

char keys[ROWS][COLS] = {
  {'k', 'o'},
{'m','p'},
};

byte rowPins[ROWS] = {6,7}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {4,5}; // connect to the column pinouts of the keypad


Keypad kpd = Keypad(makeKeymap(keys),rowPins,colPins, ROWS,COLS);

unsigned long loopCount;
unsigned long startTime;
String msg;

void setup(){
  // puts the SDA and SCL lines in input mode
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  Wire.begin();
  Serial.begin(9600);
  loopCount = 0;
  startTime = millis();
  msg = "";
   
}

// receives a key, the arduino passes it as keyboard input to the host, then it goes into a 100 ms delay and after the delay it releases all pressed keys
// then the loop starts again
void loop(){
  loopCount++;
  if ( (millis()-startTime)>5000 ) {
      Serial.print("Average loops per second = ");
      Serial.println(loopCount/5);
      startTime = millis();
      loopCount = 0;
  }
  // receive the message from the slave number 8
  Wire.requestFrom(8, 4); // receives a byte from slave number 8
  while(Wire.available()){// if i received a keystroke
    char c = Wire.read();
    if(c>=0){
      Keyboard.press(c);
    }
  }
  Keyboard.releaseAll();
  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (kpd.getKeys())
  {
      for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
      {
          if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
          {
              switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                  case PRESSED:
                  msg = " PRESSED.";
                  Keyboard.press(kpd.key[i].kchar);
              break;
                  case HOLD:
                  msg = " HOLD.";
              break;
                  case RELEASED:
                  msg = " RELEASED.";
                  Keyboard.release(kpd.key[i].kchar);
              break;
                  case IDLE:
                  msg = " IDLE.";
              }
              Serial.print("Key ");
              Serial.print(kpd.key[i].kchar);
              Serial.println(msg);
          }
      }
  }
 delay(10);
}

