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

#define MAX_PROBABILITY 100.0f              // 성공확률 최대치
#define WAIT_TIME 2                         // 대기시간
#define WAIT_TIME_2 4                       // 대기시간 
#define Initial_Money 10000                 // 초기 자금 설정

// 보유 자금을 초기 자금으로 설정
int total_money = Initial_Money;

// 게임 난이도를 나타내는 열거형
enum Difficulty
{
    EASY = 1,
    HARD = 2
};

typedef struct
{
    int isTry;                   // 강화를 할 것인지 선택
    int level;                   // 현재 무기의 레벨
    float success_rate;          // 현재 강화 성공확률
    time_t retTime;              // 대기시간 임시저장 변수
    int randNum;                 // 랜덤값을 저장할 변수
} Weapon;

// ANSI 이스케이프 코드를 사용하여 텍스트의 색상을 바꾸는 함수
void changeTextColor(int color)
{
    printf("\033[38;5;%dm", color);
}

// ANSI 이스케이프 코드를 사용하여 텍스트의 색상을 리셋하는 함수
void resetTextColor()
{
    printf("\033[0m");
}

// 강화 게이지바
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

// 난이도 선택 후 스크린
void printdifficultyScreen()
{
    system("@cls||clear");
    changeTextColor(208);
    printf("┌───────────────────────────────┐\n");
    printf("♥ EASY MODE 를 선택하셨습니다 ! ♥\n");
    printf("└───────────────────────────────┘\n");
    resetTextColor();
}


// 타이틀 화면 스크린, 난이도 화면 스크린
void printtitleScrren()
{
    changeTextColor(33);
    printf("┌────────────────────────┐\t");
    resetTextColor();
    changeTextColor(5);
    printf("┌───────────┐\n");
    resetTextColor();
    changeTextColor(33);
    printf("● Project A Game Start ! ●\t");
    resetTextColor();
    changeTextColor(5);
    printf("♣ EASY MODE ♣\n");
    resetTextColor();
    changeTextColor(33);
    printf("└────────────────────────┘\t");
    resetTextColor();
    changeTextColor(5);
    printf("└───────────┘\n\n");
    resetTextColor();
}

// 강화 성공 스크린
void printSuccessScreen(int level)
{
    changeTextColor(48);
    printf("\n★☆★☆★☆ SUCCESS ☆★☆★☆★\n");
    printf("☆                   ☆\n");
    if (level + 1 <= 9)
    {
        printf("★   + %d  ->  + %d    ★\n", level, level + 1);
    }
    else if (level + 1 == 10)
    {
        printf("★   + %d  ->  + %d   ★\n", level, level + 1);
    }
    else if (level + 1 <= 12)
    {
        printf("★   + %d  ->  + %d  ★\n", level, level + 1);
    }
    printf("☆                   ☆\n");
    printf("★☆★☆★☆ SUCCESS ☆★☆★☆★\n");
    resetTextColor();
}

// 강화 실패 스크린
void printFailedScreen(int level)
{
    changeTextColor(196);
    printf("★☆★☆★☆ Failed ☆★☆★☆★\n");
    printf("☆                  ☆\n");
    if (level <= 9)
    {
        printf("★   + %d  ->  + 0   ★\n", level);
    }
    else if (level <= 12)
    {
        printf("★   + %d  ->  + 0  ★\n", level);
    }
    printf("☆                  ☆\n");
    printf("★☆★☆★☆ Failed ☆★☆★☆★\n");
    resetTextColor();
}

// 12레벨 달성 스크린
void printLevelTwelve(int weapon_level, int sellPrice)
{
    printf("\n축하합니다! 최종 무기 Lv.12에 달성하셨습니다.\n");
    printf("+ %d 무기는 자동적으로 판매됩니다.\n", weapon_level);
    printf("판매 금액은 %d원 입니다.\n\n", sellPrice);
    printf("곧 업데이트 될 보유자금은 %d원 입니다.\n\n", total_money + sellPrice);
}

// 게임 클리어 스크린
void printGameClear()
{
    changeTextColor(3);
    printf("\n★ Game Clear ★\n");
    printf("보유자금 200000원 이상으로 게임을 종료합니다.\n");
    resetTextColor();
}

