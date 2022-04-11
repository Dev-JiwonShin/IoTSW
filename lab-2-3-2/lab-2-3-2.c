#include <stdio.h>
#include <setjmp.h>
#include <wiringPi.h>

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf__, 1)


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
            keypadnum = KeypadRead();
        } else {
            keypadnum = stopper;
            stopper = -1;
        }

        if (keypadnum == 0) {
            TRY
                    {
                        for (i = 0; i < 8; i++) {
                            stopper = KeypadRead();
                            if (stopper != -1) {
                                THROW;
                            }
                            LedControl(i);
                            delay(500);
                        }
                        digitalWrite(LedRed[i - 1], LOW);
                    }
                CATCH
                    {
                        for (i = 7; i >= 0; i--) {
                            digitalWrite(LedRed[i], LOW);
                        }
                    }
            ETRY;

        } else if (keypadnum == 1) {
            TRY
                    {
                        for (i = 7; i >= 0; i--) {
                            stopper = KeypadRead();
                            if (stopper != -1) {
                                THROW;
                            }
                            LedControl(i);
                            delay(500);
                        }
                        digitalWrite(LedRed[i + 1], LOW);
                    }
                CATCH
                    {
                        for (i = 7; i >= 0; i--) {
                            digitalWrite(LedRed[i], LOW);
                        }
                    }
            ETRY;

        } else if (keypadnum == 2) {
            TRY
                    {
                        while (1) {

                            for (i = 0; i < 8; i++) {
                                stopper = KeypadRead();
                                if (stopper != -1) {
                                    THROW;
                                }
                                LedControl(i);
                                delay(500);
                            }
                        }
                        digitalWrite(LedRed[i - 1], LOW);
                    }
                CATCH
                    {
                        for (i = 7; i >= 0; i--) {
                            digitalWrite(LedRed[i], LOW);
                        }
                    }ETRY;
        } else if (keypadnum == 3) {
            TRY
                    {
                        while (1) {

                            for (i = 7; i >= 0; i--) {
                                stopper = KeypadRead();
                                if (stopper != -1) {
                                    THROW;
                                }
                                LedControl(i);
                                delay(500);
                            }
                        }
                        digitalWrite(LedRed[i + 1], LOW);
                    }
                CATCH
                    {
                        for (i = 7; i >= 0; i--) {
                            digitalWrite(LedRed[i], LOW);
                        }
                    }ETRY;

        } else if (keypadnum == 4) {
            TRY
                    {
                        while (1) {
                            stopper = KeypadRead();
                            if (stopper != -1) {
                                THROW;
                            }
                        }
                    }
                CATCH
                    {
                        for (i = 7; i >= 0; i--) {
                            digitalWrite(LedRed[i], LOW);
                        }
                    }ETRY;
        }
    }
    return 0;
}
