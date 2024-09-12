#include <stdio.h>

int main() {
	
	char string[20] = "abcd";
	//string = "abcd"; 작동 오류. 공간의 크기가 맞지않음
	printf("%d\n", sizeof(string)); // 20출력
	
	int i;
	i = printf("%s\n",string); // abcd 출력
	printf("%d\n",i); // 5 출력
	
	return 0;
}