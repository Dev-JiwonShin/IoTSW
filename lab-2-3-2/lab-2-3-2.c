// KeyPad 버튼에 따른 LED ON/OFF 순서 변경
// Key 4 선택 시 LED 1~8의 순서로 ON/OFF
// Key 5 선택 시 LED 8~1의 순서로 ON/OFF

// Wiring Pi Library 헤더파일 선언
#include <wiringPi.h>

const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
// 0, 1, 2, 3, 4, 5, 6, 7
const int Keypad[5] = {16, 19, 4, 17, 18};
// 3, 4, 0, 1, 2
// 3, 4 -> 예제
// 0, 1 -> 키패드1 아니면 2 클릭 시 동일한 동작을 반복
// 2    -> 키패드3 클릭 시 현재 수행중인 ON/OFF를 정지


int KeypadRead() {
    int i, keypadnum = -1;
    for (i = 0; i < 5; i++) {
        if (!digitalRead(Keypad[i])) {
            keypadnum = i;
            break;
        }
    }
    return keypadnum;
}

void LedControl(int num) {
    int i;
    for (i = 0; i < 8; i++) {
        if (i == num)
            digitalWrite(LedRed[i], HIGH);
        else
            digitalWrite(LedRed[i], LOW);
    }
}

int main(void) {
    int i, j, keypadnum = -1;
    if (wiringPiSetupGpio() == -1)
        return 1;
    for (i = 0; i < 8; i++) {
        pinMode(LedRed[i], OUTPUT);
        digitalWrite(LedRed[i], LOW);
    }
    for (i = 0; i < 5; i++) {
        pinMode(Keypad[i], INPUT);
    }
    while (1) {
        keypadnum = KeypadRead();
        if (keypadnum == 0) {
            for (i = 0; i < 8; i++) {
                LedControl(i);
                delay(500);
            }
            digitalWrite(LedRed[i - 1], LOW);
        } else if (keypadnum == 1) {
            for (i = 7; i >= 0; i--) {
                LedControl(i);
                delay(500);
            }
            digitalWrite(LedRed[i + 1], LOW);
        } else if (keypadnum == 2) {
            for (i = 0; i < 8; i++) {
                LedControl(i);
                delay(500);
//                if (i == 7) {
//                    digitalWrite(LedRed[i - 1], LOW);
//                    i=0;
//                }
            }
            digitalWrite(LedRed[i - 1], LOW);
        } else if (keypadnum == 3) {
            for (i = 7; i >= 0; i--) {
                LedControl(i);
                delay(500);
            }
            digitalWrite(LedRed[i + 1], LOW);
        } else if (keypadnum == 4) {
//            delay(1000000);
            return 0;
            //            for (i = 7; i >= 0; i--) {
            //                LedControl(i);
            //                delay(500);
            //            }
            //            digitalWrite(LedRed[i + 1], LOW);
        }
    }
    return 0;
}
