#include "Project A.h"

int main(void)
{
    Weapon weapon = { 0, 0, MAX_PROBABILITY, 0, 0 }; // EASY 구조체 초기화
    Weapon_HARD weapon_HARD = { 0, 0, MAX_PROBABILITY_HARD, 0 }; // HARD 구조체 초기화

    srand((int)time(NULL));  // 랜덤 시드값 설정

    int difficulty;
    printf("난이도 선택\n\n1. 이지 모드 | 2. 하드 모드\n");
    loadPlayerInfo(&total_money, &weapon.level);
    loadPlayerInfo_HARD(&total_money_HARD, &weapon_HARD.level_HARD);
    printf("[1] 이지 모드에 저장되어 있는 현재 정보 : 보유자금 = %d원 | 무기레벨 = + %d\n", total_money, weapon.level);
    printf("[2] 하드 모드에 저장되어 있는 현재 정보 : 보유자금 = %d원 | 무기레벨 = + %d\n\n", total_money_HARD, weapon_HARD.level_HARD);
    printf("입력 : ");
    scanf("%d", &difficulty);

    // 버퍼 비우기
    int bufferDel_M;
    while ((bufferDel_M = getchar()) != '\n' && bufferDel_M != EOF);

    if (difficulty != EASY && difficulty != HARD)
    {
        printf("잘못된 선택입니다. 기본적으로 이지 모드로 시작합니다.\n");
        difficulty = EASY;

        weapon.retTime = time(0) + WAIT_TIME;
        while (time(0) < weapon.retTime);
    }

    // EASY MODE
#pragma region EASY MODE
    if (difficulty == EASY)
    {
        printdifficultyScreen();
        weapon.retTime = time(0) + WAIT_TIME;
        while (time(0) < weapon.retTime);

        total_money = Initial_Money; // 게임 시작 시 보유 자금 초기화

        // 게임 시작 전 화면 초기화 및 플레이어 정보 불러오기
        system("@cls||clear");
        loadPlayerInfo(&total_money, &weapon.level);

        // 플레이어 정보를 불러왔을때 무기 레벨이 0보다 클 경우 무기 자동 판매
        AutoInfosellScreen(weapon, weapon.level, calculateSellPrice(weapon.level), total_money, weapon.retTime);

        // 플레이어 정보를 불러왔을때 무기 레벨이 0보다 클 경우 무기 자동 판매 (보유자금에 무기 판매 가격 추가)
        int sellPrice = calculateSellPrice(weapon.level);
        total_money += sellPrice;

        // 플레이어 정보를 불러왔을때 무기 레벨이 0보다 클 경우 무기 자동 판매 (무기 레벨 초기화)
        weapon.level = 0;

        // 게임 조건 설정 : 보유 자금이 20만원 초과 or 보유 자금이 0원 이하
        while (total_money < 200000 && total_money >= 0)
        {
            int upgradeCost = calculateUpgradeCost(weapon.level);
            int sellPrice = calculateSellPrice(weapon.level);

            // 화면 정리
            system("@cls||clear");

            // 타이틀 화면 출력
            printtitleScrren();

            // 현재 상태와 강화 도전 질의 출력
            weapon.success_rate = calculateProbability(weapon.level);
            printf("보유자금 : %d원\n", total_money);
            printf("무기레벨 : + %d\n", weapon.level);
            printf("성공확률 : %.2f%%\n\n", weapon.success_rate);
            printf("번호를 선택해 주세요!\n");
            printf("1.강화   2.무기판매   3.종료   4. 저장\n\n");
            // 선택 번호에 따른 설명 출력
            printExplanation(1, upgradeCost, 0, 0, 0);  // upgradeCost만 전달, 나머지는 0으로 표시
            printExplanation(2, 0, sellPrice, 0, 0);    // sellPrice만 전달, 나머지는 0으로 표시
            printExplanation(3, 0, 0, total_money, weapon.level);  // total_money, weapon.level만 전달, 나머지는 0으로 표시
            printExplanation(4, 0, 0, total_money, weapon.level);  // total_money, weapon.level만 전달, 나머지는 0으로 표시
            printf("\n입력 : ");
            scanf("%d", &weapon.isTry);

            // 버퍼 비우기
            int bufferDel;
            while ((bufferDel = getchar()) != '\n' && bufferDel != EOF);

            // 미리 강화 비용을 계산하여 돈이 부족하면 강화 시도하지 않음
            if (weapon.isTry == 1 && upgradeCost > total_money)
            {
                printf("돈이 부족하여 강화에 도전할 수 없습니다.\n");
                printf("강화 단계는 그대로 유지됩니다.\n");

                weapon.retTime = time(0) + WAIT_TIME_2;
                while (time(0) < weapon.retTime);

                continue;
            }

            switch (weapon.isTry)
            {
            case 1:        // 강화 도전
                // 랜덤 값 추출
                weapon.randNum = rand() % 100;

                printf("\n강화중..\n");

#pragma region 디버깅 코드 출력
                /*printf("[디버깅] 랜덤 값 : %d | 성공 확률 : %.2f\n", weapon.randNum, weapon.success_rate);
                if (weapon.randNum < weapon.success_rate)
                {
                    printf("[디버깅] 랜덤 값(%d) < 성공 확률(%.2f) 이므로 강화 성공입니다.\n", weapon.randNum, weapon.success_rate);
                }
                else if (weapon.randNum >= weapon.success_rate)
                {
                    printf("[디버깅] 랜덤 값(%d) => 성공 확률(%.2f) 이므로 강화 실패입니다.\n", weapon.randNum, weapon.success_rate);
                }*/
#pragma endregion

                // 강화 비용 계산
                printf("곧 업데이트 될 보유자금은 %d원 입니다.\n\n", total_money - upgradeCost);

                // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                const float INTERVAL = 0.1;
                float elapsedTime = 0.0;

                while (elapsedTime < WAIT_TIME)
                {
                    printProgressBar(elapsedTime / WAIT_TIME * 100);
                    Sleep(INTERVAL * 1000);
                    elapsedTime += INTERVAL;
                }
                printProgressBar(100.0);
                printf("\n");

                // 돈이 충분하면 강화 시도
                total_money -= upgradeCost;

                // 추출한 랜덤 값이 성공확률 보다 작으면 성공
                if (weapon.randNum < weapon.success_rate)
                {
                    // 성공화면 출력
                    printSuccessScreen(weapon.level);

                    // 강화에 성공 했을 시, 레벨을 하나 증가 시키고, 성공확률을 보정
                    weapon.level++;
                }
                else {
                    // 실패화면 출력
                    printf("이런..! 손이 미끌어졌네.\n");
                    printFailedScreen(weapon.level);

                    int failureCost = calculateFailureCost(weapon.level);

                    if (total_money < failureCost)
                    {
                        printf("보유 자금이 부족합니다. + %d 무기를 잃었습니다.\n", weapon.level);
                        weapon.level = 0;
                    }
                    else
                    {
                        // 사용자에게 강화 유지 또는 초기화 선택
                        printf("\n1. 강화 유지   2. 초기화\n");
                        printf("강화 유지 비용은 %d원 입니다.\n", failureCost);
                        printf("입력 : ");
                        scanf("%d", &weapon.isTry);

                        if (weapon.isTry == 1)
                        {
                            // 강화 유지 선택 시 보유 자금의 50%를 차감하고 강화 유지.
                            printf("\n%d원을 차감하고 강화 레벨을 유지합니다.\n", failureCost);
                            total_money -= failureCost;
                            printf("강화 유지 후 업데이트 될 보유자금은 %d원 입니다.\n\n", total_money);
                            break;
                        }
                        if (weapon.isTry == 2)
                        {
                            printf("+ %d 무기를 잃었습니다.\n", weapon.level);
                            weapon.level = 0;
                            break;
                        }
                    }
                }

                if (weapon.level == 12)
                {
                    while (1)
                    {
                        // 버퍼 비우기
                        int bufferDel;
                        while ((bufferDel = getchar()) != '\n' && bufferDel != EOF);

                        int choice_lv12;
                        system("@cls||clear");
                        printf("+ 12 레벨 달성을 축하합니다!\n\n");
                        printf("미니게임 or 무기판매를 선택해 주세요.\n");
                        printf("미니게임을 클리어할 시 게임이 즉시 클리어 됩니다.\n\n");
                        printf("1. 미니게임   2. 무기 판매\n\n");
                        printf("입력 : ");
                        scanf("%d", &choice_lv12);

                        switch (choice_lv12)
                        {
                        case 1:
                            printf("미니게임을 선택하셨습니다!\n");
                            system("@cls||clear");
                            printf("\n+ 12 레벨 달성! 미니게임을 시작합니다.\n");

                            weapon.retTime = time(0) + WAIT_TIME_2;
                            while (time(0) < weapon.retTime);

                            int miniGameResult = MiniGame(weapon, weapon.level, calculateSellPrice(weapon.level), total_money);
                            if (miniGameResult == 1)
                            {
                                return 0;
                            }
                            else
                            {
                                int sellPrice = calculateSellPrice(weapon.level);
                                total_money += sellPrice;
                                weapon.level = 0;
                            }
                            break;
                        case 2:
                            sellPrice = calculateSellPrice(weapon.level);
                            printLevelTwelve(weapon.level, sellPrice);
                            total_money += sellPrice;
                            weapon.level = 0;
                            break;
                        default:
                            printf("\n잘못된 번호를 입력하셨습니다. 다시 시도해 주세요.\n");
                            printf("\n계속하려면 Enter키를 누르십시오.\n");
                            while (_getch() != '\r');
                            continue;
                        }
                        break;
                    }
                }
                break;

            case 2:         // 무기 판매
                printf("\n무기 판매중..\n");

                // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                const float INTERVAL_2 = 0.1;
                float elapsedTime_2 = 0.0;

                while (elapsedTime_2 < WAIT_TIME)
                {
                    printProgressBar(elapsedTime_2 / WAIT_TIME * 100);
                    Sleep(INTERVAL_2 * 1000);
                    elapsedTime_2 += INTERVAL_2;
                }
                printProgressBar(100.0);
                printf("\n\n");

                // 레벨에 맞는 무기 판매 가격 계산
                int sellPrice = calculateSellPrice(weapon.level);
                printf("무기 판매로 %d원을 획득하였습니다.\n", sellPrice);
                printf("곧 업데이트 될 보유자금은 %d원 입니다.\n\n", total_money + sellPrice);

                // 보유자금에 무기 판매 가격 추가
                total_money += sellPrice;

                // 무기 레벨 초기화
                weapon.level = 0;
                break;

            case 3:         // 종료
                // 종료를 할 경우 프로그램 종료
                printf("보유자금 : %d원 / 무기레벨 : + %d 는 자동 저장됩니다.\n", total_money, weapon.level);

                // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                const float INTERVAL_3 = 0.1;
                float elapsedTime_3 = 0.0;

                while (elapsedTime_3 < WAIT_TIME)
                {
                    printProgressBar(elapsedTime_3 / WAIT_TIME * 100);
                    Sleep(INTERVAL_3 * 1000);
                    elapsedTime_3 += INTERVAL_3;
                }
                printProgressBar(100.0);
                printf("\n\n");
                printf("Game Over!\n");

                weapon.retTime = time(0) + WAIT_TIME;
                while (time(0) < weapon.retTime);


                savePlayerInfo(total_money, weapon.level);
                return -1;

            case 4:         // 저장
                // 저장을 할 경우 보유자금 & 무기 레벨 저장
                printf("\n정보 저장중..\n");

                // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                const float INTERVAL_4 = 0.1;
                float elapsedTime_4 = 0.0;

                while (elapsedTime_4 < WAIT_TIME)
                {
                    printProgressBar(elapsedTime_4 / WAIT_TIME * 100);
                    Sleep(INTERVAL_4 * 1000);
                    elapsedTime_4 += INTERVAL_4;
                }
                printProgressBar(100.0);
                printf("\n\n");

                // 플레이어 정보 저장
                savePlayerInfo(total_money, weapon.level);
                printf("보유자금 : %d원 / 무기레벨 : + %d 이 저장되었습니다.\n", total_money, weapon.level);
                printf("게임을 계속 진행합니다.\n\n");
                break;
            default:
                printf("잘못된 번호를 입력하셨습니다. 다시 시도해 주세요.\n");
                break;
            }

            // 턴마다 진행 대기
            printf("\n계속하려면 Enter키를 누르십시오.\n");
            while (_getch() != '\r');

            // 보유자금이 20만원 이상일 경우
            if (total_money >= 200000)
            {
                printGameClear();
            }

            // 보유자금이 0원 미만일 경우
            if (total_money <= 0)
            {
                // 보유자금이 0원인데 무기 레벨까지 0일 경우 게임 실패
                if (weapon.level == 0)
                {
                    printGameFailed();
                }
                else
                {
                    // 화면 정리
                    system("@cls||clear");

                    printf("보유 자금 0원으로 현재 보유중인 + %d 무기는 자동 판매됩니다.\n", weapon.level);
                    printf("\n무기 판매중..\n");

                    // 레벨에 맞는 무기 판매 가격 계산
                    int sellPrice = calculateSellPrice(weapon.level);
                    printf("+ %d 무기 판매로 %d원을 획득합니다.\n", weapon.level, sellPrice);

                    // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                    const float INTERVAL_5 = 0.1;
                    float elapsedTime_5 = 0.0;

                    while (elapsedTime_5 < WAIT_TIME_2)
                    {
                        printProgressBar(elapsedTime_5 / WAIT_TIME_2 * 100);
                        Sleep(INTERVAL_5 * 1000);
                        elapsedTime_5 += INTERVAL_5;
                    }
                    printProgressBar(100.0);
                    printf("\n\n");

                    // 보유자금에 무기 판매 가격 추가
                    total_money += sellPrice;

                    // 무기 레벨 초기화
                    weapon.level = 0;
                }
            }
        }
    }
#pragma endregion

    // HARD MODE
#pragma region HARD MODE
    if (difficulty == HARD)
    {
        printdifficultyScreen_HARD();
        weapon.retTime = time(0) + WAIT_TIME;
        while (time(0) < weapon.retTime);

        total_money_HARD = Initial_Money_HARD; // 게임 시작 시 보유 자금 초기화

        // 게임 시작 전 화면 초기화 및 플레이어 정보 불러오기
        system("@cls||clear");
        loadPlayerInfo_HARD(&total_money_HARD, &weapon_HARD.level_HARD);

        // 플레이어 정보를 불러왔을때 무기 레벨이 0보다 클 경우 무기 자동 판매
        AutoInfosellScreen_HARD(weapon, weapon_HARD, weapon_HARD.level_HARD, calculateSellPrice_HARD(weapon_HARD.level_HARD), total_money_HARD, weapon.retTime);

        // 플레이어 정보를 불러왔을때 무기 레벨이 0보다 클 경우 무기 자동 판매 (보유자금에 무기 판매 가격 추가)
        int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
        total_money_HARD += sellPrice_HARD;

        // 무기 레벨 초기화
        weapon_HARD.level_HARD = 0;

        // 게임 조건 설정 : 보유 자금이 20만원 초과 or 보유 자금이 0원 이하
        while (total_money_HARD < 200000 && total_money_HARD >= 0)
        {
            int upgradeCost_HARD = calculateUpgradeCost_HARD(weapon_HARD.level_HARD);
            int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);

            // 화면 정리
            system("@cls||clear");

            // 타이틀 화면 출력
            printtitleScrren_HARD();

            // 현재 상태와 강화 도전 질의 출력
            weapon_HARD.success_rate_HARD = calculateProbability_HARD(weapon_HARD.level_HARD);
            printf("보유자금 : %d원\n", total_money_HARD);
            printf("무기레벨 : + %d\n", weapon_HARD.level_HARD);
            printf("성공확률 : %.2f%%\n\n", weapon_HARD.success_rate_HARD);
            printf("번호를 선택해 주세요!\n");
            printf("1.강화   2.무기판매   3.종료   4. 저장\n\n");
            // 선택 번호에 따른 설명 출력
            printExplanation(1, upgradeCost_HARD, 0, 0, 0);  // upgradeCost만 전달, 나머지는 0으로 표시
            printExplanation(2, 0, sellPrice_HARD, 0, 0);    // sellPrice만 전달, 나머지는 0으로 표시
            printExplanation(3, 0, 0, total_money_HARD, weapon_HARD.level_HARD);  // total_money, weapon.level만 전달, 나머지는 0으로 표시
            printExplanation(4, 0, 0, total_money_HARD, weapon_HARD.level_HARD);  // total_money, weapon.level만 전달, 나머지는 0으로 표시
            printf("\n입력 : ");
            scanf("%d", &weapon_HARD.isTry_HARD);

            // 버퍼 비우기
            int bufferDel_HARD;
            while ((bufferDel_HARD = getchar()) != '\n' && bufferDel_HARD != EOF);

            // 미리 강화 비용을 계산하여 돈이 부족하면 강화 시도하지 않음
            if (weapon_HARD.isTry_HARD == 1 && upgradeCost_HARD > total_money_HARD)
            {
                printf("돈이 부족하여 강화에 도전할 수 없습니다.\n");
                printf("강화 단계는 그대로 유지됩니다.\n");

                weapon.retTime = time(0) + WAIT_TIME_2;
                while (time(0) < weapon.retTime);

                continue;
            }

            switch (weapon_HARD.isTry_HARD)
            {
            case 1:        // 강화 도전
                // 랜덤 값 추출
                weapon_HARD.randNum_HARD = rand() % 100;

                printf("\n강화중..\n");

                // 디버깅 코드 출력
                /*printf("[디버깅] 랜덤 값 : %d | 성공 확률 : %.2f\n", weapon_HARD.randNum_HARD, weapon_HARD.success_rate_HARD);
                if (weapon_HARD.randNum_HARD < weapon_HARD.success_rate_HARD)
                {
                    printf("[디버깅] 랜덤 값(%d) < 성공 확률(%.2f) 이므로 강화 성공입니다.\n", weapon_HARD.randNum_HARD, weapon_HARD.success_rate_HARD);
                }
                else if (weapon_HARD.randNum_HARD >= weapon_HARD.success_rate_HARD)
                {
                    printf("[디버깅] 랜덤 값(%d) => 성공 확률(%.2f) 이므로 강화 실패입니다.\n", weapon_HARD.randNum_HARD, weapon_HARD.success_rate_HARD);
                }*/

                // 강화 비용 계산
                printf("곧 업데이트 될 보유자금은 %d원 입니다.\n\n", total_money_HARD - upgradeCost_HARD);

                // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                const float INTERVAL_HARD = 0.1;
                float elapsedTime_HARD = 0.0;

                while (elapsedTime_HARD < WAIT_TIME)
                {
                    printProgressBar_HARD(elapsedTime_HARD / WAIT_TIME * 100);
                    Sleep(INTERVAL_HARD * 1000);
                    elapsedTime_HARD += INTERVAL_HARD;
                }
                printProgressBar_HARD(100.0);
                printf("\n\n");

                // 돈이 충분하면 강화 시도
                total_money_HARD -= upgradeCost_HARD;

                // 추출한 랜덤 값이 성공확률 보다 작으면 성공
                if (weapon_HARD.randNum_HARD < weapon_HARD.success_rate_HARD)
                {
                    // 성공화면 출력
                    printSuccessScreen_HARD(weapon_HARD.level_HARD);

                    // 강화에 성공 했을 시, 레벨을 하나 증가 시키고, 성공확률을 보정
                    weapon_HARD.level_HARD++;
                }
                else
                {
                    // 실패화면 출력
                    printf("이런..! 손이 미끌어졌네.\n");
                    printFailedScreen_HARD(weapon_HARD.level_HARD);

                    int failureCost_HARD = calculateFailureCost_HARD(weapon_HARD.level_HARD);

                    if (total_money_HARD < failureCost_HARD)
                    {
                        printf("보유 자금이 부족합니다. + %d 무기를 잃었습니다.\n", weapon_HARD.level_HARD);
                        weapon_HARD.level_HARD = 0;
                    }
                    else
                    {
                        // 사용자에게 강화 유지 또는 초기화 선택
                        printf("\n1. 강화 유지   2. 초기화\n");
                        printf("강화 유지 비용은 %d원 입니다.\n", failureCost_HARD);
                        printf("입력 : ");
                        scanf("%d", &weapon_HARD.isTry_HARD);

                        if (weapon_HARD.isTry_HARD == 1)
                        {
                            // 강화 유지 선택 시 보유 자금의 50%를 차감하고 강화 유지.
                            printf("\n%d원을 차감하고 강화 레벨을 유지합니다.\n", failureCost_HARD);
                            total_money_HARD -= failureCost_HARD;
                            printf("강화 유지 후 업데이트 될 보유자금은 %d원 입니다.\n\n", total_money_HARD);
                            break;
                        }
                        if (weapon_HARD.isTry_HARD == 2)
                        {
                            printf("+ %d 무기를 잃었습니다.\n", weapon_HARD.level_HARD);
                            weapon_HARD.level_HARD = 0;
                            break;
                        }
                    }
                }

                if (weapon_HARD.level_HARD == 12)
                {
                    while (1)
                    {
                        // 버퍼 비우기
                        int bufferDel_HARD;
                        while ((bufferDel_HARD = getchar()) != '\n' && bufferDel_HARD != EOF);

                        int choice_lv12_HARD;
                        system("@cls||clear");
                        printf("+ 12 레벨 달성을 축하합니다!\n\n");
                        printf("미니게임 or 무기판매를 선택해 주세요.\n");
                        printf("미니게임을 클리어할 시 게임이 즉시 클리어 됩니다.\n\n");
                        printf("1. 미니게임   2. 무기 판매\n\n");
                        printf("입력 : ");
                        scanf("%d", &choice_lv12_HARD);

                        switch (choice_lv12_HARD)
                        {
                        case 1:
                            printf("미니게임을 선택하셨습니다!\n");
                            system("@cls||clear");
                            printf("\n+ 12 레벨 달성! 미니게임을 시작합니다.\n");

                            weapon.retTime = time(0) + WAIT_TIME_2;
                            while (time(0) < weapon.retTime);

                            int miniGameResult_HARD = MiniGame_HARD(weapon_HARD, weapon_HARD.level_HARD, calculateSellPrice_HARD(weapon_HARD.level_HARD), total_money_HARD);
                            if (miniGameResult_HARD == 1)
                            {
                                return 0;
                            }
                            else
                            {
                                int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
                                total_money_HARD += sellPrice_HARD;
                                weapon_HARD.level_HARD = 0;
                            }
                            break;
                        case 2:
                            sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
                            printLevelTwelve_HARD(weapon_HARD.level_HARD, sellPrice_HARD);
                            total_money_HARD += sellPrice_HARD;
                            weapon_HARD.level_HARD = 0;
                            break;
                        default:
                            printf("\n잘못된 번호를 입력하셨습니다. 다시 시도해 주세요.\n");
                            printf("\n계속하려면 Enter키를 누르십시오.\n");
                            while (_getch() != '\r');
                            continue;
                        }
                        break;
                    }
                }
                break;

            case 2:         // 무기 판매
                printf("\n무기 판매중..\n");

                // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                const float INTERVAL_HARD_2 = 0.1;
                float elapsedTime_HARD_2 = 0.0;

                while (elapsedTime_HARD_2 < WAIT_TIME)
                {
                    printProgressBar_HARD(elapsedTime_HARD_2 / WAIT_TIME * 100);
                    Sleep(INTERVAL_HARD_2 * 1000);
                    elapsedTime_HARD_2 += INTERVAL_HARD_2;
                }
                printProgressBar_HARD(100.0);
                printf("\n\n");

                // 레벨에 맞는 무기 판매 가격 계산
                int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
                printf("무기 판매로 %d원을 획득하였습니다.\n", sellPrice_HARD);
                printf("곧 업데이트 될 보유자금은 %d원 입니다.\n\n", total_money_HARD + sellPrice_HARD);

                // 보유자금에 무기 판매 가격 추가
                total_money_HARD += sellPrice_HARD;

                // 무기 레벨 초기화
                weapon_HARD.level_HARD = 0;
                break;

            case 3:         // 종료
                // 종료를 할 경우 프로그램 종료
                printf("보유자금 : %d원 / 무기레벨 : + %d 는 자동 저장됩니다.\n", total_money_HARD, weapon_HARD.level_HARD);

                // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                const float INTERVAL_HARD_3 = 0.1;
                float elapsedTime_HARD_3 = 0.0;

                while (elapsedTime_HARD_3 < WAIT_TIME)
                {
                    printProgressBar_HARD(elapsedTime_HARD_3 / WAIT_TIME * 100);
                    Sleep(INTERVAL_HARD_3 * 1000);
                    elapsedTime_HARD_3 += INTERVAL_HARD_3;
                }
                printProgressBar_HARD(100.0);
                printf("\n\n");
                printf("Game Over!\n");

                weapon.retTime = time(0) + WAIT_TIME;
                while (time(0) < weapon.retTime);

                savePlayerInfo_HARD(total_money_HARD, weapon_HARD.level_HARD);
                return -1;

            case 4:         // 저장
                // 저장을 할 경우 보유자금 & 무기 레벨 저장
                printf("\n정보 저장중..\n");

                // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                const float INTERVAL_HARD_4 = 0.1;
                float elapsedTime_HARD_4 = 0.0;

                while (elapsedTime_HARD_4 < WAIT_TIME)
                {
                    printProgressBar_HARD(elapsedTime_HARD_4 / WAIT_TIME * 100);
                    Sleep(INTERVAL_HARD_4 * 1000);
                    elapsedTime_HARD_4 += INTERVAL_HARD_4;
                }
                printProgressBar_HARD(100.0);
                printf("\n\n");

                // 플레이어 정보 저장
                savePlayerInfo_HARD(total_money_HARD, weapon_HARD.level_HARD);
                printf("보유자금 : %d원 / 무기레벨 : + %d 이 저장되었습니다.\n", total_money_HARD, weapon_HARD.level_HARD);
                printf("게임을 계속 진행합니다.\n\n");
                break;
            default:
                printf("잘못된 번호를 입력하셨습니다. 다시 시도해 주세요.\n");
                break;
            }

            // 턴마다 진행 대기
            printf("\n계속하려면 Enter키를 누르십시오.\n");
            while (_getch() != '\r');

            // 보유자금이 20만원 이상일 경우
            if (total_money >= 200000)
            {
                printGameClear_HARD();
            }

            // 보유자금이 0원 미만일 경우
            if (total_money_HARD <= 0)
            {
                // 보유자금이 0원인데 무기 레벨까지 0일 경우 게임 실패
                if (weapon_HARD.level_HARD == 0)
                {
                    printGameFailed_HARD();
                }
                else
                {
                    printf("보유 자금 0원으로 현재 보유중인 + %d 무기는 자동 판매됩니다.\n", weapon_HARD.level_HARD);
                    printf("\n무기 판매중..\n");

                    // 레벨에 맞는 무기 판매 가격 계산
                    int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
                    printf("+ %d 무기 판매로 %d원을 획득합니다.\n", weapon_HARD.level_HARD, sellPrice_HARD);

                    // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
                    const float INTERVAL_HARD_5 = 0.1;
                    float elapsedTime_HARD_5 = 0.0;

                    while (elapsedTime_HARD_5 < WAIT_TIME_2)
                    {
                        printProgressBar_HARD(elapsedTime_HARD_5 / WAIT_TIME_2 * 100);
                        Sleep(INTERVAL_HARD_5 * 1000);
                        elapsedTime_HARD_5 += INTERVAL_HARD_5;
                    }
                    printProgressBar_HARD(100.0);
                    printf("\n\n");

                    // 보유자금에 무기 판매 가격 추가
                    total_money_HARD += sellPrice_HARD;

                    // 무기 레벨 초기화
                    weapon_HARD.level_HARD = 0;
                }
            }
        }
    }
#pragma endregion

    return 0;
}