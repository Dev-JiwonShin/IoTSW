// KeyPad 버튼을 누르고 있을 경우 동일한 번호의 LED가 ON
// KeyPad 버튼을 누르지 않을 경우 LED 전체 OFF

// Wiring Pi Library 헤더파일 선언
#include <wiringPi.h>

const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
// 0, 1, 2, 3, 4, 5, 6, 7
const int Keypad[8] = {16, 13, 12, 6, 21, 26, 20, 19};
// 3, 2, 1, 0, 7, 6, 5, 4

int KeypadRead() {
    int i, keypadnum = -1;
    for (i = 0; i < 8; i++) {
        if (!digitalRead(Keypad[i])) {
            keypadnum = i;
            break;
        }
    }
    return keypadnum;
}

void LedControl(int keypadnum) {
    int i;
    for (i = 0; i < 8; i++) {
        if (i == keypadnum)
            digitalWrite(LedRed[i], LOW);
        else
            digitalWrite(LedRed[i], HIGH);
    }
}

int main(void) {
    int i, keypadnum = -1;
    if (wiringPiSetupGpio() == -1)
        return 1;
    for (i = 0; i < 8; i++) {
        pinMode(LedRed[i], OUTPUT);
        digitalWrite(LedRed[i], HIGH);
    }
    for (i = 0; i < 8; i++)
        pinMode(Keypad[i], INPUT);
    while (1) {
        keypadnum = KeypadRead();
        LedControl(keypadnum);
    }
    return 0;
}