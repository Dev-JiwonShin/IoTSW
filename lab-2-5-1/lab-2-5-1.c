#include <wiringPi.h> // GPIO Access Library 헤더파일 선언
#include <softPwm.h> // Software PWM library 헤더파일 선언
// Motor 핀 설정
#define MOTOR_MT_N_PIN 17
#define MOTOR_MT_P_PIN 4
// Motor 회전 방향 정의
#define LEFT_ROTATE 1
#define RIGHT_ROTATE 2

// Motor 정지 함수
void MotorStop() {
    softPwmWrite(MOTOR_MT_N_PIN, 0);
    softPwmWrite(MOTOR_MT_P_PIN, 0);
}

// Motor 회전&속도 제어 함수
void MotorControl(int rotate,int speed) {
    if (rotate == LEFT_ROTATE) {
        digitalWrite(MOTOR_MT_P_PIN, LOW);
        softPwmWrite(MOTOR_MT_N_PIN, speed);
    } 
    else if (rotate == RIGHT_ROTATE) {
        digitalWrite(MOTOR_MT_N_PIN, LOW);
        softPwmWrite(MOTOR_MT_P_PIN, speed);
    }
}

int main(void) {
    if (wiringPiSetupGpio() == -1)
    return 1;
// Motor 핀 출력으로 설정
pinMode(MOTOR_MT_N_PIN, OUTPUT);
pinMode(MOTOR_MT_P_PIN, OUTPUT);
// Motor 핀 PWM 제어 핀으로 설정
// 주기: 100ms
softPwmCreate(MOTOR_MT_N_PIN, 0, 128);
softPwmCreate(MOTOR_MT_P_PIN, 0, 128);
while (1) {
    MotorControl(LEFT_ROTATE,25); 
    delay(2000);
        MotorStop(); // Motor 정지
        delay(2000);

        MotorControl(LEFT_ROTATE,50); 
        delay(2000);
        MotorStop(); // Motor 정지
        delay(2000);

        MotorControl(LEFT_ROTATE,75); 
        delay(2000);
        MotorStop(); // Motor 정지
        delay(2000);

        MotorControl(LEFT_ROTATE,100); 
        delay(2000);
        MotorStop(); // Motor 정지
        delay(4000);
        
        MotorControl(RIGHT_ROTATE,100); 
        delay(2000);
        MotorStop(); // Motor 정지
        delay(2000);
        
        MotorControl(RIGHT_ROTATE,75); 
        delay(2000);
        MotorStop(); // Motor 정지
        delay(2000);
        
        MotorControl(RIGHT_ROTATE,50); 
        delay(2000);
        MotorStop(); // Motor 정지
        delay(2000);
        
        MotorControl(RIGHT_ROTATE,25); 
        delay(2000);
        MotorStop(); // Motor 정지
        delay(4000);

    }
    return 0;
}