#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct trump {
    int order;
    char shape[3];
    char number[3]; // 숫자를 문자로 저장하기 위해 변경
};

void make_card(struct trump m_card[]);
void display_card(struct trump m_card[]);

void display_card(struct trump m_card[]) {
    for (int i = 0; i < 52; i++) {
        printf("%s", m_card[i].shape);

        // 10 다음에 공백 추가
        if (strcmp(m_card[i].number, "10") == 0) {
            printf("%-2s ", m_card[i].number); // 공백 추가
        } else {
            printf("%-2s", m_card[i].number);
        }

        if (i % 13 == 12) {
            printf("\n");
        }
    }
}
void shuffle_card (trump m_card [])

{

int i, rnd; trump temp; srand (time(NULL)); //random number initialization 
for(i=0;i<52;i++)

{

rnd=rand()%52;

temp=m_card [rnd];

m_card [rnd]=m_card[i];

m_card [i]=temp;

}

}
void make_card(struct trump m_card[]) {
    int i, j;
    char shape[4][3] = {"H", "D", "S", "C"};
    
    for (i = 0; i < 4; i++) {
        for (j = i * 13; j < i * 13 + 13; j++) {
            m_card[j].order = i;
            strcpy(m_card[j].shape, shape[i]);
            int num = j % 13 + 2;
            
            switch (num) {
                case 14:
                    strcpy(m_card[j].number, "A");
                    break;
                case 11:
                    strcpy(m_card[j].number, "J");
                    break;
                case 12:
                    strcpy(m_card[j].number, "Q");
                    break;
                case 13:
                    strcpy(m_card[j].number, "K");
                    break;
                default:
                    sprintf(m_card[j].number, "%d", num); // 숫자를 문자열로 변환
                    break;
            }
        }
    }
}

int main(void) {
    struct trump card[52];
    make_card(card);
    shuffle_card(card);
    display_card(card);
    return 0;
}
