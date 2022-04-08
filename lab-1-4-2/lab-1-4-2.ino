enum { REST = 0, DO = 262, RE = 294, MI = 330, FA = 349, SOL = 392, LA = 440, SHI = 494, DO2 = 523 };
#define BUZZER 5 // Arduino PIN 정의
int Num = 97;
int Frequency[97] = {DO, REST, DO, REST, DO, REST, DO, REST, DO, REST, MI, REST, SOL, REST, SOL, REST, MI, REST, DO, REST, SOL, REST, SOL, REST, MI, REST, SOL, REST, SOL, REST, MI, REST, DO, REST, DO, REST, DO, REST,SOL, REST, SOL, REST, MI, REST, DO, REST, SOL, REST, SOL, REST, SOL, REST, SOL, REST, SOL, REST, MI, REST, DO, REST, SOL, REST, SOL, REST, SOL, REST, SOL, REST, SOL, REST, MI, REST, DO, REST, SOL, REST, SOL, REST, SOL, REST, LA, REST, SOL, REST, DO2, REST, SOL, REST, DO2, REST, SOL, REST, MI, REST, RE, REST, DO};

int Delay[97] = {500, 0, 250, 0, 250, 0, 500, 0, 500, 0, 500, 0, 250, 0, 250, 0, 500, 0, 500, 0, 250, 0, 250, 0, 500, 0, 250, 0, 250, 0, 500, 0, 500, 0, 500, 0, 1000, 0, 500, 0, 500, 0, 500, 0, 500, 0, 500, 0, 500, 0, 1000, 0, 500, 0, 500, 0, 500, 0, 500, 0, 500, 0, 500, 0, 1000, 0, 500, 0, 500, 0, 500, 0, 500, 0, 250, 0, 250, 0, 250, 0, 250, 0, 1000, 0, 500, 0, 500, 0, 500, 0, 500, 0, 500, 0, 500, 0, 1000};

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
