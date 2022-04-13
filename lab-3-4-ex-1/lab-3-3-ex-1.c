#include <FreeRTOS_AVR.h>
#define MS2TICKS(ms) (ms / portTICK_PERIOD_MS)
#define FND_SIZE 6
const int Keypad[4] = { 2, 3, 21, 20 };
const int FndSelectPin[6] = { 22, 23, 24, 25, 26, 27 };
const int FndPin[8] = { 30, 31, 32, 33, 34, 35, 36, 37 };
const int FndFont[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66,
0x60, 0x7D, 0x07, 0x7F, 0x67 };
SemaphoreHandle_t Sem;
Int SendValue = 0;
int Fnd[ FND_SIZE ] = { 0, };
// FND의 값을 왼쪽으로 Shift하고
// 파라미터로 들어온 새로운 값(data)를 0번지에 넣는 함수
void ShiftInsert( int data ) {
int i;
for( i = 1; i < FND_SIZE; i++ ) {
Fnd[ FND_SIZE – i ] = Fnd[ FND_SIZE – i - 1 ];
}
Fnd[ 0 ] = data;
}


// Keypad ISR
// 전역 변수(sendValue)로 값을 전달하기 때문에 세마포로 보호
void KeypadControl1() {
delay(50);
SendValue = 1;
xSemaphoreGive(Sem);
}
void KeypadControl2() {
delay(50);
SendValue = 2;
xSemaphoreGive(Sem);
}
void KeypadControl3() {
delay(50);
SendValue = 3;
xSemaphoreGive(Sem);
}
void KeypadControl4() {
delay(50);
SendValue = 4;
xSemaphoreGive(Sem);
}
void KeypadTask( void* arg ) {
int i;
int keypad;
while(1) {
// 세마포어를 통해 키패드가 눌렸음을 Keypad ISR로부터
// 전달 받음
// portMAX_DELAY: 세마포를 받기 전까지 Block
// 입력된 번호는 ShiftInsert를 통해 Fnd[ ] 에 삽입
if( xSemaphoreTake(Sem, portMAX_DELAY) ) {
keypad = SendValue;
ShiftInsert(keypad);
}
}
}

void FndSelect( int pos ) {
int i;
for( i = 0; i < 6; i++ ) {
if( i == pos ) {
digitalWrite(FndSelectPin[ i ], LOW);
}
else {
digitalWrite(FndSelectPin[ i ], HIGH);
}
}
}
void FndDisplay( int pos, int num ) {
int i;
int flag = 0;
int shift = 0x01;
FndSelect( pos );
for( i = 0; i < 8; i++ ) {
flag = ( FndFont[ num ] & shift );
digitalWrite( FndPin[ i ], flag );
shift <<= 1;
}
}
void FndTask( void* arg ) {
int i;
// 지속적으로 Fnd[ ] 데이터를 FND에 출력
while(1) {
for( i = 0; i < FND_SIZE; i++ ) {
delay(3);
FndDisplay( i, Fnd[ i ] );
}
}
}


void setup() {
int i;
for( i = 0; i < 6; i++ ) {
pinMode( FndSelectPin[ i ], OUTPUT );
}
for( i = 0; i < 8; i++ ) {
pinMode( FndPin[ i ], OUTPUT );
}
for( i = 0; i < 4; i++ ) {
pinMode( Keypad[ i ], INPUT );
}
attachInterrupt( 0, KeypadControl1, RISING );
attachInterrupt( 1, KeypadControl2, RISING );
attachInterrupt( 2, KeypadControl3, RISING );
attachInterrupt( 3, KeypadControl4, RISING );
vSemaphoreCreateBinary( Sem1 );
xTaskCreate( KeypadTask, NULL, 200, NULL, 2, NULL );
xTaskCreate( FndTask, NULL, 200, NULL, 1, NULL );
vTaskStartScheduler();
}
void loop() {
}

