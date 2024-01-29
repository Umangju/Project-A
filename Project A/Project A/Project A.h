#ifndef PROJECT_A_H
#define Project_A_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// EASY MODE
#pragma region EASY MODE

#define MAX_PROBABILITY 100.0f              // ����Ȯ�� �ִ�ġ
#define WAIT_TIME 2                         // ���ð�
#define WAIT_TIME_2 4                       // ���ð� 
#define Initial_Money 10000                 // �ʱ� �ڱ� ����

// ���� �ڱ��� �ʱ� �ڱ����� ����
int total_money = Initial_Money;

// ���� ���̵��� ��Ÿ���� ������
enum Difficulty
{
    EASY = 1,
    HARD = 2
};

typedef struct
{
    int isTry;                   // ��ȭ�� �� ������ ����
    int level;                   // ���� ������ ����
    float success_rate;          // ���� ��ȭ ����Ȯ��
    time_t retTime;              // ���ð� �ӽ����� ����
    int randNum;                 // �������� ������ ����
} Weapon;

// ANSI �̽������� �ڵ带 ����Ͽ� �ؽ�Ʈ�� ������ �ٲٴ� �Լ�
void changeTextColor(int color)
{
    printf("\033[38;5;%dm", color);
}

// ANSI �̽������� �ڵ带 ����Ͽ� �ؽ�Ʈ�� ������ �����ϴ� �Լ�
void resetTextColor()
{
    printf("\033[0m");
}

// ��ȭ ��������
void printProgressBar(float progress)
{
    const int barWidth = 50;
    int pos = barWidth * progress / 100.0;
    printf("[");
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
        {
            printf("=");
        }
        else if (i == pos)
        {
            printf(">");
        }
        else
        {
            printf(" ");
        }
    }
    printf("] %.1f%%\r", progress);
    fflush(stdout);
}

// ���̵� ���� �� ��ũ��
void printdifficultyScreen()
{
    system("@cls||clear");
    changeTextColor(208);
    printf("������������������������������������������������������������������\n");
    printf("�� EASY MODE �� �����ϼ̽��ϴ� ! ��\n");
    printf("������������������������������������������������������������������\n");
    resetTextColor();
}


// Ÿ��Ʋ ȭ�� ��ũ��, ���̵� ȭ�� ��ũ��
void printtitleScrren()
{
    changeTextColor(33);
    printf("����������������������������������������������������\t");
    resetTextColor();
    changeTextColor(5);
    printf("��������������������������\n");
    resetTextColor();
    changeTextColor(33);
    printf("�� Project A Game Start ! ��\t");
    resetTextColor();
    changeTextColor(5);
    printf("�� EASY MODE ��\n");
    resetTextColor();
    changeTextColor(33);
    printf("����������������������������������������������������\t");
    resetTextColor();
    changeTextColor(5);
    printf("��������������������������\n\n");
    resetTextColor();
}

// ��ȭ ���� ��ũ��
void printSuccessScreen(int level)
{
    changeTextColor(48);
    printf("\n�ڡ١ڡ١ڡ� SUCCESS �١ڡ١ڡ١�\n");
    printf("��                   ��\n");
    if (level + 1 <= 9)
    {
        printf("��   + %d  ->  + %d    ��\n", level, level + 1);
    }
    else if (level + 1 == 10)
    {
        printf("��   + %d  ->  + %d   ��\n", level, level + 1);
    }
    else if (level + 1 <= 12)
    {
        printf("��   + %d  ->  + %d  ��\n", level, level + 1);
    }
    printf("��                   ��\n");
    printf("�ڡ١ڡ١ڡ� SUCCESS �١ڡ١ڡ١�\n");
    resetTextColor();
}

// ��ȭ ���� ��ũ��
void printFailedScreen(int level)
{
    changeTextColor(196);
    printf("�ڡ١ڡ١ڡ� Failed �١ڡ١ڡ١�\n");
    printf("��                  ��\n");
    if (level <= 9)
    {
        printf("��   + %d  ->  + 0   ��\n", level);
    }
    else if (level <= 12)
    {
        printf("��   + %d  ->  + 0  ��\n", level);
    }
    printf("��                  ��\n");
    printf("�ڡ١ڡ١ڡ� Failed �١ڡ١ڡ١�\n");
    resetTextColor();
}

// 12���� �޼� ��ũ��
void printLevelTwelve(int weapon_level, int sellPrice)
{
    printf("\n�����մϴ�! ���� ���� Lv.12�� �޼��ϼ̽��ϴ�.\n");
    printf("+ %d ����� �ڵ������� �Ǹŵ˴ϴ�.\n", weapon_level);
    printf("�Ǹ� �ݾ��� %d�� �Դϴ�.\n\n", sellPrice);
    printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n\n", total_money + sellPrice);
}

