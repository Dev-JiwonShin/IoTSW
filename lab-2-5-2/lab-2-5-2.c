// Wiring Pi Library 헤더파일 선언
#include <wiringPi.h>
// LED ON/OFF 정의
#define LED_ON 1
#define LED_OFF 0

// 라즈베리파이 및 LED 핀 정의
const int Led[16] = {
    4, 17, 18, 27, 22, 23, 24, 25,
    6, 12, 13, 16, 19, 20, 26, 21
};

int main(void) {
    int i; // for문 변수
    if (wiringPiSetupGpio() == -1) {
        return 1;
    }
    for (i = 0; i < 16; i++) {
        pinMode(Led[i], OUTPUT); // LED 핀 출력모드 설정
        digitalWrite(Led[i], LED_OFF); // LED 전체 OFF
    }

    softPwmCreate(Led[0], 0, 128);

    while (1) {
        int cnt = 0;
        while (cnt < 100) {
            softPwmWrite(Led[0], cnt);
            delay(50);
            cnt++;
        }
        delay(100);

        while (cnt > 0) {
            softPwmWrite(Led[0], cnt);
            delay(50);
            cnt--;
        }
        delay(100);
    }
    return 0;
}
