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
void shop(int* score, int* experience, int* level);  // ������ �κ�
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
            y -= 1;
            gotoxy(i + 1, y);
            printf("��");
            Sleep(50);
            printf("\b  ");
        }
      
        if (rnd == i)
        {
            gotoxy(rnd - 1, 2);
            printf("��");
            gotoxy(46, 9);
            printf("��Ȯ�� �¾ҽ��ϴ�! ");
            Sleep(50);
            (*r_c)++;
            *score += 10;  
        }
        else if ((rnd - 1 <= i) && (i <= rnd + 1))
        {
            gotoxy(rnd - 1, 2);
            printf("��");
            gotoxy(46, 9);
            printf("������ �¾ҽ��ϴ�. ");
            Sleep(50);
            (*r_c)++;
            *score += 5;   
        }
        else if (rnd - 2 == i || rnd + 2 == i)
        {
            gotoxy(rnd - 1, 2);
            printf("��");
            gotoxy(46, 9);
            printf("���� �־����ϴ�. ");
            Sleep(50);
            (*r_c)++;
            *score += 2;   
        }
        else
        {
            gotoxy(rnd - 1, 2);
            printf("��");
            gotoxy(46, 9);
            printf("���ƽ��ϴ�. ");
            Sleep(50);
        }
    }
}

void show_final_score(int score, int mode, int score_history[][2], int history_count, int level)
{
    system("cls");
    printf("������ �������ϴ�.\n");
    printf("���� ����: %d\n", score);
    printf("����: %d\n", level);
    
    printf("�ֱ� ��� ���:\n");
    for (int i = history_count > 5 ? history_count - 5 : 0; i < history_count; i++) {
        const char* mode_name = (score_history[i][0] == 1) ? "�ð����� ���" : "����Ƚ�� ���";
        printf("%dȸ�� (%s) : %d��\n", i + 1, mode_name, score_history[i][1]);
    }
    
    printf("\n������ ������Ϸ��� �ƹ�Ű�� ��������.\n");
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
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
        printf("������ ���� ���� ȯ���մϴ�!\n");
        printf("���� ����: %d\n", *score);
        printf("1. ������ ��� (50��) - ����ġ�� 50 ������ŵ�ϴ�.\n");
        printf("2. ������ ��� (200��) - ����ġ�� 300 ������ŵ�ϴ�.\n");
        printf("3. ���� ���� ġƮ - ������ 300 ������ŵ�ϴ�.\n");
        printf("4. ������\n");
        
        choice = getch() - '0';
        if (choice == 1 && *score >= 50) {  // 50���� �ʿ��մϴ�.
            *score -= 50;  // ���� ����
            *experience += 50;  // ����ġ ����
            printf("����ġ�� 50 �����߽��ϴ�.\n");
            level_up(level, experience);  // ������ Ȯ��
        } else if (choice == 2 && *score >= 200) {  // 200���� �ʿ��մϴ�.
            *score -= 200;  // ���� ����
            *experience += 300;  // ����ġ ����
            printf("����ġ�� 300 �����߽��ϴ�.\n");
            level_up(level, experience);  // ������ Ȯ��
        } else if (choice == 3) {  // 0�� �Ҹ�
            *score += 300;  // ���� ����
            printf("������ 300 �����߽��ϴ�.\n");
        } else if (choice == 4) {
            break;  // ���� ������
        } else {
            printf("�߸��� �����̰ų� ������ �����մϴ�.\n");
        }
        Sleep(1000); // 1�� ���
    }
}

void level_up(int* level, int* experience)
{
    int required_experience = (*level) * 20;  
    while (*experience >= required_experience) {
        (*level)++;
        *experience -= required_experience;  
        required_experience = (*level) * 20; 
        printf("������! ���� ����: %d\n", *level);
        Sleep(1000); // 1�� ���
    }
}

void warning_screen()
{
    printf("���! 5ȸ ������ �����߽��ϴ�.\n");
    Sleep(1000);
}

void change_skin(char* target_char)
{
    int choice;
    while (1) {
        system("cls");
        printf("��Ų ���� �޴�\n");
        printf("���� ��Ų: %c\n", *target_char);
        printf("1. A ( ���� ��Ų )\n");
        printf("2. H ( ���� ��Ų )\n");
        printf("3. ������\n");
        
        choice = getch() - '0';
        if (choice == 1) {
            *target_char = 'A';  // ��Ų A�� ����
            printf("��Ų�� A�� ����Ǿ����ϴ�.\n");
        } else if (choice == 2) {
            *target_char = 'H';  // ��Ų H�� ����
            printf("��Ų�� H�� ����Ǿ����ϴ�.\n");
        } else if (choice == 3) {
            break;  // ���� ������
        } else {
            printf("�߸��� �����Դϴ�.\n");
        }
        Sleep(1000); // 1�� ���
    }
}


void display_current_time()
{
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    gotoxy(46, 10);
    printf("���� �ð�: %02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
}

