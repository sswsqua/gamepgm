#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_HISTORY 5

// 함수 프로토타입 선언
void intro_game(void);
void select_mode(int* mode);
void horizontal_slide(int x, int y, char *c2);
void draw_rectangle(int r, int c, char* target_char);
void display_text(int count, int max_attempts, int score, int max_time, int mode, int level);
void game_control(int* r_c, int rnd, int* score, char* target_char);
void show_final_score(int score, int mode, int score_history[][2], int history_count, int level);
void gotoxy(int x, int y);
void shop(int* score, int* experience, int* level);
void level_up(int* level, int* experience);
void warning_screen();
void change_skin(char* target_char);
void display_current_time();

int achievement_score = 0;  // 업적 점수
int achievement_unlocked = 0;  // 업적 달성 여부

int main(void)
{
    int count = 0, rnd;
    int r_count = 0;
    int score = 0;
    int mode;
    int max_attempts = 10;  
    int max_time = 10;      
    int score_history[MAX_HISTORY][2] = {0};  
    int history_count = 0;  
    int level = 1;  
    int experience = 0;  
    int warning_count = 0;

    char target_char = '0'; 
    srand(time(NULL));

    while (1) {
        intro_game();
        select_mode(&mode); 

        if (mode == 5) {  // 게임 종료
            printf("게임을 종료합니다...\n");
            break; 
        }

        if (mode == 4) {  // 스킨 변경
            change_skin(&target_char);
            continue;
        }

        if (mode == 3) {  // 상점
            shop(&score, &experience, &level); 
            continue; 
        }

        if (mode == 6) {  // 업적 열람실
            system("cls");
            printf("업적 열람실\n");
            printf("현재 업적 점수: %d\n", achievement_score);
            if (achievement_unlocked) {
                printf("100점 업적을 달성했습니다!\n");
            } else {
                printf("아직 업적을 달성하지 못했습니다.\n");
            }
            printf("뒤로 가려면 아무 키나 누르세요...\n");
            getch();
            continue;
        }

        count = 0;
        score = 0;

        if (mode == 1) {  // 시간제한 모드
            time_t start_time = time(NULL);
            do {
                system("cls");
                draw_rectangle(20, 20, &target_char);
                rnd = rand() % 35 + 4;  
                gotoxy(rnd - 1, 2); 
                printf("(%c)", target_char); 
                count++;
                display_text(count, max_attempts, score, max_time - (time(NULL) - start_time), mode, level);
                display_current_time(); 
                game_control(&r_count, rnd, &score, &target_char);
            } while (time(NULL) - start_time < max_time);
        } else {  // 제한횟수 모드
            do {
                system("cls");
                draw_rectangle(20, 20, &target_char);
                rnd = rand() % 35 + 4;  
                gotoxy(rnd - 1, 2); 
                printf("(%c)", target_char); 
                count++;
                display_text(count, max_attempts, score, max_time, mode, level);
                display_current_time(); 
                game_control(&r_count, rnd, &score, &target_char);
            } while (count < max_attempts);
        }

        experience += score;  
        level_up(&level, &experience);
        warning_count++;
        if (warning_count >= 5) {
            warning_screen();
            warning_count -= 5;
        }

        if (history_count < MAX_HISTORY) {
            score_history[history_count][0] = mode;  
            score_history[history_count][1] = score; 
            history_count++;
        } else {
            for (int i = 1; i < MAX_HISTORY; i++) {
                score_history[i - 1][0] = score_history[i][0];  
                score_history[i - 1][1] = score_history[i][1];  
            }
            score_history[MAX_HISTORY - 1][0] = mode;  
            score_history[MAX_HISTORY - 1][1] = score; 
        }

        show_final_score(score, mode, score_history, history_count, level);
    }

    return 0;
}

void intro_game(void)
{
    printf("양궁 게임\n\n"); 
    printf("목표물((●))을 맞추는 게임입니다. \n");
    printf("중앙에 적중시 10점, 테두리는 5점입니다.\n");
    printf("화살은 스페이스키로 발사합니다. \n\n");
    printf("아무키나 누르면 시작합니다.\n\n ");
    getch();
}

