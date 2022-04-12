// GPIO Access Library 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

// 각 FND와 연결된 라즈베리파이 핀(S0, S1, …, S5)
const int FndSelectPin[6] = {4, 17, 18, 27, 22, 23};
// FND의 LED와 연결된 라즈베리파이 핀(A, B, …, H)
const int FndPin[8] = {6, 12, 13, 16, 19, 20, 26, 21};
// FND에 출력되는 문자 (0~9) 배열
const int FndFont[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };

const int FndFont_dot[10] = { 0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xE7 };


// 0. |	191	/277	0xBF	1 0 1 1   1 1 1 1
// 1. |	134	/206	0x86	1 0 0 0   0 1 1 0
// 2. |	219	/333	0xDB	1 1 0 1   1 0 1 1
// 3. |	207	/317	0xCF	1 1 0 0   1 1 1 1
// 4. |	230	/346	0xE6	1 1 1 0   0 1 1 0
// 5. |	237	/355	0xED	1 1 1 0   1 1 0 1
// 6. |	253	/375	0xFD	1 1 1 1   1 1 0 1
// 7. |	135	/207	0x87	1 0 0 0   0 1 1 1
// 8. |	255	/377	0xFF	1 1 1 1   1 1 1 1
// 9. |	231	/347	0xE7	1 1 1 0   0 1 1 1


// Set timer
unsigned long pre_time = 0;
unsigned long cur_time = 0;
const int duration = 10;


// 초기화 함수, WiringPi 라이브러리 초기화, Select 핀 및 LED 핀 초기화를 담당)
void Init() {
	int i;
	if (wiringPiSetupGpio() == -1) {
		printf("wiringPiSetupGpio() error\n");
		exit(-1);
	}
	for (i = 0; i < 6; i++) {
        pinMode(FndSelectPin[i], OUTPUT); // Select 핀을 출력으로 설정
        digitalWrite(FndSelectPin[i], HIGH); // Select 핀 OFF
    }
    for (i = 0; i < 8; i++) {
        pinMode(FndPin[i], OUTPUT); // LED 핀을 출력으로 설정
        digitalWrite(FndPin[i], LOW); // LED 핀을 OFF
    }
}

// FND를 선택하는 함수, S0 ~ S5 중 파라미터(position)에 해당하는 FND 선택
void FndSelect(int position) {
	int i;
	for (i = 0; i < 6; i++) {
		if (i == position) {
            digitalWrite(FndSelectPin[i], LOW); // 선택된 FND의 Select 핀 ON
            } else {
            digitalWrite(FndSelectPin[i], HIGH); // 선택되지 않은 FND의 Select 핀 OFF
        }
    }
}

// FND를 출력하는 함수
// void FndDisplay(int position, int num, int cnt) {
	void FndDisplay(int position, int num) {
		int i;
    int flag = 0; // FndPin[ ]을 ON/OFF
    int shift = 0x01; // FndFont와 And 연산하여 출력할 LED의 상태 결정
    for (i = 0; i < 8; i++) {
    	// if(i!=4){
    		flag = (FndFont[num] & shift);
    	// }
    	// else{
    		// flag = (FndFont_dot[num] & shift); 
    	// }
    	digitalWrite(FndPin[i], flag); 
    	shift <<= 1; 
    }
    FndSelect(position);
}

int main() {
	int pos, cnt = -1;
    int data[6] = {0, 1, 2, 3, 4, 5}; // 출력할 문자 데이터
    pre_time = millis();
    Init();

    while (cnt < 10) {
    	
    	while (1) {
    		cur_time = millis();
    		if (cur_time - pre_time >= duration) {
                pre_time = cur_time;// Update previous counter time.
                break;
                } else {

                	for (pos = 0; pos < 6; pos++) {
     //            		switch (cnt) {
     //            			case 0 :
     //            			break;
     //            			case 1:
     //            			break;
     //            			case 2:
     //            			break;
     //            			case 3:
     //            			break;
     //            			case 4:
     //            			break;
     //            			case 5:
     //            			break;
     //            			default :
     //            			break;
    	// }
    	            // FndDisplay( pos, data[ pos ], cnt);
    	            FndDisplay(pos, data[pos]);
                    // WiringPi 라이브러리에서 정의된 delay() 함수, void delay( unsinged int howLong )
                }
                delay(1); 
            }
        }
        // delay(500);
        cnt++;
        if (cnt == 10)
        cnt = 0;
    }


// for( int i = 0; i < 6; i++ ) {

// 	while(1) {
// 		for( pos = 0; pos < 6; pos++ ) {
// 			// FndDisplay( pos, data[ pos ], cnt);
// 			FndDisplay( pos, data[ pos ]);
// 			delay(1); // WiringPi 라이브러리에서 정의된 delay() 함수, void delay( unsinged int howLong )
// 		}
// 	}		
// 		delay(500); // WiringPi 라이브러리에서 정의된 delay() 함수, void delay( unsinged int howLong )
// 	}


return 0;
}
