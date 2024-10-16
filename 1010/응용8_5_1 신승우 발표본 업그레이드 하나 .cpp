#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_HISTORY 5

// �Լ� ������Ÿ�� ����
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

int achievement_score = 0;  // ���� ����
int achievement_unlocked = 0;  // ���� �޼� ����

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

        if (mode == 5) {  // ���� ����
            printf("������ �����մϴ�...\n");
            break; 
        }

        if (mode == 4) {  // ��Ų ����
            change_skin(&target_char);
            continue;
        }

        if (mode == 3) {  // ����
            shop(&score, &experience, &level); 
            continue; 
        }

        if (mode == 6) {  // ���� ������
            system("cls");
            printf("���� ������\n");
            printf("���� ���� ����: %d\n", achievement_score);
            if (achievement_unlocked) {
                printf("100�� ������ �޼��߽��ϴ�!\n");
            } else {
                printf("���� ������ �޼����� ���߽��ϴ�.\n");
            }
            printf("�ڷ� ������ �ƹ� Ű�� ��������...\n");
            getch();
            continue;
        }

        count = 0;
        score = 0;

        if (mode == 1) {  // �ð����� ���
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
        } else {  // ����Ƚ�� ���
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
    printf("��� ����\n\n"); 
    printf("��ǥ��((��))�� ���ߴ� �����Դϴ�. \n");
    printf("�߾ӿ� ���߽� 10��, �׵θ��� 5���Դϴ�.\n");
    printf("ȭ���� �����̽�Ű�� �߻��մϴ�. \n\n");
    printf("�ƹ�Ű�� ������ �����մϴ�.\n\n ");
    getch();
}

void select_mode(int* mode)
{
    printf("��带 �����ϼ���:\n");
    printf("1. �ð����� ���\n");
    printf("2. ����Ƚ�� ���\n");
    printf("3. ����\n");
    printf("4. ��Ų ����\n");
    printf("5. ���� ����\n");
    printf("6. ���� ������\n");  

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
    printf("\n��尡 ���õǾ����ϴ�.\n");
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
    printf("�����̽�Ű�� ������\n");
    gotoxy(46, 3);
    printf("ȭ���� �߻�˴ϴ�.\n");
    gotoxy(46, 5);

    if (mode == 1) {
        printf("�õ� Ƚ�� : %d", count);
        gotoxy(46, 7);
        printf("���� �ð� : %d��", max_time);
    } else {
        printf("���� Ƚ�� : %d", max_attempts - count);
    }

    gotoxy(46, 6);
    printf("���� : %d", score);
    gotoxy(46, 8);
    printf("���� : %d", level);
}

void game_control(int* r_c, int rnd, int* score, char* target_char)
{
    int i = 1, k = 1, y;
    char *horse = "��", chr;
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
                    achievement_score += 10; // ���� ���� �߰�
                    if (achievement_score >= 100) {
                        achievement_unlocked = 1; // ���� �޼�
                    }
                }
                else if (i >= rnd - 3 && i <= rnd + 3)
                {
                    *score += 5; 
                    achievement_score += 5; // ���� ���� �߰�
                    if (achievement_score >= 100) {
                        achievement_unlocked = 1; // ���� �޼�
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
    printf("���� ����!\n");
    printf("���� ����: %d\n", score);
    printf("����: %d\n", level);
    printf("���: %d\n", mode);
    printf("���� ���:\n");
    for (int i = 0; i < history_count; i++)
    {
        printf("��� %d: %d��\n", score_history[i][0], score_history[i][1]);
    }
    printf("�ƹ� Ű�� ������ ���� �޴��� ���ư��ϴ�...\n");
    getch();
}

void gotoxy(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void shop(int* score, int* experience, int* level)
{
    // ���� ��� ����
    printf("������ ���� ���� ȯ���մϴ�!\n");
    printf("���� ����: %d, ����ġ: %d, ����: %d\n", *score, *experience, *level);
    printf("������ �׸��� �����ϼ���...\n");
    // ���� ���� �߰�
    printf("�ƹ� Ű�� ���� ���� �޴��� ���ư��ϴ�...\n");
    getch();
}

void level_up(int* level, int* experience)
{
    if (*experience >= (*level * 100)) {
        (*level)++;
        *experience = 0;  
        printf("���� ��! ���� ����: %d\n", *level);
    }
}

void warning_screen()
{
    printf("���: �ʹ� ���� ������ ����Ǿ����ϴ�!\n");
    printf("��� �� ������ �����մϴ�...\n");
    Sleep(2000);
}

void change_skin(char* target_char)
{
    printf("������ ��Ų�� �Է��ϼ���: ");
    scanf(" %c", target_char);
    printf("��Ų�� ����Ǿ����ϴ�: %c\n", *target_char);
}

void display_current_time()
{
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    gotoxy(46, 10);
    printf("���� �ð�: %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
}

