#include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 void selection_sort(int r[], int n);
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
 selection_sort(lotto, 6);
 return 0;
 }
 void selection_sort(int r[], int n)
 {
 int i, j, min, temp;
 for (i=0;i<=n;i++)
 {
 min= i;
 for (j=i+1;j<=n;j++)
 if (r[j] < r[min])
 min= j;
 temp= r[min];
 r[min] = r[i];
 r[i] = temp;
 }
 for(i=0;i<=5;i++)
 printf("%2d\n", r[i]);
 }

