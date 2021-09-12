# C_2048game
**Build & Run**

- 사용 헤더 및 라이브러리:
#include <stdio.h>		// 표준 입출력을 위하여
#include <stdlib.h>		// random() 함수 사용을 위하여
#include <time.h>		// time attack 기능 구현을 위하여
#include <conio.h>		// 키보드 입력을 위하여
#include <string.h>	// 게임 결과를 텍스트 파일로 저장하기 위하여

- 구조체:
typedef struct board{       // 게임보드 타일 정보
    int num;    // 타일의 숫자
    int cc;     // 타일의 변화 여부->타일끼리 한번 더해지면 1 반환, 변화 없으면 0 반환
}Board;

typedef struct ranking{     // 랭킹 정보 구조체
    char name[20];  // 이름
    int score;      // 점수
    int time;       // 걸린시간
    int success;    // 성공여부
    int move;      // 이동횟수
    int combo;     // 최대 콤보횟수
}Ranking;

typedef struct scores{	    // 랭킹 Sort를 위한 사용자 정보 임시 저장용 구조체
    int score;
    int player;
}Scores;

**Play the Game**

프로그램 실행 시 나오는 메뉴:	(입력값이 4가 아니고, 플레이 횟수가 10 이하일 경우 반복해서 출력됨)
1. Game Start
2. How to
3. Ranking
4. Exit
>> (입력값)

실행하고자 하는 기능의 번호를 누르면 됩니다.
입력값: 1

입력값: 2
게임하는 방법에 대한 설명글 출력

입력값: 3
현재 점수의 랭킹 정보 출력

입력값: 4
프로그램 종료

**Features**

- 숫자 이동(’w’, ‘a’, ‘s’, ‘d’ 입력 시)
∙사용함수: 
kbhit() // 키보드 입력 여부를 알기 위해
void move_down(Board board[][5], Ranking *player) // 숫자들 아래로 이동
void move_up(Board board[][5], Ranking *player) // 숫자들 위로 이동
void move_right(Board board[][5], Ranking *player) // 숫자들 우로 이동
void move_left(Board board[][5], Ranking *player) // 숫자들 좌로 이동
void move_control(int player_move, Board board[][5], Ranking *player, int *temp_combo)
// 방향 이동 및 콤보 측정 함수
∙알고리즘: 사용자 키보드값을 반환하여 각 입력에 맞게 숫자들을 이동하도록 구현

- 새로운 숫자 생성
∙사용함수:
void produce_number(Board board[][5]) // 빈 자리에 2개의 2, 또는 4 생성
rand()
∙알고리즘:
한 칸에 숫자가 없으면 0이 저장되는데, 0으로 저장된 칸들 중 임의의 칸을 지정하고, 랜덤으로 2,2 또는 4를 저장함

- 게임 오버 / 게임 클리어 체크
∙사용함수:
int board_full(Board board[][5]) // 보드가 꽉 차 있는지 확인(꽉 차면 1 반환)
∙알고리즘:
게임 시작 시 매 이동이 끝난 후 보드의 모든 칸들을 조사하고, 
모든 칸들의 숫자가 0이 아니면(보드가 꽉 차 있는 상태) 1을 반환
그 경우가 아니라면 0을 반환

- 점수
∙기존의 2048 게임의 점수 체계를 참고하여 매 이동마다 새로 만들어진 숫자를 기존의 점수에 계속 더하는 식으로 점수를 계산함
∙Ex.> 2-2 -> 4 일시 4점, 8-8 -> 16일시 16점을 기존의 점수에 더함

- 랭킹
∙사용함수:
void swap(Scores *x, Scores *y) // 점수 랭킹 정보 정렬을 위한 swap 알고리즘
void SelectionSort(Scores *score, int n) // 점수 랭킹 정보 정렬 시 사용되는 Selection Sort 알고리즘
void sort_ranking(Ranking *player) // 점수 랭킹 정보 정렬 및 출력
void write_ranking(Ranking *player) // 게임 종료 시 게임 사용자 정보를 “Result.txt”에 저장
∙알고리즘:
랭킹 정보를 정렬하기 위해서 Selection Sort 방식의 정렬 알고리즘을 이용함
게임 종료 시 사용자의 이름을 입력받고, 게임에서 기록된 사용자의 정보(점수, 시간, 성공여부, 이동횟수, 콤보)를 
프로그램 실행 폴더에 “Result.txt” 파일을 만들어 저장함.
-> 기존에 “Result.txt” 파일이 있을 경우, 그 파일에 기록을 덧붙여 저장함.

- 타임어택
∙사용함수:
time()
∙알고리즘:
게임 시작 직후, time() 함수를 이용하여 현재 시간을 정수값으로 time_t start 변수에 저장하고, 매 이동이 종료된 시점의 시간을 time_t end 변수에 저장하여 두 변수의 차이값을 매크로 변수 TIME_LIMIT에서 뺀 값을 출력함.
-> 시간 단위는 초로 설정되어 있음.
-> TIME_LIMIT의 default 값은 1000으로 저장되어 있고, 코드의 상단에서 언제든지 변화 가능함.

- 콤보
∙사용함수:
void move_control(int player_move, Board board[][5], Ranking *player, int *temp_combo)
∙알고리즘:
숫자가 이동될 때마다 각 칸의 cc값(숫자들 변화 여부)를 확인하여 변화가 감지되면(cc 값이 1이 되면) temp_combo++를 실행하고, 특정 이동에서 숫자들의 변화 여부가 감지되지 않는다면 temp_combo의 값과 현재 저장되어 있는 콤보의 값과 비교하여 temp_combo 가 더 큰 경우 현재 콤보값을 temp_combo의 값으로 대체하게 됨.
-> 따라서 콤보는 최대 콤보의 값이 됨.

**Trouble Shooting Points**

- 기존의 2048에서는 모든 숫자들이 한쪽으로 몰려 있을 때, 해당 방향의 방향키를 눌렀을 때 숫자들의 변화가 없다면 아무 동작을 하지 않고, 숫자가 랜덤하게 배치되지 않았지만, 본인이 만든 2048에서는 턴이 넘어가면서 랜덤한 숫자가 생성됨.

- 게임 플레이 중 남은 시간이 실시간으로 출력되지 않고, 사용자가 이동방향을 입력했을 시에만 남은시간이 출력됨.

- 게임 플레이 도중 게임을 그만하고 싶을 때, 입력할 수 있는 특정한 키가 없어 사용자가 프로그램을 종료해야만 함.