// ���� Ŭ���� ��ũ��
void printGameClear()
{
    changeTextColor(3);
    printf("\n�� Game Clear ��\n");
    printf("�����ڱ� 200000�� �̻����� ������ �����մϴ�.\n");
    resetTextColor();
}

// �̴ϰ������� Ŭ���� �� ��� ��ũ��
void printMiniGameClear()
{
    changeTextColor(3);
    printf("\n�� Mini Game Clear ��\n");
    printf("�̴ϰ��� Ŭ����� ������ �����մϴ�.\n");
    resetTextColor();
}

// ���� ���� ��ũ��
void printGameFailed()
{
    changeTextColor(3);
    printf("\n�� Game Failed ��\n");
    printf("�����ڱ� 0�� ���Ϸ� ������ �����մϴ�.\n");
    resetTextColor();
}

// ���� �� ���� �ҷ��� �� ���� ������ �ִٸ� �ڵ� �Ǹ� �Լ�
void AutoInfosellScreen(Weapon weapon, int level, int sellPrice, int total_money, int retTime)
{
    if (weapon.level > 0)
    {
        changeTextColor(122);
        printf("����������������������������������������������������������������������������������������\n");
        if (weapon.level <= 9)
        {
            printf("������ �������� + %d ����� �ڵ� �Ǹŵ˴ϴ�. ��\n", weapon.level);
        }
        else if (weapon.level <= 12)
        {
            printf("������ �������� + %d ����� �ڵ� �Ǹŵ˴ϴ�.��\n", weapon.level);
        }
        printf("����������������������������������������������������������������������������������������\n");
        resetTextColor();
        printf("\n���� �Ǹ���..\n\n");

        // ���� �Ǹ� ���� ���
        int sellPrice = calculateSellPrice(weapon.level);
        printf("+ %d ���� �Ǹŷ� %d���� ȹ���մϴ�.\n\n", weapon.level, sellPrice);
        printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n", total_money + sellPrice);

        // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
        const float INTERVAL_6 = 0.1;
        float elapsedTime_6 = 0.0;

        while (elapsedTime_6 < WAIT_TIME_2)
        {
            printProgressBar(elapsedTime_6 / WAIT_TIME_2 * 100);
            Sleep(INTERVAL_6 * 1000);
            elapsedTime_6 += INTERVAL_6;
        }
        printProgressBar(100.0);
        printf("\n\n");
    }
}

// ��ȭ ���� Ȯ�� ���
float calculateProbability(int level)
{
    switch (level)
    {
    case 0: return 100.0f; // 100%
    case 1: return 90.0f;  // 90%
    case 2: return 80.0f;  // 80%
    case 3: return 70.0f;  // 70%
    case 4: return 60.0f;  // 60%
    case 5: return 50.0f;  // 50%
    case 6: return 40.0f;  // 40%
    case 7: return 30.0f;  // 30%
    case 8: return 20.0f;  // 20%
    case 9: return 10.0f;  // 10%
    case 10: return 5.0f;  //  5%
    case 11: return 2.0f;  //  2%
    case 12: return 0.0f;  // Lv.12������ Ȯ���� 0% (���� ���� ����)
    }
}

// ��ȭ ��� ���
int calculateUpgradeCost(int level)
{
    switch (level)
    {
    case 0: return 0;
    case 1: return 50;
    case 2: return 200;
    case 3: return 500;
    case 4: return 800;
    case 5: return 1000;
    case 6: return 1500;
    case 7: return 2000;
    case 8: return 4000;
    case 9: return 8000;
    case 10: return 12000;
    case 11: return 15000;
    default: return 0;
    }
}

// ���� �Ǹ� ���� ���
int calculateSellPrice(int level)
{
    switch (level)
    {
    case 0: return 0;
    case 1: return 100; // case 0 ���� ��ȭ ��� ���� ���� ���� �뷱�� [50]
    case 2: return 200; // case 0 ~ 1���� ��ȭ ��� ���� ���� ���� �뷱�� [50]
    case 3: return 500; // case 0 ~ 2���� ��ȭ ��� ���� ���� ���� �뷱�� [250]
    case 4: return 1000; // case 0 ~ 3���� ��ȭ ��� ���� ���� ���� �뷱�� [750]
    case 5: return 2000; // case 0 ~ 4���� ��ȭ ��� ���� ���� ���� �뷱�� [1550]
    case 6: return 3500; // case 0 ~ 5���� ��ȭ ��� ���� ���� ���� �뷱�� [2550]
    case 7: return 5000; // case 0 ~ 6���� ��ȭ ��� ���� ���� ���� �뷱�� [4050]
    case 8: return 10000; // case 0 ~ 7���� ��ȭ ��� ���� ���� ���� �뷱�� [6050]
    case 9: return 13000; // case 0 ~ 8���� ��ȭ ��� ���� ���� ���� �뷱�� [10050]
    case 10: return 22000; // case 0 ~ 9���� ��ȭ ��� ���� ���� ���� �뷱�� [18050]
    case 11: return 50000; // case 0 ~ 10���� ��ȭ ��� ���� ���� ���� �뷱�� [30050]
    case 12: return 75000; // case 0 ~ 11���� ��ȭ ��� ���� ���� ���� �뷱�� [45050]
    default: return 0;
    }
}

