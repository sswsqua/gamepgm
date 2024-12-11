커서의 위치 제어

gotoxy(x, y): 콘솔에서 커서의 위치를 (x, y) 좌표로 이동시키는 함수입니다. windows.h 라이브러리를 사용하여 구현합니다.

예제 코드: gotoxy(2, 4); printf("Hello");

goto1 파일 : hello 를 원하는 위치에 출력하도록 하는 예제.

![image](https://github.com/user-attachments/assets/eeeb55a8-ec64-4add-8061-5358c02fdc59)

goto2 파일 : 구구단 3단을 원하는 위치에 출력하도록 하는 예제.

![image](https://github.com/user-attachments/assets/fecf9e9c-e9f2-4c90-b1b1-f3189a7c60a3)

system("cls"): 화면을 지우는 명령입니다.

getch(): 사용자가 키를 누를 때까지 대기하는 함수입니다.

예제 코드에서 getch()를 사용하여 주기적으로 화면을 지우고 3단 출력 등의 작업을 수행합니다.

화면 지우기1 파일 : 화면에 출력된 것들을 지우고 새로 출력함.

![image](https://github.com/user-attachments/assets/b9829bea-514a-47c6-a4bb-8a9542e65018)

화면 지우기2 파일 : 화면에 출력된 것들을 지우면서 구구단을 9단까지 출력함.

![image](https://github.com/user-attachments/assets/300d931f-3945-49b6-a30a-2a794d3b3bb6)

getchar(): 한 문자 입력.

getche(): 한 문자 입력 후 즉시 출력.

getch(): 한 문자 입력 후 출력하지 않음.

입력 버퍼 비우기: getch() 등에서 입력 버퍼를 처리할 때 유용합니다.

ASCII 코드: 컴퓨터 내부에서 문자를 처리하기 위한 코드.

스캔 코드: 각 키에 대한 코드 값. 예를 들어, 확장키 코드(화살표 키, Home, End 등).

예제 코드에서는 getch()를 사용하여 ASCII 코드와 확장키 코드(2바이트)를 구별하는 방법을 보여줍니다.

확장키 아스키 파일 : 입력을 하면 그에 해당하는 아스키와 확장키를 출력함.

![image](https://github.com/user-attachments/assets/16848633-edb4-41db-ae5a-a08eda139fdb)


move_arrow_key: 화살표 키 입력에 따라 화면에서 커서 위치를 이동시키는 함수.

예제 코드에서는 화살표 키에 맞춰 (x, y) 좌표를 변경하는 방법을 다룹니다.

방향키로 위치 옮기기 파일 : 방향키에 따른 좌표 이동 ( 입력 구현하지 않았으므로 코드에서 원하는 키 값 기입 )


![image](https://github.com/user-attachments/assets/2ac63d83-851c-4428-b8be-ee769f63d628)

움직이기 파일 : 방향키에 따른 A 문자 이동

![image](https://github.com/user-attachments/assets/592f2e38-b442-4064-8707-e393feac33c1)

정사각형 그리기: 텍스트 모드에서 사각형을 그리는 방법을 설명합니다. 

기본적으로 확장 문자(─, │, ┌, ┘ 등)를 사용하여 사각형을 그립니다.

예제 코드: draw_square(int size) 함수로 크기를 지정하여 사각형을 그립니다.

사각형 그리기 파일 : 사각형을 그리는 방법에 대한 예제 파일. 0xa3~6 기호를 사용함.

![image](https://github.com/user-attachments/assets/87db13e2-cfe5-4861-9a81-07bc028f8b42)

사각형 옵션넣어 그리기 파일 : 입력을 받은 값을 한 변으로 하는 정사각형을 그리는 예제.

![image](https://github.com/user-attachments/assets/1b8b7a87-000d-4caa-8b70-20b23944d75e)


메뉴 출력: getch()를 사용하여 사용자의 입력을 받고, 입력에 따라 메뉴에서 선택을 처리합니다.

예제 코드에서는 간식 만들기 메뉴와 그 하위 메뉴(햄버거, 스파게티)를 구현하는 방법을 보여줍니다.

메뉴판 만들기 파일 : 입력을 받으면 그에 해당하는 정보를 보여주는 화면으로 넘어가는 예제.

![image](https://github.com/user-attachments/assets/272ce8e0-6506-4a08-913f-4c7229e7982f)
![image](https://github.com/user-attachments/assets/72504b3a-212c-4dab-ac2d-eee98d6153ee)

메뉴판 만들기2 파일 : 이전의 예제에서 좀 더 메뉴의 종류와 수를 발전시킨 예제. 카테고리를 고른 후 메뉴를 고르도록 함.

![image](https://github.com/user-attachments/assets/687b4b5e-b389-4b2b-ac8f-cafe8cf3c180)
![image](https://github.com/user-attachments/assets/76ccf152-8bfc-4519-be91-fbe32ed731f3)

주사위 눈금 파일 : 랜덤 난수(주사위)를 굴려서 나오는 결과를 보여줌. 1회 실행시 10회차까지 나열함.

![image](https://github.com/user-attachments/assets/7ca3e712-e30c-4e93-a30b-716aec0bc321)


난수 생성: rand() 함수를 사용하여 특정 범위 내 난수를 생성합니다.

예: rand() % 6 + 1 → 1부터 6 사이의 난수 생성 (주사위 눈금).

중복 없는 난수 생성: 중복을 제거한 난수를 생성하기 위한 방법도 다룹니다.

45까지 확률 파일 : 45까지 랜덤하게 나오는 확률을 구현하는 예제.

![image](https://github.com/user-attachments/assets/4058089c-6deb-4d7d-af2f-7ec46e89ba8e)

45까지 미중복 파일 : 45까지 중복하지 않게 랜덤 확률을 구현하는 예제.

![image](https://github.com/user-attachments/assets/6140437c-1e3b-49eb-bfb1-eba0510dc2b2)

45까지 미중복 정렬 파일 : 45까지 중복하지않게 랜덤한 확률을 구현 후 정렬하는 예제.
그러나 정렬이 완전하지는 않으므로 보완 필요

![image](https://github.com/user-attachments/assets/5a4e3c9a-d870-4824-b007-23af5c7a686b)

가변 인수 함수: 인수의 개수가 고정되지 않은 함수 예시로 printf()와 scanf()가 있습니다. 

이를 구현하려면 stdarg.h 헤더의 va_list, va_start, va_arg, va_end를 사용합니다.

예제 코드: sum(int count, ...) 함수는 가변 인수를 받아 합계를 계산합니다.

가변 인수 파일 : 입력과 출력의 개수가 고정되어 있지 않고 변할수 있는 인수 구현에 대한 예제.

![image](https://github.com/user-attachments/assets/5198fff9-66b8-4776-a3f4-fcfac2c7aaf2)






