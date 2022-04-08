void pinMode_(uint8_t pin, uint8_t mode)
{
  uint8_t bit = digitalPinToBitMask(pin); // 전달된 pin에 대응하는 레지스터를 표시하는 bit를 찾음
  uint8_t port = digitalPinToPort(pin); // 전달된 pin에 해당하는 PORT를 찾음
  volatile uint8_t *reg;
  if (port == NOT_A_PIN) return; // 전달된 pin에 해당하는 port가 존재하지 않으면 함수 종료
  // 사용자가 pin 번호를 잘못 입력했을 경우를 대비
  reg = portModeRegister(port); // PORT에 해당하는 DDR을 찾음
  if (mode == INPUT) {
//    …
    *reg &= ~bit; // INPUT 모드 설정
//    …
  }
  else {
//    …
    *reg |= bit; // OUTPUT 모드 설정
//    …
  }
}

void digitalWrite_(uint8_t pin, uint8_t val)
{
  uint8_t bit = digitalPinToBitMask(pin); // 전달된 pin에 대응하는 레지스터를 표시하는 bit를 찾음
  uint8_t port = digitalPinToPort(pin); // 전달된 pin에 해당하는 PORT를 찾음
  volatile uint8_t *out;
  if (port == NOT_A_PIN) return; // 전달된 pin에 해당하는 port가 존재하지 않으면 함수 종료
  // 사용자가 pin 번호를 잘못 입력했을 경우를 대비
  out = portOutputRegister(port); // PORT에 해당하는 Port Output Register를 찾음
  if (val == LOW)
    *out &= ~bit; // 0V 출력
  else {
    *out |= bit; // 5V 출력
  }
}

uint8_t Led[4] = {5, 6, 7, 8}; // Arduino PIN 정의
void setup() {
  int i;
  for (i = 0; i < 4; i++)
    pinMode_(Led[i], OUTPUT); // 각 PIN을 출력으로 설정
}

void loop() {
  int i;
  for (i = 0; i < 4; i++) {
    digitalWrite_(Led[i], HIGH); // 순차적으로 PIN에 HIGH 출력(RED LED ON)
    delay(500); // 500ms 지연
    digitalWrite_(Led[i], LOW); // 순차적으로 PIN에 LOW 출력(RED LED OFF)
    delay(500); // 500ms 지연
  }
}
