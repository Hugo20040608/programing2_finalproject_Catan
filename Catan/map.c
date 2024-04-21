#include "map.h"

// 印出地圖
// new code by hugo
void print_map(mapStruct *map, int32_t total_player)
{
    // the sea
    printf(sea_color "                                                " color_end "  " brick_color "  " color_end " : brick\n");
    printf(sea_color "                                                " color_end "\n");
    // the -1 row
    printf(sea_color "                      3：1                      " color_end "  " lumber_color "  " color_end " : lumber\n");
    // the 0 row
    printf(sea_color "                      /  \\                      " color_end "\n");
    // 1st row
    printf(sea_color "                     " color_end);
    print_top(map[0]);
    printf(sea_color "                     " color_end);
    printf("  " ore_color "  " color_end " : ore\n");
    // 2nd row
    printf(sea_color "                    " color_end);
    print_second_floor(map[0]);
    printf(sea_color "                    " color_end);
    printf("\n");
    // 3rd row
    printf(sea_color "        " lumber_color "2:1" sea_color " --" color_end);
    print_top(map[1]);
    print_middle(map[0]);
    print_top(map[2]);
    printf(sea_color "-- " grain_color "2:1" sea_color "        " color_end "  " grain_color "  " color_end " : grain\n");
    // 4th row
    printf(sea_color "           \\ " color_end);
    print_second_floor(map[1]);
    print_forth_floor(map[0]);
    print_second_floor(map[2]);
    printf(sea_color " /           " color_end "\n");
    // 5th row
    printf(sea_color "       " color_end);
    print_top(map[3]);
    print_middle(map[1]);
    print_top(map[4]);
    print_middle(map[2]);
    print_top(map[5]);
    printf(sea_color "       " color_end);
    printf("  " wool_color "  " color_end " : wool\n");
    // 6th row
    printf(sea_color "      " color_end);
    print_second_floor(map[3]);
    print_forth_floor(map[1]);
    print_second_floor(map[4]);
    print_forth_floor(map[2]);
    print_second_floor(map[5]);
    printf(sea_color "      " color_end);
    printf("\n");
    // 7th row
    printf(sea_color "     " color_end);
    print_single_house(map[3].corner[5]);
    print_middle(map[3]);
    print_top(map[6]);
    print_middle(map[4]);
    print_top(map[7]);
    print_middle(map[5]);
    print_single_house(map[5].corner[2]);
    printf(sea_color "     " color_end);
    printf("\n");
    // 8th row
    printf(sea_color "      " color_end);
    print_single_road(1, map[3].side[4]);
    print_forth_floor(map[3]);
    print_second_floor(map[6]);
    print_forth_floor(map[4]);
    print_second_floor(map[7]);
    print_forth_floor(map[5]);
    print_single_road(0, map[5].side[2]);
    printf(sea_color "      " color_end);
    printf("\n");
    // 9th row
    printf(sea_color " " brick_color "2:1" sea_color " --" color_end);
    print_top(map[8]);
    print_middle(map[6]);
    print_top(map[9]);
    print_middle(map[7]);
    print_top(map[10]);
    printf(sea_color "-- " ore_color "2:1" sea_color " " color_end "  \x1b[48;5;1m  " color_end " : player0\n");
    // 10th row
    printf(sea_color "    \\ " color_end);
    print_second_floor(map[8]);
    print_forth_floor(map[6]);
    print_second_floor(map[9]);
    print_forth_floor(map[7]);
    print_second_floor(map[10]);
    printf(sea_color " /    " color_end "\n");
    // 11th row
    printf(sea_color "     " color_end);
    print_single_house(map[8].corner[5]);
    print_middle(map[8]);
    print_top(map[11]);
    print_middle(map[9]);
    print_top(map[12]);
    print_middle(map[10]);
    print_single_house(map[10].corner[2]);
    printf(sea_color "     " color_end);
    printf("  \x1b[48;5;4m  " color_end " : player1\n");
    // 12th row
    printf(sea_color "      " color_end);
    print_single_road(1, map[8].side[4]);
    print_forth_floor(map[8]);
    print_second_floor(map[11]);
    print_forth_floor(map[9]);
    print_second_floor(map[12]);
    print_forth_floor(map[10]);
    print_single_road(0, map[10].side[2]);
    printf(sea_color "      " color_end);
    printf("\n");
    // 13th row
    printf(sea_color "       " color_end);
    print_top(map[13]);
    print_middle(map[11]);
    print_top(map[14]);
    print_middle(map[12]);
    print_top(map[15]);
    printf(sea_color "       " color_end);
    printf("  \x1b[48;5;127m  " color_end " : player2\n");
    // 14th row
    printf(sea_color "      " color_end);
    print_second_floor(map[13]);
    print_forth_floor(map[11]);
    print_second_floor(map[14]);
    print_forth_floor(map[12]);
    print_second_floor(map[15]);
    printf(sea_color "      " color_end);
    printf("\n");
    // 15th row
    printf(sea_color "     " color_end);
    print_single_house(map[13].corner[5]);
    print_middle(map[13]);
    print_top(map[16]);
    print_middle(map[14]);
    print_top(map[17]);
    print_middle(map[15]);
    print_single_house(map[15].corner[2]);
    printf(sea_color "     " color_end);
    if (total_player == 3)
    {
        printf("\n");
    }
    else if (total_player == 4)
    {
        printf("  \x1b[48;5;208m  " color_end " : player3\n");
    }
    // 16th row
    printf(sea_color "    / " color_end);
    print_single_road(1, map[13].side[4]);
    print_forth_floor(map[13]);
    print_second_floor(map[16]);
    print_forth_floor(map[14]);
    print_second_floor(map[17]);
    print_forth_floor(map[15]);
    print_single_road(0, map[15].side[2]);
    printf(sea_color " \\    " color_end "\n");
    // 17th row
    printf(sea_color " 3:1 --" color_end);
    print_bottom(map[13]);
    print_middle(map[16]);
    print_top(map[18]);
    print_middle(map[17]);
    print_bottom(map[15]);
    printf(sea_color "-- 3:1 " color_end "\n");
    // 18th row
    printf(sea_color "             " color_end);
    print_single_road(1, map[16].side[4]);
    print_forth_floor(map[16]);
    print_second_floor(map[18]);
    print_forth_floor(map[17]);
    print_single_road(0, map[17].side[2]);
    printf(sea_color "             " color_end);
    printf("\n");
    // 19th row
    printf(sea_color "              " color_end);
    print_bottom(map[16]);
    print_middle(map[18]);
    print_bottom(map[17]);
    printf(sea_color "              " color_end);
    printf("\n");
    // 20th row
    printf(sea_color "               \\  / " color_end);
    print_single_road(1, map[18].side[4]);
    print_forth_floor(map[18]);
    print_single_road(0, map[18].side[2]);
    printf(sea_color " \\  /               " color_end "\n");
    // 21st row
    printf(sea_color "               3:1   " color_end);
    print_bottom(map[18]);
    printf(sea_color "   " wool_color "2:1" sea_color "               " color_end "\n");
    // the sea
    printf(sea_color "                                                " color_end "\n");
    printf(sea_color "                                                " color_end "\n");

    return;
}
// new code by hugo end

