// GPIO Access Library 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
// 각 FND와 연결된 라즈베리파이 핀(S0, S1, …, S5)
const int FndSelectPin[6] = { 4, 17, 18, 27, 22, 23 };
// FND의 LED와 연결된 라즈베리파이 핀(A, B, …, H)
const int FndPin[8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
// FND에 출력되는 문자 (0~9) 배열
// const int FndFont[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };
// const int FndFont[6] = {0x76,0x79,0x38,0x38,0x3F,0x7F};
const int FndFont[6] = {0x7F,0x3F,0x38,0x38,0x79,0x76};

// 초기화 함수, WiringPi 라이브러리 초기화, Select 핀 및 LED 핀 초기화를 담당)
void Init() {
	int i;
	if( wiringPiSetupGpio() == -1 ) {
		printf( "wiringPiSetupGpio() error\n");
		exit(-1);
	}
	for( i = 0; i < 6; i++ ) {
		pinMode( FndSelectPin[ i ], OUTPUT ); // Select 핀을 출력으로 설정
		digitalWrite( FndSelectPin[ i ], HIGH ); // Select 핀 OFF
	}
	for( i = 0; i < 8; i++ ) {
		pinMode( FndPin[ i ], OUTPUT ); // LED 핀을 출력으로 설정
		digitalWrite( FndPin[ i ], LOW ); // LED 핀을 OFF
	}
}

// FND를 선택하는 함수, S0 ~ S5 중 파라미터(position)에 해당하는 FND 선택
void FndSelect (int position) {
	int i;
	for( i = 0; i < 6; i++ ) {
		if( i == position ) {
			digitalWrite( FndSelectPin[ i ], LOW ); // 선택된 FND의 Select 핀 ON
		}
		else {
			digitalWrite( FndSelectPin[ i ], HIGH ); // 선택되지 않은 FND의 Select 핀 OFF
		}
	}
}

// FND를 출력하는 함수
void FndDisplay(int position, int num) {
	int i, j;
	int flag = 0; // FndPin[ ]을 ON/OFF
	int shift = 0x01; // FndFont와 And 연산하여 출력할 LED의 상태 결정
	for( i = 0; i < 8; i++ ) {
		flag = ( FndFont[num] & shift ); // i = 0, FndFont[ 0 ] = 0x3F라 하면 (0b00111111 & 0b00000100 = 1) 이다.
		digitalWrite( FndPin[ i ], flag ); // FndPin[ ]을 flag( 0또는 1 )로 ON/OFF
		shift <<= 1; // 왼쪽으로 한 비트 쉬프트한다. I = 0이라 하면, ( shift = 0b00000001 )에서 ( shift = 0b00000010)로 변한다.
	}
	FndSelect( position ) ;
}

int main() {
	int pos;
	// int data[6] = { 0, 1, 2, 3, 4, 5 }; // 출력할 문자 데이터
	// output : 5 4 3 2 1 0
	// int data[6] = {  5,4,3,2,1,0 }; // 출력할 문자 데이터
	// output : 0 1 2 3 4 5
	char data[] = "OLLEH"; // 출력할 문자 데이터
	Init();
	while(1) {
		for( pos = 0; pos < 6; pos++ ) {
			FndDisplay( pos, data[ pos ] );
			delay(1); // WiringPi 라이브러리에서 정의된 delay() 함수, void delay( unsinged int howLong )
		}
	}
	return 0;
}