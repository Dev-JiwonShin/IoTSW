#include <MsTimer2.h>

int Led[8] = {5, 5,6,6, 7,7,8, 8}; // Arduino PIN 정의

void LedControl() {
  static int counter = 0;
  static byte output = HIGH; // LED ON/OFF를 결정할 변수
  digitalWrite(Led[counter++], output); // LED ON/OFF 수행
    output = ! output; // 현재와 반대 상태로 전환

  if (counter > 7 ) {
    counter = 0; // 배열 인덱스 초기화
//    output = ! output; // 현재와 반대 상태로 전환

  }
}
void setup() {
 
  
  int i;
  for (i = 0; i < 8; i++)
    pinMode(Led[i], OUTPUT); // 각 PIN을 출력으로 설정
  MsTimer2::set(500, LedControl); // Timer 설정
  MsTimer2::start(); // Timer 시작
Serial.begin(9600);
Serial.println("here");
}
void loop() {
}
