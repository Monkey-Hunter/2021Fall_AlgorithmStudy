#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

#define LEFT 97
#define RIGHT 100
#define UP 119
#define DOWN 115
#define TIME_LIMIT 1000

typedef struct board{       // 게임보드 타일 정보

    int num;    // 타일의 숫자
    int cc;     // 타일의 변화 여부
}Board;

typedef struct ranking{     // 랭킹 정보 구조체

    char name[20];  // 이름
    int score;      // 점수
    int time;       // 걸린시간
    int success;    // 성공여부
    int move;       // 이동횟수
    int combo;      // 최대 콤보횟수

}Ranking;

void print_board(Board board[][5], Ranking player){   // 현재 보드 상황 출력

    printf("|----|----|----|----|----|\n");

    for(int i=0;i<5;i++){
        printf("|");
        for(int j=0;j<5;j++){
            if(board[i][j].num == 0)
                printf("    |");
            else
                printf("%4d|", board[i][j].num);
        }
        printf("\n|----|----|----|----|----|\n");
    }
    printf("Score: %d\tTime: %d\n", player.score, TIME_LIMIT - player.time);
}

int board_full(Board board[][5]){     // 보드가 꽉 차 있는지 확인(꽉 차면 게임오버)

    int flag = 1;

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(board[i][j].num == 0)
                return 0;

    return flag;
}

void produce_number(Board board[5][5]){    // 빈 자리에 2, 4 생성

    srand(time(NULL));
    int random_x, random_y, random_num;

    do{
        random_x = rand()%5;
        random_y = rand()%5;
        random_num = rand()%2;

    }while(board[random_x][random_y].num != 0);

    if(random_num == 0)
        board[random_x][random_y].num = 2;
    else
        board[random_x][random_y].num = 4;

    return;
}

void init_board(Board board[][5], Ranking *player){        // 게임 시작 시 보드 초기화

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++){
            board[i][j].num = 0;
            board[i][j].cc = 0;
        }
    
    srand(time(NULL));
    int noc = rand()%2;
    int random_x, random_y;

    if(noc == 0){
        for(int i=0;i<2;i++){
            do{
                random_x = rand()%5;
                random_y = rand()%5;
            }while(board[random_x][random_y].num != 0);

            board[random_x][random_y].num = 2;
        }
    }

    else{
        random_x = rand()%5;
        random_y = rand()%5;
        board[random_x][random_y].num = 4;
    }

    player->score = 0;
    player->move = 0;
    player->combo = 0;

    print_board(board, *player);

    return;
}

void init_board_cc(Board board[][5]){

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            board[i][j].cc = 0;
    
    return;
}

void move_down(Board board[][5], Ranking *player){         // 숫자들 아래로 이동

    init_board_cc(board);
    int temp_row[5] = {0, }, time = 0;
    player->move += 1;

    while(time<4){

        for(int row=3; row>=0; row--){

            for(int col=0; col<5; col++)
                temp_row[col] = board[row][col].num;

            for(int i=0;i<5;i++){
                if(board[row+1][i].num == temp_row[i] && (board[row][i].cc == 0 && board[row+1][i].cc == 0)){
                    if(board[row+1][i].num != 0){
                        board[row+1][i].num += temp_row[i];
                        board[row+1][i].cc = 1;
                        player->score += board[row+1][i].num;
                        temp_row[i] = 0;
                    }
                }

                else if(board[row+1][i].num == 0){
                    board[row+1][i].num = temp_row[i];
                    temp_row[i] = 0;
                }
            }

            for(int i=0; i<5; i++)
                board[row][i].num = temp_row[i];
            
        }
        time ++;
    }

    return;
}

void move_up(Board board[][5], Ranking *player){         // 숫자들 위로 이동

    init_board_cc(board);
    int temp_row[5] = {0, }, time = 0;
    player->move += 1;

    while(time<4){

        for(int row=1; row<=4; row++){

            for(int col=0; col<5; col++)
                temp_row[col] = board[row][col].num;

            for(int i=0;i<5;i++){
                if(board[row-1][i].num == temp_row[i] && (board[row][i].cc == 0 && board[row-1][i].cc == 0)){
                    if(board[row-1][i].num != 0){
                        board[row-1][i].num += temp_row[i];
                        board[row-1][i].cc = 1;
                        player->score += board[row-1][i].num;
                        temp_row[i] = 0;
                    }
                }

                else if(board[row-1][i].num == 0){
                    board[row-1][i].num = temp_row[i];
                    temp_row[i] = 0;
                }
            }

            for(int i=0; i<5; i++)
                board[row][i].num = temp_row[i];
            
        }
        time ++;
    }

    return;
}

