// GPIO Access Library 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
// 각 FND와 연결된 라즈베리파이 핀(S0, S1, …, S5)
const int FndSelectPin[6] = { 4, 17, 18, 27, 22, 23 };
// FND의 LED와 연결된 라즈베리파이 핀(A, B, …, H)
const int FndPin[8] = { 6, 12, 13, 16, 19, 20, 26, 21 };
// FND에 출력되는 문자 (0~9) 배열
const int FndFont[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };


// 초기화 함수, WiringPi 라이브러리 초기화, Select 핀 및 LED 핀 초기화를 담당)
void Init() {
	int i;
	if( wiringPiSetupGpio() == -1 ) {
		printf( "wiringPiSetupGpio() error\n");
		exit(-1);
	}
	for( i = 0; i < 6; i++ ) {
		pinMode( FndSelectPin[ i ], OUTPUT ); // Select 핀을 출력으로 설정
		digitalWrite( FndSelectPin[ i ], HIGH); // Select 핀 OFF
	}
	for( i = 0; i < 8; i++ ) {
		pinMode( FndPin[ i ], OUTPUT ); // LED 핀을 출력으로 설정
		digitalWrite( FndPin[ i ], LOW ); // LED 핀을 OFF
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
		shift <<= 1; // 왼쪽으로 한 비트 쉬프트한다. i = 0이라 하면, ( shift = 0b00000001 )에서 ( shift = 0b00000010)로 변한다.
	}
	digitalWrite( FndSelectPin[ position ], LOW );
}

int main( int argc, char **argv ) {
	if( argc != 3) {
		printf( "Usage: %s [ position ] [ number ] ", argv[ 0 ] );
		exit( -1 );
	}
	Init();
	// argv[1] = position, argv[2] = number, argv는 문자 스트링이므로 정수로 변환
	// int atoi( const char *string )
	FndDisplay( atoi( argv[1] ), atoi( argv[2] ) );
	return 0;
}