// ���� ��ȣ�� ���� ���� ��� �Լ�
void printExplanation(int choice, int upgradeCost, int sellPrice, int total_money, int weapon_level) {
    switch (choice) {
    case 1:
        printf("[1] ��ȭ��� %d���� ������ �����Դϴ�.\n", upgradeCost);
        break;
    case 2:
        printf("[2] �����Ǹ� ��� %d���� ȹ���� �����Դϴ�.\n", sellPrice);
        break;
    case 3:
        printf("[3] ���� �������� �ڱ� %d���� ���ⷹ�� + %d�� ����ǰ� ������ ����˴ϴ�.\n", total_money, weapon_level);
        break;
    case 4:
        printf("[4] ���� �������� �ڱ� %d���� ���ⷹ�� + %d�� ����ǰ� ������ �̾ ����˴ϴ�.\n", total_money, weapon_level);
        break;
    default:
        printf("���� ��ȣ�� ���� ������ �����ϴ�.\n");
    }
}

// ��ȭ ���� �� ���� ���� �� ����� 50%�� ��ȯ
int calculateFailureCost(int level)
{
    int sellPrice = calculateSellPrice(level);
    return sellPrice / 2;
}

// �÷��̾� ���� ����
void savePlayerInfo(int total_money, int weapon_level)
{
    FILE* file = fopen("Player_info.txt", "w");

    if (file == NULL)
    {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "�����ڱ� : %d\n���� ���� : %d", total_money, weapon_level);

    fclose(file);
}

// �÷����� ���� �ҷ�����
void loadPlayerInfo(int* total_money, int* weapon_level)
{
    FILE* file = fopen("Player_info.txt", "r");

    if (file == NULL)
    {
        // ������ ���� ��� �ʱⰪ���� ����
        *total_money = Initial_Money;
        *weapon_level = 0;
        return;
    }

    fscanf(file, "�����ڱ� : %d\n���� ���� : %d", total_money, weapon_level);

    fclose(file);
}
#pragma endregion

// HARD MODE
#pragma region HARD MODE
#define MAX_PROBABILITY_HARD 100.0f              // ����Ȯ�� �ִ�ġ
#define Initial_Money_HARD 10000                 // �ʱ� �ڱ� ����

// ���� �ڱ��� �ʱ� �ڱ����� ����
int total_money_HARD = Initial_Money_HARD;

typedef struct
{
    int isTry_HARD;                   // ��ȭ�� �� ������ ����
    int level_HARD;                   // ���� ������ ����
    float success_rate_HARD;          // ���� ��ȭ ����Ȯ��
    int randNum_HARD;                 // �������� ������ ����
} Weapon_HARD;

// ANSI �̽������� �ڵ带 ����Ͽ� �ؽ�Ʈ�� ������ �ٲٴ� �Լ�
void changeTextColor_HARD(int color_HARD)
{
    printf("\033[38;5;%dm", color_HARD);
}

// ANSI �̽������� �ڵ带 ����Ͽ� �ؽ�Ʈ�� ������ �����ϴ� �Լ�
void resetTextColor_HARD()
{
    printf("\033[0m");
}

// ��ȭ ��������
void printProgressBar_HARD(float progress_HARD)
{
    const int barWidth_HARD = 50;
    int pos_HARD = barWidth_HARD * progress_HARD / 100.0;
    printf("[");
    for (int i = 0; i < barWidth_HARD; ++i)
    {
        if (i < pos_HARD)
        {
            printf("=");
        }
        else if (i == pos_HARD)
        {
            printf(">");
        }
        else
        {
            printf(" ");
        }
    }
    printf("] %.1f%%\r", progress_HARD);
    fflush(stdout);
}

// ���̵� ���� �� ��ũ��
void printdifficultyScreen_HARD()
{
    system("@cls||clear");
    changeTextColor_HARD(208);
    printf("������������������������������������������������������������������\n");
    printf("�� HARD MODE �� �����ϼ̽��ϴ� ! ��\n");
    printf("������������������������������������������������������������������\n");
    resetTextColor_HARD();
}

