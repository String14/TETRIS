#include "consol_setting.h" //gotoxy()
#include "TETRIS.h"

// 기본 생성자
TETRIS::TETRIS() {}

// TETRIS 맵을 (런타임 도중의 상태 그대로) 출력하는 함수
void TETRIS::printTETRISmap() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			gotoxy(1 + j * 2, 1 + i);
			if (TETRIS_MAP[i][j] == 9) cout << "▦";
			else if (TETRIS_MAP[i][j] == 0) cout << "  ";
			else if (TETRIS_MAP[i][j] == 1) cout << "■";
			else if (TETRIS_MAP[i][j] == 2) cout << "□";
		}
	}
}

// 인터페이스를 (런타임 도중의 상태 그대로) 출력하는 함수
void TETRIS::printINTERFACE() {
	// 인터페이스 테투리 출력
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < INTERFACE_WIDTH; j++) {
			gotoxy(29 + j * 2, 1 + i);
			if (TETRIS_INTERFACE[i][j] == 9) cout << "▦";
			else if (TETRIS_INTERFACE[i][j] == 1) cout << "■";
			else if (TETRIS_INTERFACE[i][j] == 0) cout << "  ";
		}
	}

	// 글자 출력 (NEXT, HOLD, SCORE)
	gotoxy(35, 9);	cout << "NEXT";
	gotoxy(35, 18);	cout << "HOLD";
	gotoxy(33, 21);	cout << "SCORE";
	gotoxy(33, 22);	cout << "0";
}

// TETRIS 블록을 랜덤으로 리턴해주는 함수
void TETRIS::setrandomBLOCK() {
	// 랜덤 난수 생성을 위한 시드값 설정
	srand((unsigned int)time(NULL));

	// 같은 블록이 너무나 자주 연속적으로 나오는걸 방지하기 위해서
	// 한 번의 연속은 코드 상으로 제어해준다.
	int temp = random_NEXTBLOCK;

	// 0 ~ 6 의 난수 생성
	random_NEXTBLOCK = rand() % 7;

	// 만약 연속된 값이 나왔다면 단 한번에 한해 다시 난수를 생성한다.
	if (temp == random_NEXTBLOCK) {
		// 0 ~ 6 의 난수 생성
		random_NEXTBLOCK = rand() % 7;
	}
}

// TETRIS 블록을 맵에 세팅하는 함수 (이동중인 블록)
void TETRIS::setBLOCKinMAP() {
	// 런타임을 통틀어 가장 처음 호출된 경우에만
	// == random_NEXTBLOCK 의 값이 -1 일 경우에만
	// 랜덤 블록 생성 함수를 호출해서 출력될 블록을 설정해준다.
	if (random_NEXTBLOCK == -1) setrandomBLOCK();
	my_BLOCK = random_NEXTBLOCK;

	// TETRIS_MAP 사출구 부분 청소 (테스트용, 나중에 필히 지울 것)
	// *** TODO delete this loop ***
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 2일 경우에만 0으로 변경해서 블록 출력부를 청소해준다.
			if (TETRIS_MAP[1 + i][5 + j] == 2) TETRIS_MAP[1 + i][5 + j] = 0;
			else continue;
		}
	}

	// 블럭 출력 && GAME OVER 인지 판별
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 사출구 중, 블록을 출력해야 할 부분이 이미 차 있다면 GAME OVER
			// 따라서 사출구와 블록이 모두 1 일 경우 GAME OVER 되는 것이다.
			if (TETRIS_MAP[1 + i][5 + j] == 1 &&
				TETRIS_BLOCK[my_BLOCK][i][j] == 1) {
				GAME = OVER;
				change2in1();
			}

			// 블럭값이 4*4이므로
			// 값이 1 일 경우에만 TETRIS_MAP의 사출구 부분 (1, 5) 을 수정한다.
			// 만약 앞선 조건문에서 GAME OVER 되었더라도 출력은 한다.
			// 플레이어가 시각적으로 GAME OVER 되었음을 알아야 하므로.
			// 게임이 진행중인 경우에는 문제없이 전부 출력되게 한다.
			if (TETRIS_BLOCK[my_BLOCK][i][j] == 1)
				TETRIS_MAP[1 + i][5 + j] = 2;
			else continue;
		}
	}

	// 랜덤 블록 생성 (다음 차례에 출연할 블록)
	setrandomBLOCK();

	// 인터페이스 다음 블록 출력부 청소
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 1일 경우에만 0으로 변경해서 블록 출력부를 청소해준다.
			if (TETRIS_INTERFACE[3 + i][2 + j] == 1)
				TETRIS_INTERFACE[3 + i][2 + j] = 0;
			else continue;
		}
	}

	// 인터페이스 다음 블록 출력부에 출력
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 1 일 경우 -> 인터페이스를 수정한다 (1, 1)
			if (TETRIS_BLOCK[random_NEXTBLOCK][i][j] == 1)
				TETRIS_INTERFACE[3 + i][2 + j] = 1;
			else continue;
		}
	}
}