// 미니게임으로 클리어 할 경우 스크린
void printMiniGameClear()
{
    changeTextColor(3);
    printf("\n★ Mini Game Clear ★\n");
    printf("미니게임 클리어로 게임을 종료합니다.\n");
    resetTextColor();
}

// 게임 실패 스크린
void printGameFailed()
{
    changeTextColor(3);
    printf("\n★ Game Failed ★\n");
    printf("보유자금 0원 이하로 게임을 종료합니다.\n");
    resetTextColor();
}

// 시작 시 정보 불러온 뒤 무기 레벨이 있다면 자동 판매 함수
void AutoInfosellScreen(Weapon weapon, int level, int sellPrice, int total_money, int retTime)
{
    if (weapon.level > 0)
    {
        changeTextColor(122);
        printf("┌──────────────────────────────────────────┐\n");
        if (weapon.level <= 9)
        {
            printf("│현재 보유중인 + %d 무기는 자동 판매됩니다. │\n", weapon.level);
        }
        else if (weapon.level <= 12)
        {
            printf("│현재 보유중인 + %d 무기는 자동 판매됩니다.│\n", weapon.level);
        }
        printf("└──────────────────────────────────────────┘\n");
        resetTextColor();
        printf("\n무기 판매중..\n\n");

        // 무기 판매 가격 계산
        int sellPrice = calculateSellPrice(weapon.level);
        printf("+ %d 무기 판매로 %d원을 획득합니다.\n\n", weapon.level, sellPrice);
        printf("곧 업데이트 될 보유자금은 %d원 입니다.\n", total_money + sellPrice);

        // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
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

// 강화 성공 확률 계산
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
    case 12: return 0.0f;  // Lv.12에서의 확률은 0% (최종 무기 레벨)
    }
}

// 강화 비용 계산
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

// 무기 판매 가격 계산
int calculateSellPrice(int level)
{
    switch (level)
    {
    case 0: return 0;
    case 1: return 100; // case 0 까지 강화 비용 더한 값에 대한 밸런스 [50]
    case 2: return 200; // case 0 ~ 1까지 강화 비용 더한 값에 대한 밸런스 [50]
    case 3: return 500; // case 0 ~ 2까지 강화 비용 더한 값에 대한 밸런스 [250]
    case 4: return 1000; // case 0 ~ 3까지 강화 비용 더한 값에 대한 밸런스 [750]
    case 5: return 2000; // case 0 ~ 4까지 강화 비용 더한 값에 대한 밸런스 [1550]
    case 6: return 3500; // case 0 ~ 5까지 강화 비용 더한 값에 대한 밸런스 [2550]
    case 7: return 5000; // case 0 ~ 6까지 강화 비용 더한 값에 대한 밸런스 [4050]
    case 8: return 10000; // case 0 ~ 7까지 강화 비용 더한 값에 대한 밸런스 [6050]
    case 9: return 13000; // case 0 ~ 8까지 강화 비용 더한 값에 대한 밸런스 [10050]
    case 10: return 22000; // case 0 ~ 9까지 강화 비용 더한 값에 대한 밸런스 [18050]
    case 11: return 50000; // case 0 ~ 10까지 강화 비용 더한 값에 대한 밸런스 [30050]
    case 12: return 75000; // case 0 ~ 11까지 강화 비용 더한 값에 대한 밸런스 [45050]
    default: return 0;
    }
}

// 선택 번호에 따른 설명 출력 함수
void printExplanation(int choice, int upgradeCost, int sellPrice, int total_money, int weapon_level) {
    switch (choice) {
    case 1:
        printf("[1] 강화비용 %d원이 차감될 예정입니다.\n", upgradeCost);
        break;
    case 2:
        printf("[2] 무기판매 비용 %d원을 획득할 예정입니다.\n", sellPrice);
        break;
    case 3:
        printf("[3] 현재 보유중인 자금 %d원과 무기레벨 + %d가 저장되고 게임이 종료됩니다.\n", total_money, weapon_level);
        break;
    case 4:
        printf("[4] 현재 보유중인 자금 %d원과 무기레벨 + %d가 저장되고 게임이 이어서 진행됩니다.\n", total_money, weapon_level);
        break;
    default:
        printf("선택 번호에 대한 설명이 없습니다.\n");
    }
}

