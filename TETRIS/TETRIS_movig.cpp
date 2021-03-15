#include "TETRIS.h"
#include "consol_setting.h"

//  ������� ����� �̵��ϴ� �Լ� (���� ������ ������� �ʾ���)
void TETRIS::threadBLOCK() {
	// ���� �Ʒ��� ������ �� �ִ��� �Ǻ�
	// ���� ���� ���ٱ����� (1) ���� ���ִ� �ϴ���
	// setBLOCKinMAP() �Լ����� GAME OVER�� �Ǻ����ֱ� ������ ������.
	// ���� �̰������� �⺻������ ������ �� �ִٴ� ���� �Ͽ� �����Ѵ�.
	Y = -1; // ��ǥ�� �ʱ�ȭ
	bool END = 1; // ��ϾƷ� ���� �ִ°�?
	bool isTWO = 1; // ��� (2) �� ã�� �� �ִ°�?
	while(END && isTWO) {
		// ��� �����̴°� �����ֱ� ���� ������ 0.1��
		Sleep(150);

		// ���� (2) �� ã�� ���Ͽ����Ƿ�
		isTWO = 0;
		int a = 1;
		// ��ü �� �� (2) �� ��Ҹ� ã�´�.
		// �� �ٷ� �Ʒ��ٿ� (1) �� �ִ��� Ž���Ѵ�.
		// �ϳ��� �ٷ� �Ʒ��� (1) �� �ִٸ� �̵� ����
		// �ƴ϶�� ��� �̵��Ѵ�.
		for (int i = HEIGHT - 2; i > 0; i--) {
			for (int j = 1; j < WIDTH - 1; j++) {
				if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i - 1][j] == 2) {
					// ��ĭ �Ʒ��� �̵�
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i - 1][j] = 0;

					// ��� (2) �� �߰��Ͽ����Ƿ�
					isTWO = 1;

					// �ؿ������� Ž���Ͽ����Ƿ�,
					// �� �ϳ��� ��� �Ʒ��� 1�̳� 9��� �������� �ߵ�
					if (TETRIS_MAP[i + 1][j] == 1 || TETRIS_MAP[i + 1][j] == 9) {
						END = 0;
					}
				}
			}
		}

		// ��� �̵��� ����Ǹ� (2) �� (1) �� �ٲ��ش�.
		if (!END) change2in1();

		// ��� ���
		printTETRISmap();

		// ���� Ű���� �Է°��� �ִٸ�
		// ������ �߿� �Է°��� �޾Ƽ� �� �����̰� �ϱ�
		if (_kbhit() && END) {
			moveBLOCK();
		}
	}

	// ��� �����
	fillBLOCK(deleteBLOCK());
	
	// ��� ���
	printTETRISmap();
	printINTERFACE();
}

// Ű���� �Է¿� ���� ����� �̵���Ű�� �Լ�
void TETRIS::moveBLOCK() {
	// �� (����Ű ��)
	if (::GetAsyncKeyState(VK_UP) & 0x0001) moving_UP();
	// �� (����Ű �Ʒ�)
	else if (::GetAsyncKeyState(VK_DOWN) & 0x0001) moving_DOWN();
	// �� (����Ű ������)
	else if (::GetAsyncKeyState(VK_RIGHT) & 0x0001) moving_RIGHT();
	// �� (����Ű ����)
	else if (::GetAsyncKeyState(VK_LEFT) & 0x0001) moving_LEFT();

	// �� (�����̽� ��)
	else if (::GetAsyncKeyState(VK_SPACE) & 0x0001) moving_SPACE();
	// TAB (��)
	else if (::GetAsyncKeyState(VK_TAB) & 0x0001) moving_TAB();

	// ESC (���� Ű)
	else if (::GetAsyncKeyState(VK_ESCAPE) & 0x0001) moving_ESCAPE();
}

// moveBLOCK�� ���� �Լ�
// *** moveBLOCK �ۿ��� ȣ������ �� �� ***
// �� (����Ű ��) �� ���� ������ �����ϴ� �Լ�
void TETRIS::moving_UP() {
	// ��� ȸ��
}

// moveBLOCK�� ���� �Լ�
// *** moveBLOCK �ۿ��� ȣ������ �� �� ***
// �� (����Ű �Ʒ�) �� ���� ������ �����ϴ� �Լ�
void TETRIS::moving_DOWN() {
	// ��� ����

	bool END = 1; // ��ϾƷ� ���� �ִ°�?
	if (END) {
		for (int i = HEIGHT - 2; i > 0; i--) {
			for (int j = 1; j < WIDTH - 1; j++) {
				if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i - 1][j] == 2) {
					// ��ĭ �Ʒ��� �̵�
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i - 1][j] = 0;
					if (TETRIS_MAP[i + 1][j] == 1 || TETRIS_MAP[i + 1][j] == 9) END = 0;
				}
			}
		}
	}

	if (!END) {
		// ��� �̵��� ����Ǹ� (2) �� (1) �� �ٲ��ش�.
		change2in1();
	}
}

