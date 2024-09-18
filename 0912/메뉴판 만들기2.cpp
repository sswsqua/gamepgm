#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int menu_display(void);
int sub_menu_display01(void); // 햄버거에 대한 서브 메뉴 출력과 번호 입력
int sub_menu_display02(void); // 스파게티에 대한 서브 메뉴 출력과 번호 입력
void sub_main01(void); // 햄버거에 대한 서브 메뉴 제어
void sub_main02(void); // 스파게티에 대한 서브 메뉴 제어
void chicken_burger(void);
void cheese_burger(void);
void tomato_spaghetti(void);
void cream_spaghetti(void);
void press_any_key(void); // 아무키나 누르면 이전 메뉴로

int main(void) {
    int c;
    while ((c = menu_display()) != 3) {
        switch (c) {
            case 1: sub_main01(); break;
            case 2: sub_main02(); break;
            default: break;
        }
    }
    return 0;
}

int menu_display(void) {
    int select;
    system("cls");
    printf("간식 만들기\n\n");
    printf("1. 햄버거 \n");
    printf("2. 스파게티\n");
    printf("3. 프로그램 종료\n\n");
    printf("메뉴번호 입력>");
    select = getch() - '0'; // '0'의 ASCII 값을 빼서 숫자로 변환
    return select;
}

void sub_main01(void) {
    int c;
    while ((c = sub_menu_display01()) != 3) {
        switch (c) {
            case 1: chicken_burger(); break;
            case 2: cheese_burger(); break;
            default: break;
        }
    }
}

void chicken_burger(void) {
    system("cls");
    printf("치킨버거 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

void cheese_burger(void) {
    system("cls");
    printf("치즈버거 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

int sub_menu_display01(void) {
    int select;
    system("cls");
    printf("햄버거 만들기\n\n");
    printf("1. 치킨버거\n");
    printf("2. 치즈버거\n");
    printf("3. 메인 메뉴로 이동\n\n");
    printf("메뉴번호 입력>");
    select = getch() - '0'; // '0'의 ASCII 값을 빼서 숫자로 변환
    return select;
}

void sub_main02(void) {
    int c;
    while ((c = sub_menu_display02()) != 3) {
        switch (c) {
            case 1: tomato_spaghetti(); break;
            case 2: cream_spaghetti(); break;
            default: break;
        }
    }
}

int sub_menu_display02(void) {
    int select;
    system("cls");
    printf("스파게티 만들기\n\n");
    printf("1. 토마토 스파게티\n");
    printf("2. 크림 스파게티\n");
    printf("3. 메인 메뉴로 이동\n\n");
    printf("메뉴번호 입력>");
    select = getch() - '0'; // '0'의 ASCII 값을 빼서 숫자로 변환
    return select;
}

void tomato_spaghetti(void) {
    system("cls");
    printf("토마토 스파게티 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

void cream_spaghetti(void) {
    system("cls");
    printf("크림 스파게티 만드는 방법\n");
    printf("중략\n");
    press_any_key();
}

void press_any_key(void) {
    printf("\n\n");
    printf("아무 키나 누르면 이전 메뉴로...");
    getch();
}
 