// 멤버변수 GAME을 리턴해주는 함수
bool TETRIS::isGAME() {
	return this->GAME;
}

// 이동중인 블록 (2) 를 채워진 블록 (1) 로 바꿔주는 함수
// 블록이 목적지에 도착해야함
// *** 반드시 이동이 종료하고 호출 할 것 ***
void TETRIS::change2in1() {
	int count = 0;
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			if (TETRIS_MAP[i][j] == 2) {
				TETRIS_MAP[i][j] = 1;
				count++;
				if (count == 4) return;
			}
		}
	}
}

// 1로 가득찬 줄을 지우는 함수 (지웠는지 여부 bool로 반환)
bool TETRIS::deleteBLOCK() {
	bool isALLFULL = FALSE;
	bool isDELETED = FALSE;

	for (int i = 1; i < HEIGHT; i++) {
		// 만약 저번에 확인했던 줄이 전부 1이었다면
		// 전줄을 (i - 1) 전부 0으로 변경한다.
		if (isALLFULL) {
			for (int j = 1; j < WIDTH - 1; j++) {
				TETRIS_MAP[i - 1][j] = 0;
			}

			// 한 줄을 비웠다면 isALLFULL을 다시 FALSE로 변경해준다.
			// 만약 FLASE로 두지 않는다면 한번이라도 가득찬 줄을 만난 다음에는
			// 그 아래로 싹다 지워버리게 된다.
			isALLFULL = FALSE;
			isDELETED = TRUE;
		}

		// 만약 첫번째 인자가 0이라면 바로 다음 줄을 확인한다.
		if (TETRIS_MAP[i][1] == 0) continue;
		// 아니라면 두번째 인자를 확인한다. (-1은 테두리 제외다)
		for (int j = 2; j < WIDTH - 1; j++) {
			if (TETRIS_MAP[i][j] == 1) isALLFULL = TRUE;
			// 하나라도 1아닌 것이 나온다면 isALLFULL을 FALSE로 변경하고
			// 반복문을 빠져나와 다음 줄을 확인한다.
			else {
				isALLFULL = FALSE;
				break;
			}
		}
	}

	// 삭제 기록을 반환한다.
	return isDELETED;
}

