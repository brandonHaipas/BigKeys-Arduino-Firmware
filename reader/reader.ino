#include "Keyboard.h"
#include <Keypad.h>
#include <Wire.h>
//This code is for the keyboard that is directly connected to the computer via USB, the other keyboard units will have a writer.ino file
const byte ROWS = 2; // four rows
const byte COLS = 2; // four columns

char keys[ROWS][COLS] = {
  {'1', '2'},
  {'3','4'},
};

byte rowPins[ROWS] = {4,5}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7}; // connect to the column pinouts of the keypad

// keep on watching the video later
// as everything I need for this to work is for the keypad to send keyboad input to the device, all I need to do is to flash
// a simple keypad program into the platform.

Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins, ROWS,COLS);

void setup(){
  Wire.begin();
  Serial.begin(9600);
  Keyboard.begin();
}

// receives a key, the arduino passes it as keyboard input to the host, then it goes into a 100 ms delay and after the delay it releases all pressed keys
// then the loop starts again
void loop(){
  Wire.requestFrom(8, 1); // receives a byte from slave number 8
  while(Wire.available()){// if i received a keystroke
    char c = Wire.read();
    Serial.println("Estoy en loop xd");
    Keyboard.press(c);
  }
  char key = keypad.getKey();
  if (key != NO_KEY){  
    Serial.println(key); 
    Keyboard.press(key);
  }
  delay(200);
  Keyboard.releaseAll();
}

