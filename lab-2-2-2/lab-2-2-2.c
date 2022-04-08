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
void LEDControl(int pinnum)
{
  int i;
  for (i = 0; i < 16; i++)
  {
    if (i == pinnum){
      digitalWrite(Led[i], LED_ON);
      digitalWrite(Led[i+1], LED_ON);
}

    else
      digitalWrite(Led[i], LED_OFF);
  }
} int main(void)
{
  int i;
  if (wiringPiSetupGpio() == -1)
    return 1;
  for (i = 0; i < 16; i++)
  {
    pinMode(Led[i], OUTPUT);
    digitalWrite(Led[i], LED_OFF);
  }
  while (1)
  {
    for (i = 0; i < 8; i++)
    {
      LEDControl(i);
      delay(500);
	i++;
    } 
  return 0;
}
