#include <MsTimer2.h>
//int Led[8] = {5, 5, 6, 6, 7, 7, 8, 8}; // Arduino PIN 정의
//int Led[8] = {5, 6,5,6,7,8,7,8}; // Arduino PIN 정의
//int Led[8] = {5,6,7,8}; // Arduino PIN 정의
int Led[32] = {5, 5, 6, 6, 7, 7, 8, 8, 5, 5, 6, 6, 7, 7, 8, 8, 5, 5, 6, 6, 7, 7, 8, 8, 5, 5, 6, 6, 7, 7, 8, 8}; // Arduino PIN 정의

void LedControl() {
  static int counter = 0;
  static byte output = HIGH; // LED ON/OFF를 결정할 변수
  digitalWrite(Led[counter++], output); // LED ON/OFF 수행
  output = ! output; // 현재와 반대 상태로 전환

  if (counter > 31 ) {
    counter = 0; // 배열 인덱스 초기화
  }
}
void setup() {
  int i;
  for (i = 0; i < 32; i++) {
    pinMode(Led[i], OUTPUT); // 각 PIN을 출력으로 설정
    if (i < 8) {
      MsTimer2::set(500, LedControl); // Timer 설정
      MsTimer2::start(); // Timer 시작
      delay(500);
    }
    else if (i < 16) {
      MsTimer2::set(1000, LedControl); // Timer 설정
      MsTimer2::start(); // Timer 시작
      delay(1000);
    }
    else if (i < 24) {
      MsTimer2::set(1500, LedControl); // Timer 설정
      MsTimer2::start(); // Timer 시작
      delay(1500);
    }
    else if (i < 32) {
      MsTimer2::set(2000, LedControl); // Timer 설정
      MsTimer2::start(); // Timer 시작
      delay(2000);
      if (i == 31) {
        i = 0;
        //        MsTimer2::set(5000, LedControl); // Timer 설정
        //           MsTimer2::start(); // Timer 시작

      }
    }
  }



  //MsTimer2::stop(); // Timer 정지


}
void loop() {
}
