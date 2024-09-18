#include <stdio.h>

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b) {
    switch(key) {
        case 72:  // 위쪽 화살표 키
            (*y1)--;  
            if (*y1 < 1) *y1 = 1;  
            break;
        case 75:  // 왼쪽 화살표 키
            (*x1)--;  
            if (*x1 < 1) *x1 = 1;  
            break;
        case 77:  // 오른쪽 화살표 키
            (*x1)++;  
            if (*x1 > x_b) *x1 = x_b;  
            break;
        case 80:  // 아래쪽 화살표 키
            (*y1)++;  
            if (*y1 > y_b) *y1 = y_b;  
            break;
        default:
            return;  
    }
}

int main() {
    int x = 1, y = 1;
    char key = 80; // 예시로 아래쪽 화살표 키
    move_arrow_key(key, &x, &y, 10, 10); // 최대 x, y 값을 10으로 설정
    printf("Position: (%d, %d)\n", x, y);
    return 0;
}