void move_right(Board board[][5], Ranking *player){         // 숫자들 우로 이동

    init_board_cc(board);
    int temp_col[5] = {0, }, time = 0;
    player->move += 1;

    while(time<4){

        for(int col=3; col>=0; col--){

            for(int row=0; row<5; row++)
                temp_col[row] = board[row][col].num;

            for(int i=0;i<5;i++){
                if(board[i][col+1].num == temp_col[i] && (board[i][col].cc == 0 && board[i][col+1].cc == 0)){
                    if(board[i][col+1].num != 0){
                        board[i][col+1].num += temp_col[i];
                        board[i][col+1].cc = 1;
                        player->score += board[i][col+1].num;
                        temp_col[i] = 0;
                    }
                }

                else if(board[i][col+1].num == 0){
                    board[i][col+1].num = temp_col[i];
                    temp_col[i] = 0;
                }
            }

            for(int i=0; i<5; i++)
                board[i][col].num = temp_col[i];
            
        }
        time ++;
    }

    return;
}

void move_left(Board board[][5], Ranking *player){         // 숫자들 좌로 이동

    init_board_cc(board);
    int temp_col[5] = {0, }, time = 0;
    player->move += 1;

    while(time<4){

        for(int col=1; col<=4; col++){

            for(int row=0; row<5; row++)
                temp_col[row] = board[row][col].num;

            for(int i=0;i<5;i++){
                if(board[i][col-1].num == temp_col[i] && (board[i][col].cc == 0 && board[i][col-1].cc == 0)){
                    if(board[i][col-1].num != 0){
                        board[i][col-1].num += temp_col[i];
                        board[i][col-1].cc = 1;
                        player->score += board[i][col-1].num;
                        temp_col[i] = 0;
                    }
                }

                else if(board[i][col-1].num == 0){
                    board[i][col-1].num = temp_col[i];
                    temp_col[i] = 0;
                }
            }

            for(int i=0; i<5; i++)
                board[i][col].num = temp_col[i];
            
        }
        time ++;
    }

    return;
}

// 방향 이동 및 콤보 측정 함수
void move_control(int player_move, Board board[][5], Ranking *player, int *temp_combo){

    int check=0;

    switch (player_move){       // WASD 입력
        case LEFT:
            move_left(board, player);
            produce_number(board);
            print_board(board, *player);
            break;
        case RIGHT:
            move_right(board, player);
            produce_number(board);
            print_board(board, *player);
            break;
        case UP:
            move_up(board, player);
            produce_number(board);
            print_board(board, *player);
            break;
        case DOWN:
            move_down(board, player);
            produce_number(board);
            print_board(board, *player);
            break;
        
        default:
            break;
        }
    
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            check += board[i][j].cc;
    
    if(check>0){
        *temp_combo += check;
        if(*temp_combo > player->combo)
            player->combo = *temp_combo;
    }

    else
        *temp_combo = 0;
    
    return;
}

int game_success(Board board[][5]){

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(board[i][j].num == 2048)
                return 1;

    return 0;
}

typedef struct scores{
    int score;
    int player;
}Scores;

void swap(Scores *x, Scores *y){
    int xtemp_score = x->score;
    int xtemp_player = x->player;

    x->score = y->score;
    y->score = xtemp_score;

    x->player = y->player;
    y->player = xtemp_player;
}

void SelectionSort(Scores *score, int n){

    for(int i=0;i<n-1;i++){
        int max = i;

        for(int j=i+1; j<n; j++)
            if(score[j].score > score[max].score)
                max = j;
        
        swap(&score[max], &score[i]);
    }
}