void select_mode(int* mode)
{
    printf("모드를 선택하세요:\n");
    printf("1. 시간제한 모드\n");
    printf("2. 제한횟수 모드\n");
    printf("3. 상점\n");
    printf("4. 스킨 변경\n");
    printf("5. 게임 종료\n");
    printf("6. 업적 열람실\n");  

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
        } else if (ch == '4') {
            *mode = 4;
            break;
        } else if (ch == '5') {
            *mode = 5;
            break;
        } else if (ch == '6') {
            *mode = 6;
            break;
        }
    }
    printf("\n모드가 선택되었습니다.\n");
    Sleep(1000);
}

void horizontal_slide(int x, int y, char *c2)
{
    gotoxy(x, y);
    printf("%s", c2);
    Sleep(50);
    printf("\b ");
}

void draw_rectangle(int r, int c, char* target_char)
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

void display_text(int count, int max_attempts, int score, int max_time, int mode, int level)
{
    gotoxy(46, 2);
    printf("스페이스키를 누르면\n");
    gotoxy(46, 3);
    printf("화살이 발사됩니다.\n");
    gotoxy(46, 5);

    if (mode == 1) {
        printf("시도 횟수 : %d", count);
        gotoxy(46, 7);
        printf("남은 시간 : %d초", max_time);
    } else {
        printf("남은 횟수 : %d", max_attempts - count);
    }

    gotoxy(46, 6);
    printf("점수 : %d", score);
    gotoxy(46, 8);
    printf("레벨 : %d", level);
}

void game_control(int* r_c, int rnd, int* score, char* target_char)
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
            y--;
            gotoxy(i + 1, y);
            printf("%c", ' '); 
            Sleep(10);
            gotoxy(i + 1, y);
            if (y == 2)
            {
                if (i >= rnd - 1 && i <= rnd + 1)
                {
                    *score += 10; 
                    achievement_score += 10; // 업적 점수 추가
                    if (achievement_score >= 100) {
                        achievement_unlocked = 1; // 업적 달성
                    }
                }
                else if (i >= rnd - 3 && i <= rnd + 3)
                {
                    *score += 5; 
                    achievement_score += 5; // 업적 점수 추가
                    if (achievement_score >= 100) {
                        achievement_unlocked = 1; // 업적 달성
                    }
                }
                break;
            }
        }
    }
}

void show_final_score(int score, int mode, int score_history[][2], int history_count, int level)
{
    system("cls");
    printf("게임 종료!\n");
    printf("최종 점수: %d\n", score);
    printf("레벨: %d\n", level);
    printf("모드: %d\n", mode);
    printf("점수 기록:\n");
    for (int i = 0; i < history_count; i++)
    {
        printf("모드 %d: %d점\n", score_history[i][0], score_history[i][1]);
    }
    printf("아무 키나 누르면 메인 메뉴로 돌아갑니다...\n");
    getch();
}

void gotoxy(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void shop(int* score, int* experience, int* level)
{
    // 상점 기능 구현
    printf("상점에 오신 것을 환영합니다!\n");
    printf("현재 점수: %d, 경험치: %d, 레벨: %d\n", *score, *experience, *level);
    printf("구매할 항목을 선택하세요...\n");
    // 구매 로직 추가
    printf("아무 키나 눌러 메인 메뉴로 돌아갑니다...\n");
    getch();
}

void level_up(int* level, int* experience)
{
    if (*experience >= (*level * 100)) {
        (*level)++;
        *experience = 0;  
        printf("레벨 업! 현재 레벨: %d\n", *level);
    }
}

void warning_screen()
{
    printf("경고: 너무 많은 게임이 진행되었습니다!\n");
    printf("잠시 후 게임을 종료합니다...\n");
    Sleep(2000);
}

void change_skin(char* target_char)
{
    printf("변경할 스킨을 입력하세요: ");
    scanf(" %c", target_char);
    printf("스킨이 변경되었습니다: %c\n", *target_char);
}

void display_current_time()
{
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    gotoxy(46, 10);
    printf("현재 시간: %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
}

