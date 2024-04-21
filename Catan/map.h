#pragma once
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "catan.h"
#define brick_color "\x1b[48;5;209m"
#define lumber_color "\x1b[48;5;136m"
#define ore_color "\x1b[48;5;249m"
#define grain_color "\x1b[48;5;220m"
#define wool_color "\x1b[48;5;46m"
#define player1_color "\x1b[38;5;1m"
#define player2_color "\x1b[38;5;4m"
#define player3_color "\x1b[38;5;127m"
#define player4_color "\x1b[38;5;208m" // change color
#define sea_color "\x1b[48;5;63m"
#define color_end "\x1b[0;m"

// 印出地圖
void print_map(mapStruct *map, int32_t total_player);

// 印出地圖需要的其他函式
void print_top(mapStruct map);
void print_bottom(mapStruct map);
void print_second_floor(mapStruct map);
void print_middle(mapStruct map);
void print_forth_floor(mapStruct map);
void print_single_house(int32_t kind_of_house);
void print_single_road(int32_t left, int32_t who_own);

// 建立地圖
// 隨機決定資源位置和數字位置
void generate_map(mapStruct *map_Catan);

// 配合建立地圖
void map_initialize(mapStruct *map, int32_t number, int32_t resource_R, int32_t index);

// 印出簡單地圖(編號0~18的板塊)
// 用來給玩家選擇蓋哪個位置
void map_for_choose();

// type:邊(0)或腳(1)  hex: 板塊編號  index:角位
void sync_map(int32_t type, int32_t hex, int32_t index, mapStruct *map);