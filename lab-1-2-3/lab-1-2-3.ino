#include <MsTimer2.h>

//int Led[8] = {5, 5, 6, 6, 7, 7, 8, 8}; // Arduino PIN 정의
int Led[9] = {5, 5, 6, 6, 7, 7, 8, 8, 9}; // Arduino PIN 정의


void LedControl() {
  static int counter = 0;
    static int roundCounter = 0;

  static byte output = HIGH; // LED ON/OFF를 결정할 변수
  digitalWrite(Led[counter++], output); // LED ON/OFF 수행
     digitalWrite(Led[8], output); // LED ON/OFF 수행

//   if (roundCounter > 0 ) {
//
//   }   else if (roundCounter > 7 ) {
//   }   else if (roundCounter > 15 ) {
//   }   else if (roundCounter > 23 ) {
//   }
 
  
  
  output = ! output; // 현재와 반대 상태로 전환

  if (counter > 7 ) {
    counter = 0; // 배열 인덱스 초기화
  }
}

void setup() {
  int j;
  int i;
  for (i = 0; i < 9; i++)
    pinMode(Led[i], OUTPUT); // 각 PIN을 출력으로 설정

  for (j = 0; j < 5; j++)
  {
    if (j == 0) {
      MsTimer2::set(500, LedControl); // Timer 설정
      MsTimer2::start(); // Timer 시작
      delay(4000);
    }
    else if (j == 1) {
      MsTimer2::set(1000, LedControl); // Timer 설정
      MsTimer2::start(); // Timer 시작
      delay(8000);
    }
    else if (j == 2) {
      MsTimer2::set(1500, LedControl); // Timer 설정
      MsTimer2::start(); // Timer 시작
      delay(12000);
    }
    else if (j == 3) {
      MsTimer2::set(2000, LedControl); // Timer 설정
      MsTimer2::start(); // Timer 시작
      delay(16000);
    }
    else if (j == 4) {
      j = -1;
    }

    Serial.begin(9600);
    Serial.println("here");
  }

}
void loop() { 
//  MsTimer2::set(1000, LedControl_16); // Timer 설정
//  MsTimer2::start(); // Timer
}
