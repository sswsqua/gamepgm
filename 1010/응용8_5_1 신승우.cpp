#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_HISTORY 5

void intro_game(void);
void select_mode(int* mode);
void horizontal_slide(int x, int y, char *c2);
void draw_rectangle(int r, int c);
void display_text(int count, int max_attempts, int score, int max_time, int mode);
void game_control(int* r_c, int rnd, int* score);
void show_final_score(int score, int mode, int score_history[][2], int history_count);
void gotoxy(int x, int y);

int main(void)
{
    int count = 0, rnd;
    int r_count = 0;
    int score = 0;
    int mode;
    int max_attempts = 10;  // 기본 최대 시도 횟수
    int max_time = 10;      // 제한 시간을 10초로 설정
    int score_history[MAX_HISTORY][2] = {0};  // 최근 5회의 점수와 모드 기록 (mode, score)
    int history_count = 0;  // 점수 기록 개수

    srand(time(NULL));

    while (1) {
        intro_game();
        select_mode(&mode);  // 모드 선택

        // 게임 종료 모드
        if (mode == 3) {
            printf("게임을 종료합니다...\n");
            break;
        }

        count = 0;
        score = 0;

        if (mode == 1) {
            // 시간 제한 모드
            time_t start_time = time(NULL);
            do
            {
                system("cls");
                draw_rectangle(20, 20);
                rnd = rand() % 35 + 4;  // 표적 위치 랜덤
                gotoxy(rnd - 1, 2); // 괄호를 포함하기 위해 위치 조정
                printf("(●)"); // 괄호와 동그라미 표적 출력
                count++;
                display_text(count, max_attempts, score, max_time - (time(NULL) - start_time), mode);
                game_control(&r_count, rnd, &score);
            } while (time(NULL) - start_time < max_time);
        } else {
            // 횟수 제한 모드
            do
            {
                system("cls");
                draw_rectangle(20, 20);
                rnd = rand() % 35 + 4;  // 표적 위치 랜덤
                gotoxy(rnd - 1, 2); // 괄호를 포함하기 위해 위치 조정
                printf("(●)"); // 괄호와 동그라미 표적 출력
                count++;
                display_text(count, max_attempts, score, max_time, mode);
                game_control(&r_count, rnd, &score);
            } while (count < max_attempts);
        }

        // 점수 기록
        if (history_count < MAX_HISTORY) {
            score_history[history_count][0] = mode;  // 모드 기록
            score_history[history_count][1] = score; // 점수 기록
            history_count++;
        } else {
            for (int i = 1; i < MAX_HISTORY; i++) {
                score_history[i - 1][0] = score_history[i][0];  // 모드 쉬프트 
                score_history[i - 1][1] = score_history[i][1];  // 점수 쉬프트 
            }
            score_history[MAX_HISTORY - 1][0] = mode;  // 현재 모드 저장 
            score_history[MAX_HISTORY - 1][1] = score; // 현재 점수 저장  
        }

        // 게임 종료 후 최종 점수 출력
        show_final_score(score, mode, score_history, history_count);
    }

    return 0;
}

void intro_game(void)
{
    printf("말타며 화살쏘기\n\n");
    printf("말을 타고 이동하면서 \n");
    printf("목표물((●))을 맞추는 게임입니다. \n");
    printf("화살은 스페이스키로 발사합니다. \n\n");
    printf("아무키나 누르면 시작합니다. ");
    getch();
}

void select_mode(int* mode)
{
    printf("모드를 선택하세요:\n");
    printf("1. 시간제한 모드\n");
    printf("2. 제한횟수 모드\n");
    printf("3. 게임 종료\n");
    while (1) {
        char ch = getch();
        if (ch == '1') {
            *mode = 1;
            break;
        } else if (ch == '2') {
            *mode = 2;
            break;
        } else if (ch == '3') {
            *mode = 3;
            break;
        }
    }
    printf("\n모드가 선택되었습니다. 시작합니다...\n");
    Sleep(1000); // 1초 대기
}

