#include "consol_setting.h"
#include "TETRIS.h"

// made by �ڰ���

int main() {
	// �ܼ� ȯ�� ����
	consol_set();

	// ��Ʈ���� ��ü ����
	TETRIS MY_TETRIS;

	// ����
	gotoxy(11, 8);
	cout << "GAME START" << endl << endl;

	// ������ ����
	// Ŭ������ �ɹ� �Լ��� ���ٽ� ���
	/*thread T1([&]()
	{
		MY_TETRIS.threadBLOCK();
	});*/

	// ���� ����
	while (MY_TETRIS.isGAME()) {
		// �� & ��� & �������̽� ����
		MY_TETRIS.setBLOCKinMAP();

		// �� & ��� & �������̽� ���
		MY_TETRIS.printTETRISmap();
		MY_TETRIS.printINTERFACE();

		// ��� �ڵ������� �Ʒ��� �������� �ϱ�
		MY_TETRIS.threadBLOCK();

		// ���� Ž��
		if (MY_TETRIS.isGAME() == OVER) {
			Sleep(500);
			break;
		}
	}

	// ������ ����
	//T1.join();

	// ����
	system("cls");
	gotoxy(15, 10);
	cout << "GAME OVER" << endl << endl;
	gotoxy(3, 20);
}