// 印出地圖需要的其他函式
void print_top(mapStruct map)
{
    if (map.corner[0] == 0)
    {
        printf("#");
    }
    else if (map.corner[0] == 1)
    {
        printf(player1_color "#" color_end);
    }
    else if (map.corner[0] == 2)
    {
        printf(player2_color "#" color_end);
    }
    else if (map.corner[0] == 3)
    {
        printf(player3_color "#" color_end);
    }
    else if (map.corner[0] == 4)
    {
        printf(player4_color "#" color_end);
    }
    else if (map.corner[0] == 6)
    {
        printf(player1_color "$" color_end);
    }
    else if (map.corner[0] == 7)
    {
        printf(player2_color "$" color_end);
    }
    else if (map.corner[0] == 8)
    {
        printf(player3_color "$" color_end);
    }
    else if (map.corner[0] == 9)
    {
        printf(player4_color "$" color_end);
    }
    printf(" ");
    if (map.side[0] == 0)
    {
        printf("--");
    }
    else if (map.side[0] == 1)
    {
        printf(player1_color "--" color_end);
    }
    else if (map.side[0] == 2)
    {
        printf(player2_color "--" color_end);
    }
    else if (map.side[0] == 3)
    {
        printf(player3_color "--" color_end);
    }
    else if (map.side[0] == 4)
    {
        printf(player4_color "--" color_end);
    }
    printf(" ");
    if (map.corner[1] == 0)
    {
        printf("#");
    }
    else if (map.corner[1] == 1)
    {
        printf(player1_color "#" color_end);
    }
    else if (map.corner[1] == 2)
    {
        printf(player2_color "#" color_end);
    }
    else if (map.corner[1] == 3)
    {
        printf(player3_color "#" color_end);
    }
    else if (map.corner[1] == 4)
    {
        printf(player4_color "#" color_end);
    }
    else if (map.corner[1] == 6)
    {
        printf(player1_color "$" color_end);
    }
    else if (map.corner[1] == 7)
    {
        printf(player2_color "$" color_end);
    }
    else if (map.corner[1] == 8)
    {
        printf(player3_color "$" color_end);
    }
    else if (map.corner[1] == 9)
    {
        printf(player4_color "$" color_end);
    }

    return;
}