// Ÿ��Ʋ ȭ�� ��ũ��, ���̵� ȭ�� ��ũ��
void printtitleScrren_HARD()
{
    changeTextColor_HARD(33);
    printf("����������������������������������������������������\t");
    resetTextColor_HARD();
    changeTextColor_HARD(5);
    printf("��������������������������\n");
    resetTextColor_HARD();
    changeTextColor_HARD(33);
    printf("�� Project A Game Start ! ��\t");
    resetTextColor_HARD();
    changeTextColor_HARD(5);
    printf("�� HARD MODE ��\n");
    resetTextColor_HARD();
    changeTextColor_HARD(33);
    printf("����������������������������������������������������\t");
    resetTextColor_HARD();
    changeTextColor_HARD(5);
    printf("��������������������������\n\n");
    resetTextColor_HARD();
}

// ��ȭ ���� ��ũ��
void printSuccessScreen_HARD(int level_HARD)
{
    changeTextColor_HARD(48);
    printf("�ڡ١ڡ١ڡ� SUCCESS �١ڡ١ڡ١�\n");
    printf("��                   ��\n");
    if (level_HARD + 1 <= 9)
    {
        printf("��   + %d  ->  + %d    ��\n", level_HARD, level_HARD + 1);
    }
    else if (level_HARD + 1 == 10)
    {
        printf("��   + %d  ->  + %d   ��\n", level_HARD, level_HARD + 1);
    }
    else if (level_HARD + 1 <= 12)
    {
        printf("��   + %d  ->  + %d  ��\n", level_HARD, level_HARD + 1);
    }
    printf("��                   ��\n");
    printf("�ڡ١ڡ١ڡ� SUCCESS �١ڡ١ڡ١�\n");
    resetTextColor_HARD();
}

// ��ȭ ���� ��ũ��
void printFailedScreen_HARD(int level_HARD)
{
    changeTextColor_HARD(196);
    printf("�ڡ١ڡ١ڡ� Failed �١ڡ١ڡ١�\n");
    printf("��                  ��\n");
    if (level_HARD <= 9)
    {
        printf("��   + %d  ->  + 0   ��\n", level_HARD);
    }
    else if (level_HARD <= 12)
    {
        printf("��   + %d  ->  + 0  ��\n", level_HARD);
    }
    printf("��                  ��\n");
    printf("�ڡ١ڡ١ڡ� Failed �١ڡ١ڡ١�\n");
    resetTextColor_HARD();
}

// 12���� �޼� ��ũ��
void printLevelTwelve_HARD(int weapon_level_HARD, int sellPrice_HARD)
{
    printf("\n�����մϴ�! ���� ���� Lv.12�� �޼��ϼ̽��ϴ�.\n");
    printf("+ %d ����� �ڵ������� �Ǹŵ˴ϴ�.\n", weapon_level_HARD);
    printf("�Ǹ� �ݾ��� %d�� �Դϴ�.\n\n", sellPrice_HARD);
    printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n\n", total_money_HARD + sellPrice_HARD);
}

// ���� Ŭ���� ��ũ��
void printGameClear_HARD()
{
    changeTextColor_HARD(3);
    printf("\n�� Game Clear ��\n");
    printf("�����ڱ� 200000�� �̻����� ������ �����մϴ�.\n");
    resetTextColor_HARD();
}

// �̴ϰ������� Ŭ���� �� ��� ��ũ��
void printMiniGameClear_HARD()
{
    changeTextColor_HARD(3);
    printf("\n�� Mini Game Clear ��\n");
    printf("�̴ϰ��� Ŭ����� ������ �����մϴ�.\n");
    resetTextColor_HARD();
}

// ���� ���� ��ũ��
void printGameFailed_HARD()
{
    changeTextColor_HARD(3);
    printf("\n�� Game Failed ��\n");
    printf("�����ڱ� 0�� ���Ϸ� ������ �����մϴ�.\n");
    resetTextColor_HARD();
}

// ���� �� ���� �ҷ��� �� ���� ������ �ִٸ� �ڵ� �Ǹ� �Լ�
void AutoInfosellScreen_HARD(Weapon weapon, Weapon_HARD weapon_HARD, int level_HARD, int sellPrice_HARD, int total_money_HARD, int retTime)
{
    if (weapon_HARD.level_HARD > 0)
    {
        changeTextColor_HARD(122);
        printf("����������������������������������������������������������������������������������������\n");
        if (weapon_HARD.level_HARD <= 9)
        {
            printf("������ �������� + %d ����� �ڵ� �Ǹŵ˴ϴ�. ��\n", weapon_HARD.level_HARD);
        }
        else if (weapon_HARD.level_HARD <= 12)
        {
            printf("������ �������� + %d ����� �ڵ� �Ǹŵ˴ϴ�.��\n", weapon_HARD.level_HARD);
        }
        printf("����������������������������������������������������������������������������������������\n");
        resetTextColor_HARD();
        printf("\n���� �Ǹ���..\n\n");

        // ���� �Ǹ� ���� ���
        int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
        printf("+ %d ���� �Ǹŷ� %d���� ȹ���մϴ�.\n\n", weapon_HARD.level_HARD, sellPrice_HARD);
        printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n", total_money_HARD + sellPrice_HARD);

        // ��ȭ ���α׷����� (������ �ð�(��) ��ŭ ���)
        const float INTERVAL_HARD_6 = 0.1;
        float elapsedTime_HARD_6 = 0.0;

        while (elapsedTime_HARD_6 < WAIT_TIME)
        {
            printProgressBar_HARD(elapsedTime_HARD_6 / WAIT_TIME * 100);
            Sleep(INTERVAL_HARD_6 * 1000);
            elapsedTime_HARD_6 += INTERVAL_HARD_6;
        }
        printProgressBar_HARD(100.0);
        printf("\n\n");
    }
}