void sort_ranking(Ranking *player){

    Scores score[10];

    for(int i=0;i<10;i++){
        score[i].score = player[i].score;
        score[i].player = i;
    }

    SelectionSort(score, 10);

    for(int i=0;i<10;i++){
        printf("Ranking No. %d\n", i+1);
        printf("Score: %d\n", score[i].score);
        printf("Name: %s\n\n", player[score[i].player].name);
    }

    return;
}


void write_ranking(Ranking *player){
    FILE *fp;
    char result[5];
    char name[20];

    if(player->success)
        strcpy(result, "WIN");
    else
        strcpy(result, "LOSE");

    printf("Enter your name: ");
    scanf("%s", name);
    strcpy(player->name, name);

    fp = fopen("Result.txt", "a+");

    fputs("\n", fp);
    fprintf(fp, "%s: %s\n", "Name", name);
    fprintf(fp, "%s: %s\n", "Result", result);
    fprintf(fp, "%s: %d\n", "Score", player->score);
    fprintf(fp, "%s: %d%s\n", "Time", player->time, "seconds");
    fprintf(fp, "%s: %d\n", "Number of Moves", player->move);
    fprintf(fp, "%s: %d\n", "Maximum Combo", player->combo);

    fclose(fp);

    return;
} 

int main(){

    Board board[5][5] = {0, };
    Ranking player[10] = {0, };
    int player_num = 0;

    time_t start, end;

    char player_move;
    int menu, temp_combo=0;

do{ 
    fflush(stdin);
    printf("2048!\n1. Game Start\n2. How to\n3. Ranking\n4. Exit\n>> ");
    scanf("%d", &menu);
    printf("\n");

    switch (menu)
    {
    case 1:         // Game Start
        init_board(board, &player[player_num]);
        time(&start);

        while(1){
            
            player[player_num].time = difftime(end, start);
            
            // 시간 제한에 걸려 Game Over 상황
            if(player[player_num].time >= TIME_LIMIT){

                printf("\nGAME OVER! TIME'S UP!\n\n");                    
                player[player_num].success = 0;
                write_ranking(&player[player_num]);
                printf("File Saved!\n\n");

                break;
            }

            // 보드가 꽉 차서 Game Over 상황
            if(board_full(board)){    

                printf("\nGAME OVER! THE BOARD IS FULL!\n\n");
                player[player_num].success = 0;
                write_ranking(&player[player_num]);
                printf("File Saved!\n\n");

                break;
            }

            // Game Win 상황
            if(game_success(board)){      

                printf("\nYou Won!\n\n");
                write_ranking(&player[player_num]);
                printf("\nScore: %d\nMove: %d\nCombo: %d\n\n", player[player_num].score, player[player_num].move, player[player_num].combo);
                player[player_num].success = 1;
                printf("File Saved!\n\n");

                break;
            }

            if(kbhit()){
                player_move = _getch();
                time(&end);
                move_control(player_move, board, &player[player_num], &temp_combo);
            }

            time(&end);
        }

        player_num++;
        
        break;

    case 2:         // How to
        printf("\n게임 규칙 설명\n\n");
        printf("* 게임 시작시 2개의 2또는 4가 랜덤한 곳에서 생성된다.\n");
        printf("* 방향키(W, A, S, D)를 누르면 해당하는 방향으로 게임판에 있는 숫자를 전부 몰게 된다.\n");
        printf("* 이동하면서 같은 숫자를 만날 경우 합쳐지며, 빈 자리 중 한칸에 랜덤하게 2 또는 4가 생성된다.\n");
        printf("* 이를 반복하여 2048 타일을 만들면 게임 클리어\n");
        printf("* 2048을 만들기 전 더 이상 숫자를 몰 수 없는 경우(25 칸이 꽉 차 있으면서 인접한 두 칸이 같지 않을 경우) 게임오버\n\n");
        printf("주의\n* 숫자가 더해질 때 3개 이상이 한번에 더해지지 않는다. (Ex. 4-4-4-4 or 4-4-8 -> 8-8 not 16\n\n");

        break;
    
    case 3:         // Ranking
        printf("\nCurrent Ranking: \n\n");
        sort_ranking(player);

        break;
    
    case 4:         // Exit
        break;

    default:
        printf("다시 입력해주세요.\n\n");
        break;
    }


}while(menu != 4 && player_num<10);
    

}