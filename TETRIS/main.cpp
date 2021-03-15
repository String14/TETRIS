#include "consol_setting.h"
#include "TETRIS.h"

// made by 박건희

int main() {
	// 콘솔 환경 설정
	consol_set();

	// 테트리스 객체 선언
	TETRIS MY_TETRIS;

	// 시작
	gotoxy(11, 8);
	cout << "GAME START" << endl << endl;

	// 쓰레드 시작
	// 클래스의 맴버 함수라 람다식 사용
	/*thread T1([&]()
	{
		MY_TETRIS.threadBLOCK();
	});*/

	// 게임 진행
	while (MY_TETRIS.isGAME()) {
		// 맵 & 블록 & 인터페이스 정의
		MY_TETRIS.setBLOCKinMAP();

		// 맵 & 블록 & 인터페이스 출력
		MY_TETRIS.printTETRISmap();
		MY_TETRIS.printINTERFACE();

		// 블록 자동적으로 아래로 내려오게 하기
		MY_TETRIS.threadBLOCK();

		// 종료 탐색
		if (MY_TETRIS.isGAME() == OVER) {
			Sleep(500);
			break;
		}
	}

	// 쓰레드 종료
	//T1.join();

	// 종료
	system("cls");
	gotoxy(15, 10);
	cout << "GAME OVER" << endl << endl;
	gotoxy(3, 20);
}