enum { REST = 0, DO = 262, RE = 294, MI = 330, FA = 349, SOL = 392, LA = 440, SHI = 494, DO2 = 523 };
#define BUZZER 5 // Arduino PIN 정의
int Num = 9;
int Frequency[] = { DO, RE, MI, REST, FA, SOL, LA, SHI, DO2 }; // 음계 정의
int Delay[] = { 500, 0, 500, 500, 500, 500, 1000, 0, 500 }; // 유지시간 정의
void setup() {
  pinMode(BUZZER, OUTPUT); // 5번 PIN을 출력으로 설정
}
void loop() {
  int i;
  for (i = 0; i < Num; i++) {
    tone(BUZZER, Frequency[i]); // 5번 PIN을 통해 출력
    delay(Delay[i]); // 유지 시간
  }
}
