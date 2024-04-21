#pragma once

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 54

//0:磚塊  1:樹木  2:岩石  3:稻米  4:羊毛

#ifndef CHARACTER
#define CHARACTER
typedef struct _characterStruct
{
    // 點數相關
    int32_t victory_point;
    int32_t road_length;
    int32_t used_road;    //15
    int32_t used_knight;
    int32_t used_development_card;
    int32_t get_rob;
    int32_t settlement;   //5
    int32_t city;         //4
    // 資源
    int32_t brick;  // 磚頭
    int32_t lumber; // 樹木
    int32_t ore;    // 岩石
    int32_t grain;  // 稻米
    int32_t wool;   // 羊毛
    // 發展卡
    int32_t knight_card;       // 14
    int32_t roadbuilding_card; // 2
    int32_t year_of_plenty;    // 2
    int32_t monopoly;          // 2
    int32_t victory_card;      // 5
    // 港口
    int32_t port[7];
    //最大騎士卡
    int32_t max_knight_card;
    int32_t max_road_card;
} characterStruct;
#endif

#ifndef MAP
#define MAP
typedef struct _mapStruct
{
    // int32_t seat_number;
    int32_t roll_dice_number;
    int32_t corner[6]; // 從左上角開始為陣列0，順時針到5(0: 無人持有，1~4: 1~4玩家持有房子，6~9: 1~4玩家持有城市)
    int32_t side[6];   // 從頂部為陣列0，順時針到5(0: 無人持有，1~4: 1~4玩家持有)
    int32_t robber;    // 有無robber
    int32_t resourse;  // 此板塊的資源類型
    int32_t port[6];   // 同corner位置(0: 無, 1: 3換1, 2: 2換1)
} mapStruct;
#endif

#ifndef BANK
#define BANK
typedef struct _bankStruct
{
    int32_t brick;
    int32_t lumber;
    int32_t ore;
    int32_t grain;
    int32_t wool;
    int32_t knight_card;
    int32_t roadbuilding_card;
    int32_t year_of_plenty;
    int32_t monopoly;
    int32_t victory_card;
} bankStruct;
#endif

//玩家初始化
//要先取得幾位玩家參與，並給予空間
// 使用函式把數據清成0
void player_initialize(characterStruct *player);

//擲骰子
//隨機擲骰子，若骰到七要執行robber
void roll_dice(characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map, bankStruct *bank);

//使用發展卡
//0:不使用  1:使用騎士卡  2:使用豐收之年卡  3:使用道路建造卡  4:使用壟斷市場卡
int32_t use_development_card(characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map, mapStruct *player_build, bankStruct *bank);

//挑選手牌的資源
void choose_card(int32_t resource[], int32_t player_number, int32_t choose_num, characterStruct *player);
 
//判斷手卡是否滿足要求的數量
//若滿足return 1，不滿足return 0
int32_t judge_card(characterStruct *player, int32_t resource[]);

/*
//整個交易系統
//挑選交易的卡牌(自己加對方(使用choose card和judge card))，詢問對方意願，是否討價還價，最後決定跟誰交換
void trade(characterStruct *p1, characterStruct *p2, int type, int amount) ;
*/
 
//執行robber
//檢查玩家手卡、移動robber、抽資源
void robber(characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map, bankStruct *bank);
    
//使用騎士卡
void use_knight_card(characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map);

//使用豐收之年卡
void use_year_of_plenty_card(characterStruct *player, int32_t player_number, bankStruct *bank);
 
//使用道路建造卡
void use_road_building_card(mapStruct* map, characterStruct *player, int32_t player_number, mapStruct *player_build, int32_t total_player);
 
//使用壟斷市場卡
void use_monopoly_card(characterStruct *player, int32_t player_number, int32_t total_player);
 
//建造
//決定是否建造路、村莊、升級成城市、抽發展卡
void build(mapStruct *mapCatan, mapStruct *player_build, int32_t player_number, characterStruct *player, bankStruct *bank, int32_t total_player);

//判斷是否有人滿足獲勝條件
//是return 1，否return 0
int win(characterStruct *players, int32_t player_number);

//將當格資源給附近玩家
void give_resource_card( mapStruct *map , int32_t dice_number, characterStruct *player, bankStruct *bank);

//印出玩家資訊
void print_player_info( characterStruct *player, int32_t total_player);

//跟銀行交易
void bank_trade(characterStruct *player, int32_t player_number, mapStruct *map, bankStruct *bank);

void is_buildable(mapStruct *map_Catan, mapStruct *player, int32_t player_number);

void all_settlement_buildable(mapStruct *player);

void all_unbuildable(mapStruct *player);

void shuffleArray(int arr[], int size);

void buy_development_card ( characterStruct *player, int32_t player_number, int32_t index, int32_t card[25], bankStruct *bank, int32_t total_player );

void bank_initialize(bankStruct *bank);

void print_bank_info(bankStruct *bank);

int32_t computer_choice ( characterStruct *player, int32_t player_number, int32_t flag[7] );

void computer_build(mapStruct *mapCatan, mapStruct *player_build, int32_t player_number, characterStruct *player, bankStruct *bank, int32_t type, int32_t total_player);

void player_trade(characterStruct *player, int32_t player_number, int32_t total_player);

void dfs(int currentVertex, int currentPath, int player_number);

int32_t whose_road_length( mapStruct *map ,int32_t player_number );

void is_longest_road( characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map);

void initializeGraphAndNodeValues( mapStruct *map_Catan );

void game_start_build(mapStruct *map_Catan, mapStruct *player1_build, mapStruct *player2_build, mapStruct *player3_build, mapStruct *player4_build, characterStruct *player1, characterStruct *player2, characterStruct *player3, characterStruct *player4, int32_t total_player, characterStruct *player);

void one_point_roadbuildable(mapStruct *player_build, int32_t hex, int32_t index, int32_t player_number);

void ending_info(characterStruct *player, int32_t total_player);