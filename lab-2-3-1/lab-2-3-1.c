#include <wiringPi.h>
// constants won't change. They're used here to set pin numbers:
const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
// 0, 1, 2, 3, 4, 5, 6, 7
const int Keypad[8] = {16, 13, 12, 6, 21, 26, 20, 19};
// 3, 2, 1, 0, 7, 6, 5, 4



// Variables will change:
int ledState[8] = {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};         // the current state of the output pin
int buttonState[8];             // the current reading from the input pin
int lastButtonState[8] = {LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime[8] = {0,0,0,0,0,0,0,0};  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


int reading[8]={-1,-1,-1,-1,-1,-1,-1,-1};

void LedControl(int keypadnum) {
    int i;
    for (i = 0; i < 8; i++) {
        if (i == keypadnum)
          digitalWrite(LedRed[i], HIGH);
      else
          digitalWrite(LedRed[i], LOW);
  }
}


int KeypadRead() {
    int i, keypadnum = -1;
    for (i = 0; i < 8; i++) {
        reading[i]= !digitalRead(Keypad[i]);

// If the switch changed, due to noise or pressing:
        if ( reading[i]!= lastButtonState) {
// reset the debouncing timer
          lastDebounceTime[i] = millis();
      }

      if ((millis() - lastDebounceTime[i]) > debounceDelay) {
// whatever the reading is at, it's been there for longer than the debounce
// delay, so take it as the actual current state:

// if the button state has changed:
          if ( reading[i] != buttonState[i]) {
            buttonState[i] =  reading[i];

// only toggle the LED if the new button state is HIGH
            if (buttonState[i] == HIGH) {
              ledState = !ledState;
          }
      }
  }


// save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState[i] =  reading[i];


  if (reading[i]) {
    keypadnum = i;
    break;
}

}
return keypadnum;
}

int main(void) {

//void setup(){
    int i, keypadnum = -1;
    if (wiringPiSetupGpio() == -1)
        return 1;
    for (i = 0; i < 8; i++) {
        pinMode(LedRed[i], OUTPUT);
        digitalWrite(LedRed[i], LOW);
    }
    for (i = 0; i < 8; i++)
        pinMode(Keypad[i], INPUT);
//}


//void loop(){
    while (1) {
        keypadnum = KeypadRead();
        LedControl(keypadnum);
    }
//}


    return 0;
}
