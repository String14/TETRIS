#pragma once
// ���� ���̺귯�� ����Ʈ
#include <iostream> // �����
#include <iomanip> // ����� ����
#include <windows.h> // �ý���
#include <conio.h> // Ű���� �̺�Ʈ
#include <time.h> // �ð�
#include <string> // ���ڿ�
#include <fstream> // ���� �����
#include <algorithm> // ����
#include <functional> // ��������
using namespace std;

#pragma once

// �ܼ� Ŀ�� ��ġ �����ϴ� �Լ�
void gotoxy(int x, int y);

// �ܼ� ���� ������ enum ����
enum colorName {
	BLACK, D_BLUE, D_GREEN, D_SKYBLUE,
	D_RED, D_VIOLET, D_YELLOW, GRAY,
	D_GRAY, BLUE, GREEN, SKYBLUE, RED,
	VIOLET, YELLOW, WHITE
};

// �ܼ� ���� ������ �Լ�
void color(int bgColor, int textColor);

// �ܼ� ȯ�� ������ ���� �Լ�
void consol_set();