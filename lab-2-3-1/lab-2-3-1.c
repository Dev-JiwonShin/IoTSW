#include <stdbool.h>
#include <wiringPi.h>

const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
// 0, 1, 2, 3, 4, 5, 6, 7
const int Keypad[8] = {16, 13, 12, 6, 21, 26, 20, 19};
// 3, 2, 1, 0, 7, 6, 5, 4

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState[8] = {};             // the current reading from the input pin
int lastButtonState[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime[8] = {0, 0, 0, 0, 0, 0, 0, 0};  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

int KeypadRead() {
    int i, keypadnum = -1;
    for (i = 0; i < 8; i++) {
        int reading = !digitalRead(Keypad[i]);
        if (reading) {

            // If the switch changed, due to noise or pressing:
            if (reading != lastButtonState[i]) {
                // reset the debouncing timer
                lastDebounceTime[i] = millis();
            }

            if ((millis() - lastDebounceTime[i]) > debounceDelay) {
                // whatever the reading is at, it's been there for longer
                // than the debounce delay, so take it as the actual current state:
                buttonState[i] = reading;
            }

            // set the LED using the state of the button:
//            digitalWrite(ledPin, buttonState);
//            int j;
//            for (j = 0; j < 8; j++) {
//                if (j == i)
//                    digitalWrite(LedRed[j], HIGH);
//                else
//                    digitalWrite(LedRed[j], LOW);
//            }

            // save the reading.  Next time through the loop,
            // it'll be the lastButtonState:
            lastButtonState[i] = reading;
            keypadnum = i;
            break;

        }
    }
    return keypadnum;
}

void LedControl(int keypadnum) {
    int i;
    for (i = 0; i < 8; i++) {
        if (lastButtonState[i] == LOW) {
            if (i == keypadnum)
                digitalWrite(LedRed[i], HIGH);
            else
                digitalWrite(LedRed[i], LOW);
        }
    }
}

int main(void) {
    int i, keypadnum = -1;
    if (wiringPiSetupGpio() == -1)
        return 1;
    for (i = 0; i < 8; i++) {
        pinMode(LedRed[i], OUTPUT);
        digitalWrite(LedRed[i], LOW);
    }
    for (i = 0; i < 8; i++)
        pinMode(Keypad[i], INPUT);
    while (1) {
        keypadnum = KeypadRead();
        LedControl(keypadnum);
    }
    return 0;
}