void print_bottom(mapStruct map)
{
    if (map.corner[4] == 0)
    {
        printf("#");
    }
    else if (map.corner[4] == 1)
    {
        printf(player1_color "#" color_end);
    }
    else if (map.corner[4] == 2)
    {
        printf(player2_color "#" color_end);
    }
    else if (map.corner[4] == 3)
    {
        printf(player3_color "#" color_end);
    }
    else if (map.corner[4] == 4)
    {
        printf(player4_color "#" color_end);
    }
    else if (map.corner[4] == 6)
    {
        printf(player1_color "$" color_end);
    }
    else if (map.corner[4] == 7)
    {
        printf(player2_color "$" color_end);
    }
    else if (map.corner[4] == 8)
    {
        printf(player3_color "$" color_end);
    }
    else if (map.corner[4] == 9)
    {
        printf(player4_color "$" color_end);
    }
    printf(" ");
    if (map.side[3] == 0)
    {
        printf("--");
    }
    else if (map.side[3] == 1)
    {
        printf(player1_color "--" color_end);
    }
    else if (map.side[3] == 2)
    {
        printf(player2_color "--" color_end);
    }
    else if (map.side[3] == 3)
    {
        printf(player3_color "--" color_end);
    }
    else if (map.side[3] == 4)
    {
        printf(player4_color "--" color_end);
    }
    printf(" ");
    if (map.corner[3] == 0)
    {
        printf("#");
    }
    else if (map.corner[3] == 1)
    {
        printf(player1_color "#" color_end);
    }
    else if (map.corner[3] == 2)
    {
        printf(player2_color "#" color_end);
    }
    else if (map.corner[3] == 3)
    {
        printf(player3_color "#" color_end);
    }
    else if (map.corner[3] == 4)
    {
        printf(player4_color "#" color_end);
    }
    else if (map.corner[3] == 6)
    {
        printf(player1_color "$" color_end);
    }
    else if (map.corner[3] == 7)
    {
        printf(player2_color "$" color_end);
    }
    else if (map.corner[3] == 8)
    {
        printf(player3_color "$" color_end);
    }
    else if (map.corner[3] == 9)
    {
        printf(player4_color "$" color_end);
    }

    return;
}

void print_second_floor(mapStruct map)
{
    if (map.side[5] == 0)
    {
        printf("/");
    }
    else if (map.side[5] == 1)
    {
        printf(player1_color "/" color_end);
    }
    else if (map.side[5] == 2)
    {
        printf(player2_color "/" color_end);
    }
    else if (map.side[5] == 3)
    {
        printf(player3_color "/" color_end);
    }
    else if (map.side[5] == 4)
    {
        printf(player4_color "/" color_end);
    }

    if (map.resourse == 0)
    {
        printf(brick_color "      " color_end);
    }
    else if (map.resourse == 1)
    {
        printf(lumber_color "      " color_end);
    }
    else if (map.resourse == 2)
    {
        printf(ore_color "      " color_end);
    }
    else if (map.resourse == 3)
    {
        printf(grain_color "      " color_end);
    }
    else if (map.resourse == 4)
    {
        printf(wool_color "      " color_end);
    }
    else if (map.resourse == 10)
    {
        printf("      ");
    }

    if (map.side[1] == 0)
    {
        printf("\\");
    }
    else if (map.side[1] == 1)
    {
        printf(player1_color "\\" color_end);
    }
    else if (map.side[1] == 2)
    {
        printf(player2_color "\\" color_end);
    }
    else if (map.side[1] == 3)
    {
        printf(player3_color "\\" color_end);
    }
    else if (map.side[1] == 4)
    {
        printf(player4_color "\\" color_end);
    }

    return;
}

void print_middle(mapStruct map)
{
    printf(" ");
    if (map.robber == 1)
    {
        if (map.resourse == 0)
        {
            printf(brick_color "robbed" color_end " ");
        }
        else if (map.resourse == 1)
        {
            printf(lumber_color "robbed" color_end " ");
        }
        else if (map.resourse == 2)
        {
            printf(ore_color "robbed" color_end " ");
        }
        else if (map.resourse == 3)
        {
            printf(grain_color "robbed" color_end " ");
        }
        else if (map.resourse == 4)
        {
            printf(wool_color "robbed" color_end " ");
        }
        else
        {
            printf("robbed ");
        }
    }
    else
    {
        if (map.resourse == 0)
        {
            printf(brick_color "  ");
        }
        else if (map.resourse == 1)
        {
            printf(lumber_color "  ");
        }
        else if (map.resourse == 2)
        {
            printf(ore_color "  ");
        }
        else if (map.resourse == 3)
        {
            printf(grain_color "  ");
        }
        else if (map.resourse == 4)
        {
            printf(wool_color "  ");
        }
        else if (map.resourse == 10)
        {
            printf("  ");
        }

        if (map.roll_dice_number < 10)
        {
            if (map.roll_dice_number == 7)
            {
                printf("     ");
            }
            else
            {
                printf("0%d", map.roll_dice_number);
            }
        }
        else
        {
            printf("%d", map.roll_dice_number);
        }

        if (map.roll_dice_number != 7)
        {
            printf("  " color_end " ");
        }
    }

    return;
}