// 강화 실패 후 레벨 유지 시 비용의 50%를 반환
int calculateFailureCost(int level)
{
    int sellPrice = calculateSellPrice(level);
    return sellPrice / 2;
}

// 플레이어 정보 저장
void savePlayerInfo(int total_money, int weapon_level)
{
    FILE* file = fopen("Player_info.txt", "w");

    if (file == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    fprintf(file, "보유자금 : %d\n무기 레벨 : %d", total_money, weapon_level);

    fclose(file);
}

// 플레리어 정보 불러오기
void loadPlayerInfo(int* total_money, int* weapon_level)
{
    FILE* file = fopen("Player_info.txt", "r");

    if (file == NULL)
    {
        // 파일이 없을 경우 초기값으로 설정
        *total_money = Initial_Money;
        *weapon_level = 0;
        return;
    }

    fscanf(file, "보유자금 : %d\n무기 레벨 : %d", total_money, weapon_level);

    fclose(file);
}
#pragma endregion

// HARD MODE
#pragma region HARD MODE
#define MAX_PROBABILITY_HARD 100.0f              // 성공확률 최대치
#define Initial_Money_HARD 10000                 // 초기 자금 설정

// 보유 자금을 초기 자금으로 설정
int total_money_HARD = Initial_Money_HARD;

typedef struct
{
    int isTry_HARD;                   // 강화를 할 것인지 선택
    int level_HARD;                   // 현재 무기의 레벨
    float success_rate_HARD;          // 현재 강화 성공확률
    int randNum_HARD;                 // 랜덤값을 저장할 변수
} Weapon_HARD;

// ANSI 이스케이프 코드를 사용하여 텍스트의 색상을 바꾸는 함수
void changeTextColor_HARD(int color_HARD)
{
    printf("\033[38;5;%dm", color_HARD);
}

// ANSI 이스케이프 코드를 사용하여 텍스트의 색상을 리셋하는 함수
void resetTextColor_HARD()
{
    printf("\033[0m");
}

// 강화 게이지바
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

// 난이도 선택 후 스크린
void printdifficultyScreen_HARD()
{
    system("@cls||clear");
    changeTextColor_HARD(208);
    printf("┌───────────────────────────────┐\n");
    printf("♥ HARD MODE 를 선택하셨습니다 ! ♥\n");
    printf("└───────────────────────────────┘\n");
    resetTextColor_HARD();
}

// 타이틀 화면 스크린, 난이도 화면 스크린
void printtitleScrren_HARD()
{
    changeTextColor_HARD(33);
    printf("┌────────────────────────┐\t");
    resetTextColor_HARD();
    changeTextColor_HARD(5);
    printf("┌───────────┐\n");
    resetTextColor_HARD();
    changeTextColor_HARD(33);
    printf("● Project A Game Start ! ●\t");
    resetTextColor_HARD();
    changeTextColor_HARD(5);
    printf("♣ HARD MODE ♣\n");
    resetTextColor_HARD();
    changeTextColor_HARD(33);
    printf("└────────────────────────┘\t");
    resetTextColor_HARD();
    changeTextColor_HARD(5);
    printf("└───────────┘\n\n");
    resetTextColor_HARD();
}

// 강화 성공 스크린
void printSuccessScreen_HARD(int level_HARD)
{
    changeTextColor_HARD(48);
    printf("★☆★☆★☆ SUCCESS ☆★☆★☆★\n");
    printf("☆                   ☆\n");
    if (level_HARD + 1 <= 9)
    {
        printf("★   + %d  ->  + %d    ★\n", level_HARD, level_HARD + 1);
    }
    else if (level_HARD + 1 == 10)
    {
        printf("★   + %d  ->  + %d   ★\n", level_HARD, level_HARD + 1);
    }
    else if (level_HARD + 1 <= 12)
    {
        printf("★   + %d  ->  + %d  ★\n", level_HARD, level_HARD + 1);
    }
    printf("☆                   ☆\n");
    printf("★☆★☆★☆ SUCCESS ☆★☆★☆★\n");
    resetTextColor_HARD();
}

// 강화 실패 스크린
void printFailedScreen_HARD(int level_HARD)
{
    changeTextColor_HARD(196);
    printf("★☆★☆★☆ Failed ☆★☆★☆★\n");
    printf("☆                  ☆\n");
    if (level_HARD <= 9)
    {
        printf("★   + %d  ->  + 0   ★\n", level_HARD);
    }
    else if (level_HARD <= 12)
    {
        printf("★   + %d  ->  + 0  ★\n", level_HARD);
    }
    printf("☆                  ☆\n");
    printf("★☆★☆★☆ Failed ☆★☆★☆★\n");
    resetTextColor_HARD();
}

// 12레벨 달성 스크린
void printLevelTwelve_HARD(int weapon_level_HARD, int sellPrice_HARD)
{
    printf("\n축하합니다! 최종 무기 Lv.12에 달성하셨습니다.\n");
    printf("+ %d 무기는 자동적으로 판매됩니다.\n", weapon_level_HARD);
    printf("판매 금액은 %d원 입니다.\n\n", sellPrice_HARD);
    printf("곧 업데이트 될 보유자금은 %d원 입니다.\n\n", total_money_HARD + sellPrice_HARD);
}

// 게임 클리어 스크린
void printGameClear_HARD()
{
    changeTextColor_HARD(3);
    printf("\n★ Game Clear ★\n");
    printf("보유자금 200000원 이상으로 게임을 종료합니다.\n");
    resetTextColor_HARD();
}

// 미니게임으로 클리어 할 경우 스크린
void printMiniGameClear_HARD()
{
    changeTextColor_HARD(3);
    printf("\n★ Mini Game Clear ★\n");
    printf("미니게임 클리어로 게임을 종료합니다.\n");
    resetTextColor_HARD();
}

// 게임 실패 스크린
void printGameFailed_HARD()
{
    changeTextColor_HARD(3);
    printf("\n★ Game Failed ★\n");
    printf("보유자금 0원 이하로 게임을 종료합니다.\n");
    resetTextColor_HARD();
}

// 시작 시 정보 불러온 뒤 무기 레벨이 있다면 자동 판매 함수
void AutoInfosellScreen_HARD(Weapon weapon, Weapon_HARD weapon_HARD, int level_HARD, int sellPrice_HARD, int total_money_HARD, int retTime)
{
    if (weapon_HARD.level_HARD > 0)
    {
        changeTextColor_HARD(122);
        printf("┌──────────────────────────────────────────┐\n");
        if (weapon_HARD.level_HARD <= 9)
        {
            printf("│현재 보유중인 + %d 무기는 자동 판매됩니다. │\n", weapon_HARD.level_HARD);
        }
        else if (weapon_HARD.level_HARD <= 12)
        {
            printf("│현재 보유중인 + %d 무기는 자동 판매됩니다.│\n", weapon_HARD.level_HARD);
        }
        printf("└──────────────────────────────────────────┘\n");
        resetTextColor_HARD();
        printf("\n무기 판매중..\n\n");

        // 무기 판매 가격 계산
        int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
        printf("+ %d 무기 판매로 %d원을 획득합니다.\n\n", weapon_HARD.level_HARD, sellPrice_HARD);
        printf("곧 업데이트 될 보유자금은 %d원 입니다.\n", total_money_HARD + sellPrice_HARD);

        // 강화 프로그래스바 (지정된 시간(초) 만큼 대기)
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

// 강화 성공 확률 계산
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
    case 12: return 0.0f;  // Lv.12에서의 확률은 0% (최종 무기 레벨)
    }
}

// 강화 비용 계산
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

// 무기 판매 가격 계산
int calculateSellPrice_HARD(int level_HARD)
{
    switch (level_HARD)
    {
    case 0: return 0;
    case 1: return 100; // case 0 까지 강화 비용 더한 값에 대한 밸런스 [50]
    case 2: return 200; // case 0 ~ 1까지 강화 비용 더한 값에 대한 밸런스 [50]
    case 3: return 500; // case 0 ~ 2까지 강화 비용 더한 값에 대한 밸런스 [250]
    case 4: return 1000; // case 0 ~ 3까지 강화 비용 더한 값에 대한 밸런스 [750]
    case 5: return 2000; // case 0 ~ 4까지 강화 비용 더한 값에 대한 밸런스 [1550]
    case 6: return 3500; // case 0 ~ 5까지 강화 비용 더한 값에 대한 밸런스 [2550]
    case 7: return 5000; // case 0 ~ 6까지 강화 비용 더한 값에 대한 밸런스 [4050]
    case 8: return 10000; // case 0 ~ 7까지 강화 비용 더한 값에 대한 밸런스 [6050]
    case 9: return 13000; // case 0 ~ 8까지 강화 비용 더한 값에 대한 밸런스 [10050]
    case 10: return 22000; // case 0 ~ 9까지 강화 비용 더한 값에 대한 밸런스 [18050]
    case 11: return 50000; // case 0 ~ 10까지 강화 비용 더한 값에 대한 밸런스 [30050]
    case 12: return 75000; // case 0 ~ 11까지 강화 비용 더한 값에 대한 밸런스 [45050]
    default: return 0;
    }
}

// 선택 번호에 따른 설명 출력 함수
void printExplanation_HARD(int choice_HARD, int upgradeCost_HARD, int sellPrice_HARD, int total_money_HARD, int weapon_level_HARD)
{
    switch (choice_HARD)
    {
    case 1:
        printf("[1] 강화비용 %d원이 차감될 예정입니다.\n", upgradeCost_HARD);
        break;
    case 2:
        printf("[2] 무기판매 비용 %d원을 획득할 예정입니다.\n", sellPrice_HARD);
        break;
    case 3:
        printf("[3] 현재 보유중인 자금 %d원과 무기레벨 + %d가 저장되고 게임이 종료됩니다.\n", total_money_HARD, weapon_level_HARD);
        break;
    case 4:
        printf("[4] 현재 보유중인 자금 %d원과 무기레벨 + %d가 저장되고 게임이 이어서 진행됩니다.\n", total_money_HARD, weapon_level_HARD);
        break;
    default:
        printf("선택 번호에 대한 설명이 없습니다.\n");
    }
}

// 강화 실패 후 레벨 유지 시 비용의 50%를 반환
int calculateFailureCost_HARD(int level_HARD)
{
    int sellPrice = calculateSellPrice(level_HARD);
    return sellPrice / 2;
}

// 플레이어 정보 저장
void savePlayerInfo_HARD(int total_money_HARD, int weapon_level_HARD)
{
    FILE* file = fopen("Player_info_HARD.txt", "w");

    if (file == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    fprintf(file, "보유자금 : %d\n무기 레벨 : %d", total_money_HARD, weapon_level_HARD);

    fclose(file);
}

// 플레이어 정보 불러오기
void loadPlayerInfo_HARD(int* total_money_HARD, int* weapon_level_HARD)
{
    FILE* file = fopen("Player_info_HARD.txt", "r");

    if (file == NULL)
    {
        // 파일이 없을 경우 초기값으로 설정
        *total_money_HARD = Initial_Money_HARD;
        *weapon_level_HARD = 0;
        return;
    }

    fscanf(file, "보유자금 : %d\n무기 레벨 : %d", total_money_HARD, weapon_level_HARD);

    fclose(file);
}
#pragma endregion

// MINI GAME [EASY]
#pragma region MINI GAME [EASY]
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

// 커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

// 공룡을 그리는 함수
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

// 나무를 그리는 함수
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

// 충돌 했을때 게임오버 그려줌
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

// 충돌했으면 1을 반환, 아니면 0을 반환
int isCollision(const int treeX, const int dinoY)
{
    // 트리의 X가 공룡의 몸체쪽에 있을때,
    // 공룡의 높이가 충분하지 않다면 충돌로 처리
    GotoXY(0, 0);
    printf("treeX : %d, dinoY : %d", treeX, dinoY); // 이런식으로 적절한 X, Y를 찾습니다.
    if (treeX <= 8 && treeX >= 4 &&
        dinoY > 8)
    {
        return 1;
    }
    return 0;
}

// 게임 구동 함수
int MiniGame(Weapon weapon, int level, int sellPrice, int total_money)
{
    // 게임 시작시 초기화
    int isJumping = 0;
    int isBottom = 1;
    const int gravity = 3;

    int dinoY = DINO_BOTTOM_Y;
    int treeX = TREE_BOTTOM_X;

    int score = 0;
    clock_t start, curr;    // 점수 변수 초기화
    start = clock();        // 시작시간 초기화

    while (1) // 한 판에 대한 루프
    {
        // 충돌체크 트리의 x값과 공룡의 y값으로 판단
        if (isCollision(treeX, dinoY))
        {
            DrawGameOver(score);
            break; // 게임 종료
        }

        // z키가 눌렸고, 바닥이 아닐때 점프
        if (GetKeyDown() == ' ' && isBottom) // 현재 키 [Space bar]
        {
            isJumping = 1;
            isBottom = 0;
        }

        // 점프중이라면 Y를 감소, 점프가 끝났으면 Y를 증가.
        if (isJumping)
        {
            dinoY -= gravity;
        }
        else
        {
            dinoY += gravity;
        }

        // Y가 계속해서 증가하는걸 막기위해 바닥을 지정.
        if (dinoY >= DINO_BOTTOM_Y)
        {
            dinoY = DINO_BOTTOM_Y;
            isBottom = 1;
        }

        // 나무가 왼쪽으로 (x음수) 가도록하고
        // 나무의 위치가 왼쪽 끝으로가면 다시 오른쪽 끝으로 소환.
        treeX -= 2;
        if (treeX <= 0)
        {
            treeX = TREE_BOTTOM_X;
        }

        // 점프의 맨위를 찍으면 점프가 끝난 상황.
        if (dinoY <= 3)
        {
            isJumping = 0;
        }

        DrawDino(dinoY);        // draw dino
        DrawTree(treeX);        // draw Tree

        curr = clock();            // 현재시간 받아오기
        if (((curr - start) / CLOCKS_PER_SEC) >= 1)    // 1초가 넘었을때
        {
            score++;    // 스코어 UP
            start = clock();    // 시작시간 초기화
        }
        Sleep(60);
        system("@cls||clear");    //clear

        // 점수출력을 1초마다 해주는것이 아니라 항상 출력해주면서, 1초가 지났을때 ++
        GotoXY(22, 0);    // 커서를 가운데 위쪽으로 옮긴다. 콘솔창이 cols=100이므로 2*x이므로 22정도 넣어줌
        printf("Score : %d ", score);    // 점수 출력
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
        printf("미니게임 실패\n");
        printf("미니게임 실패로 + %d 무기는 자동판매되며, 게임이 이어서 진행됩니다.\n", weapon.level);
        int sellPrice = calculateSellPrice(weapon.level);
        printf("\n+ %d 무기 판매로 %d원을 획득합니다.\n\n", weapon.level, sellPrice);
        printf("곧 업데이트 될 보유자금은 %d원 입니다.\n", total_money + sellPrice);
        return 0;
    }
}

#pragma endregion

// MINI GAME [HARD]
#pragma region MINI GAME [HARD]
#define DINO_BOTTOM_Y_HARD 12
#define TREE_BOTTOM_Y_HARD 20
#define TREE_BOTTOM_X_HARD 45

// 커서의 위치를 x, y로 이동하는 함수
void GotoXY_HARD(int x, int y)
{
    COORD PosH;
    PosH.X = 2 * x;
    PosH.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), PosH);
}

