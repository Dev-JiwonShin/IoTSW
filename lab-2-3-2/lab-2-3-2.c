// KeyPad 버튼에 따른 LED ON/OFF 순서 변경
// Key 4 선택 시 LED 1~8의 순서로 ON/OFF
// Key 5 선택 시 LED 8~1의 순서로 ON/OFF

// Wiring Pi Library 헤더파일 선언
#include <wiringPi.h>

const int LedRed[8] = {4, 17, 18, 27, 22, 23, 24, 25};
// 0, 1, 2, 3, 4, 5, 6, 7
//const int Keypad[5] = {16, 19, 17, 18, 27};
//const int Keypad[5] = {16, 19, 4, 17, 18};
const int Keypad[5] = {16, 19, 6, 12, 13};
//const int Keypad[8] = {16, 13, 12, 6, 21, 26, 20, 19};
// 3, 2, 1, 0, 7, 6, 5, 4

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

// 쓰레드 함수
void *t_function(void *data) {
    pid_t pid;            // process id
    pthread_t tid;        // thread id

    pid = getpid();
    tid = pthread_self();

    char *thread_name = (char *) data;
    int i = 0;

    while (i < 3)   // 0,1,2 까지만 loop 돌립니다.
    {
        // 넘겨받은 쓰레드 이름과
        // 현재 process id 와 thread id 를 함께 출력
        printf("[%s] pid:%u, tid:%x --- %d\n",
               thread_name, (unsigned int) pid, (unsigned int) tid, i);
        i++;
        sleep(1);  // 1초간 대기
    }
}

int main(void) {
//    pthread_t p_thread[2];
//    int thr_id;
//    int status;
//    char p1[] = "onClickListener";   // 1번 쓰레드 이름
//    char p2[] = "thread_2";   // 2번 쓰레드 이름
//    char pM[] = "thread_m";   // 메인 쓰레드 이름
//
//
//    // 1번 쓰레드 생성
//    // 쓰레드 생성시 함수는 t_function
//    // t_function 의 매개변수로 p1 을 넘긴다.
//    thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *) p1);
//
//    // pthread_create() 으로 성공적으로 쓰레드가 생성되면 0 이 리턴
//    if (thr_id < 0) {
//        perror("thread create error : ");
//        exit(0);
//    }
//
//    // 2번 쓰레드 생성
//    thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *) p2);
//    if (thr_id < 0) {
//        perror("thread create error : ");
//        exit(0);
//    }
//
//    // main() 함수에서도 쓰레드에서 돌아가고 있는 동일한 함수 실행
//    t_function((void *) pM);
//
//    // 쓰레드 종료를 기다린다.
//    pthread_join(p_thread[0], (void **) &status);
//    pthread_join(p_thread[1], (void **) &status);


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
    int looper = -1;
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
//            stopper = 1;
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
            //            delay(1000000);
//            return 0;
            //            for (i = 7; i >= 0; i--) {
            //                LedControl(i);
            //                delay(500);
            //            }
            //            digitalWrite(LedRed[i + 1], LOW);
        }
    }
    return 0;
}
