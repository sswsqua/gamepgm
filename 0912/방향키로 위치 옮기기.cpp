#include <stdio.h>

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b) {
    switch(key) {
        case 72:  // ���� ȭ��ǥ Ű
            (*y1)--;  
            if (*y1 < 1) *y1 = 1;  
            break;
        case 75:  // ���� ȭ��ǥ Ű
            (*x1)--;  
            if (*x1 < 1) *x1 = 1;  
            break;
        case 77:  // ������ ȭ��ǥ Ű
            (*x1)++;  
            if (*x1 > x_b) *x1 = x_b;  
            break;
        case 80:  // �Ʒ��� ȭ��ǥ Ű
            (*y1)++;  
            if (*y1 > y_b) *y1 = y_b;  
            break;
        default:
            return;  
    }
}

int main() {
    int x = 1, y = 1;
    char key = 80; // ���÷� �Ʒ��� ȭ��ǥ Ű
    move_arrow_key(key, &x, &y, 10, 10); // �ִ� x, y ���� 10���� ����
    printf("Position: (%d, %d)\n", x, y);
    return 0;
}

