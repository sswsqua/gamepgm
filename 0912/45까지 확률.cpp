#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int i;
    srand(time(NULL));
    for(i = 1; i <= 6; i++)
        printf("%2d\n", rand() % 45 + 1);
    return 0;
}

