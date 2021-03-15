#include "TETRIS.h"
#include "consol_setting.h"

//  쓰레드로 블록을 이동하는 함수 (아직 쓰레드 사용하진 않았음)
void TETRIS::threadBLOCK() {
	// 블럭이 아래로 내려갈 수 있는지 판별
	// 만약 가장 윗줄까지도 (1) 블럭이 차있다 하더라도
	// setBLOCKinMAP() 함수에서 GAME OVER을 판별해주기 때문에 괜찮다.
	// 따라서 이곳에서는 기본적으로 움직일 수 있다는 가정 하에 시작한다.
	Y = -1; // 좌표값 초기화
	bool END = 1; // 블록아래 벽이 있는가?
	bool isTWO = 1; // 요소 (2) 를 찾을 수 있는가?
	while(END && isTWO) {
		// 블록 움직이는걸 보여주기 위한 딜레이 0.1초
		Sleep(150);

		// 아직 (2) 를 찾지 못하였으므로
		isTWO = 0;
		int a = 1;
		// 전체 맵 중 (2) 인 요소를 찾는다.
		// 그 바로 아랫줄에 (1) 이 있는지 탐색한다.
		// 하나라도 바로 아래에 (1) 이 있다면 이동 중지
		// 아니라면 계속 이동한다.
		for (int i = HEIGHT - 2; i > 0; i--) {
			for (int j = 1; j < WIDTH - 1; j++) {
				if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i - 1][j] == 2) {
					// 한칸 아래로 이동
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i - 1][j] = 0;

					// 요소 (2) 를 발견하였으므로
					isTWO = 1;

					// 밑에서부터 탐색하였으므로,
					// 단 하나라도 블록 아래가 1이나 9라면 정지조건 발동
					if (TETRIS_MAP[i + 1][j] == 1 || TETRIS_MAP[i + 1][j] == 9) {
						END = 0;
					}
				}
			}
		}

		// 블록 이동이 종료되면 (2) 를 (1) 로 바꿔준다.
		if (!END) change2in1();

		// 결과 출력
		printTETRISmap();

		// 만약 키보드 입력값이 있다면
		// 쓰레드 중에 입력값을 받아서 블럭 움직이게 하기
		if (_kbhit() && END) {
			moveBLOCK();
		}
	}

	// 블록 지우기
	fillBLOCK(deleteBLOCK());
	
	// 결과 출력
	printTETRISmap();
	printINTERFACE();
}

// 키보드 입력에 따라 블록을 이동시키는 함수
void TETRIS::moveBLOCK() {
	// ↑ (방향키 위)
	if (::GetAsyncKeyState(VK_UP) & 0x0001) moving_UP();
	// ↓ (방향키 아래)
	else if (::GetAsyncKeyState(VK_DOWN) & 0x0001) moving_DOWN();
	// → (방향키 오른쪽)
	else if (::GetAsyncKeyState(VK_RIGHT) & 0x0001) moving_RIGHT();
	// ← (방향키 왼쪽)
	else if (::GetAsyncKeyState(VK_LEFT) & 0x0001) moving_LEFT();

	// □ (스페이스 바)
	else if (::GetAsyncKeyState(VK_SPACE) & 0x0001) moving_SPACE();
	// TAB (탭)
	else if (::GetAsyncKeyState(VK_TAB) & 0x0001) moving_TAB();

	// ESC (종료 키)
	else if (::GetAsyncKeyState(VK_ESCAPE) & 0x0001) moving_ESCAPE();
}

// moveBLOCK의 하위 함수
// *** moveBLOCK 밖에서 호출하지 말 것 ***
// ↑ (방향키 위) 에 대한 반응을 적용하는 함수
void TETRIS::moving_UP() {
	// 블록 회전
}

// moveBLOCK의 하위 함수
// *** moveBLOCK 밖에서 호출하지 말 것 ***
// ↓ (방향키 아래) 에 대한 반응을 적용하는 함수
void TETRIS::moving_DOWN() {
	// 블록 가속

	bool END = 1; // 블록아래 벽이 있는가?
	if (END) {
		for (int i = HEIGHT - 2; i > 0; i--) {
			for (int j = 1; j < WIDTH - 1; j++) {
				if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i - 1][j] == 2) {
					// 한칸 아래로 이동
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i - 1][j] = 0;
					if (TETRIS_MAP[i + 1][j] == 1 || TETRIS_MAP[i + 1][j] == 9) END = 0;
				}
			}
		}
	}

	if (!END) {
		// 블록 이동이 종료되면 (2) 를 (1) 로 바꿔준다.
		change2in1();
	}
}

