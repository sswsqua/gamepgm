예제 업그레이드하기 발표자료

하나 더 업그레이드 한 자료도 있음.

업그레이드한 게임 ㅡ 말타며 활쏘기

1. 게임 소개와 모드 선택

![image](https://github.com/user-attachments/assets/db86be3c-9808-49be-87dd-7f8a61389ec2)


   ![image](https://github.com/user-attachments/assets/f1c02d5e-49e6-4c9d-9acf-d7a65c8b6bc9)

게임이 시작되면 intro_game() 함수가 실행되어 게임 소개가 출력됩니다.

사용자는 select_mode() 함수에서 5가지 모드 중 하나를 선택할 수 있습니다:

![image](https://github.com/user-attachments/assets/3d43666c-617d-48ae-b0ea-3b0ec94644b1)


제한시간 게임 (1번 모드): 지정된 시간 동안 타겟 문자를 맞추는 게임.

횟수제한 게임 (2번 모드): 정해진 횟수 동안 타겟을 맞추는 게임.

상점 (3번 모드): 아이템을 구매하여 점수나 경험치를 얻는 모드.

스킨 변경 (4번 모드): 타겟 문자의 스킨을 변경하는 모드.

게임 종료 (5번 모드): 게임을 종료하는 옵션.

2. 게임 진행 
각 모드에 따라 다른 방식으로 게임이 진행됩니다.

![image](https://github.com/user-attachments/assets/31ac5e1b-ad27-4045-bef3-a1f2edd4c0c2)


예를 들어, 시간 제한 모드에서는 타겟 문자가 무작위 위치에 나타나고, 사용자는 문자를 맞추는 것이 목표입니다.

제한 횟수 모드는 사용자가 정해진 횟수 동안 타겟을 맞추는 방식입니다.

3. 점수와 경험치

![image](https://github.com/user-attachments/assets/33cc0c76-29d4-4726-b6d2-a310a5c1fbaf)


게임에서 점수를 얻고, 경험치를 쌓을 수 있습니다. 경험치가 일정량 이상 쌓이면 레벨업을 하며, 레벨에 따라 게임이 점점 어려워질 수 있습니다.

![image](https://github.com/user-attachments/assets/51028775-ef5d-43df-b3eb-125b22291ec7)


상점에서는 점수를 이용해 아이템을 구매하고, 레벨을 올릴 수 있습니다. 상점에서 구매할 수 있는 아이템은 점수와 경험치를 증가시키는 것들입니다.

4. 스킨 변경

![image](https://github.com/user-attachments/assets/41d42aea-ed0b-40e5-80a1-c0abd6c89ba1)


 타겟 문자의 스킨을 A 또는 H로 바꿀 수 있습니다. 이는 게임의 외형을 바꾸는 요소입니다.

5. 기타 기능

warning_screen()은 일정 횟수 이상 경고 메시지를 보여주는 기능입니다.

show_final_score() 함수는 게임 종료 후 점수와 레벨을 출력합니다.

draw_rectangle()는 화면에 사각형을 그리는 함수입니다.

display_current_time()은 현재 시간을 표시합니다.

6. 기타 세부 사항
   
gotoxy() 함수는 콘솔에서 커서를 지정된 위치로 이동시키는 함수입니다.

게임은 getch() 함수로 사용자의 키 입력을 처리하고, 게임을 진행하며, 이를 통해 타겟을 맞추는 동작을 합니다.



7. 추가적으로 하나 더 업그레이드하기 진행.

업적을 추가하였습니다.

int achievement_score = 0;  // 업적 점수

int achievement_unlocked = 0;  // 업적 달성 여부

if (mode == 6) {  // 업적 열람실

   system("cls");
    
   printf("업적 열람실\n");

   printf("업적 점수: %d\n", achievement_score);
   
if (achievement_unlocked) {

   printf("100점 업적을 달성했습니다!\n");
   
} else {

   printf("아직 업적을 달성하지 못했습니다.\n");
}



