enum { REST=0, DO=262, RE=294, MI=330, FA=349, SOL=392, LA=440, SHI=494, DO2=523 };
#define BUZZER 5 // Arduino PIN 정의
int Num = 48;
int Frequency[] = {SOL, REST,SOL,REST, LA,REST, LA,REST, SOL, REST,SOL, REST,MI, REST,SOL, REST,SOL, REST,MI, REST,MI, REST,RE, REST,SOL, REST,SOL, REST,LA, REST,LA, REST,SOL, REST,SOL,REST, MI, REST,SOL, REST,MI, REST,RE, REST,MI, REST,DO};
int Delay[] = { 500,  0, 500,  0,500,  0,500, 0, 500, 0, 500, 0, 1000,  0,500, 0, 500,  0,500,  0,500, 0, 1500,  0,500,   0,500,  0,500, 0, 500,  0,500, 0, 500,  0,1000,  0,500, 0, 500,  0,500,  0,500,  0,1500};

void setup() {
  pinMode(BUZZER, OUTPUT); // 5번 PIN을 출력으로 설정
}

void loop() {
  int i;
  for(i=0; i<Num; i++) {
tone(BUZZER, Frequency[i]); // 5번 PIN을 통해 출력
delay(Delay[i]); // 유지 시간
}
}