// deleteBLOCK 호출 후 비워진 공간을 블록으로 채우는 함수
// *** deleteBLOCK 호출 후 반드시 호출해야 한다. ***
void TETRIS::fillBLOCK(bool isDELETED) {
	// 반드시 삭제된 줄이 있을 경우에만 다음 내용이 실행되어야 한다.
	if (isDELETED) {
		// -2 -> (배열크기(20)-1)-테두리(1)
		int local = HEIGHT - 2;
		int EMPTYnum = 0;

		while (TRUE) {
			// 가장 밑부분이 채워져있는 경우
			if (local == HEIGHT - 2) {
				// 블록이 채워져있는 줄을 탐색해 local 값을 갱신한다.
				serchFULL(local);
				// local 값을 새로 얻은 후 비워진 줄을 탐색한다.
				serchEMPTY(local, EMPTYnum);
			}
			// 아니라면 (가장 밑부분이 비워져있는 경우)
			// local 위로 블록이 채워져있지 않는 줄을 탐색한다.
			else serchEMPTY(local, EMPTYnum);

			// 만약 local 위로 전부 비어져있다면 이곳에서 정지한다.
			if (local == 0) break;

			// local의 윗부분 블록을 EMPTYnum만큼 아래로 내린다.
			dropBLOCK(local, EMPTYnum);

			// 비워진 공간을 채웠으므로 다시 밑바닥에서부터 탐색한다.
			local = HEIGHT - 2;
			// 같은 이유로 EMPTYnum도 초기화한다.
			EMPTYnum = 0;

			// 블록이 채워져있는 줄을 탐색한다.
			serchFULL(local);
		}

		Sleep(500);
	}
}

// fillBLOCK의 하위 함수
// *** fillBLOCK 밖에서 호출하지 말 것 ***
// 비워진 공간의 위치와 갯수를 탐색하여 반환하는 함수
int TETRIS::serchEMPTY(int& local, int& EMPTYnum) {
	// local 위치 부터 1이 있는 줄을 찾는다 (밑에서 위로 탐색)
	// 1이 하나라도 있다는 것 -> 비워진 줄이 아니라는 뜻
	for (int i = local; i >= 1; i--) {
		for (int j = 1; j < WIDTH - 1; j++) {
			// 1을 찾으면 바로 새로 갱신된 위치와 지워진 줄의 갯수를 반환한다.
			if (TETRIS_MAP[i][j] == 1) return local, EMPTYnum;
		}
		local--;
		EMPTYnum++;
	}

	return local, EMPTYnum;
}

// fillBLOCK의 하위 함수
// *** fillBLOCK 밖에서 호출하지 말 것 ***
// 채워진 공간의 위치를 탐색하여 반환하는 함수
int TETRIS::serchFULL(int& local) {
	int count_1 = 0;

	// local 위치 부터 1이 있는 줄을 찾는다 (밑에서 위로 탐색)
	// 1이 하나라도 있다는 것 -> 비워진 줄이 아니라는 뜻
	// 반대로 1이 하나도 없다는 것 (count_1 == 0) -> 비워진 줄이라는 뜻
	for (int i = local; i >= 1; i--) {
		int count_1 = 0;
		for (int j = 1; j < WIDTH - 1; j++) {
			// 1을 찾으면 바로 새로 갱신된 위치와 지워진 줄의 갯수를 반환한다.
			if (TETRIS_MAP[i][j] == 1) count_1++;
		}

		// 만약 비워진 줄이라면 현재의 위치 정보를 반환한다.
		if (count_1 == 0) return local;
		// 아니라면 위치 정보를 갱신한다.
		else local--;
	}

	return local;
}

// fillBLOCK의 하위 함수
// *** fillBLOCK 밖에서 호출하지 말 것 ***
// local 위의 모든 블록을 아래로 EMPTYnum만큼 내리는 함수
int TETRIS::dropBLOCK(int& local, int& EMPTYnum) {
	bool isALLEMPTY = FALSE;

	for (int i = local; i >= 1; i--) {
		for (int j = 1; j < WIDTH - 1; j++) {
			// 이동할 블록이 1 (채워진 블록) 일 경우에만 블록 이동 가능
			if (TETRIS_MAP[i][j] == 1) {
				// local의 인자를 local + EMPTYnum 위치로 이동
				TETRIS_MAP[i + EMPTYnum][j] = TETRIS_MAP[i][j];
				// 이동한 줄은 0으로 초기화한다.
				// (serchFULL에서 새로운 local을 찾기 위해)
				TETRIS_MAP[i][j] = 0;
			}
			else continue;
		}
	}

	return local, EMPTYnum;
}

// 기본 소멸자
TETRIS::~TETRIS() {}