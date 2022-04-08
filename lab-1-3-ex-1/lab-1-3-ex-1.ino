#include <MsTimer2.h>
int Button = 2; // Arduino Button PIN 정의(인터럽트 0번 사용)
int Led [3] = {5, 6, 7}; // Arduino LED PIN 정의
// Timer function
void LedControl() {
  static int counter = 0; // ISR에서 사용할 배열 인덱스
  static byte output = HIGH; // LED(1, 9) ON/OFF
  // LED(1, 9) ON/OFF 수행
  digitalWrite(Led[counter++], output);
  if (counter > 1) {
    counter = 0; // 배열 인덱스 초기화
    output = ! output; // 현재와 반대 상태로 전환
  }
}
// ISR
void ButtonLedControl() {
  static byte output = HIGH; // LED(16) ON/OFF를 결정할 변수
  digitalWrite(Led[2], output); // LED(16) ON/OFF 수행
  output = ! output; // 현재와 반대 상태로 전환
} 
void setup() {
  int i;
  // Button PIN을 입력으로 설정
  pinMode(Button, INPUT_PULLUP);
  // LED PIN을 출력으로 설정
  for (i = 0; i < 3; i++)
    pinMode(Led[i], OUTPUT);
  // 인터럽트 설정
  attachInterrupt(0, ButtonLedControl, RISING);
  // Timer 설정
  MsTimer2::set(500, LedControl);
  // Timer 시작
  MsTimer2::start();
}
void loop() {
}
