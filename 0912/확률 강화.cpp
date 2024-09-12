#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int a;
	int main(void)
{
	int i;
	srand(time(NULL));
	for(i=1;i<=10;i++)
	a=rand()%100+1;
	if(a<=30) {
		printf("%d success",a);
	}
	else printf("%d fail",a);
	return 0;
}