// 키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown_HARD()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

// 공룡을 그리는 함수
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

// 나무를 그리는 함수
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

// 충돌 했을때 게임오버 그려줌
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

// 충돌했으면 1을 반환, 아니면 0을 반환
int isCollision_HARD(const int treeX_HARD, const int dinoY_HARD)
{
    // 트리의 X가 공룡의 몸체쪽에 있을때,
    // 공룡의 높이가 충분하지 않다면 충돌로 처리
    GotoXY_HARD(0, 0);
    printf("treeX : %d, dinoY : %d", treeX_HARD, dinoY_HARD); // 이런식으로 적절한 X, Y를 찾습니다.
    if (treeX_HARD <= 8 && treeX_HARD >= 4 &&
        dinoY_HARD > 8)
    {
        return 1;
    }
    return 0;
}

// 게임 구동 함수
int MiniGame_HARD(Weapon_HARD weapon_HARD, int level_HARD, int sellPrice_HARD, int total_money_HARD)
{
    // 게임 시작시 초기화
    int isJumping_HARD = 0;
    int isBottom_HARD = 1;
    const int gravity_HARD = 3;

    int dinoY_HARD = DINO_BOTTOM_Y_HARD;
    int treeX_HARD = TREE_BOTTOM_X_HARD;

    int score_HARD = 0;
    clock_t start_HARD, curr_HARD;    // 점수 변수 초기화
    start_HARD = clock();        // 시작시간 초기화

    while (1) // 한 판에 대한 루프
    {
        // 충돌체크 트리의 x값과 공룡의 y값으로 판단
        if (isCollision_HARD(treeX_HARD, dinoY_HARD))
        {
            DrawGameOver_HARD(score_HARD);
            break; // 게임 종료
        }

        // z키가 눌렸고, 바닥이 아닐때 점프
        if (GetKeyDown_HARD() == ' ' && isBottom_HARD) // 현재 키 [Space bar]
        {
            isJumping_HARD = 1;
            isBottom_HARD = 0;
        }

        // 점프중이라면 Y를 감소, 점프가 끝났으면 Y를 증가.
        if (isJumping_HARD)
        {
            dinoY_HARD -= gravity_HARD;
        }
        else
        {
            dinoY_HARD += gravity_HARD;
        }

        // Y가 계속해서 증가하는걸 막기위해 바닥을 지정.
        if (dinoY_HARD >= DINO_BOTTOM_Y_HARD)
        {
            dinoY_HARD = DINO_BOTTOM_Y_HARD;
            isBottom_HARD = 1;
        }

        // 나무가 왼쪽으로 (x음수) 가도록하고
        // 나무의 위치가 왼쪽 끝으로가면 다시 오른쪽 끝으로 소환.
        treeX_HARD -= 2;
        if (treeX_HARD <= 0)
        {
            treeX_HARD = TREE_BOTTOM_X;
        }

        // 점프의 맨위를 찍으면 점프가 끝난 상황.
        if (dinoY_HARD <= 3)
        {
            isJumping_HARD = 0;
        }

        DrawDino_HARD(dinoY_HARD);        // draw dino
        DrawTree_HARD(treeX_HARD);        // draw Tree

        curr_HARD = clock();            // 현재시간 받아오기
        if (((curr_HARD - start_HARD) / CLOCKS_PER_SEC) >= 1)    // 1초가 넘었을때
        {
            score_HARD++;    // 스코어 UP
            start_HARD = clock();    // 시작시간 초기화
        }
        Sleep(60);
        system("@cls||clear");    //clear

        // 점수출력을 1초마다 해주는것이 아니라 항상 출력해주면서, 1초가 지났을때 ++
        GotoXY_HARD(22, 0);    // 커서를 가운데 위쪽으로 옮긴다. 콘솔창이 cols=100이므로 2*x이므로 22정도 넣어줌
        printf("Score : %d ", score_HARD);    // 점수 출력
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
        printf("미니게임 실패\n");
        printf("미니게임 실패로 + %d 무기는 자동판매되며, 게임이 이어서 진행됩니다.\n", weapon_HARD.level_HARD);
        int sellPrice_HARD = calculateSellPrice_HARD(weapon_HARD.level_HARD);
        printf("\n+ %d 무기 판매로 %d원을 획득합니다.\n\n", weapon_HARD.level_HARD, sellPrice_HARD);
        printf("곧 업데이트 될 보유자금은 %d원 입니다.\n", total_money_HARD + sellPrice_HARD);
        return 0;
    }
}
#pragma endregion

#endif  // Project A.h