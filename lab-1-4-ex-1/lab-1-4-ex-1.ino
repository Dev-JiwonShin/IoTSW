#define BUZZER 5 // Arduino PIN 정의
void setup() {
  pinMode(BUZZER, OUTPUT); // 5번 PIN을 출력으로 설정
}
void loop() {
  tone(BUZZER, 262); // 5번 PIN을 통해 262Hz 출력(도 출력)
  delay(500); // 500ms 유지 시간
  tone(BUZZER, 294); // 5번 PIN을 통해 294Hz 출력(레 출력)
  // delay(500); // 500ms 유지 시간이 없어 소리가 들리지 않음, 주석 제거 시 소리 출력
  tone(BUZZER, 330); // 5번 PIN을 통해 330Hz 출력(미 출력)
  delay(500); // 500ms 유지 시간
  noTone(BUZZER); // 출력 종료
  delay(500); // 500ms 동안 소리 미 출력
  tone(BUZZER, 349); // 5번 PIN을 통해 349Hz 출력(파 출력)
  delay(500); // 500ms 유지 시간
  tone(BUZZER, 392, 500); // 5번 PIN을 통해 392Hz 출력(솔 출력), 0.5초 지속 후 종료
  delay(500); // 500ms 지연
  tone(BUZZER, 440, 500); // 5번 PIN을 통해 440Hz 출력(라 출력), 0.5초 지속 후 종료
  delay(1000); // 1000ms 유지 시간, 0.5초 간 소리 출력 후 0.5초간 소리 미 출력
  tone(BUZZER, 494, 500); // 5번 PIN을 통해 494Hz 출력(시 출력)
  // delay(500); // 500ms 유지 시간이 없어 소리가 들리지 않음, 주석 제거 시 소리 출력
  tone(BUZZER, 523, 500); // 5번 PIN을 통해 523Hz 출력(도 출력), 0.5초 지속 후 종료
  delay(500); // 500ms 지연
}
