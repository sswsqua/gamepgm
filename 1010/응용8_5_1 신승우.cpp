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
    int max_attempts = 10;  // �⺻ �ִ� �õ� Ƚ��
    int max_time = 10;      // ���� �ð��� 10�ʷ� ����
    int score_history[MAX_HISTORY][2] = {0};  // �ֱ� 5ȸ�� ������ ��� ��� (mode, score)
    int history_count = 0;  // ���� ��� ����

    srand(time(NULL));

    while (1) {
        intro_game();
        select_mode(&mode);  // ��� ����

        // ���� ���� ���
        if (mode == 3) {
            printf("������ �����մϴ�...\n");
            break;
        }

        count = 0;
        score = 0;

        if (mode == 1) {
            // �ð� ���� ���
            time_t start_time = time(NULL);
            do
            {
                system("cls");
                draw_rectangle(20, 20);
                rnd = rand() % 35 + 4;  // ǥ�� ��ġ ����
                gotoxy(rnd - 1, 2); // ��ȣ�� �����ϱ� ���� ��ġ ����
                printf("(��)"); // ��ȣ�� ���׶�� ǥ�� ���
                count++;
                display_text(count, max_attempts, score, max_time - (time(NULL) - start_time), mode);
                game_control(&r_count, rnd, &score);
            } while (time(NULL) - start_time < max_time);
        } else {
            // Ƚ�� ���� ���
            do
            {
                system("cls");
                draw_rectangle(20, 20);
                rnd = rand() % 35 + 4;  // ǥ�� ��ġ ����
                gotoxy(rnd - 1, 2); // ��ȣ�� �����ϱ� ���� ��ġ ����
                printf("(��)"); // ��ȣ�� ���׶�� ǥ�� ���
                count++;
                display_text(count, max_attempts, score, max_time, mode);
                game_control(&r_count, rnd, &score);
            } while (count < max_attempts);
        }

        // ���� ���
        if (history_count < MAX_HISTORY) {
            score_history[history_count][0] = mode;  // ��� ���
            score_history[history_count][1] = score; // ���� ���
            history_count++;
        } else {
            for (int i = 1; i < MAX_HISTORY; i++) {
                score_history[i - 1][0] = score_history[i][0];  // ��� ����Ʈ 
                score_history[i - 1][1] = score_history[i][1];  // ���� ����Ʈ 
            }
            score_history[MAX_HISTORY - 1][0] = mode;  // ���� ��� ���� 
            score_history[MAX_HISTORY - 1][1] = score; // ���� ���� ����  
        }

        // ���� ���� �� ���� ���� ���
        show_final_score(score, mode, score_history, history_count);
    }

    return 0;
}

void intro_game(void)
{
    printf("��Ÿ�� ȭ����\n\n");
    printf("���� Ÿ�� �̵��ϸ鼭 \n");
    printf("��ǥ��((��))�� ���ߴ� �����Դϴ�. \n");
    printf("ȭ���� �����̽�Ű�� �߻��մϴ�. \n\n");
    printf("�ƹ�Ű�� ������ �����մϴ�. ");
    getch();
}

void select_mode(int* mode)
{
    printf("��带 �����ϼ���:\n");
    printf("1. �ð����� ���\n");
    printf("2. ����Ƚ�� ���\n");
    printf("3. ���� ����\n");
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
    printf("\n��尡 ���õǾ����ϴ�. �����մϴ�...\n");
    Sleep(1000); // 1�� ���
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
    printf("�����̽�Ű�� ������\n");
    gotoxy(46, 3);
    printf("ȭ���� �߻�˴ϴ�.\n");
    gotoxy(46, 5);

    // ��忡 ���� ǥ�� ���� ����
    if (mode == 1) {
        printf("�õ� Ƚ�� : %d", count);
        gotoxy(46, 7);
        printf("���� �ð� : %d��", max_time);
    } else {
        printf("���� Ƚ�� : %d", max_attempts - count);
        // ���� Ƚ�� ��忡���� ���� �ð� ǥ�� �� ��
    }

    gotoxy(46, 6);
    printf("���� : %d", score);
}


void game_control(int* r_c, int rnd, int* score)
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
            y -= 1;
            gotoxy(i + 1, y);
            printf("��");
            Sleep(50);
            printf("\b  ");
        }
      
        // ��Ȯ�� �¾��� �� Ȯ��
        if (rnd == i)
        {
            gotoxy(rnd - 1, 2);
            printf("��");
            gotoxy(46, 9);
            printf("��Ȯ�� �¾ҽ��ϴ�! ");
            Sleep(50);
            (*r_c)++;
            *score += 10;  // ��Ȯ�� �¾��� �� ����
        }
        // ���� �¾��� �� Ȯ��
        else if ((rnd - 1 <= i) && (i <= rnd + 1))
        {
            gotoxy(rnd - 1, 2);
            printf("��");
            gotoxy(46, 9);
            printf("������ �¾ҽ��ϴ�. ");
            Sleep(50);
            (*r_c)++;
            *score += 5;   // ������ �¾��� �� ����
        }
        // ��ȣ�� �¾��� ��
        else if (rnd - 2 == i || rnd + 2 == i)
        {
            gotoxy(rnd - 1, 2);
            printf("��");
            gotoxy(46, 9);
            printf("��ȣ�� ������ϴ�. ");
            Sleep(50);
            (*r_c)++;
            *score += 5;   // ��ȣ�� �¾��� �� ����
        }
      
        gotoxy(1, 24);
        printf("�ƹ�Ű�� ������ ���� ����...");
        getch();
    }
}

void show_final_score(int score, int mode, int score_history[][2], int history_count)
{
    system("cls");
    printf("������ �������ϴ�.\n");
    printf("���� ����: %d\n", score);
    
    for (int i = 0; i < history_count; i++) {
        const char* mode_name = (score_history[i][0] == 1) ? "�ð����� ���" : "����Ƚ�� ���";
        printf("%dȸ�� (%s) : %d\n", i + 1, mode_name, score_history[i][1]);
    }
    
    printf("\n������ ������Ϸ��� �ƹ�Ű�� ��������.\n�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
    getch();
}

void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