void horizontal_slide(int x, int y, char *c2)
{
    gotoxy(x, y);
    printf("%s", c2);
    Sleep(50);
    printf("\b ");
}

void draw_rectangle(int r, int c)
{
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[7]; 
    for (i = 1; i < 7; i++)
        b[i] = 0xa0 + i;

    printf("%c%c", a, b[3]);
    for (i = 0; i < c; i++)
        printf("%c%c%c%c", a, b[1], a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for (i = 0; i < r; i++)
    {
        printf("%c%c", a, b[2]);
        for (j = 0; j < c; j++)
            printf("  ");
        printf("%c%c", a, b[2]);
        printf("\n");
    }
    printf("%c%c", a, b[6]);
    for (i = 0; i < c; i++)
        printf("%c%c%c%c", a, b[1], a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

void display_text(int count, int max_attempts, int score, int max_time, int mode)
{
    gotoxy(46, 2);
    printf("스페이스키를 누르면\n");
    gotoxy(46, 3);
    printf("화살이 발사됩니다.\n");
    gotoxy(46, 5);

    // 모드에 따라 표시 내용 변경
    if (mode == 1) {
        printf("시도 횟수 : %d", count);
        gotoxy(46, 7);
        printf("남은 시간 : %d초", max_time);
    } else {
        printf("남은 횟수 : %d", max_attempts - count);
        // 제한 횟수 모드에서는 남은 시간 표시 안 함
    }

    gotoxy(46, 6);
    printf("점수 : %d", score);
}


void game_control(int* r_c, int rnd, int* score)
{
    int i = 1, k = 1, y;
    char *horse = "▲", chr;
    do
    {
        i += k;
        if (i > 39)
            k = -1;
        else if (i < 3)
            k = +1;
        horizontal_slide(i + 1, 21, horse);
    } while (!kbhit());
   
    chr = getch();
    y = 21;
    if (chr == 32)
    {
        while (y > 2)
        {
            y -= 1;
            gotoxy(i + 1, y);
            printf("↑");
            Sleep(50);
            printf("\b  ");
        }
      
        // 정확히 맞았을 때 확인
        if (rnd == i)
        {
            gotoxy(rnd - 1, 2);
            printf("☆");
            gotoxy(46, 9);
            printf("정확히 맞았습니다! ");
            Sleep(50);
            (*r_c)++;
            *score += 10;  // 정확히 맞았을 때 점수
        }
        // 근접 맞았을 때 확인
        else if ((rnd - 1 <= i) && (i <= rnd + 1))
        {
            gotoxy(rnd - 1, 2);
            printf("☆");
            gotoxy(46, 9);
            printf("가까이 맞았습니다. ");
            Sleep(50);
            (*r_c)++;
            *score += 5;   // 가까이 맞았을 때 점수
        }
        // 괄호에 맞았을 때
        else if (rnd - 2 == i || rnd + 2 == i)
        {
            gotoxy(rnd - 1, 2);
            printf("☆");
            gotoxy(46, 9);
            printf("괄호에 맞췄습니다. ");
            Sleep(50);
            (*r_c)++;
            *score += 5;   // 괄호에 맞았을 때 점수
        }
      
        gotoxy(1, 24);
        printf("아무키나 누르면 다음 진행...");
        getch();
    }
}

void show_final_score(int score, int mode, int score_history[][2], int history_count)
{
    system("cls");
    printf("게임이 끝났습니다.\n");
    printf("최종 점수: %d\n", score);
    
    for (int i = 0; i < history_count; i++) {
        const char* mode_name = (score_history[i][0] == 1) ? "시간제한 모드" : "제한횟수 모드";
        printf("%d회차 (%s) : %d\n", i + 1, mode_name, score_history[i][1]);
    }
    
    printf("\n게임을 재시작하려면 아무키나 누르세요.\nㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    getch();
}

void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

