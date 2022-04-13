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
// Motor 회전 함수
void MotorControl(int rotate) {
if (rotate == LEFT_ROTATE) {
digitalWrite(MOTOR_MT_P_PIN, LOW);
softPwmWrite(MOTOR_MT_N_PIN, 50);
}
else if (rotate == RIGHT_ROTATE) {
digitalWrite(MOTOR_MT_N_PIN, LOW);
softPwmWrite(MOTOR_MT_P_PIN, 50);
}
}int main(void)
{
if (wiringPiSetupGpio() == -1)
return 1;
// Motor 핀 출력으로 설정
pinMode(MOTOR_MT_N_PIN, OUTPUT);
pinMode(MOTOR_MT_P_PIN, OUTPUT);
// Motor 핀 PWM 제어 핀으로 설정
// 주기: 100ms
softPwmCreate(MOTOR_MT_N_PIN, 0, 100);
softPwmCreate(MOTOR_MT_P_PIN, 0, 100);
while (1)
{
MotorControl(LEFT_ROTATE); // Motor 왼쪽으로 회전
delay(2000);
MotorStop(); // Motor 정지
delay(1000);
MotorControl(RIGHT_ROTATE); // Motor 오른쪽으로 회전
delay(2000);
MotorStop(); // Motor 정지
delay(1000);
}
return 0;
}