#include <Keypad.h>
#include <Wire.h>
//This code is for the keyboard that is connected to the master or other units
const byte ROWS = 2;  // four rows
const byte COLS = 2;  // four columns
char keys[ROWS][COLS] = {
  { '5', '6' },
  { '7', '8' }
};

byte rowPins[ROWS] = { 4, 5 };        // connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 7};  // connect to the column pinouts of the keypad

char key = NO_KEY;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestEvent);
}

void loop() {
  key = keypad.getKey();

  delay(100);
}

void requestEvent(){
  // if I receive a keystroke I write something, else I don't 
   Wire.write(key); 
}