void print_forth_floor(mapStruct map)
{
    if (map.resourse == 0)
    {
        printf(brick_color "      " color_end);
    }
    else if (map.resourse == 1)
    {
        printf(lumber_color "      " color_end);
    }
    else if (map.resourse == 2)
    {
        printf(ore_color "      " color_end);
    }
    else if (map.resourse == 3)
    {
        printf(grain_color "      " color_end);
    }
    else if (map.resourse == 4)
    {
        printf(wool_color "      " color_end);
    }
    else if (map.resourse == 10)
    {
        printf("      ");
    }
    return;
}

void print_single_house(int32_t kind_of_house)
{
    if (kind_of_house == 0)
    {
        printf("#");
    }
    else if (kind_of_house == 1)
    {
        printf(player1_color "#" color_end);
    }
    else if (kind_of_house == 2)
    {
        printf(player2_color "#" color_end);
    }
    else if (kind_of_house == 3)
    {
        printf(player3_color "#" color_end);
    }
    else if (kind_of_house == 4)
    {
        printf(player4_color "#" color_end);
    }
    else if (kind_of_house == 6)
    {
        printf(player1_color "$" color_end);
    }
    else if (kind_of_house == 7)
    {
        printf(player2_color "$" color_end);
    }
    else if (kind_of_house == 8)
    {
        printf(player3_color "$" color_end);
    }
    else if (kind_of_house == 9)
    {
        printf(player4_color "$" color_end);
    }

    return;
}

void print_single_road(int32_t left, int32_t who_own)
{
    // left==0: '/'  ;;;  left==1: '\'
    if (left == 0)
    {
        if (who_own == 0)
        {
            printf("/");
        }
        else if (who_own == 1)
        {
            printf(player1_color "/" color_end);
        }
        else if (who_own == 2)
        {
            printf(player2_color "/" color_end);
        }
        else if (who_own == 3)
        {
            printf(player3_color "/" color_end);
        }
        else if (who_own == 4)
        {
            printf(player4_color "/" color_end);
        }
    }
    else if (left == 1)
    {
        if (who_own == 0)
        {
            printf("\\");
        }
        else if (who_own == 1)
        {
            printf(player1_color "\\" color_end);
        }
        else if (who_own == 2)
        {
            printf(player2_color "\\" color_end);
        }
        else if (who_own == 3)
        {
            printf(player3_color "\\" color_end);
        }
        else if (who_own == 4)
        {
            printf(player4_color "\\" color_end);
        }
    }

    return;
}

// 建立地圖
// 隨機決定資源位置和數字位置
void generate_map(mapStruct *map_Catan)
{
    int32_t number_on_terrain[12] = {0};
    number_on_terrain[1] = 1;
    number_on_terrain[11] = 1;
    number_on_terrain[6] = 1;
    for (int32_t i = 2; i < 11; i++)
    {
        if (i != 6)
        {
            number_on_terrain[i] = 2;
        }
    }
    int32_t resourse_of_terrain[5] = {0};
    resourse_of_terrain[0] = 3;
    resourse_of_terrain[1] = 4;
    resourse_of_terrain[2] = 3;
    resourse_of_terrain[3] = 4;
    resourse_of_terrain[4] = 4;
    srand(time(NULL));
    for (int32_t i = 0; i < 19; i++)
    {
        int32_t tmp_number_on_terrain = 0;
        int32_t tmp_resourse_of_terrain = 0;
        while (1)
        {
            tmp_number_on_terrain = (rand() % 11) + 1;
            if (number_on_terrain[tmp_number_on_terrain] != 0)
            {
                number_on_terrain[tmp_number_on_terrain]--;
                break;
            }
        }
        if (tmp_number_on_terrain != 6)
        {
            while (1)
            {
                tmp_resourse_of_terrain = rand() % 5;
                if (resourse_of_terrain[tmp_resourse_of_terrain] != 0)
                {
                    resourse_of_terrain[tmp_resourse_of_terrain]--;
                    break;
                }
            }
        }
        map_initialize(&(map_Catan[i]), tmp_number_on_terrain + 1, tmp_resourse_of_terrain, i);
    }
    return;
}