// ��ȭ ���� Ȯ�� ���
float calculateProbability_HARD(int level_HARD)
{
    switch (level_HARD)
    {
    case 0: return 90.0f;   // 90%
    case 1: return 80.0f;   // 80%
    case 2: return 70.0f;   // 70%
    case 3: return 60.0f;   // 60%
    case 4: return 50.0f;   // 50%
    case 5: return 40.0f;   // 40%
    case 6: return 30.0f;   // 30%
    case 7: return 20.0f;   // 20%
    case 8: return 10.0f;   // 10%
    case 9: return 5.0f;    //  5%
    case 10: return 2.0f;   //  2%
    case 11: return 1.0f;   //  1%
    case 12: return 0.0f;  // Lv.12������ Ȯ���� 0% (���� ���� ����)
    }
}

// ��ȭ ��� ���
int calculateUpgradeCost_HARD(int level_HARD)
{
    switch (level_HARD)
    {
    case 0: return 0;
    case 1: return 50;
    case 2: return 200;
    case 3: return 500;
    case 4: return 800;
    case 5: return 1000;
    case 6: return 1500;
    case 7: return 2000;
    case 8: return 4000;
    case 9: return 8000;
    case 10: return 12000;
    case 11: return 15000;
    default: return 0;
    }
}

// ���� �Ǹ� ���� ���
int calculateSellPrice_HARD(int level_HARD)
{
    switch (level_HARD)
    {
    case 0: return 0;
    case 1: return 100; // case 0 ���� ��ȭ ��� ���� ���� ���� �뷱�� [50]
    case 2: return 200; // case 0 ~ 1���� ��ȭ ��� ���� ���� ���� �뷱�� [50]
    case 3: return 500; // case 0 ~ 2���� ��ȭ ��� ���� ���� ���� �뷱�� [250]
    case 4: return 1000; // case 0 ~ 3���� ��ȭ ��� ���� ���� ���� �뷱�� [750]
    case 5: return 2000; // case 0 ~ 4���� ��ȭ ��� ���� ���� ���� �뷱�� [1550]
    case 6: return 3500; // case 0 ~ 5���� ��ȭ ��� ���� ���� ���� �뷱�� [2550]
    case 7: return 5000; // case 0 ~ 6���� ��ȭ ��� ���� ���� ���� �뷱�� [4050]
    case 8: return 10000; // case 0 ~ 7���� ��ȭ ��� ���� ���� ���� �뷱�� [6050]
    case 9: return 13000; // case 0 ~ 8���� ��ȭ ��� ���� ���� ���� �뷱�� [10050]
    case 10: return 22000; // case 0 ~ 9���� ��ȭ ��� ���� ���� ���� �뷱�� [18050]
    case 11: return 50000; // case 0 ~ 10���� ��ȭ ��� ���� ���� ���� �뷱�� [30050]
    case 12: return 75000; // case 0 ~ 11���� ��ȭ ��� ���� ���� ���� �뷱�� [45050]
    default: return 0;
    }
}

// ���� ��ȣ�� ���� ���� ��� �Լ�
void printExplanation_HARD(int choice_HARD, int upgradeCost_HARD, int sellPrice_HARD, int total_money_HARD, int weapon_level_HARD)
{
    switch (choice_HARD)
    {
    case 1:
        printf("[1] ��ȭ��� %d���� ������ �����Դϴ�.\n", upgradeCost_HARD);
        break;
    case 2:
        printf("[2] �����Ǹ� ��� %d���� ȹ���� �����Դϴ�.\n", sellPrice_HARD);
        break;
    case 3:
        printf("[3] ���� �������� �ڱ� %d���� ���ⷹ�� + %d�� ����ǰ� ������ ����˴ϴ�.\n", total_money_HARD, weapon_level_HARD);
        break;
    case 4:
        printf("[4] ���� �������� �ڱ� %d���� ���ⷹ�� + %d�� ����ǰ� ������ �̾ ����˴ϴ�.\n", total_money_HARD, weapon_level_HARD);
        break;
    default:
        printf("���� ��ȣ�� ���� ������ �����ϴ�.\n");
    }
}

