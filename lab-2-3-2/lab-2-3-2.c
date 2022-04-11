#include <wiringPi.h>

const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
const int Keypad[5] = {16, 19, 6, 12, 13};


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

    int stopper = -1;
    while (1) {
        if (stopper == -1) {
            keypadnum = stopper;
            stopper = -1;
        } else {
            keypadnum = KeypadRead();
        }

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
            try
            {
                while (true) {
                    stopper = KeypadRead();
                    if (stopper != -1) {
                        throw stopper;
                    }
                    for (i = 0; i < 8; i++) {
                        LedControl(i);
                        delay(500);
                    }
                }
                digitalWrite(LedRed[i - 1], LOW);
            }
            catch(int index)
            {
                for (i = 7; i >= 0; i--) {
                    digitalWrite(LedRed[i], LOW);
                }
            }
        } else if (keypadnum == 3) {
            try
            {
                while (true) {
                    stopper = KeypadRead();
                    if (stopper != -1) {
                        throw stopper;
                    }
                    for (i = 7; i >= 0; i--) {
                        LedControl(i);
                        delay(500);
                    }
                }
                digitalWrite(LedRed[i + 1], LOW);
            }
            catch(int index)
            {
                for (i = 7; i >= 0; i--) {
                    digitalWrite(LedRed[i], LOW);
                }
            }

        } else if (keypadnum == 4) {
            try
            {
                while (true) {
                    stopper = KeypadRead();
                    if (stopper != -1) {
                        throw stopper;
                    }
                }
            }
            catch(int index)
            {
                for (i = 7; i >= 0; i--) {
                    digitalWrite(LedRed[i], LOW);
                }
            }
        }
    }
    return 0;
}
