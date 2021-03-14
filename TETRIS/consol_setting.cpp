#include "consol_setting.h"

// �ܼ� Ŀ�� ��ġ �����ϴ� �Լ�
void gotoxy(int x, int y) {
	COORD Pos = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// �ܼ� ���� ������ ���� �Լ�
void color(int bgColor, int textColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);
}

// �ܼ� ȯ�� ������ ���� �Լ�
void consol_set() {
	// �ܼ�â ����
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	// ��ġ ����, ��ġ ����, �ܼ�â ����, �ܼ�â ���� 
	MoveWindow(console, 550, 250, 392, 450, TRUE);

	// Title ����
	system("title TETRIS by GUN");

	// ���, ���ڻ� ����
	//system("color 3E"); // 0~F

	// ��ũ�ѹ� �����
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);

	// Ŀ�� �����
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	cout << fixed;
	cout << showpoint;
}