// ��ȭ ���� �� ���� ���� �� ����� 50%�� ��ȯ
int calculateFailureCost_HARD(int level_HARD)
{
    int sellPrice = calculateSellPrice(level_HARD);
    return sellPrice / 2;
}

// �÷��̾� ���� ����
void savePlayerInfo_HARD(int total_money_HARD, int weapon_level_HARD)
{
    FILE* file = fopen("Player_info_HARD.txt", "w");

    if (file == NULL)
    {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "�����ڱ� : %d\n���� ���� : %d", total_money_HARD, weapon_level_HARD);

    fclose(file);
}

// �÷��̾� ���� �ҷ�����
void loadPlayerInfo_HARD(int* total_money_HARD, int* weapon_level_HARD)
{
    FILE* file = fopen("Player_info_HARD.txt", "r");

    if (file == NULL)
    {
        // ������ ���� ��� �ʱⰪ���� ����
        *total_money_HARD = Initial_Money_HARD;
        *weapon_level_HARD = 0;
        return;
    }

    fscanf(file, "�����ڱ� : %d\n���� ���� : %d", total_money_HARD, weapon_level_HARD);

    fclose(file);
}
#pragma endregion

// MINI GAME [EASY]
#pragma region MINI GAME [EASY]
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

// Ŀ���� ��ġ�� x, y�� �̵��ϴ� �Լ�
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// Ű������ �Է��� �ް�, �Էµ� Ű�� ���� ��ȯ�ϴ� �Լ�
int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

// ������ �׸��� �Լ�
void DrawDino(int dinoY)
{
    GotoXY(0, dinoY);
    static int legFlag = 1;
    printf("        $$$$$$$ \n");
    printf("       $$ $$$$$$\n");
    printf("       $$$$$$$$$\n");
    printf("$      $$$      \n");
    printf("$$     $$$$$$$  \n");
    printf("$$$   $$$$$     \n");
    printf(" $$  $$$$$$$$$$ \n");
    printf(" $$$$$$$$$$$    \n");
    printf("  $$$$$$$$$$    \n");
    printf("    $$$$$$$$    \n");
    printf("     $$$$$$     \n");
    if (legFlag)
    {
        printf("     $    $$$    \n");
        printf("     $$          ");
        legFlag = 0;
    }
    else
    {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = 1;
    }
}

// ������ �׸��� �Լ�
void DrawTree(int treeX)
{
    GotoXY(treeX, TREE_BOTTOM_Y);
    printf("$$$$");
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    printf(" $$ ");
    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    printf(" $$ ");
}

// �浹 ������ ���ӿ��� �׷���
void DrawGameOver(const int score)
{
    system("@cls||clear");
    int x = 18;
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);

    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}

// �浹������ 1�� ��ȯ, �ƴϸ� 0�� ��ȯ
int isCollision(const int treeX, const int dinoY)
{
    // Ʈ���� X�� ������ ��ü�ʿ� ������,
    // ������ ���̰� ������� �ʴٸ� �浹�� ó��
    GotoXY(0, 0);
    printf("treeX : %d, dinoY : %d", treeX, dinoY); // �̷������� ������ X, Y�� ã���ϴ�.
    if (treeX <= 8 && treeX >= 4 &&
        dinoY > 8)
    {
        return 1;
    }
    return 0;
}

