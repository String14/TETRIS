#include "consol_setting.h"

// 콘솔 커서 위치 변경하는 함수
void gotoxy(int x, int y) {
	COORD Pos = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 콘솔 색상 설정을 위한 함수
void color(int bgColor, int textColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);
}

// 콘솔 환경 설정을 위한 함수
void consol_set() {
	// 콘솔창 설정
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	// 위치 가로, 위치 세로, 콘솔창 가로, 콘솔창 세로 
	MoveWindow(console, 550, 250, 392, 450, TRUE);

	// Title 설정
	system("title TETRIS by GUN");

	// 배경, 글자색 설정
	//system("color 3E"); // 0~F

	// 스크롤바 지우기
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);

	// 커서 지우기
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	cout << fixed;
	cout << showpoint;
}