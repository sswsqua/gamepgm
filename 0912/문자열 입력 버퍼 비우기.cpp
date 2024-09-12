#include <stdio.h>

int main()
{
		char string[20];
		char c;
		scanf("%s", string);  // 실행 이후 개행문자가 남아있어 밑의 scanf에 입력이 강제로 됨.
		getchar();		// 입력 버퍼 비워주기
		// fflush(stdin);     출력버퍼를 비워줌. 
		//그러나 gcc에서는 작동안됨. vc에서는 확장해서 사용하므로동작.
		scanf("%c", &c);
		// scanf(" %c", &c);  으로하면 공백문자를 구분자로 인식. getchar(); 대신 가능.

		printf("%s\n", string);
		printf("!!%c!!\n", c);
		return 0;
}
