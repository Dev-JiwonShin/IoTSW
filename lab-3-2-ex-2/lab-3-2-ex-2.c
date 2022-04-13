#include <FreeRTOS_AVR.h>
#define MS2TICKS(ms) (ms / portTICK_PERIOD_MS )
#define LED1 5
#define LED2 6
void LedTask(int* pParam) {
int led, turn, param = *pParam;
if (param == 1) {
led = LED1; turn = HIGH;
}
else {
led = LED2; turn = LOW;
}
while (1) {
digitalWrite(led, turn);
// 500ms 지연
vTaskDelay(MS2TICKS(500));
turn = (turn == HIGH) ? LOW : HIGH;
}
}
void setup() {
// LED, Buzzer Pin 출력으로 설정
int param[2] = { 1, 2 };
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
// Task 생성
xTaskCreate(LedTask, NULL, 200, &param[0], 1, NULL);
xTaskCreate(LedTask, NULL, 200, &param[1], 2, NULL);
// scheduler 시작
vTaskStartScheduler();
}
void loop() {
}