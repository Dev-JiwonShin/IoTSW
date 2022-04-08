void setup() {
  // Digital 13번 핀을 출력으로 설정
  // 16진수 또는 2진수를 이용하여 표현 가능
  DDRB = 0x80; // DDRB = 0b10000000;
}
void loop() {
  // Digital 13번 핀에 5V인가 - LED ON
  PORTB = 0x80; // PORTB = 0b10000000;
  // 1초 지연
  delay(1000);
  // Digital 13번 핀에 0V 인가 - LED OFF
  PORTB = 0x00; // PORTB = 0b00000000;
  // 1초 지연
  delay(1000);
}
