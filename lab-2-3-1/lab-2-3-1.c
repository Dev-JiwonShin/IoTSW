#include <stdbool.h>
#include <wiringPi.h>

const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
// 0, 1, 2, 3, 4, 5, 6, 7
const int Keypad[8] = {16, 13, 12, 6, 21, 26, 20, 19};
// 3, 2, 1, 0, 7, 6, 5, 4

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


int KeypadRead() {

    int i, keypadnum = -1;
    for (i = 0; i < 8; i++) {
//        if (debounce(Keypad[i]) == 1) {
//            keypadnum = i;
//            break;
//        }


        int reading = !digitalRead(Keypad[i]);
        if (reading) {
            keypadnum = i;
            break;
        }


//        int reading = digitalRead(Keypad[i]); //스위치 버턴상태값을 읽는다.

//
//        if (reading) {
//
//            if (reading != lastButtonState) { //현재 읽은 버턴의 상태값과 이전상태가 다른지 체크
//                lastDebounceTime = millis(); // 다르면 변화(On/Off)가 일어난거니 그 시간을 변수에 저장시킨다.
//            }
//
//            if ((millis() - lastDebounceTime) > debounceDelay) {  //버턴변화가 50시간값 안에 발생했으면 바운스(채터링)으로 무시
//
//                if (reading != buttonState) { // 버턴이 On/Off 됐는지 확인(버턴의 변화가 일어났는가)
//                    buttonState = reading; //버턴의 변화가 일어났으면 그 변화를 기록했다가 다음 버턴 변화의 비교대상이 됨
////                if (reading) {
//                    keypadnum = i;
//                    break;
////                }
//                }
//            }
//        }
//
//        lastButtonState = reading; //현재 읽은 버턴의 상태를 다음 버턴의 상태와 비교하기 위해 변수에 저장한다.
//
//
////        if (!digitalRead(Keypad[i])) {
////            keypadnum = i;
////            break;
////        }
//    }
        return keypadnum;
    }

    void LedControl(int keypadnum) {
        int i;
        for (i = 0; i < 8; i++) {
            if (i == keypadnum)
                digitalWrite(LedRed[i], HIGH);
            else
                digitalWrite(LedRed[i], LOW);
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
