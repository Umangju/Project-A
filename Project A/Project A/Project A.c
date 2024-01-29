#include "Project A.h"

int main(void)
{
    Weapon weapon = { 0, 0, MAX_PROBABILITY, 0, 0 }; // EASY ����ü �ʱ�ȭ
    Weapon_HARD weapon_HARD = { 0, 0, MAX_PROBABILITY_HARD, 0 }; // HARD ����ü �ʱ�ȭ

    srand((int)time(NULL));  // ���� �õ尪 ����

    int difficulty;
    printf("���̵� ����\n\n1. ���� ��� | 2. �ϵ� ���\n");
    loadPlayerInfo(&total_money, &weapon.level);
    loadPlayerInfo_HARD(&total_money_HARD, &weapon_HARD.level_HARD);
    printf("[1] ���� ��忡 ����Ǿ� �ִ� ���� ���� : �����ڱ� = %d�� | ���ⷹ�� = + %d\n", total_money, weapon.level);
    printf("[2] �ϵ� ��忡 ����Ǿ� �ִ� ���� ���� : �����ڱ� = %d�� | ���ⷹ�� = + %d\n\n", total_money_HARD, weapon_HARD.level_HARD);
    printf("�Է� : ");
    scanf("%d", &difficulty);

    // ���� ����
    int bufferDel_M;
    while ((bufferDel_M = getchar()) != '\n' && bufferDel_M != EOF);

    if (difficulty != EASY && difficulty != HARD)
    {
        printf("�߸��� �����Դϴ�. �⺻������ ���� ���� �����մϴ�.\n");
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

        total_money = Initial_Money; // ���� ���� �� ���� �ڱ� �ʱ�ȭ

        // ���� ���� �� ȭ�� �ʱ�ȭ �� �÷��̾� ���� �ҷ�����
        system("@cls||clear");
        loadPlayerInfo(&total_money, &weapon.level);

        // �÷��̾� ������ �ҷ������� ���� ������ 0���� Ŭ ��� ���� �ڵ� �Ǹ�
        AutoInfosellScreen(weapon, weapon.level, calculateSellPrice(weapon.level), total_money, weapon.retTime);

        // �÷��̾� ������ �ҷ������� ���� ������ 0���� Ŭ ��� ���� �ڵ� �Ǹ� (�����ڱݿ� ���� �Ǹ� ���� �߰�)
        int sellPrice = calculateSellPrice(weapon.level);
        total_money += sellPrice;

        // �÷��̾� ������ �ҷ������� ���� ������ 0���� Ŭ ��� ���� �ڵ� �Ǹ� (���� ���� �ʱ�ȭ)
        weapon.level = 0;

        // ���� ���� ���� : ���� �ڱ��� 20���� �ʰ� or ���� �ڱ��� 0�� ����
        while (total_money < 200000 && total_money >= 0)
        {
            int upgradeCost = calculateUpgradeCost(weapon.level);
            int sellPrice = calculateSellPrice(weapon.level);

            // ȭ�� ����
            system("@cls||clear");

            // Ÿ��Ʋ ȭ�� ���
            printtitleScrren();

            // ���� ���¿� ��ȭ ���� ���� ���
            weapon.success_rate = calculateProbability(weapon.level);
            printf("�����ڱ� : %d��\n", total_money);
            printf("���ⷹ�� : + %d\n", weapon.level);
            printf("����Ȯ�� : %.2f%%\n\n", weapon.success_rate);
            printf("��ȣ�� ������ �ּ���!\n");
            printf("1.��ȭ   2.�����Ǹ�   3.����   4. ����\n\n");
            // ���� ��ȣ�� ���� ���� ���
            printExplanation(1, upgradeCost, 0, 0, 0);  // upgradeCost�� ����, �������� 0���� ǥ��
            printExplanation(2, 0, sellPrice, 0, 0);    // sellPrice�� ����, �������� 0���� ǥ��
            printExplanation(3, 0, 0, total_money, weapon.level);  // total_money, weapon.level�� ����, �������� 0���� ǥ��
            printExplanation(4, 0, 0, total_money, weapon.level);  // total_money, weapon.level�� ����, �������� 0���� ǥ��
            printf("\n�Է� : ");
            scanf("%d", &weapon.isTry);

            // ���� ����
            int bufferDel;
            while ((bufferDel = getchar()) != '\n' && bufferDel != EOF);

            // �̸� ��ȭ ����� ����Ͽ� ���� �����ϸ� ��ȭ �õ����� ����
            if (weapon.isTry == 1 && upgradeCost > total_money)
            {
                printf("���� �����Ͽ� ��ȭ�� ������ �� �����ϴ�.\n");
                printf("��ȭ �ܰ�� �״�� �����˴ϴ�.\n");

                weapon.retTime = time(0) + WAIT_TIME_2;
                while (time(0) < weapon.retTime);

                continue;
            }

            switch (weapon.isTry)
            {
            case 1:        // ��ȭ ����
                // ���� �� ����
                weapon.randNum = rand() % 100;

                printf("\n��ȭ��..\n");

#pragma region ����� �ڵ� ���
                /*printf("[�����] ���� �� : %d | ���� Ȯ�� : %.2f\n", weapon.randNum, weapon.success_rate);
                if (weapon.randNum < weapon.success_rate)
                {
                    printf("[�����] ���� ��(%d) < ���� Ȯ��(%.2f) �̹Ƿ� ��ȭ �����Դϴ�.\n", weapon.randNum, weapon.success_rate);
                }
                else if (weapon.randNum >= weapon.success_rate)
                {
                    printf("[�����] ���� ��(%d) => ���� Ȯ��(%.2f) �̹Ƿ� ��ȭ �����Դϴ�.\n", weapon.randNum, weapon.success_rate);
                }*/
#pragma endregion

                // ��ȭ ��� ���
                printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n\n", total_money - upgradeCost);

                // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

                // ���� ����ϸ� ��ȭ �õ�
                total_money -= upgradeCost;

                // ������ ���� ���� ����Ȯ�� ���� ������ ����
                if (weapon.randNum < weapon.success_rate)
                {
                    // ����ȭ�� ���
                    printSuccessScreen(weapon.level);

                    // ��ȭ�� ���� ���� ��, ������ �ϳ� ���� ��Ű��, ����Ȯ���� ����
                    weapon.level++;
                }
                else {
                    // ����ȭ�� ���
                    printf("�̷�..! ���� �̲�������.\n");
                    printFailedScreen(weapon.level);

                    int failureCost = calculateFailureCost(weapon.level);

                    if (total_money < failureCost)
                    {
                        printf("���� �ڱ��� �����մϴ�. + %d ���⸦ �Ҿ����ϴ�.\n", weapon.level);
                        weapon.level = 0;
                    }
                    else
                    {
                        // ����ڿ��� ��ȭ ���� �Ǵ� �ʱ�ȭ ����
                        printf("\n1. ��ȭ ����   2. �ʱ�ȭ\n");
                        printf("��ȭ ���� ����� %d�� �Դϴ�.\n", failureCost);
                        printf("�Է� : ");
                        scanf("%d", &weapon.isTry);

                        if (weapon.isTry == 1)
                        {
                            // ��ȭ ���� ���� �� ���� �ڱ��� 50%�� �����ϰ� ��ȭ ����.
                            printf("\n%d���� �����ϰ� ��ȭ ������ �����մϴ�.\n", failureCost);
                            total_money -= failureCost;
                            printf("��ȭ ���� �� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n\n", total_money);
                            break;
                        }
                        if (weapon.isTry == 2)
                        {
                            printf("+ %d ���⸦ �Ҿ����ϴ�.\n", weapon.level);
                            weapon.level = 0;
                            break;
                        }
                    }
                }

                if (weapon.level == 12)
                {
                    while (1)
                    {
                        // ���� ����
                        int bufferDel;
                        while ((bufferDel = getchar()) != '\n' && bufferDel != EOF);

                        int choice_lv12;
                        system("@cls||clear");
                        printf("+ 12 ���� �޼��� �����մϴ�!\n\n");
                        printf("�̴ϰ��� or �����ǸŸ� ������ �ּ���.\n");
                        printf("�̴ϰ����� Ŭ������ �� ������ ��� Ŭ���� �˴ϴ�.\n\n");
                        printf("1. �̴ϰ���   2. ���� �Ǹ�\n\n");
                        printf("�Է� : ");
                        scanf("%d", &choice_lv12);

                        switch (choice_lv12)
                        {
                        case 1:
                            printf("�̴ϰ����� �����ϼ̽��ϴ�!\n");
                            system("@cls||clear");
                            printf("\n+ 12 ���� �޼�! �̴ϰ����� �����մϴ�.\n");

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
                            printf("\n�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �õ��� �ּ���.\n");
                            printf("\n����Ϸ��� EnterŰ�� �����ʽÿ�.\n");
                            while (_getch() != '\r');
                            continue;
                        }
                        break;
                    }
                }
                break;

            case 2:         // ���� �Ǹ�
                printf("\n���� �Ǹ���..\n");

                // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

                // ������ �´� ���� �Ǹ� ���� ���
                int sellPrice = calculateSellPrice(weapon.level);
                printf("���� �Ǹŷ� %d���� ȹ���Ͽ����ϴ�.\n", sellPrice);
                printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n\n", total_money + sellPrice);

                // �����ڱݿ� ���� �Ǹ� ���� �߰�
                total_money += sellPrice;

                // ���� ���� �ʱ�ȭ
                weapon.level = 0;
                break;

            case 3:         // ����
                // ���Ḧ �� ��� ���α׷� ����
                printf("�����ڱ� : %d�� / ���ⷹ�� : + %d �� �ڵ� ����˴ϴ�.\n", total_money, weapon.level);

                // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

            case 4:         // ����
                // ������ �� ��� �����ڱ� & ���� ���� ����
                printf("\n���� ������..\n");

                // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

                // �÷��̾� ���� ����
                savePlayerInfo(total_money, weapon.level);
                printf("�����ڱ� : %d�� / ���ⷹ�� : + %d �� ����Ǿ����ϴ�.\n", total_money, weapon.level);
                printf("������ ��� �����մϴ�.\n\n");
                break;
            default:
                printf("�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �õ��� �ּ���.\n");
                break;
            }

            // �ϸ��� ���� ���
            printf("\n����Ϸ��� EnterŰ�� �����ʽÿ�.\n");
            while (_getch() != '\r');

            // �����ڱ��� 20���� �̻��� ���
            if (total_money >= 200000)
            {
                printGameClear();
            }

            // �����ڱ��� 0�� �̸��� ���
            if (total_money <= 0)
            {
                // �����ڱ��� 0���ε� ���� �������� 0�� ��� ���� ����
                if (weapon.level == 0)
                {
                    printGameFailed();
                }
                else
                {
                    // ȭ�� ����
                    system("@cls||clear");

                    printf("���� �ڱ� 0������ ���� �������� + %d ����� �ڵ� �Ǹŵ˴ϴ�.\n", weapon.level);
                    printf("\n���� �Ǹ���..\n");

                    // ������ �´� ���� �Ǹ� ���� ���
                    int sellPrice = calculateSellPrice(weapon.level);
                    printf("+ %d ���� �Ǹŷ� %d���� ȹ���մϴ�.\n", weapon.level, sellPrice);

                    // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

                    // �����ڱݿ� ���� �Ǹ� ���� �߰�
                    total_money += sellPrice;

                    // ���� ���� �ʱ�ȭ
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

        total_money_HARD = Initial_Money_HARD; // ���� ���� �� ���� �ڱ� �ʱ�ȭ

        // ���� ���� �� ȭ�� �ʱ�ȭ �� �÷��̾� ���� �ҷ�����
        system("@cls||clear");
        loadPlayerInfo_HARD(&total_money_HARD, &weapon_HARD.level_HARD);

        // �÷��̾� ������ �ҷ������� ���� ������ 0���� Ŭ ��� ���� �ڵ� �Ǹ�
        AutoInfosellScreen_HARD(weapon, weapon_HARD, weapon_HARD.level_HARD, calculateSellPrice_HARD(weapon_HARD.level_HARD), total_money_HARD, weapon.retTime);

        // �÷��̾� ������ �ҷ������� ���� ������ 0���� Ŭ ��� ���� �ڵ� �Ǹ� (�����ڱݿ� ���� �Ǹ� ���� �߰�)
        int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
        total_money_HARD += sellPrice_HARD;

        // ���� ���� �ʱ�ȭ
        weapon_HARD.level_HARD = 0;

        // ���� ���� ���� : ���� �ڱ��� 20���� �ʰ� or ���� �ڱ��� 0�� ����
        while (total_money_HARD < 200000 && total_money_HARD >= 0)
        {
            int upgradeCost_HARD = calculateUpgradeCost_HARD(weapon_HARD.level_HARD);
            int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);

            // ȭ�� ����
            system("@cls||clear");

            // Ÿ��Ʋ ȭ�� ���
            printtitleScrren_HARD();

            // ���� ���¿� ��ȭ ���� ���� ���
            weapon_HARD.success_rate_HARD = calculateProbability_HARD(weapon_HARD.level_HARD);
            printf("�����ڱ� : %d��\n", total_money_HARD);
            printf("���ⷹ�� : + %d\n", weapon_HARD.level_HARD);
            printf("����Ȯ�� : %.2f%%\n\n", weapon_HARD.success_rate_HARD);
            printf("��ȣ�� ������ �ּ���!\n");
            printf("1.��ȭ   2.�����Ǹ�   3.����   4. ����\n\n");
            // ���� ��ȣ�� ���� ���� ���
            printExplanation(1, upgradeCost_HARD, 0, 0, 0);  // upgradeCost�� ����, �������� 0���� ǥ��
            printExplanation(2, 0, sellPrice_HARD, 0, 0);    // sellPrice�� ����, �������� 0���� ǥ��
            printExplanation(3, 0, 0, total_money_HARD, weapon_HARD.level_HARD);  // total_money, weapon.level�� ����, �������� 0���� ǥ��
            printExplanation(4, 0, 0, total_money_HARD, weapon_HARD.level_HARD);  // total_money, weapon.level�� ����, �������� 0���� ǥ��
            printf("\n�Է� : ");
            scanf("%d", &weapon_HARD.isTry_HARD);

            // ���� ����
            int bufferDel_HARD;
            while ((bufferDel_HARD = getchar()) != '\n' && bufferDel_HARD != EOF);

            // �̸� ��ȭ ����� ����Ͽ� ���� �����ϸ� ��ȭ �õ����� ����
            if (weapon_HARD.isTry_HARD == 1 && upgradeCost_HARD > total_money_HARD)
            {
                printf("���� �����Ͽ� ��ȭ�� ������ �� �����ϴ�.\n");
                printf("��ȭ �ܰ�� �״�� �����˴ϴ�.\n");

                weapon.retTime = time(0) + WAIT_TIME_2;
                while (time(0) < weapon.retTime);

                continue;
            }

            switch (weapon_HARD.isTry_HARD)
            {
            case 1:        // ��ȭ ����
                // ���� �� ����
                weapon_HARD.randNum_HARD = rand() % 100;

                printf("\n��ȭ��..\n");

                // ����� �ڵ� ���
                /*printf("[�����] ���� �� : %d | ���� Ȯ�� : %.2f\n", weapon_HARD.randNum_HARD, weapon_HARD.success_rate_HARD);
                if (weapon_HARD.randNum_HARD < weapon_HARD.success_rate_HARD)
                {
                    printf("[�����] ���� ��(%d) < ���� Ȯ��(%.2f) �̹Ƿ� ��ȭ �����Դϴ�.\n", weapon_HARD.randNum_HARD, weapon_HARD.success_rate_HARD);
                }
                else if (weapon_HARD.randNum_HARD >= weapon_HARD.success_rate_HARD)
                {
                    printf("[�����] ���� ��(%d) => ���� Ȯ��(%.2f) �̹Ƿ� ��ȭ �����Դϴ�.\n", weapon_HARD.randNum_HARD, weapon_HARD.success_rate_HARD);
                }*/

                // ��ȭ ��� ���
                printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n\n", total_money_HARD - upgradeCost_HARD);

                // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

                // ���� ����ϸ� ��ȭ �õ�
                total_money_HARD -= upgradeCost_HARD;

                // ������ ���� ���� ����Ȯ�� ���� ������ ����
                if (weapon_HARD.randNum_HARD < weapon_HARD.success_rate_HARD)
                {
                    // ����ȭ�� ���
                    printSuccessScreen_HARD(weapon_HARD.level_HARD);

                    // ��ȭ�� ���� ���� ��, ������ �ϳ� ���� ��Ű��, ����Ȯ���� ����
                    weapon_HARD.level_HARD++;
                }
                else
                {
                    // ����ȭ�� ���
                    printf("�̷�..! ���� �̲�������.\n");
                    printFailedScreen_HARD(weapon_HARD.level_HARD);

                    int failureCost_HARD = calculateFailureCost_HARD(weapon_HARD.level_HARD);

                    if (total_money_HARD < failureCost_HARD)
                    {
                        printf("���� �ڱ��� �����մϴ�. + %d ���⸦ �Ҿ����ϴ�.\n", weapon_HARD.level_HARD);
                        weapon_HARD.level_HARD = 0;
                    }
                    else
                    {
                        // ����ڿ��� ��ȭ ���� �Ǵ� �ʱ�ȭ ����
                        printf("\n1. ��ȭ ����   2. �ʱ�ȭ\n");
                        printf("��ȭ ���� ����� %d�� �Դϴ�.\n", failureCost_HARD);
                        printf("�Է� : ");
                        scanf("%d", &weapon_HARD.isTry_HARD);

                        if (weapon_HARD.isTry_HARD == 1)
                        {
                            // ��ȭ ���� ���� �� ���� �ڱ��� 50%�� �����ϰ� ��ȭ ����.
                            printf("\n%d���� �����ϰ� ��ȭ ������ �����մϴ�.\n", failureCost_HARD);
                            total_money_HARD -= failureCost_HARD;
                            printf("��ȭ ���� �� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n\n", total_money_HARD);
                            break;
                        }
                        if (weapon_HARD.isTry_HARD == 2)
                        {
                            printf("+ %d ���⸦ �Ҿ����ϴ�.\n", weapon_HARD.level_HARD);
                            weapon_HARD.level_HARD = 0;
                            break;
                        }
                    }
                }

                if (weapon_HARD.level_HARD == 12)
                {
                    while (1)
                    {
                        // ���� ����
                        int bufferDel_HARD;
                        while ((bufferDel_HARD = getchar()) != '\n' && bufferDel_HARD != EOF);

                        int choice_lv12_HARD;
                        system("@cls||clear");
                        printf("+ 12 ���� �޼��� �����մϴ�!\n\n");
                        printf("�̴ϰ��� or �����ǸŸ� ������ �ּ���.\n");
                        printf("�̴ϰ����� Ŭ������ �� ������ ��� Ŭ���� �˴ϴ�.\n\n");
                        printf("1. �̴ϰ���   2. ���� �Ǹ�\n\n");
                        printf("�Է� : ");
                        scanf("%d", &choice_lv12_HARD);

                        switch (choice_lv12_HARD)
                        {
                        case 1:
                            printf("�̴ϰ����� �����ϼ̽��ϴ�!\n");
                            system("@cls||clear");
                            printf("\n+ 12 ���� �޼�! �̴ϰ����� �����մϴ�.\n");

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
                            printf("\n�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �õ��� �ּ���.\n");
                            printf("\n����Ϸ��� EnterŰ�� �����ʽÿ�.\n");
                            while (_getch() != '\r');
                            continue;
                        }
                        break;
                    }
                }
                break;

            case 2:         // ���� �Ǹ�
                printf("\n���� �Ǹ���..\n");

                // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

                // ������ �´� ���� �Ǹ� ���� ���
                int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
                printf("���� �Ǹŷ� %d���� ȹ���Ͽ����ϴ�.\n", sellPrice_HARD);
                printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n\n", total_money_HARD + sellPrice_HARD);

                // �����ڱݿ� ���� �Ǹ� ���� �߰�
                total_money_HARD += sellPrice_HARD;

                // ���� ���� �ʱ�ȭ
                weapon_HARD.level_HARD = 0;
                break;

            case 3:         // ����
                // ���Ḧ �� ��� ���α׷� ����
                printf("�����ڱ� : %d�� / ���ⷹ�� : + %d �� �ڵ� ����˴ϴ�.\n", total_money_HARD, weapon_HARD.level_HARD);

                // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

            case 4:         // ����
                // ������ �� ��� �����ڱ� & ���� ���� ����
                printf("\n���� ������..\n");

                // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

                // �÷��̾� ���� ����
                savePlayerInfo_HARD(total_money_HARD, weapon_HARD.level_HARD);
                printf("�����ڱ� : %d�� / ���ⷹ�� : + %d �� ����Ǿ����ϴ�.\n", total_money_HARD, weapon_HARD.level_HARD);
                printf("������ ��� �����մϴ�.\n\n");
                break;
            default:
                printf("�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �õ��� �ּ���.\n");
                break;
            }

            // �ϸ��� ���� ���
            printf("\n����Ϸ��� EnterŰ�� �����ʽÿ�.\n");
            while (_getch() != '\r');

            // �����ڱ��� 20���� �̻��� ���
            if (total_money >= 200000)
            {
                printGameClear_HARD();
            }

            // �����ڱ��� 0�� �̸��� ���
            if (total_money_HARD <= 0)
            {
                // �����ڱ��� 0���ε� ���� �������� 0�� ��� ���� ����
                if (weapon_HARD.level_HARD == 0)
                {
                    printGameFailed_HARD();
                }
                else
                {
                    printf("���� �ڱ� 0������ ���� �������� + %d ����� �ڵ� �Ǹŵ˴ϴ�.\n", weapon_HARD.level_HARD);
                    printf("\n���� �Ǹ���..\n");

                    // ������ �´� ���� �Ǹ� ���� ���
                    int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
                    printf("+ %d ���� �Ǹŷ� %d���� ȹ���մϴ�.\n", weapon_HARD.level_HARD, sellPrice_HARD);

                    // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
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

                    // �����ڱݿ� ���� �Ǹ� ���� �߰�
                    total_money_HARD += sellPrice_HARD;

                    // ���� ���� �ʱ�ȭ
                    weapon_HARD.level_HARD = 0;
                }
            }
        }
    }
#pragma endregion

    return 0;
}