// ���� ���� �Լ�
int MiniGame(Weapon weapon, int level, int sellPrice, int total_money)
{
    // ���� ���۽� �ʱ�ȭ
    int isJumping = 0;
    int isBottom = 1;
    const int gravity = 3;

    int dinoY = DINO_BOTTOM_Y;
    int treeX = TREE_BOTTOM_X;

    int score = 0;
    clock_t start, curr;    // ���� ���� �ʱ�ȭ
    start = clock();        // ���۽ð� �ʱ�ȭ

    while (1) // �� �ǿ� ���� ����
    {
        // �浹üũ Ʈ���� x���� ������ y������ �Ǵ�
        if (isCollision(treeX, dinoY))
        {
            DrawGameOver(score);
            break; // ���� ����
        }

        // zŰ�� ���Ȱ�, �ٴ��� �ƴҶ� ����
        if (GetKeyDown() == ' ' && isBottom) // ���� Ű [Space bar]
        {
            isJumping = 1;
            isBottom = 0;
        }

        // �������̶�� Y�� ����, ������ �������� Y�� ����.
        if (isJumping)
        {
            dinoY -= gravity;
        }
        else
        {
            dinoY += gravity;
        }

        // Y�� ����ؼ� �����ϴ°� �������� �ٴ��� ����.
        if (dinoY >= DINO_BOTTOM_Y)
        {
            dinoY = DINO_BOTTOM_Y;
            isBottom = 1;
        }

        // ������ �������� (x����) �������ϰ�
        // ������ ��ġ�� ���� �����ΰ��� �ٽ� ������ ������ ��ȯ.
        treeX -= 2;
        if (treeX <= 0)
        {
            treeX = TREE_BOTTOM_X;
        }

        // ������ ������ ������ ������ ���� ��Ȳ.
        if (dinoY <= 3)
        {
            isJumping = 0;
        }

        DrawDino(dinoY);        // draw dino
        DrawTree(treeX);        // draw Tree

        curr = clock();            // ����ð� �޾ƿ���
        if (((curr - start) / CLOCKS_PER_SEC) >= 1)    // 1�ʰ� �Ѿ�����
        {
            score++;    // ���ھ� UP
            start = clock();    // ���۽ð� �ʱ�ȭ
        }
        Sleep(60);
        system("@cls||clear");    //clear

        // ��������� 1�ʸ��� ���ִ°��� �ƴ϶� �׻� ������ָ鼭, 1�ʰ� �������� ++
        GotoXY(22, 0);    // Ŀ���� ��� �������� �ű��. �ܼ�â�� cols=100�̹Ƿ� 2*x�̹Ƿ� 22���� �־���
        printf("Score : %d ", score);    // ���� ���
    }
    if (score >= 30)
    {
        system("@cls||clear");
        printMiniGameClear();
        return 1;
    }
    else
    {
        system("@cls||clear");
        printf("�̴ϰ��� ����\n");
        printf("�̴ϰ��� ���з� + %d ����� �ڵ��ǸŵǸ�, ������ �̾ ����˴ϴ�.\n", weapon.level);
        int sellPrice = calculateSellPrice(weapon.level);
        printf("\n+ %d ���� �Ǹŷ� %d���� ȹ���մϴ�.\n\n", weapon.level, sellPrice);
        printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n", total_money + sellPrice);
        return 0;
    }
}

#pragma endregion

// MINI GAME [HARD]
#pragma region MINI GAME [HARD]
#define DINO_BOTTOM_Y_HARD 12
#define TREE_BOTTOM_Y_HARD 20
#define TREE_BOTTOM_X_HARD 45

// Ŀ���� ��ġ�� x, y�� �̵��ϴ� �Լ�
void GotoXY_HARD(int x, int y)
{
    COORD PosH;
    PosH.X = 2 * x;
    PosH.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), PosH);
}

// Ű������ �Է��� �ް�, �Էµ� Ű�� ���� ��ȯ�ϴ� �Լ�
int GetKeyDown_HARD()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

// ������ �׸��� �Լ�
void DrawDino_HARD(int dinoY_HARD)
{
    GotoXY_HARD(0, dinoY_HARD);
    static int legFlag_HARD = 1;
    printf("        $$$$$$$ \n");
    printf("       $$ $$$$$$\n");
    printf("       $$$$$$$$$\n");
    printf("$      $$$      \n");
    printf("$$     $$$$$$$  \n");
    printf("$$$   $$$$$     \n");
    printf(" $$  $$$$$$$$$$ \n");
    printf(" $$$$$$$$$$$    \n");
    printf("  $$$$$$$$$$    \n");
    printf("    $$$$$$$$    \n");
    printf("     $$$$$$     \n");
    if (legFlag_HARD)
    {
        printf("     $    $$$    \n");
        printf("     $$          ");
        legFlag_HARD = 0;
    }
    else
    {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag_HARD = 1;
    }
}

// ������ �׸��� �Լ�
void DrawTree_HARD(int treeX_HARD)
{
    GotoXY_HARD(treeX_HARD, TREE_BOTTOM_Y_HARD);
    printf("$$$$");
    GotoXY_HARD(treeX_HARD, TREE_BOTTOM_Y_HARD + 1);
    printf(" $$ ");
    GotoXY_HARD(treeX_HARD, TREE_BOTTOM_Y_HARD + 2);
    printf(" $$ ");
    GotoXY_HARD(treeX_HARD, TREE_BOTTOM_Y_HARD + 3);
    printf(" $$ ");
    GotoXY_HARD(treeX_HARD, TREE_BOTTOM_Y_HARD + 4);
    printf(" $$ ");
}

