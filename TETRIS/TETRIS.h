#pragma once
// 내장 라이브러리 임폴트
#include <iostream> // 입출력
#include <time.h> // 시간
#include <ctime> // 난수 생성
#include <thread> // 쓰레드
using namespace std;

#pragma once

// 게임 오버, 혹은 플레잉을 나타내기 위한 enum
enum GAME { OVER, PLAYING };

// TETRIS 맵 가로 설정
# define WIDTH 14
// TETRIS 맵 세로 설정
# define HEIGHT 24
// 인터페이스 가로 설정
#define INTERFACE_WIDTH 8

// TETRIS 블록 갯수 설정
# define BLOCKNUM 7

// 테트리스 객체
class TETRIS {
	// 테트리스 맵 & 테트리스 블록 선언
private:
	// TETRIS 맵 2차원 배열 (런타임 도중 계속 수정 됨)
	// 사출구가 1이 되었을 때, index[1] 이 전부 1이 아니라면
	// 게임 오버 (9 제외)
	int TETRIS_MAP[HEIGHT][WIDTH] = {
		// 주석 2번 참고
		//{ 9, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 9 },
		//{ 9, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 9 },
		{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
	};
	// 인터페이스 디자인 2차원 배열 (런타임 도중 계속 수정 됨)
	int TETRIS_INTERFACE[HEIGHT][INTERFACE_WIDTH] = {
		// NEXT BLOCK
		{ 9, 9, 9, 9, 9, 9, 9, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 9, 9, 9, 9, 9, 9, 9 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		// HOLD BLOCK
		{ 9, 9, 9, 9, 9, 9, 9, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 9, 9, 9, 9, 9, 9, 9 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		// PLAYER SCORE
		{ 9, 9, 9, 9, 9, 9, 9, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 0, 0, 0, 0, 0, 0, 9 },
		{ 9, 9, 9, 9, 9, 9, 9, 9 }
	};
	// TETRIS 블록 3차원 배열 (절대 수정 금지)
	const int TETRIS_BLOCK[BLOCKNUM][4][4] =
	{
		{	// 1
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	// 2
			{ 0, 0, 1, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	// 3
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	// 4
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	// 5
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	// 6
			{ 1, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	// 7
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	};

	// 각종 변수 선언
private:
	// setrandomBLOCK 함수를 통해 설정된 블록 값
	// (런타임 도중 계속 수정 됨)
	int random_NEXTBLOCK = -1;
	
	// 현재 이동중인 블록 값을 저장해둔다.
	int my_BLOCK;

	// 게임 진행 상태를 표기할 변수
	bool GAME = PLAYING;

	// Y 좌표값
	// 상하와 다르게 좌우는 양방향으로 움직일 수 있기 때문에 필요하다.
	// 0이면 왼쪽 가장자리 / 1이면 오른쪽 가장자리
	int Y = -1;

	// 기본 생성자, 소멸자 선언
public:
	TETRIS();
	~TETRIS();

	// 기본 테트리스 설정용 함수 선언
public:
	// TETRIS 맵을 (런타임 도중의 상태 그대로) 출력하는 함수
	void printTETRISmap();

	// 인터페이스를 (런타임 도중의 상태 그대로) 출력하는 함수
	void printINTERFACE();

	// TETRIS 블록을 랜덤으로 리턴해주는 함수
	void setrandomBLOCK();

	// TETRIS 블록을 출력하는 함수
	void setBLOCKinMAP();

	// 멤버변수 GAME을 리턴해주는 함수
	bool isGAME();

	// 블록 상태 변경용 함수 선언
private:
	// 이동중인 블록 (2) 를 채워진 블록 (1) 로 바꿔주는 함수
	// *** 반드시 이동이 종료되고 호출 할 것 ***
	void change2in1();

	// 채워진 블록 (1) 로 가득찬 줄을 지우는 함수 (지웠는지 여부 bool로 반환)
	// *** 리턴값을 fillBLOCK의 인수로 보내는 함수 ***
	bool deleteBLOCK();

	// deleteBLOCK 호출 후 비워진 줄을 블록으로 채우는 함수
	// *** deleteBLOCK과 동시에 호출해야 한다. ***
	void fillBLOCK(bool isDELETED);

	// fillBLOCK의 하위 함수
	// *** fillBLOCK 밖에서 호출하지 말 것 ***
private:
	// 비워진 공간의 위치와 갯수를 탐색하여 반환하는 함수
	int serchEMPTY(int& local, int& EMPTYnum);

	// 채워진 공간의 위치와 갯수를 탐색하여 반환하는 함수
	int serchFULL(int& local);

	// local 위의 모든 블록을 아래로 EMPTYnum만큼 내리는 함수
	int dropBLOCK(int& local, int& EMPTYnum);

	// 블록 이동에 관련된 함수
public:
	//  쓰레드로 블록을 이동하는 함수
	void threadBLOCK();

	// 키보드 입력에 따라 블록을 이동시키는 함수
	void moveBLOCK();

	// moveBLOCK의 하위 함수
	// *** moveBLOCK 밖에서 호출하지 말 것 ***
private:
	// ↑ (방향키 위) 에 대한 반응을 적용하는 함수
	void moving_UP();

	// ↓ (방향키 아래) 에 대한 반응을 적용하는 함수
	void moving_DOWN();

	// → (방향키 오른쪽) 에 대한 반응을 적용하는 함수
	void moving_RIGHT();

	// ← (방향키 왼쪽) 에 대한 반응을 적용하는 함수
	void moving_LEFT();

	// □ (스페이스 바) 에 대한 반응을 적용하는 함수
	void moving_SPACE();

	// TAB (탭) 에 대한 반응을 적용하는 함수
	void moving_TAB();

	// ESC (종료 키) 에 대한 반응을 적용하는 함수
	void moving_ESCAPE();
};