// 配合建立地圖
// new map_initialize by hugo
void map_initialize(mapStruct *map, int32_t number, int32_t resource_R, int32_t index)
{
    map->roll_dice_number = number;

    for (int32_t j = 0; j < 6; j++)
    {
        map->corner[j] = 0;
    }
    for (int32_t j = 0; j < 6; j++)
    {
        map->side[j] = 0;
    }

    if (number == 7)
    {
        map->robber = 1;
        map->resourse = 10;
    }
    else
    {
        map->robber = 0;
        map->resourse = resource_R;
    }

    for (int32_t j = 0; j < 6; j++)
    {
        map->port[j] = 0;
    }
    if (index == 0)
    {
        map->port[0] = 6;
        map->port[1] = 6;
    }
    else if (index == 1)
    {
        map->port[0] = 2;
        map->port[5] = 2;
    }
    else if (index == 2)
    {
        map->port[1] = 4;
        map->port[2] = 4;
    }
    else if (index == 3)
    {
        map->port[1] = 2;
        map->port[4] = 1;
    }
    else if (index == 5)
    {
        map->port[0] = 4;
        map->port[3] = 3;
    }
    else if (index == 8)
    {
        map->port[0] = 1;
        map->port[5] = 1;
    }
    else if (index == 10)
    {
        map->port[1] = 3;
        map->port[2] = 3;
    }
    else if (index == 13)
    {
        map->port[4] = 6;
        map->port[5] = 6;
    }
    else if (index == 15)
    {
        map->port[2] = 6;
        map->port[3] = 6;
    }
    else if (index == 16)
    {
        map->port[3] = 6;
        map->port[4] = 6;
    }
    else if (index == 17)
    {
        map->port[3] = 5;
        map->port[4] = 5;
    }
    else if (index == 18)
    {
        map->port[2] = 5;
        map->port[5] = 6;
    }

    return;
}
// new map_initialize by hugo end

void map_for_choose()
{
    printf("                   # -- #\n");
    printf("                  /      \\\n");
    printf("            # -- #   00   # -- #\n");
    printf("           /      \\      /      \\\n");
    printf("     # -- #   01   # -- #   02   # -- #\n");
    printf("    /      \\      /      \\      /      \\\n");
    printf("   #   03   # -- #   04   # -- #   05   #\n");
    printf("    \\      /      \\      /      \\      /\n");
    printf("     # -- #   06   # -- #   07   # -- #\n");
    printf("    /      \\      /      \\      /      \\\n");
    printf("   #   08   # -- #   09   # -- #   10   #\n");
    printf("    \\      /      \\      /      \\      /\n");
    printf("     # -- #   11   # -- #   12   # -- #\n");
    printf("    /      \\      /      \\      /      \\\n");
    printf("   #   13   # -- #   14   # -- #   15   #\n");
    printf("    \\      /      \\      /      \\      /\n");
    printf("     # -- #   16   # -- #   17   # -- #\n");
    printf("           \\      /      \\      /\n");
    printf("            # -- #   18   # -- #\n");
    printf("                  \\      /\n");
    printf("                   # -- #\n\n");
    return;
}