// moveBLOCK의 하위 함수
// *** moveBLOCK 밖에서 호출하지 말 것 ***
// → (방향키 오른쪽) 에 대한 반응을 적용하는 함수
void TETRIS::moving_RIGHT() {
	// 블록 오른쪽으로 이동

	if (Y == 1) return;

	bool END = 1; // 블록옆에 벽이 있는가?
	if (END) {
		for (int j = WIDTH - 2; j > 0; j--) {
			for (int i = HEIGHT - 2; i > 0; i--) {
				if (TETRIS_MAP[i][j] == 1 && TETRIS_MAP[i][j - 1] == 2) {
					return;
				} else if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i][j - 1] == 2) {
					// 한칸 오른쪽으로 이동
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i][j - 1] = 0;

					// 오른쪽 벽을 만났는지 판별
					// 만나났다면 Y값을 0으로 변경, 이번 이동까지만 완료한 후 반복문 종료
					if (TETRIS_MAP[i][j + 1] == 1 || TETRIS_MAP[i][j + 1] == 9) {
						Y = 1;
						END = 0;
					}
				}
			}
		}
	}
}

// moveBLOCK의 하위 함수
// *** moveBLOCK 밖에서 호출하지 말 것 ***
// ← (방향키 왼쪽) 에 대한 반응을 적용하는 함수
void TETRIS::moving_LEFT() {
	// 블록 왼쪽으로 이동
	Sleep(50);

	if (Y == 0) return;

	bool END = 1; // 블록옆에 벽이 있는가?
	if (END) {
		for (int j = 1; j < WIDTH - 1; j++) {
			for (int i = HEIGHT - 2; i > 0; i--) {
				if (TETRIS_MAP[i][j] == 1 && TETRIS_MAP[i][j + 1] == 2) {
					return;
				} else if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i][j + 1] == 2) {
					// 한칸 왼쪽으로 이동
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i][j + 1] = 0;

					// 왼쪽 벽을 만났는지 판별
					// 만나났다면 Y값을 0으로 변경, 이번 이동까지만 완료한 후 반복문 종료
					if (TETRIS_MAP[i][j - 1] == 1 || TETRIS_MAP[i][j - 1] == 9) {
						Y = 0;
						END = 0;
					}
				}
			}
		}
	}
}

// moveBLOCK의 하위 함수
// *** moveBLOCK 밖에서 호출하지 말 것 ***
// □ (스페이스 바) 에 대한 반응을 적용하는 함수
// 빠른 시간 안에 연속해서 사용하면 에러
void TETRIS::moving_SPACE() {
	// 블록 순간이동
	bool END = 1; // 블록아래 벽이 있는가?
	while (END) {
		// 전체 맵 중 (2) 인 요소를 찾는다.
		// 그 바로 아랫줄에 (1) 이 있는지 탐색한다.
		// 하나라도 바로 아래에 (1) 이 있다면 이동 중지
		// 아니라면 계속 이동한다.
		for (int i = HEIGHT - 2; i > 0; i--) {
			for (int j = 1; j < WIDTH - 1; j++) {
				if (TETRIS_MAP[i][j] == 0 && TETRIS_MAP[i - 1][j] == 2) {
					// 한칸 아래로 이동
					TETRIS_MAP[i][j] = 2;
					TETRIS_MAP[i - 1][j] = 0;

					// 밑에서부터 탐색하였으므로,
					// 단 하나라도 블록 아래가 1이나 9라면 정지조건 발동
					if (TETRIS_MAP[i + 1][j] == 1 || TETRIS_MAP[i + 1][j] == 9) END = 0;
				}
			}
		}
	}

	// 블록 이동이 종료되면 (2) 를 (1) 로 바꿔준다.
	change2in1();
}

// moveBLOCK의 하위 함수
// *** moveBLOCK 밖에서 호출하지 말 것 ***
// TAB (탭) 에 대한 반응을 적용하는 함수
void TETRIS::moving_TAB() {
	// 블록 저장

	// 이동중인 블록 삭제
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			if (TETRIS_MAP[i][j] == 2) TETRIS_MAP[i][j] = 0;
		}
	}

	// 저장된 블록을 꺼내 쓸 때 청소가 필요하다.
	// 인터페이스 저장된 블록 출력부 청소
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 1일 경우에만 0으로 변경해서 블록 출력부를 청소해준다.
			if (TETRIS_INTERFACE[12 + i][2 + j] == 1)
				TETRIS_INTERFACE[12 + i][2 + j] = 0;
			else continue;
		}
	}

	// 인터페이스 저장된 블록 출력부 출력
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 1 일 경우 -> 인터페이스를 수정한다 (1, 1)
			if (TETRIS_BLOCK[my_BLOCK][i][j] == 1)
				TETRIS_INTERFACE[12 + i][2 + j] = 1;
			else continue;
		}
	}
}

// moveBLOCK의 하위 함수
// *** moveBLOCK 밖에서 호출하지 말 것 ***
// ESC (종료 키) 에 대한 반응을 적용하는 함수
void TETRIS::moving_ESCAPE() {
	exit(0);
}