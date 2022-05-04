// FreeRTOS 라이브러리 사용을 위한 헤더파일 선언
#include <FreeRTOS_AVR.h>
// FreeRTOS Delay 함수에서 사용하기 위한 매크로 함수: ms -> ticks 변환
#define MS2TICKS(ms) (ms / portTICK_PERIOD_MS )
// Arduino Pin 정의
#define LED 5
#define BUZZER 9
// 음계 정의
enum { REST=0, DO=262, RE=294, MI=330, FA=349, SOL=392, LA=440, SHI=494, DO2=523 };
int Num = 9;
int Frequency[] = { DO, RE, MI, REST, FA, SOL, LA, SHI, DO2 }; // 음계 정의
int Delay[] = { 500, 0, 500, 500, 500, 500, 1000, 0, 500 }; // 유지시간 정의
void LedTask(void* arg) {
while (1) {
// LED ON
digitalWrite(LED, HIGH);
// 500ms 지연
vTaskDelay(MS2TICKS(500));
// LED OFF
digitalWrite(LED, LOW);
// 500ms 지연
vTaskDelay(MS2TICKS(500));
}
}
void BuzzerTask(void* arg) {
int i;
while (1) {
for (i = 0; i < Num; i++) {
// 9번 PIN을 통해 출력
tone(BUZZER, Frequency[i]);
// 유지 시간
vTaskDelay(MS2TICKS(Delay[i]));
}
}
}
void setup() {
// LED, Buzzer Pin 출력으로 설정
pinMode(LED, OUTPUT);
pinMode(BUZZER, OUTPUT);
// Task 생성
xTaskCreate(LedTask, NULL, 200, NULL, 1, NULL);
xTaskCreate(BuzzerTask, NULL, 200, NULL, 2, NULL);
// scheduler 시작
vTaskStartScheduler();
}
void loop() {
}