// moveBLOCK�� ���� �Լ�
// *** moveBLOCK �ۿ��� ȣ������ �� �� ***
// �� (����Ű ������) �� ���� ������ �����ϴ� �Լ�
void TETRIS::moving_RIGHT() {
	// ��� ���������� �̵�

	if (Y == 1) return;

	bool END = 1; // ��Ͽ��� ���� �ִ°�?
	if (END) {
		for (int j = WIDTH - 2; j > 0; j--) {
			for (int i = HEIGHT - 2; i > 0; i--) {
				if (TETRIS_MAP[i][j] == 1 && TETRIS_MAP[i][j - 1] == 2) {
					return;
				} else if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i][j - 1] == 2) {
					// ��ĭ ���������� �̵�
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i][j - 1] = 0;

					// ������ ���� �������� �Ǻ�
					// �������ٸ� Y���� 0���� ����, �̹� �̵������� �Ϸ��� �� �ݺ��� ����
					if (TETRIS_MAP[i][j + 1] == 1 || TETRIS_MAP[i][j + 1] == 9) {
						Y = 1;
						END = 0;
					}
				}
			}
		}
	}
}

// moveBLOCK�� ���� �Լ�
// *** moveBLOCK �ۿ��� ȣ������ �� �� ***
// �� (����Ű ����) �� ���� ������ �����ϴ� �Լ�
void TETRIS::moving_LEFT() {
	// ��� �������� �̵�
	Sleep(50);

	if (Y == 0) return;

	bool END = 1; // ��Ͽ��� ���� �ִ°�?
	if (END) {
		for (int j = 1; j < WIDTH - 1; j++) {
			for (int i = HEIGHT - 2; i > 0; i--) {
				if (TETRIS_MAP[i][j] == 1 && TETRIS_MAP[i][j + 1] == 2) {
					return;
				} else if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i][j + 1] == 2) {
					// ��ĭ �������� �̵�
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i][j + 1] = 0;

					// ���� ���� �������� �Ǻ�
					// �������ٸ� Y���� 0���� ����, �̹� �̵������� �Ϸ��� �� �ݺ��� ����
					if (TETRIS_MAP[i][j - 1] == 1 || TETRIS_MAP[i][j - 1] == 9) {
						Y = 0;
						END = 0;
					}
				}
			}
		}
	}
}

// moveBLOCK�� ���� �Լ�
// *** moveBLOCK �ۿ��� ȣ������ �� �� ***
// �� (�����̽� ��) �� ���� ������ �����ϴ� �Լ�
// ���� �ð� �ȿ� �����ؼ� ����ϸ� ����
void TETRIS::moving_SPACE() {
	// ��� �����̵�
	bool END = 1; // ��ϾƷ� ���� �ִ°�?
	while (END) {
		// ��ü �� �� (2) �� ��Ҹ� ã�´�.
		// �� �ٷ� �Ʒ��ٿ� (1) �� �ִ��� Ž���Ѵ�.
		// �ϳ��� �ٷ� �Ʒ��� (1) �� �ִٸ� �̵� ����
		// �ƴ϶�� ��� �̵��Ѵ�.
		for (int i = HEIGHT - 2; i > 0; i--) {
			for (int j = 1; j < WIDTH - 1; j++) {
				if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i - 1][j] == 2) {
					// ��ĭ �Ʒ��� �̵�
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i - 1][j] = 0;

					// �ؿ������� Ž���Ͽ����Ƿ�,
					// �� �ϳ��� ��� �Ʒ��� 1�̳� 9��� �������� �ߵ�
					if (TETRIS_MAP[i + 1][j] == 1 || TETRIS_MAP[i + 1][j] == 9) END = 0;
				}
			}
		}
	}

	// ��� �̵��� ����Ǹ� (2) �� (1) �� �ٲ��ش�.
	change2in1();
}

// moveBLOCK�� ���� �Լ�
// *** moveBLOCK �ۿ��� ȣ������ �� �� ***
// TAB (��) �� ���� ������ �����ϴ� �Լ�
void TETRIS::moving_TAB() {
	// ��� ����

	// �̵����� ��� ����
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			if (TETRIS_MAP[i][j] == 2) TETRIS_MAP[i][j] = 0;
		}
	}

	// ����� ����� ���� �� �� û�Ұ� �ʿ��ϴ�.
	// �������̽� ����� ��� ��º� û��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 1�� ��쿡�� 0���� �����ؼ� ��� ��ºθ� û�����ش�.
			if (TETRIS_INTERFACE[12 + i][2 + j] == 1)
				TETRIS_INTERFACE[12 + i][2 + j] = 0;
			else continue;
		}
	}

	// �������̽� ����� ��� ��º� ���
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 1 �� ��� -> �������̽��� �����Ѵ� (1, 1)
			if (TETRIS_BLOCK[my_BLOCK][i][j] == 1)
				TETRIS_INTERFACE[12 + i][2 + j] = 1;
			else continue;
		}
	}
}

// moveBLOCK�� ���� �Լ�
// *** moveBLOCK �ۿ��� ȣ������ �� �� ***
// ESC (���� Ű) �� ���� ������ �����ϴ� �Լ�
void TETRIS::moving_ESCAPE() {
	exit(0);
}