#include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 int main(void)
 {
 int i, j, lotto[6];
 srand(time(NULL));
 for(i=0;i<=5;i++)
 {
 lotto[i]=rand()%45+1;
 for(j=0;j<i;j++)
 {
 if (lotto[i] == lotto[j])
 {
 i--;
 break;
 }
 }
 }
 for(i=0;i<=5;i++)
 printf("%2d\n", lotto[i]);
 return 0;
 }
