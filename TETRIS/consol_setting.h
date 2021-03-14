#pragma once
// 내장 라이브러리 임폴트
#include <iostream> // 입출력
#include <iomanip> // 입출력 포맷
#include <windows.h> // 시스템
#include <conio.h> // 키보드 이벤트
#include <time.h> // 시간
#include <string> // 문자열
#include <fstream> // 파일 입출력
#include <algorithm> // 정렬
#include <functional> // 내림차순
using namespace std;

#pragma once

// 콘솔 커서 위치 변경하는 함수
void gotoxy(int x, int y);

// 콘솔 색상 설정용 enum 선언
enum colorName {
	BLACK, D_BLUE, D_GREEN, D_SKYBLUE,
	D_RED, D_VIOLET, D_YELLOW, GRAY,
	D_GRAY, BLUE, GREEN, SKYBLUE, RED,
	VIOLET, YELLOW, WHITE
};

// 콘솔 색상 설정용 함수
void color(int bgColor, int textColor);

// 콘솔 환경 설정을 위한 함수
void consol_set();