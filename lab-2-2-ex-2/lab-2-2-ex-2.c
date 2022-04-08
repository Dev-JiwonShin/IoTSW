#include <wiringPi.h>// Wiring Pi Library 헤더파일 선언
#define LED_OFF 0 // LED OFF 정의
#define LED_ON 1 // LED ON 정의
#define LED_RED 2 // LED RED 정의
#define LED_GREEN 3 // LED GREEN 정의
// 라즈베리파이 및 LED RED / GREEN 핀 정의
const int LedRed [8] = { 4, 17, 18, 27, 22, 23, 24, 25 };
const int LedGreen [8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
void LEDControl(int color) {
  int i;
  if (color == LED_RED) {
    for (i = 0; i < 8; i++) {
      digitalWrite(LedRed[i], LED_ON);
      digitalWrite(LedGreen[i], LED_OFF);
    }
  }
  else if (color == LED_GREEN) {
    for (i = 0; i < 8; i++) {
      digitalWrite(LedRed[i], LED_OFF);
      digitalWrite(LedGreen[i], LED_ON);
    }
  }
} int main(void)
{
  int i;
  if (wiringPiSetupGpio() == -1)
    return 1;
  for (i = 0; i < 8; i++)
  {
    pinMode(LedRed[i], OUTPUT);
    pinMode(LedGreen[i], OUTPUT);
    digitalWrite(LedRed[i], LED_OFF);
    digitalWrite(LedGreen[i], LED_OFF);
  }
  while (1)
  {
    LEDControl(LED_RED);
    delay(500);
    LEDControl(LED_GREEN);
    delay(500);
  }
  return 0;
}
