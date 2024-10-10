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
void shop(int* score, int* experience, int* level);  // 수정된 부분
void level_up(int* level, int* experience);
void warning_screen();
void change_skin(char* target_char);
void display_current_time();

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
            y -= 1;
            gotoxy(i + 1, y);
            printf("↑");
            Sleep(50);
            printf("\b  ");
        }
      
        if (rnd == i)
        {
            gotoxy(rnd - 1, 2);
            printf("☆");
            gotoxy(46, 9);
            printf("정확히 맞았습니다! ");
            Sleep(50);
            (*r_c)++;
            *score += 10;  
        }
        else if ((rnd - 1 <= i) && (i <= rnd + 1))
        {
            gotoxy(rnd - 1, 2);
            printf("☆");
            gotoxy(46, 9);
            printf("가까이 맞았습니다. ");
            Sleep(50);
            (*r_c)++;
            *score += 5;   
        }
        else if (rnd - 2 == i || rnd + 2 == i)
        {
            gotoxy(rnd - 1, 2);
            printf("☆");
            gotoxy(46, 9);
            printf("조금 멀었습니다. ");
            Sleep(50);
            (*r_c)++;
            *score += 2;   
        }
        else
        {
            gotoxy(rnd - 1, 2);
            printf("☆");
            gotoxy(46, 9);
            printf("놓쳤습니다. ");
            Sleep(50);
        }
    }
}

void show_final_score(int score, int mode, int score_history[][2], int history_count, int level)
{
    system("cls");
    printf("게임이 끝났습니다.\n");
    printf("최종 점수: %d\n", score);
    printf("레벨: %d\n", level);
    
    printf("최근 경기 기록:\n");
    for (int i = history_count > 5 ? history_count - 5 : 0; i < history_count; i++) {
        const char* mode_name = (score_history[i][0] == 1) ? "시간제한 모드" : "제한횟수 모드";
        printf("%d회차 (%s) : %d점\n", i + 1, mode_name, score_history[i][1]);
    }
    
    printf("\n게임을 재시작하려면 아무키나 누르세요.\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    getch();
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void shop(int* score, int* experience, int* level)
{
    int choice;
    while (1) {
        system("cls");
        printf("상점에 오신 것을 환영합니다!\n");
        printf("현재 점수: %d\n", *score);
        printf("1. 경험의 비약 (50점) - 경험치를 50 증가시킵니다.\n");
        printf("2. 경험의 비약 (200점) - 경험치를 300 증가시킵니다.\n");
        printf("3. 점수 증가 치트 - 점수를 300 증가시킵니다.\n");
        printf("4. 나가기\n");
        
        choice = getch() - '0';
        if (choice == 1 && *score >= 50) {  // 50점이 필요합니다.
            *score -= 50;  // 점수 차감
            *experience += 50;  // 경험치 증가
            printf("경험치가 50 증가했습니다.\n");
            level_up(level, experience);  // 레벨업 확인
        } else if (choice == 2 && *score >= 200) {  // 200점이 필요합니다.
            *score -= 200;  // 점수 차감
            *experience += 300;  // 경험치 증가
            printf("경험치가 300 증가했습니다.\n");
            level_up(level, experience);  // 레벨업 확인
        } else if (choice == 3) {  // 0점 소모
            *score += 300;  // 점수 증가
            printf("점수가 300 증가했습니다.\n");
        } else if (choice == 4) {
            break;  // 상점 나가기
        } else {
            printf("잘못된 선택이거나 점수가 부족합니다.\n");
        }
        Sleep(1000); // 1초 대기
    }
}

void level_up(int* level, int* experience)
{
    int required_experience = (*level) * 20;  
    while (*experience >= required_experience) {
        (*level)++;
        *experience -= required_experience;  
        required_experience = (*level) * 20; 
        printf("레벨업! 현재 레벨: %d\n", *level);
        Sleep(1000); // 1초 대기
    }
}

void warning_screen()
{
    printf("경고! 5회 게임을 진행했습니다.\n");
    Sleep(1000);
}

void change_skin(char* target_char)
{
    int choice;
    while (1) {
        system("cls");
        printf("스킨 변경 메뉴\n");
        printf("현재 스킨: %c\n", *target_char);
        printf("1. A ( 과녁 스킨 )\n");
        printf("2. H ( 과녁 스킨 )\n");
        printf("3. 나가기\n");
        
        choice = getch() - '0';
        if (choice == 1) {
            *target_char = 'A';  // 스킨 A로 변경
            printf("스킨이 A로 변경되었습니다.\n");
        } else if (choice == 2) {
            *target_char = 'H';  // 스킨 H로 변경
            printf("스킨이 H로 변경되었습니다.\n");
        } else if (choice == 3) {
            break;  // 상점 나가기
        } else {
            printf("잘못된 선택입니다.\n");
        }
        Sleep(1000); // 1초 대기
    }
}


void display_current_time()
{
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    gotoxy(46, 10);
    printf("현재 시간: %02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
}

