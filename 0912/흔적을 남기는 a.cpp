#include <stdio.h>
#include <conio.h>
#include <windows.h>
void gotoxy(int x, int y)
{
COORD Pos = {x - 1, y - 1};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
// move_arrow_key 함수의 선언
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b);

// move_arrow_key 함수의 정의
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b) {
    switch(key) {
        case 72: // 위쪽(상) 방향의 화살표 키 입력
            *y1 = *y1 - 1;
            if (*y1 < 1) *y1 = 1; // y좌표의 최소값
            break;
        case 75: // 왼쪽(좌) 방향의 화살표 키 입력
            *x1 = *x1 - 1;
            if (*x1 < 1) *x1 = 1; // x좌표의 최소값
            break;
        case 77: // 오른쪽(우) 방향의 화살표 키 입력
            *x1 = *x1 + 1;
            if (*x1 > x_b) *x1 = x_b; // x좌표의 최대값
            break;
        case 80: // 아래쪽(하) 방향의 화살표 키 입력
            *y1 = *y1 + 1;
            if (*y1 > y_b) *y1 = y_b; // y좌표의 최대값
            break;
        default:
            return;
    }
}

int main() {
    int x = 10, y = 10; // 초기 좌표
    int x_b = 20, y_b = 20; // 최대 좌표
    char key;

    printf("Press arrow keys to move. Press ESC to exit.\n");

    while (1) {
        key = _getch(); // 키 입력 받기
        if (key == 27) { // ESC 키를 누르면 종료
            break;
        }
        move_arrow_key(key, &x, &y, x_b, y_b);
        gotoxy(x,y);
        printf("A");
        //printf("Current position: (%d, %d)\n", x, y);
    }

    return 0;
}