// �浹 ������ ���ӿ��� �׷���
void DrawGameOver_HARD(const int score_HARD)
{
    system("@cls||clear");
    int x = 18;
    int y = 8;
    GotoXY_HARD(x, y);
    printf("===========================");
    GotoXY_HARD(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY_HARD(x, y + 2);
    printf("===========================");
    GotoXY_HARD(x, y + 5);
    printf("SCORE : %d", score_HARD);

    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}

// �浹������ 1�� ��ȯ, �ƴϸ� 0�� ��ȯ
int isCollision_HARD(const int treeX_HARD, const int dinoY_HARD)
{
    // Ʈ���� X�� ������ ��ü�ʿ� ������,
    // ������ ���̰� ������� �ʴٸ� �浹�� ó��
    GotoXY_HARD(0, 0);
    printf("treeX : %d, dinoY : %d", treeX_HARD, dinoY_HARD); // �̷������� ������ X, Y�� ã���ϴ�.
    if (treeX_HARD <= 8 && treeX_HARD >= 4 &&
        dinoY_HARD > 8)
    {
        return 1;
    }
    return 0;
}

// ���� ���� �Լ�
int MiniGame_HARD(Weapon_HARD weapon_HARD, int level_HARD, int sellPrice_HARD, int total_money_HARD)
{
    // ���� ���۽� �ʱ�ȭ
    int isJumping_HARD = 0;
    int isBottom_HARD = 1;
    const int gravity_HARD = 3;

    int dinoY_HARD = DINO_BOTTOM_Y_HARD;
    int treeX_HARD = TREE_BOTTOM_X_HARD;

    int score_HARD = 0;
    clock_t start_HARD, curr_HARD;    // ���� ���� �ʱ�ȭ
    start_HARD = clock();        // ���۽ð� �ʱ�ȭ

    while (1) // �� �ǿ� ���� ����
    {
        // �浹üũ Ʈ���� x���� ������ y������ �Ǵ�
        if (isCollision_HARD(treeX_HARD, dinoY_HARD))
        {
            DrawGameOver_HARD(score_HARD);
            break; // ���� ����
        }

        // zŰ�� ���Ȱ�, �ٴ��� �ƴҶ� ����
        if (GetKeyDown_HARD() == ' ' && isBottom_HARD) // ���� Ű [Space bar]
        {
            isJumping_HARD = 1;
            isBottom_HARD = 0;
        }

        // �������̶�� Y�� ����, ������ �������� Y�� ����.
        if (isJumping_HARD)
        {
            dinoY_HARD -= gravity_HARD;
        }
        else
        {
            dinoY_HARD += gravity_HARD;
        }

        // Y�� ����ؼ� �����ϴ°� �������� �ٴ��� ����.
        if (dinoY_HARD >= DINO_BOTTOM_Y_HARD)
        {
            dinoY_HARD = DINO_BOTTOM_Y_HARD;
            isBottom_HARD = 1;
        }

        // ������ �������� (x����) �������ϰ�
        // ������ ��ġ�� ���� �����ΰ��� �ٽ� ������ ������ ��ȯ.
        treeX_HARD -= 2;
        if (treeX_HARD <= 0)
        {
            treeX_HARD = TREE_BOTTOM_X;
        }

        // ������ ������ ������ ������ ���� ��Ȳ.
        if (dinoY_HARD <= 3)
        {
            isJumping_HARD = 0;
        }

        DrawDino_HARD(dinoY_HARD);        // draw dino
        DrawTree_HARD(treeX_HARD);        // draw Tree

        curr_HARD = clock();            // ����ð� �޾ƿ���
        if (((curr_HARD - start_HARD) / CLOCKS_PER_SEC) >= 1)    // 1�ʰ� �Ѿ�����
        {
            score_HARD++;    // ���ھ� UP
            start_HARD = clock();    // ���۽ð� �ʱ�ȭ
        }
        Sleep(60);
        system("@cls||clear");    //clear

        // ��������� 1�ʸ��� ���ִ°��� �ƴ϶� �׻� ������ָ鼭, 1�ʰ� �������� ++
        GotoXY_HARD(22, 0);    // Ŀ���� ��� �������� �ű��. �ܼ�â�� cols=100�̹Ƿ� 2*x�̹Ƿ� 22���� �־���
        printf("Score : %d ", score_HARD);    // ���� ���
    }
    if (score_HARD >= 60)
    {
        system("@cls||clear");
        printMiniGameClear();
        return 1;
    }
    else
    {
        system("@cls||clear");
        printf("�̴ϰ��� ����\n");
        printf("�̴ϰ��� ���з� + %d ����� �ڵ��ǸŵǸ�, ������ �̾ ����˴ϴ�.\n", weapon_HARD.level_HARD);
        int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
        printf("\n+ %d ���� �Ǹŷ� %d���� ȹ���մϴ�.\n\n", weapon_HARD.level_HARD, sellPrice_HARD);
        printf("�� ������Ʈ �� �����ڱ��� %d�� �Դϴ�.\n", total_money_HARD + sellPrice_HARD);
        return 0;
    }
}
#pragma endregion

#endif  // Project A.h