// type:邊(0)或腳(1)  hex: 板塊編號  index:角位
void sync_map(int32_t type, int32_t hex, int32_t index, mapStruct *map)
{
    if (type == 0)
    {
        int32_t value = map[hex].side[index];

        if (hex == 0)
        {
            if (index == 2)
            {
                map[2].side[5] = value;
            }
            else if (index == 3)
            {
                map[4].side[0] = value;
            }
            else if (index == 4)
            {
                map[1].side[1] = value;
            }
        }
        else if (hex == 1)
        {
            if (index == 1)
            {
                map[0].side[4] = value;
            }
            else if (index == 2)
            {
                map[4].side[5] = value;
            }
            else if (index == 3)
            {
                map[6].side[0] = value;
            }
            else if (index == 4)
            {
                map[3].side[1] = value;
            }
        }
        else if (hex == 2)
        {
            if (index == 2)
            {
                map[5].side[5] = value;
            }
            else if (index == 3)
            {
                map[7].side[0] = value;
            }
            else if (index == 4)
            {
                map[4].side[1] = value;
            }
            else if (index == 5)
            {
                map[0].side[2] = value;
            }
        }
        else if (hex == 3)
        {
            if (index == 1)
            {
                map[1].side[4] = value;
            }
            else if (index == 2)
            {
                map[6].side[5] = value;
            }
            else if (index == 3)
            {
                map[8].side[0] = value;
            }
        }
        else if (hex == 4)
        {
            if (index == 0)
            {
                map[0].side[3] = value;
            }
            else if (index == 1)
            {
                map[2].side[4] = value;
            }
            else if (index == 2)
            {
                map[7].side[5] = value;
            }
            else if (index == 3)
            {
                map[9].side[0] = value;
            }
            else if (index == 4)
            {
                map[6].side[1] = value;
            }
            else
            {
                map[1].side[2] = value;
            }
        }
        else if (hex == 5)
        {
            if (index == 3)
            {
                map[10].side[0] = value;
            }
            else if (index == 4)
            {
                map[7].side[1] = value;
            }
            else if (index == 5)
            {
                map[2].side[2] = value;
            }
        }
        else if (hex == 6)
        {
            if (index == 0)
            {
                map[1].side[3] = value;
            }
            else if (index == 1)
            {
                map[4].side[4] = value;
            }
            else if (index == 2)
            {
                map[9].side[5] = value;
            }
            else if (index == 3)
            {
                map[11].side[0] = value;
            }
            else if (index == 4)
            {
                map[8].side[1] = value;
            }
            else
            {
                map[3].side[2] = value;
            }
        }
        else if (hex == 7)
        {
            if (index == 0)
            {
                map[2].side[3] = value;
            }
            else if (index == 1)
            {
                map[5].side[4] = value;
            }
            else if (index == 2)
            {
                map[10].side[5] = value;
            }
            else if (index == 3)
            {
                map[12].side[0] = value;
            }
            else if (index == 4)
            {
                map[9].side[1] = value;
            }
            else
            {
                map[4].side[2] = value;
            }
        }
        else if (hex == 8)
        {
            if (index == 0)
            {
                map[3].side[3] = value;
            }
            else if (index == 1)
            {
                map[6].side[4] = value;
            }
            else if (index == 2)
            {
                map[11].side[5] = value;
            }
            else if (index == 3)
            {
                map[13].side[0] = value;
            }
        }
        else if (hex == 9)
        {
            if (index == 0)
            {
                map[4].side[3] = value;
            }
            else if (index == 1)
            {
                map[7].side[4] = value;
            }
            else if (index == 2)
            {
                map[12].side[5] = value;
            }
            else if (index == 3)
            {
                map[14].side[0] = value;
            }
            else if (index == 4)
            {
                map[11].side[1] = value;
            }
            else
            {
                map[6].side[2] = value;
            }
        }
        else if (hex == 10)
        {
            if (index == 0)
            {
                map[5].side[3] = value;
            }
            else if (index == 3)
            {
                map[15].side[0] = value;
            }
            else if (index == 4)
            {
                map[12].side[1] = value;
            }
            else if (index == 5)
            {
                map[7].side[2] = value;
            }
        }
        else if (hex == 11)
        {
            if (index == 0)
            {
                map[6].side[3] = value;
            }
            else if (index == 1)
            {
                map[9].side[4] = value;
            }
            else if (index == 2)
            {
                map[14].side[5] = value;
            }
            else if (index == 3)
            {
                map[16].side[0] = value;
            }
            else if (index == 4)
            {
                map[13].side[1] = value;
            }
            else
            {
                map[8].side[2] = value;
            }
        }
        else if (hex == 12)
        {
            if (index == 0)
            {
                map[7].side[3] = value;
            }
            else if (index == 1)
            {
                map[10].side[4] = value;
            }
            else if (index == 2)
            {
                map[15].side[5] = value;
            }
            else if (index == 3)
            {
                map[17].side[0] = value;
            }
            else if (index == 4)
            {
                map[14].side[1] = value;
            }
            else
            {
                map[9].side[2] = value;
            }
        }
        else if (hex == 13)
        {
            if (index == 0)
            {
                map[8].side[3] = value;
            }
            else if (index == 1)
            {
                map[11].side[4] = value;
            }
            else if (index == 2)
            {
                map[16].side[5] = value;
            }
        }
        else if (hex == 14)
        {
            if (index == 0)
            {
                map[9].side[3] = value;
            }
            else if (index == 1)
            {
                map[12].side[4] = value;
            }
            else if (index == 2)
            {
                map[17].side[5] = value;
            }
            else if (index == 3)
            {
                map[18].side[0] = value;
            }
            else if (index == 4)
            {
                map[16].side[1] = value;
            }
            else
            {
                map[11].side[2] = value;
            }
        }
        else if (hex == 15)
        {
            if (index == 0)
            {
                map[10].side[3] = value;
            }
            else if (index == 4)
            {
                map[17].side[1] = value;
            }
            else if (index == 5)
            {
                map[12].side[2] = value;
            }
        }
        else if (hex == 16)
        {
            if (index == 0)
            {
                map[11].side[3] = value;
            }
            else if (index == 1)
            {
                map[14].side[4] = value;
            }
            else if (index == 2)
            {
                map[18].side[5] = value;
            }
            else if (index == 5)
            {
                map[13].side[2] = value;
            }
        }
        else if (hex == 17)
        {
            if (index == 0)
            {
                map[12].side[3] = value;
            }
            else if (index == 1)
            {
                map[15].side[4] = value;
            }
            else if (index == 4)
            {
                map[18].side[1] = value;
            }
            else if (index == 5)
            {
                map[14].side[2] = value;
            }
        }
        else if (hex == 18)
        {
            if (index == 0)
            {
                map[14].side[3] = value;
            }
            else if (index == 1)
            {
                map[17].side[4] = value;
            }
            else if (index == 5)
            {
                map[16].side[2] = value;
            }
        }
    }
    else
    {
        int32_t value = map[hex].corner[index];

        if (hex == 0)
        {
            if (index == 2)
            {
                map[2].corner[0] = value;
            }
            else if (index == 3)
            {
                map[2].corner[5] = value;
                map[4].corner[1] = value;
            }
            else if (index == 4)
            {
                map[4].corner[0] = value;
                map[1].corner[2] = value;
            }
            else if (index == 5)
            {
                map[1].corner[1] = value;
            }
        }
        else if (hex == 1)
        {
            if (index == 1)
            {
                map[0].corner[5] = value;
            }
            else if (index == 2)
            {
                map[0].corner[4] = value;
                map[4].corner[0] = value;
            }
            else if (index == 3)
            {
                map[4].corner[5] = value;
                map[6].corner[1] = value;
            }
            else if (index == 4)
            {
                map[6].corner[0] = value;
                map[3].corner[2] = value;
            }
            else if (index == 5)
            {
                map[3].corner[1] = value;
            }
        }
        else if (hex == 2)
        {
            if (index == 0)
            {
                map[0].corner[2] = value;
            }
            else if (index == 2)
            {
                map[5].corner[0] = value;
            }
            else if (index == 3)
            {
                map[5].corner[5] = value;
                map[7].corner[1] = value;
            }
            else if (index == 4)
            {
                map[7].corner[0] = value;
                map[4].corner[2] = value;
            }
            else if (index == 5)
            {
                map[4].corner[1] = value;
                map[0].corner[3] = value;
            }
        }
        else if (hex == 3)
        {
            if (index == 1)
            {
                map[1].corner[5] = value;
            }
            else if (index == 2)
            {
                map[1].corner[4] = value;
                map[6].corner[0] = value;
            }
            else if (index == 3)
            {
                map[6].corner[5] = value;
                map[8].corner[1] = value;
            }
            else if (index == 4)
            {
                map[8].corner[0] = value;
            }
        }
        else if (hex == 4)
        {
            if (index == 0)
            {
                map[0].corner[4] = value;
                map[1].corner[2] = value;
            }
            else if (index == 1)
            {
                map[0].corner[3] = value;
                map[2].corner[5] = value;
            }
            else if (index == 2)
            {
                map[2].corner[4] = value;
                map[7].corner[0] = value;
            }
            else if (index == 3)
            {
                map[7].corner[5] = value;
                map[9].corner[1] = value;
            }
            else if (index == 4)
            {
                map[9].corner[0] = value;
                map[6].corner[2] = value;
            }
            else if (index == 5)
            {
                map[6].corner[1] = value;
                map[1].corner[3] = value;
            }
        }
        else if (hex == 5)
        {
            if (index == 0)
            {
                map[2].corner[2] = value;
            }
            else if (index == 3)
            {
                map[10].corner[1] = value;
            }
            else if (index == 4)
            {
                map[10].corner[0] = value;
                map[7].corner[2] = value;
            }
            else if (index == 5)
            {
                map[7].corner[1] = value;
                map[2].corner[3] = value;
            }
        }
        else if (hex == 6)
        {
            if (index == 0)
            {
                map[1].corner[4] = value;
                map[3].corner[2] = value;
            }
            else if (index == 1)
            {
                map[1].corner[3] = value;
                map[4].corner[5] = value;
            }
            else if (index == 2)
            {
                map[4].corner[4] = value;
                map[9].corner[0] = value;
            }
            else if (index == 3)
            {
                map[9].corner[5] = value;
                map[11].corner[1] = value;
            }
            else if (index == 4)
            {
                map[11].corner[0] = value;
                map[8].corner[2] = value;
            }
            else if (index == 5)
            {
                map[8].corner[1] = value;
                map[3].corner[3] = value;
            }
        }
        else if (hex == 7)
        {
            if (index == 0)
            {
                map[2].corner[4] = value;
                map[4].corner[2] = value;
            }
            else if (index == 1)
            {
                map[2].corner[3] = value;
                map[5].corner[5] = value;
            }
            else if (index == 2)
            {
                map[5].corner[4] = value;
                map[10].corner[0] = value;
            }
            else if (index == 3)
            {
                map[10].corner[5] = value;
                map[12].corner[1] = value;
            }
            else if (index == 4)
            {
                map[12].corner[0] = value;
                map[9].corner[2] = value;
            }
            else if (index == 5)
            {
                map[9].corner[1] = value;
                map[4].corner[3] = value;
            }
        }
        else if (hex == 8)
        {
            if (index == 0)
            {
                map[3].corner[4] = value;
            }
            else if (index == 1)
            {
                map[3].corner[3] = value;
                map[6].corner[5] = value;
            }
            else if (index == 2)
            {
                map[6].corner[4] = value;
                map[11].corner[0] = value;
            }
            else if (index == 3)
            {
                map[11].corner[5] = value;
                map[13].corner[1] = value;
            }
            else if (index == 4)
            {
                map[13].corner[0] = value;
            }
        }
        else if (hex == 9)
        {
            if (index == 0)
            {
                map[4].corner[4] = value;
                map[6].corner[2] = value;
            }
            else if (index == 1)
            {
                map[4].corner[3] = value;
                map[7].corner[5] = value;
            }
            else if (index == 2)
            {
                map[7].corner[4] = value;
                map[12].corner[0] = value;
            }
            else if (index == 3)
            {
                map[12].corner[5] = value;
                map[14].corner[1] = value;
            }
            else if (index == 4)
            {
                map[14].corner[0] = value;
                map[11].corner[2] = value;
            }
            else if (index == 5)
            {
                map[11].corner[1] = value;
                map[6].corner[3] = value;
            }
        }
        else if (hex == 10)
        {
            if (index == 0)
            {
                map[5].corner[4] = value;
                map[7].corner[2] = value;
            }
            else if (index == 1)
            {
                map[5].corner[3] = value;
            }
            else if (index == 3)
            {
                map[15].corner[1] = value;
            }
            else if (index == 4)
            {
                map[15].corner[0] = value;
                map[12].corner[2] = value;
            }
            else if (index == 5)
            {
                map[12].corner[1] = value;
                map[7].corner[3] = value;
            }
        }
        else if (hex == 11)
        {
            if (index == 0)
            {
                map[6].corner[4] = value;
                map[8].corner[2] = value;
            }
            else if (index == 1)
            {
                map[6].corner[3] = value;
                map[9].corner[5] = value;
            }
            else if (index == 2)
            {
                map[9].corner[4] = value;
                map[14].corner[0] = value;
            }
            else if (index == 3)
            {
                map[14].corner[5] = value;
                map[16].corner[1] = value;
            }
            else if (index == 4)
            {
                map[16].corner[0] = value;
                map[13].corner[2] = value;
            }
            else if (index == 5)
            {
                map[13].corner[1] = value;
                map[8].corner[3] = value;
            }
        }
        else if (hex == 12)
        {
            if (index == 0)
            {
                map[7].corner[4] = value;
                map[9].corner[2] = value;
            }
            else if (index == 1)
            {
                map[7].corner[3] = value;
                map[10].corner[5] = value;
            }
            else if (index == 2)
            {
                map[10].corner[4] = value;
                map[15].corner[0] = value;
            }
            else if (index == 3)
            {
                map[15].corner[5] = value;
                map[17].corner[1] = value;
            }
            else if (index == 4)
            {
                map[17].corner[0] = value;
                map[14].corner[2] = value;
            }
            else if (index == 5)
            {
                map[14].corner[1] = value;
                map[9].corner[3] = value;
            }
        }
        else if (hex == 13)
        {
            if (index == 0)
            {
                map[8].corner[4] = value;
            }
            else if (index == 1)
            {
                map[8].corner[3] = value;
                map[11].corner[5] = value;
            }
            else if (index == 2)
            {
                map[11].corner[4] = value;
                map[16].corner[0] = value;
            }
            else if (index == 3)
            {
                map[16].corner[5] = value;
            }
        }
        else if (hex == 14)
        {
            if (index == 0)
            {
                map[9].corner[4] = value;
                map[11].corner[2] = value;
            }
            else if (index == 1)
            {
                map[9].corner[3] = value;
                map[12].corner[5] = value;
            }
            else if (index == 2)
            {
                map[12].corner[4] = value;
                map[17].corner[0] = value;
            }
            else if (index == 3)
            {
                map[17].corner[5] = value;
                map[18].corner[1] = value;
            }
            else if (index == 4)
            {
                map[18].corner[0] = value;
                map[16].corner[2] = value;
            }
            else if (index == 5)
            {
                map[16].corner[1] = value;
                map[11].corner[3] = value;
            }
        }
        else if (hex == 15)
        {
            if (index == 0)
            {
                map[10].corner[4] = value;
                map[12].corner[2] = value;
            }
            else if (index == 1)
            {
                map[10].corner[3] = value;
            }
            else if (index == 4)
            {
                map[17].corner[2] = value;
            }
            else if (index == 5)
            {
                map[17].corner[1] = value;
                map[12].corner[3] = value;
            }
        }
        else if (hex == 16)
        {
            if (index == 0)
            {
                map[11].corner[4] = value;
                map[13].corner[2] = value;
            }
            else if (index == 1)
            {
                map[11].corner[3] = value;
                map[14].corner[5] = value;
            }
            else if (index == 2)
            {
                map[14].corner[4] = value;
                map[18].corner[0] = value;
            }
            else if (index == 3)
            {
                map[18].corner[5] = value;
            }
            else if (index == 5)
            {
                map[13].corner[3] = value;
            }
        }
        else if (hex == 17)
        {
            if (index == 0)
            {
                map[12].corner[4] = value;
                map[14].corner[2] = value;
            }
            else if (index == 1)
            {
                map[12].corner[3] = value;
                map[15].corner[5] = value;
            }
            else if (index == 2)
            {
                map[15].corner[4] = value;
            }
            else if (index == 4)
            {
                map[18].corner[2] = value;
            }
            else if (index == 5)
            {
                map[18].corner[1] = value;
                map[14].corner[3] = value;
            }
        }
        else if (hex == 18)
        {
            if (index == 0)
            {
                map[14].corner[4] = value;
                map[16].corner[2] = value;
            }
            else if (index == 1)
            {
                map[14].corner[3] = value;
                map[17].corner[5] = value;
            }
            else if (index == 2)
            {
                map[17].corner[4] = value;
            }
            else if (index == 5)
            {
                map[16].corner[3] = value;
            }
        }
    }
}