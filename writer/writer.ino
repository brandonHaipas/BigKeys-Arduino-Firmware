#include <Keypad.h>
#include <Wire.h>
//This code is for the keyboard that is connected to the master or other units
const byte ROWS = 2;  // four rows
const byte COLS = 2;  // four columns
char keys[ROWS][COLS] = {
  { 'q', 'e' },
  { 'w', 'r' }
};

byte rowPins[ROWS] = {6,7};        // connect to the row pinouts of the keypad
byte colPins[COLS] = { 4,5};  // connect to the column pinouts of the keypad

char nk = NO_KEY;
String keys_pressed;

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

unsigned long loopCount;
unsigned long startTime;
String msg;

void setup() {
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  Wire.begin(8);
  Serial.begin(9600);
  loopCount = 0;
  startTime = millis();
  msg = "";
  Wire.onRequest(requestEvent);
}

void loop() {
  keys_pressed = "";
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
                  keys_pressed += kpd.key[i].kchar;
              break;
                  case HOLD:
                  msg = " HOLD.";
              break;
                  case RELEASED:
                  msg = " RELEASED.";
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
  delay(20);
}

void requestEvent(){
  // if I receive a keystroke I write something, else I don't 
   unsigned int pressed_len = keys_pressed.length();
   int left = 4 - pressed_len;
   for(int i = 0; i<left; i++){
     keys_pressed.concat(nk);
   }
   Wire.write(keys_pressed.c_str(), 4); 
   
}