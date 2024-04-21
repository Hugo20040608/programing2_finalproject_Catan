#include "catan.h"
#include "map.h"

void player_initialize(characterStruct *player)
{
    player->victory_point = 0;
    player->road_length = 0;
    player->used_road = 0;
    // new add
    player->used_development_card = 0;
    player->get_rob = 0;
    // new add end
    player->used_knight = 0;
    player->settlement = 0;
    player->city = 0;
    player->brick = 0;
    player->lumber = 0;
    player->ore = 0;
    player->grain = 0;
    player->wool = 0;
    player->knight_card = 0;
    player->roadbuilding_card = 0;
    player->year_of_plenty = 0;
    player->monopoly = 0;
    player->victory_card = 0;

    for (int32_t i = 0; i < 6; i++)
    {
        player->port[i] = 0;
    }

    player->max_knight_card = 0;
    player->max_road_card = 0;

    return;
}

void bank_initialize(bankStruct *bank)
{
    bank->brick = 19;
    bank->lumber = 19;
    bank->ore = 19;
    bank->grain = 19;
    bank->wool = 19;
    bank->knight_card = 14;
    bank->roadbuilding_card = 2;
    bank->year_of_plenty = 2;
    bank->monopoly = 2;
    bank->victory_card = 5;

    return;
}

void roll_dice(characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map, bankStruct *bank)
{
    int32_t x = rand() % 6 + 1;
    int32_t y = rand() % 6 + 1;

    // printf("\n======================================================\n\n");
    printf("First dice:%d\n", x);
    printf("Second dice:%d\n", y);
    printf("Total:%d\n", x + y);
    // printf("\n======================================================\n\n");

    if ((x + y) == 7)
    {
        robber(player, total_player, player_number, map, bank);
    }
    else
    {
        give_resource_card(map, x + y, player, bank);
    }

    return;
}

// 每個case底下的if最後多加player[player_number].used_development_card++;
// 共8個地方

int32_t use_development_card(characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map, mapStruct *player_build, bankStruct *bank)
{
    int32_t status = 0;
    if (player_number == 0)
    {
        int32_t use_card = 0;

        printf("Which card you want to use?(1:knight card 2:roadbuilding card 3:year of plenty 4:monopoly): ");
        scanf("%d", &use_card);

        switch (use_card)
        {
        case 1:
            if (player[player_number].knight_card > 0)
            {
                use_knight_card(player, total_player, player_number, map);
                // new add
                player[player_number].used_development_card++;
                // new add end
                status = 1;
            }
            else
            {
                printf("You don't have this card.\n");
            }
            break;
        case 2:
            if (player[player_number].roadbuilding_card > 0)
            {
                use_road_building_card(map, player, player_number, player_build, total_player);
                // new add
                player[player_number].used_development_card++;
                // new add end
                status = 1;
            }
            else
            {
                printf("You don't have this card.\n");
            }
            break;
        case 3:
            if (player[player_number].year_of_plenty > 0)
            {
                use_year_of_plenty_card(player, player_number, bank);
                // new add
                player[player_number].used_development_card++;
                // new add end
                status = 1;
            }
            else
            {
                printf("You don't have this card.\n");
            }
            break;
        case 4:
            if (player[player_number].monopoly > 0)
            {
                use_monopoly_card(player, player_number, total_player);
                // new add
                player[player_number].used_development_card++;
                // new add end
                status = 1;
            }
            else
            {
                printf("You don't have this card.\n");
            }
            break;
        default:
            break;
        }
    }
    else
    {
        int32_t use_card = 0;

        if (player[player_number].knight_card > 0)
        {
            use_card = 1;
            printf("Which card you want to use?(1~4)\n");
            printf("player %d choose %d.\n", player_number, use_card);
            use_knight_card(player, total_player, player_number, map);
            // new add
            player[player_number].used_development_card++;
            // new add end
            status = 1;
        }
        else if (player[player_number].roadbuilding_card > 0)
        {
            use_card = 2;
            printf("Which card you want to use?(1~4)\n");
            printf("player %d choose %d.\n", player_number, use_card);
            use_road_building_card(map, player, player_number, player_build, total_player);
            // new add
            player[player_number].used_development_card++;
            // new add end
            status = 1;
        }
        else if (player[player_number].year_of_plenty > 0)
        {
            use_card = 3;
            printf("Which card you want to use?(1~4)\n");
            printf("player %d choose %d.\n", player_number, use_card);
            use_year_of_plenty_card(player, player_number, bank);
            // new add
            player[player_number].used_development_card++;
            // new add end
            status = 1;
        }
        else if (player[player_number].monopoly > 0)
        {
            use_card = 4;
            printf("Which card you want to use?(1~4)\n");
            printf("player %d choose %d.\n", player_number, use_card);
            use_monopoly_card(player, player_number, total_player);
            // new add
            player[player_number].used_development_card++;
            // new add end
            status = 1;
        }
    }

    return status;
}

void choose_card(int32_t resource[], int32_t player_number, int32_t choose_num, characterStruct *player)
{
    if (player_number == 0)
    {
        printf("Now you can choose the resource you want to use.\n");
        int32_t status = 0;

        while (status == 0)
        {
            printf("Brick: ");
            scanf("%d", &(resource[0]));
            printf("Lumber: ");
            scanf("%d", &(resource[1]));
            printf("Ore: ");
            scanf("%d", &(resource[2]));
            printf("Grain: ");
            scanf("%d", &(resource[3]));
            printf("Wool: ");
            scanf("%d", &(resource[4]));

            if (choose_num == (resource[0] + resource[1] + resource[2] + resource[3] + resource[4]))
            {
                status = 1;
            }
            else
            {
                printf("Your input amount is not same with the choose number.\n");
            }
        }
    }
    else
    {
        int32_t status = 0;
        printf("Now you can choose the resource you want to use.\n");

        for (int32_t i = 0; i < 5; i++)
        {
            resource[i] = 0;
        }

        int32_t temp1 = player[player_number].brick - 1;
        int32_t temp2 = temp1 + player[player_number].lumber - 1;
        int32_t temp3 = temp2 + player[player_number].ore - 1;
        int32_t temp4 = temp3 + player[player_number].grain - 1;
        int32_t temp5 = temp4 + player[player_number].wool - 1;

        if (temp1 >= choose_num)
        {
            resource[0] = choose_num;
        }
        else if (temp2 >= choose_num)
        {
            resource[0] = player[player_number].brick - 1;
            resource[1] = choose_num - temp1;
        }
        else if (temp3 >= choose_num)
        {
            resource[0] = player[player_number].brick - 1;
            resource[1] = player[player_number].lumber - 1;
            resource[2] = choose_num - temp2;
        }
        else if (temp4 >= choose_num)
        {
            resource[0] = player[player_number].brick - 1;
            resource[1] = player[player_number].lumber - 1;
            resource[2] = player[player_number].ore - 1;
            resource[3] = choose_num - temp3;
        }
        else if (temp5 >= choose_num)
        {
            resource[0] = player[player_number].brick - 1;
            resource[1] = player[player_number].lumber - 1;
            resource[2] = player[player_number].ore - 1;
            resource[3] = player[player_number].grain - 1;
            resource[4] = choose_num - temp4;
        }
        else if (temp5 + 1 >= choose_num)
        {
            resource[0] = player[player_number].brick;
            resource[1] = player[player_number].lumber - 1;
            resource[2] = player[player_number].ore - 1;
            resource[3] = player[player_number].grain - 1;
            resource[4] = player[player_number].wool - 1;
        }
        else if (temp5 + 2 >= choose_num)
        {
            resource[0] = player[player_number].brick;
            resource[1] = player[player_number].lumber;
            resource[2] = player[player_number].ore - 1;
            resource[3] = player[player_number].grain - 1;
            resource[4] = player[player_number].wool - 1;
        }
        else if (temp5 + 3 >= choose_num)
        {
            resource[0] = player[player_number].brick;
            resource[1] = player[player_number].lumber;
            resource[2] = player[player_number].ore;
            resource[3] = player[player_number].grain - 1;
            resource[4] = player[player_number].wool - 1;
        }
        else if (temp5 + 4 >= choose_num)
        {
            resource[0] = player[player_number].brick;
            resource[1] = player[player_number].lumber;
            resource[2] = player[player_number].ore;
            resource[3] = player[player_number].grain;
            resource[4] = player[player_number].wool - 1;
        }
        else
        {
            resource[0] = player[player_number].brick;
            resource[1] = player[player_number].lumber;
            resource[2] = player[player_number].ore;
            resource[3] = player[player_number].grain;
            resource[4] = player[player_number].wool;
        }

        printf("The player %d choose %d brick, %d lumber, %d ore, %d grain, %d wool.\n", player_number, resource[0], resource[1], resource[2], resource[3], resource[4]);
    }

    return;
}

int32_t judge_card(characterStruct *player, int32_t resource[])
{
    if (player->brick < resource[0])
    {
        return 0;
    }
    if (player->lumber < resource[1])
    {
        return 0;
    }
    if (player->ore < resource[2])
    {
        return 0;
    }
    if (player->grain < resource[3])
    {
        return 0;
    }
    if (player->wool < resource[4])
    {
        return 0;
    }

    return 1;
}

// 執行robber
// 檢查玩家手卡、移動robber、抽資源
void robber(characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map, bankStruct *bank)
{
    // 檢查手卡
    for (int32_t i = 0; i < total_player; i++)
    {
        int32_t total_resource = 0;

        total_resource = (player[i].brick) + (player[i].lumber) + (player[i].ore) + (player[i].grain) + (player[i].wool);

        if (total_resource > 7)
        {
            while (1)
            {
                int32_t discard = total_resource / 2;
                int32_t resource[5] = {0};

                printf("Player %d have %d cards totally, you must discard %d cards.\n", i, total_resource, discard);

                printf("\n======================================================\n\n");
                print_player_info(player, total_player);
                printf("\n======================================================\n\n");

                choose_card(resource, i, discard, player);
                if (judge_card(&(player[i]), resource) == 0)
                {
                    printf("You don't have enough card.\n");
                    continue;
                }

                // 判斷discard跟選擇的張數相不相同
                if (discard == (resource[0] + resource[1] + resource[2] + resource[3] + resource[4]))
                {
                    player[i].brick = player[i].brick - resource[0];
                    player[i].lumber = player[i].lumber - resource[1];
                    player[i].ore = player[i].ore - resource[2];
                    player[i].grain = player[i].grain - resource[3];
                    player[i].wool = player[i].wool - resource[4];

                    bank->brick = bank->brick + resource[0];
                    bank->lumber = bank->lumber + resource[1];
                    bank->ore = bank->ore + resource[2];
                    bank->grain = bank->grain + resource[3];
                    bank->wool = bank->wool + resource[4];

                    break;
                }
            }
        }
    }

    int32_t map_seat = 0;
    int32_t choose_player_get_card = 0;
    int32_t robber_seat = 0;

    for (int32_t i = 0; i < 19; i++)
    {
        if (map[i].robber == 1)
        {
            robber_seat = i;
            break;
        }
    }

    if (player_number == 0)
    {
        printf("\n======================================================\n\n");
        map_for_choose();
        printf("======================================================\n\n");

        while (1)
        {
            printf("Enter which map you want to move(0~18): ");
            scanf("%d", &map_seat);

            if (map_seat < 0 || map_seat > 18)
            {
                printf("Please choose a location by map number again!\n");
            }
            else if (map[map_seat].robber != 0)
            {
                printf("There are already robber, choose again!\n");
            }
            else
            {
                map[map_seat].robber = 1;
                map[robber_seat].robber = 0;

                break;
            }
        }

        // 選的位置上沒有玩家
        if (map[map_seat].corner[0] == 0 && map[map_seat].corner[1] == 0 && map[map_seat].corner[2] == 0 && map[map_seat].corner[3] == 0 && map[map_seat].corner[4] == 0 && map[map_seat].corner[5] == 0)
        {
            printf("There is no house at here.\n");
            printf("You already finished robber!\n");
            return;
        }

        int32_t play_stand_map[7] = {0}; // 用來儲存玩家有誰

        for (int i = 0; i < 6; i++)
        {
            play_stand_map[i] = map[map_seat].corner[i] % 5 - 1; // 玩家0~3
        }

        int32_t have_player[4] = {0};
        int32_t status = 0;

        for (int32_t i = 0; i < total_player; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (play_stand_map[j] == i && i != player_number)
                {
                    have_player[i] = 1;
                    status = 1;
                    break;
                }
            }
        }

        if (status == 0)
        {
            printf("You already finished robber!\n");
            return;
        }
        else
        {
            int32_t flag[4] = {0};
            // 計算如果玩家都沒卡可以抽

            if (have_player[0] == 1)
            {
                flag[0] = player[0].brick + player[0].lumber + player[0].ore + player[0].grain + player[0].wool;
            }
            if (have_player[1] == 1)
            {
                flag[1] = player[1].brick + player[1].lumber + player[1].ore + player[1].grain + player[1].wool;
            }
            if (have_player[2] == 1)
            {
                flag[2] = player[2].brick + player[2].lumber + player[2].ore + player[2].grain + player[2].wool;
            }
            if (have_player[3] == 1)
            {
                flag[3] = player[3].brick + player[3].lumber + player[3].ore + player[3].grain + player[3].wool;
            }

            // 如果有玩家但玩家都沒卡可以抽
            if (flag[0] == 0 && flag[1] == 0 && flag[2] == 0 && flag[3] == 0)
            {
                printf("No one has a card!\n");
                printf("You already finished robber!\n");
                return;
            }

            printf("Which player you want to choose cards? Enter player number?\n");

            for (int32_t i = 0; i < total_player; i++)
            {
                if (flag[i] != 0)
                {
                    printf("/player0%d", i);
                }
            }
        }

        printf("/: ");
        scanf("%d", &choose_player_get_card);
        // new add
        player[choose_player_get_card].get_rob++;
        // new add end

        while (1)
        {
            int32_t x = rand() % 5; // 5個資源

            if (x == 0)
            {
                if (player[choose_player_get_card].brick == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].brick--;
                    player[player_number].brick++;
                    printf("You get a brick!\n");
                    break;
                }
            }
            else if (x == 1)
            {
                if (player[choose_player_get_card].lumber == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].lumber--;
                    player[player_number].lumber++;
                    printf("You get a lumber!\n");
                    break;
                }
            }
            else if (x == 2)
            {
                if (player[choose_player_get_card].ore == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].ore--;
                    player[player_number].ore++;
                    printf("You get a ore!\n");
                    break;
                }
            }
            else if (x == 3)
            {
                if (player[choose_player_get_card].grain == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].grain--;
                    player[player_number].grain++;
                    printf("You get a grain!\n");
                    break;
                }
            }
            else if (x == 4)
            {
                if (player[choose_player_get_card].wool == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].wool--;
                    player[player_number].wool++;
                    printf("You get a wool!\n");

                    break;
                }
            }
        }
    }
    else
    {
        printf("\n======================================================\n\n");
        map_for_choose();
        printf("======================================================\n\n");

        while (1)
        {
            printf("Enter which map you want to move(0~18)\n");
            map_seat = rand() % 19;
            printf("player %d choose %d.\n", player_number, map_seat);

            if (map_seat < 0 || map_seat > 18)
            {
                printf("Please choose a location by map number again!\n");
            }
            else if (map[map_seat].robber != 0)
            {
                printf("There are already robber, choose again!\n");
            }
            else
            {
                map[map_seat].robber = 1;
                map[robber_seat].robber = 0;

                break;
            }
        }

        // 選的位置上沒有玩家
        if (map[map_seat].corner[0] == 0 && map[map_seat].corner[1] == 0 && map[map_seat].corner[2] == 0 && map[map_seat].corner[3] == 0 && map[map_seat].corner[4] == 0 && map[map_seat].corner[5] == 0)
        {
            printf("There is no house at here.\n");
            printf("You already finished robber!\n");
            return;
        }

        int32_t play_stand_map[7] = {0}; // 用來儲存玩家有誰

        for (int i = 0; i < 6; i++)
        {
            play_stand_map[i] = map[map_seat].corner[i] % 5 - 1; // 玩家0~3
        }

        int32_t have_player[4] = {0};
        int32_t flag[4] = {0};
        int32_t status = 0;

        for (int32_t i = 0; i < total_player; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (play_stand_map[j] == i && i != player_number)
                {
                    have_player[i] = 1;
                    status = 1;
                    break;
                }
            }
        }

        if (status == 0)
        {
            printf("You already finished robber!\n");
            return;
        }
        else
        {
            // 計算如果玩家都沒卡可以抽

            if (have_player[0] == 1)
            {
                flag[0] = player[0].brick + player[0].lumber + player[0].ore + player[0].grain + player[0].wool;
            }
            if (have_player[1] == 1)
            {
                flag[1] = player[1].brick + player[1].lumber + player[1].ore + player[1].grain + player[1].wool;
            }
            if (have_player[2] == 1)
            {
                flag[2] = player[2].brick + player[2].lumber + player[2].ore + player[2].grain + player[2].wool;
            }
            if (have_player[3] == 1)
            {
                flag[3] = player[3].brick + player[3].lumber + player[3].ore + player[3].grain + player[3].wool;
            }

            // 如果有玩家但玩家都沒卡可以抽
            if (flag[0] == 0 && flag[1] == 0 && flag[2] == 0 && flag[3] == 0)
            {
                printf("No one has a card!\n");
                printf("You already finished robber!\n");
                return;
            }

            printf("Which player you want to choose cards? Enter player number?\n");

            for (int32_t i = 0; i < total_player; i++)
            {
                if (flag[i] != 0)
                {
                    printf("/player0%d", i);
                }
            }
        }

        printf("/\n");

        for (int32_t i = 0; i < total_player; i++)
        {
            if (flag[i] != 0)
            {
                choose_player_get_card = i;
                printf("player %d choose player0%d.\n", player_number, i);
                break;
            }
        }
        // new add
        player[choose_player_get_card].get_rob++;
        // new add end

        while (1)
        {
            int32_t x = rand() % 5; // 5個資源

            if (x == 0)
            {
                if (player[choose_player_get_card].brick == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].brick--;
                    player[player_number].brick++;
                    printf("You get a brick!\n");
                    break;
                }
            }
            else if (x == 1)
            {
                if (player[choose_player_get_card].lumber == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].lumber--;
                    player[player_number].lumber++;
                    printf("You get a lumber!\n");
                    break;
                }
            }
            else if (x == 2)
            {
                if (player[choose_player_get_card].ore == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].ore--;
                    player[player_number].ore++;
                    printf("You get a ore!\n");
                    break;
                }
            }
            else if (x == 3)
            {
                if (player[choose_player_get_card].grain == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].grain--;
                    player[player_number].grain++;
                    printf("You get a grain!\n");
                    break;
                }
            }
            else if (x == 4)
            {
                if (player[choose_player_get_card].wool == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].wool--;
                    player[player_number].wool++;
                    printf("You get a wool!\n");

                    break;
                }
            }
        }
    }

    return;
}

void use_knight_card(characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map)
{
    // 發動騎士卡可以移動盜賊，如果盜賊的新位置上有其他玩家，可以抽其中一個玩家的資源。
    // 一回合只能出一張騎士卡(寫在main)。
    // 檢查winner(寫在main)
    // 檢查玩家手上有無騎士卡
    // print_player_info( player, player_number );
    int32_t oriowner = -1;
    int32_t ori_max_knight = -1;

    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].max_knight_card == 1)
        {
            ori_max_knight = player[i].used_knight;
            oriowner = i;
            break;
        }
    }

    int32_t map_seat = 0;
    int32_t choose_player_get_card = 0;
    int32_t robber_seat = 0;

    for (int32_t i = 0; i < 19; i++)
    {
        if (map[i].robber == 1)
        {
            robber_seat = i;
            break;
        }
    }

    if (player_number == 0)
    {
        printf("\n======================================================\n\n");
        map_for_choose();
        printf("======================================================\n\n");

        while (1)
        {
            printf("Enter which map you want to move(0~18): ");
            scanf("%d", &map_seat);

            if (map_seat < 0 || map_seat > 18)
            {
                printf("Please choose a location by map number again!\n");
            }
            else if (map[map_seat].robber != 0)
            {
                printf("There are already robber, choose again!\n");
            }
            else
            {
                map[map_seat].robber = 1;
                map[robber_seat].robber = 0;
                player[player_number].knight_card--;
                player[player_number].used_knight++;

                break;
            }
        }

        // 選的位置上沒有玩家
        if (map[map_seat].corner[0] == 0 && map[map_seat].corner[1] == 0 && map[map_seat].corner[2] == 0 && map[map_seat].corner[3] == 0 && map[map_seat].corner[4] == 0 && map[map_seat].corner[5] == 0)
        {
            printf("There is no house at here.\n");
            printf("You already use knight card!\n");
            return;
        }

        int32_t play_stand_map[7] = {0}; // 用來儲存玩家有誰

        for (int i = 0; i < 6; i++)
        {
            play_stand_map[i] = map[map_seat].corner[i] % 5 - 1; // 玩家0~3
        }

        int32_t have_player[4] = {0};
        int32_t status = 0;

        for (int32_t i = 0; i < total_player; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (play_stand_map[j] == i && i != player_number)
                {
                    have_player[i] = 1;
                    status = 1;
                    break;
                }
            }
        }

        if (status == 0)
        {
            printf("You already use knight card!\n");
            return;
        }
        else
        {
            int32_t flag[4] = {0};
            // 計算如果玩家都沒卡可以抽

            if (have_player[0] == 1)
            {
                flag[0] = player[0].brick + player[0].lumber + player[0].ore + player[0].grain + player[0].wool;
            }
            if (have_player[1] == 1)
            {
                flag[1] = player[1].brick + player[1].lumber + player[1].ore + player[1].grain + player[1].wool;
            }
            if (have_player[2] == 1)
            {
                flag[2] = player[2].brick + player[2].lumber + player[2].ore + player[2].grain + player[2].wool;
            }
            if (have_player[3] == 1)
            {
                flag[3] = player[3].brick + player[3].lumber + player[3].ore + player[3].grain + player[3].wool;
            }

            // 如果有玩家但玩家都沒卡可以抽
            if (flag[0] == 0 && flag[1] == 0 && flag[2] == 0 && flag[3] == 0)
            {
                printf("No one has a card!\n");
                printf("You already use knight card!\n");
                return;
            }

            printf("Which player you want to choose cards? Enter player number?\n");

            for (int32_t i = 0; i < total_player; i++)
            {
                if (flag[i] != 0)
                {
                    printf("/player0%d", i);
                }
            }
        }

        printf("/: ");
        scanf("%d", &choose_player_get_card);
        // new add
        player[choose_player_get_card].get_rob++;
        // new add end

        while (1)
        {
            int32_t x = rand() % 5; // 5個資源

            if (x == 0)
            {
                if (player[choose_player_get_card].brick == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].brick--;
                    player[player_number].brick++;
                    printf("You get a brick!\n");
                    break;
                }
            }
            else if (x == 1)
            {
                if (player[choose_player_get_card].lumber == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].lumber--;
                    player[player_number].lumber++;
                    printf("You get a lumber!\n");
                    break;
                }
            }
            else if (x == 2)
            {
                if (player[choose_player_get_card].ore == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].ore--;
                    player[player_number].ore++;
                    printf("You get a ore!\n");
                    break;
                }
            }
            else if (x == 3)
            {
                if (player[choose_player_get_card].grain == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].grain--;
                    player[player_number].grain++;
                    printf("You get a grain!\n");
                    break;
                }
            }
            else if (x == 4)
            {
                if (player[choose_player_get_card].wool == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].wool--;
                    player[player_number].wool++;
                    printf("You get a wool!\n");

                    break;
                }
            }
        }
    }
    else
    {
        printf("\n======================================================\n\n");
        map_for_choose();
        printf("======================================================\n\n");

        while (1)
        {
            printf("Enter which map you want to move(0~18)\n");
            map_seat = rand() % 19;
            printf("player %d choose %d.\n", player_number, map_seat);

            if (map_seat < 0 || map_seat > 18)
            {
                printf("Please choose a location by map number again!\n");
            }
            else if (map[map_seat].robber != 0)
            {
                printf("There are already robber, choose again!\n");
            }
            else
            {
                map[map_seat].robber = 1;
                map[robber_seat].robber = 0;
                player[player_number].knight_card--;
                player[player_number].used_knight++;

                break;
            }
        }

        // 選的位置上沒有玩家
        if (map[map_seat].corner[0] == 0 && map[map_seat].corner[1] == 0 && map[map_seat].corner[2] == 0 && map[map_seat].corner[3] == 0 && map[map_seat].corner[4] == 0 && map[map_seat].corner[5] == 0)
        {
            printf("There is no house at here.\n");
            printf("You already use knight card!\n");
            return;
        }

        int32_t play_stand_map[7] = {0}; // 用來儲存玩家有誰

        for (int i = 0; i < 6; i++)
        {
            play_stand_map[i] = map[map_seat].corner[i] % 5 - 1; // 玩家0~3
        }

        int32_t have_player[4] = {0};
        int32_t flag[4] = {0};
        int32_t status = 0;

        for (int32_t i = 0; i < total_player; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (play_stand_map[j] == i && i != player_number)
                {
                    have_player[i] = 1;
                    status = 1;
                    break;
                }
            }
        }

        if (status == 0)
        {
            printf("You already use knight card!\n");
            return;
        }
        else
        {
            // 計算如果玩家都沒卡可以抽

            if (have_player[0] == 1)
            {
                flag[0] = player[0].brick + player[0].lumber + player[0].ore + player[0].grain + player[0].wool;
            }
            if (have_player[1] == 1)
            {
                flag[1] = player[1].brick + player[1].lumber + player[1].ore + player[1].grain + player[1].wool;
            }
            if (have_player[2] == 1)
            {
                flag[2] = player[2].brick + player[2].lumber + player[2].ore + player[2].grain + player[2].wool;
            }
            if (have_player[3] == 1)
            {
                flag[3] = player[3].brick + player[3].lumber + player[3].ore + player[3].grain + player[3].wool;
            }

            // 如果有玩家但玩家都沒卡可以抽
            if (flag[0] == 0 && flag[1] == 0 && flag[2] == 0 && flag[3] == 0)
            {
                printf("No one has a card!\n");
                printf("You already use knight card!\n");
                return;
            }

            printf("Which player you want to choose cards? Enter player number?\n");

            for (int32_t i = 0; i < total_player; i++)
            {
                if (flag[i] != 0)
                {
                    printf("/player0%d", i);
                }
            }
        }

        printf("/\n");

        for (int32_t i = 0; i < total_player; i++)
        {
            if (flag[i] != 0)
            {
                choose_player_get_card = i;
                printf("player %d choose player0%d\n", player_number, i);
                break;
            }
        }
        // new add
        player[choose_player_get_card].get_rob++;
        // new add end

        while (1)
        {
            int32_t x = rand() % 5; // 5個資源

            if (x == 0)
            {
                if (player[choose_player_get_card].brick == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].brick--;
                    player[player_number].brick++;
                    printf("You get a brick!\n");
                    break;
                }
            }
            else if (x == 1)
            {
                if (player[choose_player_get_card].lumber == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].lumber--;
                    player[player_number].lumber++;
                    printf("You get a lumber!\n");
                    break;
                }
            }
            else if (x == 2)
            {
                if (player[choose_player_get_card].ore == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].ore--;
                    player[player_number].ore++;
                    printf("You get a ore!\n");
                    break;
                }
            }
            else if (x == 3)
            {
                if (player[choose_player_get_card].grain == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].grain--;
                    player[player_number].grain++;
                    printf("You get a grain!\n");
                    break;
                }
            }
            else if (x == 4)
            {
                if (player[choose_player_get_card].wool == 0)
                {
                    continue;
                }
                else
                {
                    player[choose_player_get_card].wool--;
                    player[player_number].wool++;
                    printf("You get a wool!\n");

                    break;
                }
            }
        }
    }

    // 最大軍隊卡：當有人發動3張騎士卡後，可以獲得最大軍隊卡，總分+2。如果有人發動的騎士卡數量超過擁有最大軍隊卡的人，立刻拿到此卡。
    int32_t maxowner = -1;
    int32_t max_used_knight = -1;

    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].used_knight > max_used_knight && player[i].used_knight >= 3)
        {
            max_used_knight = player[i].used_knight;
            maxowner = i;
        }
    }
    if ((maxowner == player_number) && (oriowner != player_number) && (max_used_knight > ori_max_knight))
    {
        player[player_number].victory_point += 2;
        player[player_number].max_knight_card = 1;

        if (oriowner != -1)
        {
            player[oriowner].victory_point -= 2;
            player[oriowner].max_knight_card = 0;
        }
    }

    return;
}

void use_year_of_plenty_card(characterStruct *player, int32_t player_number, bankStruct *bank)
{
    if (player_number == 0)
    {
        int32_t resource_type1, resource_type2;

        printf("Enter the first resource you want to get(0:brick 1:lumber 2:ore 3:grain 4:wool): ");
        scanf("%d", &resource_type1);

        switch (resource_type1)
        {
        case 0:
            player[player_number].brick++;
            bank->brick--;

            break;
        case 1:
            player[player_number].lumber++;
            bank->lumber--;
            break;
        case 2:
            player[player_number].ore++;
            bank->ore--;
            break;
        case 3:
            player[player_number].grain++;
            bank->grain--;
            break;
        case 4:
            player[player_number].wool++;
            bank->wool--;
            break;
        default:
            printf("error type!\n");
            break;
        }

        printf("Enter the second resource you want to get(0:brick 1:lumber 2:ore 3:grain 4:wool): ");
        scanf("%d", &resource_type2);

        switch (resource_type2)
        {
        case 0:
            player[player_number].brick++;
            bank->brick--;

            break;
        case 1:
            player[player_number].lumber++;
            bank->lumber--;
            break;
        case 2:
            player[player_number].ore++;
            bank->ore--;
            break;
        case 3:
            player[player_number].grain++;
            bank->grain--;
            break;
        case 4:
            player[player_number].wool++;
            bank->wool--;
            break;
        default:
            printf("error type!\n");
            break;
        }

        printf("You already use year of plenty card and get 2 type of resource\n");
        player[player_number].year_of_plenty--;
    }
    else
    {
        int32_t resource_type1, resource_type2;

        printf("Enter the first resource you want to get(0:brick 1:lumber 2:ore 3:grain 4:wool)\n");
        resource_type1 = rand() % 5;
        printf("player %d choose %d", player_number, resource_type1);

        switch (resource_type1)
        {
        case 0:
            player[player_number].brick++;
            bank->brick--;

            break;
        case 1:
            player[player_number].lumber++;
            bank->lumber--;
            break;
        case 2:
            player[player_number].ore++;
            bank->ore--;
            break;
        case 3:
            player[player_number].grain++;
            bank->grain--;
            break;
        case 4:
            player[player_number].wool++;
            bank->wool--;
            break;
        default:
            printf("error type!\n");
            break;
        }

        printf("Enter the second resource you want to get(0:brick 1:lumber 2:ore 3:grain 4:wool)\n");
        resource_type2 = rand() % 5;
        printf("player %d choose %d", player_number, resource_type2);

        switch (resource_type2)
        {
        case 0:
            player[player_number].brick++;
            bank->brick--;

            break;
        case 1:
            player[player_number].lumber++;
            bank->lumber--;
            break;
        case 2:
            player[player_number].ore++;
            bank->ore--;
            break;
        case 3:
            player[player_number].grain++;
            bank->grain--;
            break;
        case 4:
            player[player_number].wool++;
            bank->wool--;
            break;
        default:
            printf("error type!\n");
            break;
        }

        printf("You already use year of plenty card and get 2 type of resource\n");
        player[player_number].year_of_plenty--;
    }

    return;
}

// 使用道路建造卡
void use_road_building_card(mapStruct *map, characterStruct *player, int32_t player_number, mapStruct *player_build, int32_t total_player)
{
    if (player_number == 0)
    {
        int32_t status = 0;

        printf("\n======================================================\n\n");
        map_for_choose();
        printf("======================================================\n\n");

        while (status == 0)
        {
            // 建造第一條道路

            if (player[player_number].used_road == 15)
            {
                printf("You don't have any road can build.\n");
                break;
            }

            int32_t map1;
            int32_t side1;
            printf("Enter which map you want to build(0~18): ");
            scanf("%d", &map1);
            printf("Enter which side you want to build on map %d (clockwise 0~5): ", map1);
            scanf("%d", &side1);

            all_unbuildable(player_build);
            is_buildable(map, player_build, player_number + 1);

            if (player_build[map1].side[side1] == -1)
            {
                printf("You cannot build on this place!\n");
            }
            else
            {
                map[map1].side[side1] = player_number + 1;
                sync_map(0, map1, side1, map);
                printf("The first road is build sucessfully!\n");
                player[player_number].used_road++;
                status = 1;
            }
        }

        status = 0;

        while (status == 0)
        {
            // 建造第二條道路
            if (player[player_number].used_road == 15)
            {
                printf("You don't have any road can build.\n");
                break;
            }

            int32_t map2;
            int32_t side2;
            printf("Enter which map you want to build(0~18): ");
            scanf("%d", &map2);
            printf("Enter which side you want to build on map %d (clockwise 0~5): ", map2);
            scanf("%d", &side2);

            all_unbuildable(player_build);
            is_buildable(map, player_build, player_number + 1);

            if (player_build[map2].side[side2] == -1)
            {
                printf("You cannot build on this place!\n");
            }
            else
            {
                map[map2].side[side2] = player_number + 1;
                sync_map(0, map2, side2, map);
                printf("The second road is build sucessfully!\n");
                player[player_number].used_road++;
                status = 1;
            }
        }

        printf("You already use road building card!\n");
        player[player_number].roadbuilding_card--;

        // 判斷最長道路
        is_longest_road(player, total_player, player_number, map);
    }
    else
    {
        int32_t status = 0;
        int32_t map1 = 0;
        int32_t side1 = 0;
        int32_t map2 = 0;
        int32_t side2 = 0;

        printf("\n======================================================\n\n");
        map_for_choose();
        printf("======================================================\n\n");

        // 建造第一條道路
        printf("Where do you want to build your road?\n");

        if (player[player_number].used_road == 15)
        {
            printf("You don't have any road can build.\n");
            printf("You already use road building card!\n");
            player[player_number].roadbuilding_card--;
            return;
        }

        all_unbuildable(player_build);
        is_buildable(map, player_build, player_number + 1);

        for (int32_t i = 0; i < 19; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (player_build[i].side[j] != -1)
                {
                    map1 = i;
                    side1 = j;
                    status = 1;
                    break;
                }
            }

            if (status == 1)
            {
                break;
            }
        }

        if (status == 0)
        {
            printf("There is no place you can build road.\n");
            printf("You already use road building card!\n");
            player[player_number].roadbuilding_card--;
            return;
        }

        printf("Enter which map you want to build(0~18)\n");
        printf("Player %d choose %d.\n", player_number, map1);
        printf("Enter which side you want to build on map %d (clockwise 0~5)\n", map1);
        printf("Player %d choose %d.\n", player_number, side1);

        if (player_build[map1].side[side1] == -1)
        {
            printf("You cannot build on this place!\n");
        }
        else
        {
            map[map1].side[side1] = player_number + 1;
            sync_map(0, map1, side1, map);
            printf("The first road is build sucessfully!\n");
            player[player_number].used_road++;
        }

        status = 0;

        printf("\n======================================================\n\n");
        map_for_choose();
        printf("======================================================\n\n");

        if (player[player_number].used_road == 15)
        {
            printf("You don't have any road can build.\n");
            printf("You already use road building card!\n");
            player[player_number].roadbuilding_card--;

            // 判斷最長道路
            is_longest_road(player, total_player, player_number, map);
            return;
        }

        // 建造第二條道路
        printf("Where do you want to build your road?\n");

        all_unbuildable(player_build);
        is_buildable(map, player_build, player_number + 1);

        for (int32_t i = 0; i < 19; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (player_build[i].side[j] != -1)
                {
                    map2 = i;
                    side2 = j;
                    status = 1;
                    break;
                }
            }

            if (status == 1)
            {
                break;
            }
        }

        if (status == 0)
        {
            printf("There is no place you can build road.\n");
            printf("You already use road building card!\n");
            player[player_number].roadbuilding_card--;

            // 判斷最長道路
            is_longest_road(player, total_player, player_number, map);
            return;
        }

        printf("Enter which map you want to build(0~18)\n");
        printf("Player %d choose %d.\n", player_number, map2);
        printf("Enter which side you want to build on map %d (clockwise 0~5)\n", map2);
        printf("Player %d choose %d.\n", player_number, side2);

        if (player_build[map2].side[side2] == -1)
        {
            printf("You cannot build on this place!\n");
        }
        else
        {
            map[map2].side[side2] = player_number + 1;
            sync_map(0, map2, side2, map);
            printf("The first road is build sucessfully!\n");
            player[player_number].used_road++;
        }

        printf("You already use road building card!\n");
        player[player_number].roadbuilding_card--;

        // 判斷最長道路
        is_longest_road(player, total_player, player_number, map);
    }

    return;
}

void use_monopoly_card(characterStruct *player, int32_t player_number, int32_t total_player)
{
    if (player_number == 0)
    {
        int32_t resource_type;
        printf("Enter the resource you want to get(0:brick 1:lumber 2:ore 3:grain 4:wool): ");
        scanf("%d", &resource_type);

        switch (resource_type)
        {
        case 0:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].brick += player[i].brick;
                    player[i].brick = 0;
                }
            }
            break;
        case 1:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].lumber += player[i].lumber;
                    player[i].lumber = 0;
                }
            }
            break;
        case 2:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].ore += player[i].ore;
                    player[i].ore = 0;
                }
            }
            break;
        case 3:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].grain += player[i].grain;
                    player[i].grain = 0;
                }
            }
            break;
        case 4:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].wool += player[i].wool;
                    player[i].wool = 0;
                }
            }
            break;
        default:
            printf("error type\n");
            break;
        }

        printf("You already use monopoly card and get more resource!\n");
        player[player_number].monopoly--;
    }
    else
    {
        int32_t resource_type;
        printf("Enter the resource you want to get(0:brick 1:lumber 2:ore 3:grain 4:wool)\n");
        resource_type = rand() % 5;
        printf("player %d choose %d", player_number, resource_type);

        switch (resource_type)
        {
        case 0:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].brick += player[i].brick;
                    player[i].brick = 0;
                }
            }
            break;
        case 1:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].lumber += player[i].lumber;
                    player[i].lumber = 0;
                }
            }
            break;
        case 2:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].ore += player[i].ore;
                    player[i].ore = 0;
                }
            }
            break;
        case 3:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].grain += player[i].grain;
                    player[i].grain = 0;
                }
            }
            break;
        case 4:
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != player_number)
                {
                    player[player_number].wool += player[i].wool;
                    player[i].wool = 0;
                }
            }
            break;
        default:
            printf("error type\n");
            break;
        }

        printf("You already use monopoly card and get more resource!\n");
        player[player_number].monopoly--;
    }

    return;
}

// 建造
// 決定是否建造路、村莊、升級成城市
void build(mapStruct *mapCatan, mapStruct *player_build, int32_t player_number, characterStruct *player, bankStruct *bank, int32_t total_player)
{
    int32_t kind_of_building = 0;
    int32_t hex = 0;
    int32_t index = 0;
    printf("What do you want to build?\n");
    printf("1: Road 2: Settlement 3: City\n");
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &kind_of_building);
        if (kind_of_building <= 3 && kind_of_building >= 1)
        {
            break;
        }
        else
        {
            printf("You only have three choices!!\n");
        }
    }

    printf("\n======================================================\n\n");
    map_for_choose();
    printf("======================================================\n\n");

    if (kind_of_building == 1)
    {
        if (player[player_number - 1].brick == 0 || player[player_number - 1].lumber == 0)
        {
            printf("You don't havce enough resource.\n");
            return;
        }
        else if (player[player_number - 1].used_road == 15)
        {
            printf("You don't have any road can build.\n");
            return;
        }

        printf("Where do you want to build your road?\n");
        while (1)
        {
            printf("Enter the map(0~18): ");
            scanf("%d", &hex);
            printf("Enter the side of the map(0~5): ");
            scanf("%d", &index);
            if (hex >= 0 && hex <= 18 && index >= 0 && index <= 5)
            {
                break;
            }
            else
            {
                printf("Invalid choice!!\n");
            }
        }
        all_unbuildable(player_build);
        is_buildable(mapCatan, player_build, player_number);
        if (player_build[hex].side[index] == -1)
        {
            printf("This side cannot build!\n");
            printf("If you want to build at other places, please choose build function again.\n");
            return;
        }
        else
        {
            printf("Build the road successly\n");
            mapCatan[hex].side[index] = player_number;
            sync_map(0, hex, index, mapCatan);
            player[player_number - 1].brick--;
            player[player_number - 1].lumber--;
            player[player_number - 1].used_road++;
            bank->brick++;
            bank->lumber++;
            // 判斷最長道路
            is_longest_road(player, total_player, player_number - 1, mapCatan);

            printf("\n");
        }
    }
    else if (kind_of_building == 2)
    {
        if (player[player_number - 1].brick == 0 || player[player_number - 1].lumber == 0 || player[player_number - 1].grain == 0 || player[player_number - 1].wool == 0)
        {
            printf("you don't havce enough resource.\n");
            return;
        }
        else if (player[player_number - 1].settlement == 5)
        {
            printf("You don't have any settlement can build.\n");
            return;
        }

        printf("Where do you want to build your settlement?\n");
        while (1)
        {
            printf("Enter the map(0~18): ");
            scanf("%d", &hex);
            printf("Enter the corner of the map(0~5): ");
            scanf("%d", &index);
            if (hex >= 0 && hex <= 18 && index >= 0 && index <= 5)
            {
                break;
            }
            else
            {
                printf("Invalid choice!!\n");
            }
        }
        all_unbuildable(player_build);
        is_buildable(mapCatan, player_build, player_number);
        if (player_build[hex].corner[index] == -1)
        {
            printf("This corner cannot build!\n");
            printf("If you want to build at other places, please choose build function again.\n");
            return;
        }
        else
        {
            printf("Build the settlement successly\n");
            mapCatan[hex].corner[index] = player_number;

            if ((mapCatan[hex].port[index]) > 0)
            {
                player[player_number - 1].port[(mapCatan[hex].port[index]) - 1] = 1;
            }

            sync_map(1, hex, index, mapCatan);
            player[player_number - 1].brick--;
            player[player_number - 1].lumber--;
            player[player_number - 1].grain--;
            player[player_number - 1].wool--;
            bank->brick++;
            bank->lumber++;
            bank->grain++;
            bank->wool++;
            player[player_number - 1].victory_point++;
            player[player_number - 1].settlement++;
            // 判斷最長道路
            is_longest_road(player, total_player, player_number - 1, mapCatan);

            printf("\n");
        }
    }
    else if (kind_of_building == 3)
    {
        if (player[player_number - 1].grain < 2 || player[player_number - 1].ore < 3)
        {
            printf("you don't havce enough resource.\n");
            return;
        }
        else if (player[player_number - 1].city == 4)
        {
            printf("You don't have any city can build.\n");
            return;
        }

        printf("Where do you want to build your city?\n");
        while (1)
        {
            printf("Enter the map(0~18): ");
            scanf("%d", &hex);
            printf("Enter the corner of the map(0~5): ");
            scanf("%d", &index);
            if (hex >= 0 && hex <= 18 && index >= 0 && index <= 5)
            {
                break;
            }
            else
            {
                printf("Invalid choice!!\n");
            }
        }
        if (mapCatan[hex].corner[index] != player_number)
        {
            printf("You don't have settlement here! You can't build a city here!\n");
            printf("If you want to build at other places, please choose build function again.\n");
            return;
        }
        else
        {
            printf("Build the city successly\n");
            mapCatan[hex].corner[index] = 5 + player_number;
            sync_map(1, hex, index, mapCatan);
            player[player_number - 1].grain = player[player_number - 1].grain - 2;
            player[player_number - 1].ore = player[player_number - 1].ore - 3;
            bank->grain = bank->grain + 2;
            bank->ore = bank->ore + 3;
            player[player_number - 1].victory_point++;
            player[player_number - 1].city++;

            printf("\n");
        }
    }

    return;
}

// 判斷是否有人滿足獲勝條件
// 是return 1，否return 0
int win(characterStruct *player, int32_t player_number)
{
    if ((player[player_number].victory_point + player[player_number].victory_card) >= 10)
    {
        return 1;
    }

    return 0;
}

// 將當格資源給附近玩家
void give_resource_card(mapStruct *map, int32_t dice_number, characterStruct *player, bankStruct *bank)
{
    int32_t n = 0;
    for (n = 0; n < 19; n++)
    {
        if (map[n].roll_dice_number == dice_number)
        {
            if (map[n].robber == 1)
            {
                printf("There is robber at here.\n");
                return;
            }
            else if (map[n].resourse == 0)
            {
                for (int32_t i = 0; i < 6; i++)
                {
                    int32_t whoonmap;
                    whoonmap = map[n].corner[i] % 5;
                    if (whoonmap == 0)
                    {
                        continue;
                    }
                    else
                    {
                        player[whoonmap - 1].brick++;
                        bank->brick--;
                        if (map[n].corner[i] > 5) // 持有城市資源發兩張
                        {
                            player[whoonmap - 1].brick++;
                            bank->brick--;
                        }
                    }
                }
            }
            else if (map[n].resourse == 1)
            {
                for (int32_t i = 0; i < 6; i++)
                {
                    int32_t whoonmap;
                    whoonmap = map[n].corner[i] % 5;
                    if (whoonmap == 0)
                    {
                        continue;
                    }
                    else
                    {
                        player[whoonmap - 1].lumber++;
                        bank->lumber--;
                        if (map[n].corner[i] > 5) // 持有城市資源發兩張
                        {
                            player[whoonmap - 1].lumber++;
                            bank->lumber--;
                        }
                    }
                }
            }
            else if (map[n].resourse == 2)
            {
                for (int32_t i = 0; i < 6; i++)
                {
                    int32_t whoonmap;
                    whoonmap = map[n].corner[i] % 5;
                    if (whoonmap == 0)
                    {
                        continue;
                    }
                    else
                    {
                        player[whoonmap - 1].ore++;
                        bank->ore--;
                        if (map[n].corner[i] > 5) // 持有城市資源發兩張
                        {
                            player[whoonmap - 1].ore++;
                            bank->ore--;
                        }
                    }
                }
            }
            else if (map[n].resourse == 3)
            {
                for (int32_t i = 0; i < 6; i++)
                {
                    int32_t whoonmap;
                    whoonmap = map[n].corner[i] % 5;
                    if (whoonmap == 0)
                    {
                        continue;
                    }
                    else
                    {
                        player[whoonmap - 1].grain++;
                        bank->grain--;
                        if (map[n].corner[i] > 5) // 持有城市資源發兩張
                        {
                            player[whoonmap - 1].grain++;
                            bank->grain--;
                        }
                    }
                }
            }
            else if (map[n].resourse == 4)
            {
                for (int32_t i = 0; i < 6; i++)
                {
                    int32_t whoonmap;
                    whoonmap = map[n].corner[i] % 5;
                    if (whoonmap == 0)
                    {
                        continue;
                    }
                    else
                    {
                        player[whoonmap - 1].wool++;
                        bank->wool--;
                        if (map[n].corner[i] > 5) // 持有城市資源發兩張
                        {
                            player[whoonmap - 1].wool++;
                            bank->wool--;
                        }
                    }
                }
            }
        }
    }

    return;
}

// 印出玩家資訊
void print_player_info(characterStruct *player, int32_t total_player)
{
    if (total_player == 4)
    {
        // printf("\n======================================================\n\n");
        printf("Player Information\n");
        printf("Item                Player0        Player1        Player2        Player3\n");
        printf("Victory Point          %d              %d              %d              %d\n", player[0].victory_point, player[1].victory_point, player[2].victory_point, player[3].victory_point);
        printf("Road Length            %d              %d              %d              %d\n", player[0].road_length, player[1].road_length, player[2].road_length, player[3].road_length);
        printf("Used Road              %d              %d              %d              %d\n", player[0].used_road, player[1].used_road, player[2].used_road, player[3].used_road);
        printf("Used Knight            %d              %d              %d              %d\n", player[0].used_knight, player[1].used_knight, player[2].used_knight, player[3].used_knight);
        printf("Settlement             %d              %d              %d              %d\n", player[0].settlement, player[1].settlement, player[2].settlement, player[3].settlement);
        printf("City                   %d              %d              %d              %d\n", player[0].city, player[1].city, player[2].city, player[3].city);
        printf("Brick                  %d              %d              %d              %d\n", player[0].brick, player[1].brick, player[2].brick, player[3].brick);
        printf("Lumber                 %d              %d              %d              %d\n", player[0].lumber, player[1].lumber, player[2].lumber, player[3].lumber);
        printf("Ore                    %d              %d              %d              %d\n", player[0].ore, player[1].ore, player[2].ore, player[3].ore);
        printf("Grain                  %d              %d              %d              %d\n", player[0].grain, player[1].grain, player[2].grain, player[3].grain);
        printf("Wool                   %d              %d              %d              %d\n", player[0].wool, player[1].wool, player[2].wool, player[3].wool);
        printf("Knight Card            %d              %d              %d              %d\n", player[0].knight_card, player[1].knight_card, player[2].knight_card, player[3].knight_card);
        printf("Roadbuilding Card      %d              %d              %d              %d\n", player[0].roadbuilding_card, player[1].roadbuilding_card, player[2].roadbuilding_card, player[3].roadbuilding_card);
        printf("Year of Plenty         %d              %d              %d              %d\n", player[0].year_of_plenty, player[1].year_of_plenty, player[2].year_of_plenty, player[3].year_of_plenty);
        printf("Monopoly               %d              %d              %d              %d\n", player[0].monopoly, player[1].monopoly, player[2].monopoly, player[3].monopoly);
        printf("Victory Card           %d              %d              %d              %d\n", player[0].victory_card, player[1].victory_card, player[2].victory_card, player[3].victory_card);
        printf("port[0]                %d              %d              %d              %d\n", player[0].port[0], player[1].port[0], player[2].port[0], player[3].port[0]);
        printf("port[1]                %d              %d              %d              %d\n", player[0].port[1], player[1].port[1], player[2].port[1], player[3].port[1]);
        printf("port[2]                %d              %d              %d              %d\n", player[0].port[2], player[1].port[2], player[2].port[2], player[3].port[2]);
        printf("port[3]                %d              %d              %d              %d\n", player[0].port[3], player[1].port[3], player[2].port[3], player[3].port[3]);
        printf("port[4]                %d              %d              %d              %d\n", player[0].port[4], player[1].port[4], player[2].port[4], player[3].port[4]);
        printf("port[5]                %d              %d              %d              %d\n", player[0].port[5], player[1].port[5], player[2].port[5], player[3].port[5]);
        printf("max_knight_card        %d              %d              %d              %d\n", player[0].max_knight_card, player[1].max_knight_card, player[2].max_knight_card, player[3].max_knight_card);
        printf("max_road_card          %d              %d              %d              %d\n", player[0].max_road_card, player[1].max_road_card, player[2].max_road_card, player[3].max_road_card);
        // printf("\n======================================================\n\n");
    }
    else if (total_player == 3)
    {
        //printf("\n======================================================\n\n");
        printf("Player Information\n");
        printf("Item                Player0        Player1        Player2\n");
        printf("Victory Point          %d              %d              %d\n", player[0].victory_point, player[1].victory_point, player[2].victory_point);
        printf("Road Length            %d              %d              %d\n", player[0].road_length, player[1].road_length, player[2].road_length);
        printf("Used Road              %d              %d              %d\n", player[0].used_road, player[1].used_road, player[2].used_road);
        printf("Used Knight            %d              %d              %d\n", player[0].used_knight, player[1].used_knight, player[2].used_knight);
        printf("Settlement             %d              %d              %d\n", player[0].settlement, player[1].settlement, player[2].settlement);
        printf("City                   %d              %d              %d\n", player[0].city, player[1].city, player[2].city);
        printf("Brick                  %d              %d              %d\n", player[0].brick, player[1].brick, player[2].brick);
        printf("Lumber                 %d              %d              %d\n", player[0].lumber, player[1].lumber, player[2].lumber);
        printf("Ore                    %d              %d              %d\n", player[0].ore, player[1].ore, player[2].ore);
        printf("Grain                  %d              %d              %d\n", player[0].grain, player[1].grain, player[2].grain);
        printf("Wool                   %d              %d              %d\n", player[0].wool, player[1].wool, player[2].wool);
        printf("Knight Card            %d              %d              %d\n", player[0].knight_card, player[1].knight_card, player[2].knight_card);
        printf("Roadbuilding Card      %d              %d              %d\n", player[0].roadbuilding_card, player[1].roadbuilding_card, player[2].roadbuilding_card);
        printf("Year of Plenty         %d              %d              %d\n", player[0].year_of_plenty, player[1].year_of_plenty, player[2].year_of_plenty);
        printf("Monopoly               %d              %d              %d\n", player[0].monopoly, player[1].monopoly, player[2].monopoly);
        printf("Victory Card           %d              %d              %d\n", player[0].victory_card, player[1].victory_card, player[2].victory_card);
        printf("port[0]                %d              %d              %d\n", player[0].port[0], player[1].port[0], player[2].port[0]);
        printf("port[1]                %d              %d              %d\n", player[0].port[1], player[1].port[1], player[2].port[1]);
        printf("port[2]                %d              %d              %d\n", player[0].port[2], player[1].port[2], player[2].port[2]);
        printf("port[3]                %d              %d              %d\n", player[0].port[3], player[1].port[3], player[2].port[3]);
        printf("port[4]                %d              %d              %d\n", player[0].port[4], player[1].port[4], player[2].port[4]);
        printf("port[5]                %d              %d              %d\n", player[0].port[5], player[1].port[5], player[2].port[5]);
        printf("max_knight_card        %d              %d              %d\n", player[0].max_knight_card, player[1].max_knight_card, player[2].max_knight_card);
        printf("max_road_card          %d              %d              %d\n", player[0].max_road_card, player[1].max_road_card, player[2].max_road_card);
        //printf("\n======================================================\n\n");
    }

    return;
}
// void print_player_info( characterStruct *player, int32_t player_number )
//{
//     printf("\n======================================================\n\n");
//     printf("Player %d Information:\n",player_number);
//     printf("Victory Point: %d\n", player[player_number].victory_point);
//     printf("Road Length: %d\n", player[player_number].road_length);
//     printf("Used Road: %d\n", player[player_number].used_road);
//     printf("Used Knight: %d\n", player[player_number].used_knight);
//     printf("Settlement: %d\n", player[player_number].settlement);
//     printf("City: %d\n", player[player_number].city);
//     printf("Brick: %d\n", player[player_number].brick);
//     printf("Lumber: %d\n", player[player_number].lumber);
//     printf("Ore: %d\n", player[player_number].ore);
//     printf("Grain: %d\n", player[player_number].grain);
//     printf("Wool: %d\n", player[player_number].wool);
//     printf("Knight Card: %d\n", player[player_number].knight_card);
//     printf("Roadbuilding Card: %d\n", player[player_number].roadbuilding_card);
//     printf("Year of Plenty: %d\n", player[player_number].year_of_plenty);
//     printf("Monopoly: %d\n", player[player_number].monopoly);
//     printf("Victory Card: %d\n", player[player_number].victory_card);
//     printf("port[0]: %d\n", player[player_number].port[0]);
//     printf("port[1]: %d\n", player[player_number].port[1]);
//     printf("port[2]: %d\n", player[player_number].port[2]);
//     printf("port[3]: %d\n", player[player_number].port[3]);
//     printf("port[4]: %d\n", player[player_number].port[4]);
//     printf("port[5]: %d\n", player[player_number].port[5]);
//     printf("max_knight_card: %d\n", player[player_number].max_knight_card);
//     printf("\n======================================================\n\n");
//
//     return ;
// }

void bank_trade(characterStruct *player, int32_t player_number, mapStruct *map, bankStruct *bank)
{
    int32_t port = 0;
    int32_t resource[6] = {0};
    int32_t spend = 0;
    int32_t want = 0;
    int32_t status = 0;
    int32_t choose = 0;

    printf("You want to 2->1 or 3->1 or 4->1? (2->1:0  3->1:1  4->1:2)\n");
    scanf("%d", &choose);
    if (choose == 0)
    {
        for (int32_t i = 0; i < 5; i++)
        {
            if (player[player_number].port[i] != 0)
            {
                status = 1;
            }
        }
    }
    else if (choose == 1)
    {
        if (player[player_number].port[5] != 0)
        {
            status = 2;
        }
    }
    else if (choose == 2)
    {
        status = 3;
    }

    if (status == 0)
    {
        printf("You are not connect with port.\n");
        return;
    }
    else if (status == 1)
    {
        if (player[player_number].port[0] != 0)
        {
            printf("brick:0 ");
        }
        if (player[player_number].port[1] != 0)
        {
            printf("lumber:1 ");
        }
        if (player[player_number].port[2] != 0)
        {
            printf("ore:2 ");
        }
        if (player[player_number].port[3] != 0)
        {
            printf("grain:3 ");
        }
        if (player[player_number].port[4] != 0)
        {
            printf("wool:4 ");
        }

        printf("\n");

        printf("choose which resource you want to trade(0:brick 1:lumber 2:ore 3:grain 4:wool): ");
        
        scanf("%d", &spend);

        if (player[player_number].port[spend] != 0)
        {
            resource[spend] = 2;
        }
        else
        {
            printf("You are not connect with this port.\n");
            return;
        }

        if (judge_card(&player[player_number], resource) == 1)
        {
            printf("choose which resource you want(0:brick 1:lumber 2:ore 3:grain 4:wool): ");
            scanf("%d", &want);

            if (want == 0)
            {
                player[player_number].brick += 1;
                bank->brick--;
            }
            else if (want == 1)
            {
                player[player_number].lumber += 1;
                bank->lumber--;
            }
            else if (want == 2)
            {
                player[player_number].ore += 1;
                bank->ore--;
            }
            else if (want == 3)
            {
                player[player_number].grain += 1;
                bank->grain--;
            }
            else if (want == 4)
            {
                player[player_number].wool += 1;
                bank->wool--;
            }

            if (spend == 0)
            {
                player[player_number].brick -= 2;
                bank->brick += 2;
            }
            else if (spend == 1)
            {
                player[player_number].lumber -= 2;
                bank->lumber += 2;
            }
            else if (spend == 2)
            {
                player[player_number].ore -= 2;
                bank->ore += 2;
            }
            else if (spend == 3)
            {
                player[player_number].grain -= 2;
                bank->grain += 2;
            }
            else if (spend == 4)
            {
                player[player_number].wool -= 2;
                bank->wool += 2;
            }

            printf("It's a deal.\n");
        }
        else
        {
            printf("not enough card\n");
        }
    }
    else if (status == 2)
    {
        printf("choose which resource you want to trade(0:brick 1:lumber 2:ore 3:grain 4:wool): ");
        scanf("%d", &spend);

        resource[spend] = 3;

        if (judge_card(&player[player_number], resource) == 1)
        {
            printf("choose which resource you want(0:brick 1:lumber 2:ore 3:grain 4:wool): ");
            scanf("%d", &want);

            if (want == 0)
            {
                player[player_number].brick += 1;
                bank->brick--;
            }
            else if (want == 1)
            {
                player[player_number].lumber += 1;
                bank->lumber--;
            }
            else if (want == 2)
            {
                player[player_number].ore += 1;
                bank->ore--;
            }
            else if (want == 3)
            {
                player[player_number].grain += 1;
                bank->grain--;
            }
            else if (want == 4)
            {
                player[player_number].wool += 1;
                bank->wool--;
            }

            if (spend == 0)
            {
                player[player_number].brick -= 3;
                bank->brick += 3;
            }
            else if (spend == 1)
            {
                player[player_number].lumber -= 3;
                bank->lumber += 3;
            }
            else if (spend == 2)
            {
                player[player_number].ore -= 3;
                bank->ore += 3;
            }
            else if (spend == 3)
            {
                player[player_number].grain -= 3;
                bank->grain += 3;
            }
            else if (spend == 4)
            {
                player[player_number].wool -= 3;
                bank->wool += 3;
            }

            printf("It's a deal.\n");
        }
        else
        {
            printf("not enough card\n");
        }
    }
    else if (status == 3)
    {
        printf("choose which resource you want to trade(0:brick 1:lumber 2:ore 3:grain 4:wool): ");
        scanf("%d", &spend);

        resource[spend] = 4;

        if (judge_card(&player[player_number], resource) == 1)
        {
            printf("choose which resource you want(0:brick 1:lumber 2:ore 3:grain 4:wool): ");
            scanf("%d", &want);

            if (want == 0)
            {
                player[player_number].brick += 1;
                bank->brick--;
            }
            else if (want == 1)
            {
                player[player_number].lumber += 1;
                bank->lumber--;
            }
            else if (want == 2)
            {
                player[player_number].ore += 1;
                bank->ore--;
            }
            else if (want == 3)
            {
                player[player_number].grain += 1;
                bank->grain--;
            }
            else if (want == 4)
            {
                player[player_number].wool += 1;
                bank->wool--;
            }

            if (spend == 0)
            {
                player[player_number].brick -= 4;
                bank->brick += 4;
            }
            else if (spend == 1)
            {
                player[player_number].lumber -= 4;
                bank->lumber += 4;
            }
            else if (spend == 2)
            {
                player[player_number].ore -= 4;
                bank->ore += 4;
            }
            else if (spend == 3)
            {
                player[player_number].grain -= 4;
                bank->grain += 4;
            }
            else if (spend == 4)
            {
                player[player_number].wool -= 4;
                bank->wool += 4;
            }

            printf("It's a deal.\n");
        }
        else
        {
            printf("not enough card\n");
        }
    }

    return;
}

void is_buildable(mapStruct *map_Catan, mapStruct *player, int32_t player_number)
{
    // player settlement buildable
    for (int32_t i = 0; i < 19; i++)
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (map_Catan[i].side[j] == player_number)
            {
                if (j == 5)
                {
                    player[i].corner[5] = 0;
                    player[i].corner[0] = 0;
                    sync_map(1, i, 0, player);
                    sync_map(1, i, 5, player);
                }
                else
                {
                    player[i].corner[j] = 0;
                    player[i].corner[j + 1] = 0;
                    sync_map(1, i, j, player);
                    sync_map(1, i, j + 1, player);
                }
            }
        }
    }
    // player settlement unbuildable
    for (int32_t i = 0; i < 19; i++)
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (map_Catan[i].corner[j] > 0)
            {
                if (j == 5)
                {
                    player[i].corner[0] = -1;
                    player[i].corner[4] = -1;
                    player[i].corner[j] = -1;
                    sync_map(1, i, 0, player);
                    sync_map(1, i, 4, player);
                    sync_map(1, i, j, player);
                }
                else if (j == 0)
                {
                    player[i].corner[5] = -1;
                    player[i].corner[1] = -1;
                    player[i].corner[j] = -1;
                    sync_map(1, i, 5, player);
                    sync_map(1, i, 1, player);
                    sync_map(1, i, j, player);
                }
                else
                {
                    player[i].corner[j - 1] = -1;
                    player[i].corner[j + 1] = -1;
                    player[i].corner[j] = -1;
                    sync_map(1, i, j - 1, player);
                    sync_map(1, i, j + 1, player);
                    sync_map(1, i, j, player);
                }
            }
        }
    }
    // end of settlement
    // player road buildable
    for (int32_t i = 0; i < 19; i++)
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (map_Catan[i].corner[j] % 5 == player_number)
            {
                if (j == 0)
                {
                    player[i].side[0] = 0;
                    player[i].side[5] = 0;
                    sync_map(0, i, 0, player);
                    sync_map(0, i, 5, player);
                }
                else
                {
                    player[i].side[j - 1] = 0;
                    player[i].side[j] = 0;
                    sync_map(0, i, j - 1, player);
                    sync_map(0, i, j, player);
                }
            }
            if (map_Catan[i].side[j] == player_number)
            {
                if (j == 0)
                {
                    if (map_Catan[i].corner[0] == 0 || map_Catan[i].corner[0] % 5 == player_number)
                    {
                        player[i].side[5] = 0;
                        sync_map(0, i, 5, player);
                    }
                    if (map_Catan[i].corner[1] == 0 || map_Catan[i].corner[1] % 5 == player_number)
                    {
                        player[i].side[1] = 0;
                        sync_map(0, i, 1, player);
                    }
                }
                else if (j == 5)
                {
                    if (map_Catan[i].corner[0] == 0 || map_Catan[i].corner[0] % 5 == player_number)
                    {
                        player[i].side[0] = 0;
                        sync_map(0, i, 0, player);
                    }
                    if (map_Catan[i].corner[5] == 0 || map_Catan[i].corner[5] % 5 == player_number)
                    {
                        player[i].side[4] = 0;
                        sync_map(0, i, 4, player);
                    }
                }
                else
                {
                    if (map_Catan[i].corner[j] == 0 || map_Catan[i].corner[j] % 5 == player_number)
                    {
                        player[i].side[j - 1] = 0;
                        sync_map(0, i, j - 1, player);
                    }
                    if (map_Catan[i].corner[j + 1] == 0 || map_Catan[i].corner[j + 1] % 5 == player_number)
                    {
                        player[i].side[j + 1] = 0;
                        sync_map(0, i, j + 1, player);
                    }
                }
            }
        }
    }
    // player road unbuildable
    for (int32_t i = 0; i < 19; i++)
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (map_Catan[i].side[j] > 0)
            {
                player[i].side[j] = -1;
                sync_map(0, i, j, player);
            }
        }
    }
    return;
}

void all_settlement_buildable(mapStruct *player)
{
    for (int32_t i = 0; i < 19; i++)
    {
        player[i].roll_dice_number = 0;
        for (int32_t j = 0; j < 6; j++)
        {
            player[i].corner[j] = 0;
        }
        for (int32_t j = 0; j < 6; j++)
        {
            player[i].side[j] = -1;
        }
        player[i].robber = 0;
        player[i].resourse = 0;
        for (int32_t j = 0; j < 6; j++)
        {
            player[i].port[j] = 0;
        }
    }
    return;
}

void all_unbuildable(mapStruct *player)
{
    for (int32_t i = 0; i < 19; i++)
    {
        player[i].roll_dice_number = 0;
        for (int32_t j = 0; j < 6; j++)
        {
            player[i].corner[j] = -1;
        }
        for (int32_t j = 0; j < 6; j++)
        {
            player[i].side[j] = -1;
        }
        player[i].robber = 0;
        player[i].resourse = 0;
        for (int32_t j = 0; j < 6; j++)
        {
            player[i].port[j] = 0;
        }
    }
    return;
}

void shuffleArray(int arr[], int size)
{
    // 初始化隨機
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    return;
}

void buy_development_card(characterStruct *player, int32_t player_number, int32_t index, int32_t card[28], bankStruct *bank, int32_t total_player)
{
    if (card[index] == 1)
    {
        // 得到騎士卡
        player[player_number].knight_card++;
        bank->knight_card--;
        printf("You get a knight card!\n");
    }
    else if (card[index] == 2)
    {
        // 豐收之年卡
        player[player_number].year_of_plenty++;
        bank->year_of_plenty--;
        printf("You get a year of plenty card!\n");
    }
    else if (card[index] == 3)
    {
        // 道路建造卡
        player[player_number].roadbuilding_card++;
        bank->roadbuilding_card--;
        printf("You get a roadbuilding card!\n");
    }
    else if (card[index] == 4)
    {
        // 壟斷市場卡
        player[player_number].monopoly++;
        bank->monopoly--;
        printf("You get a monopoly card!\n");
    }
    else if (card[index] == 5)
    {
        // 分數卡
        player[player_number].victory_card++;
        bank->victory_card--;
        printf("You get a victory card!\n");
    }
    else if (card[index] == 6)
    {
        // 特殊事件
        printf("You get a special event card!\n");
        printf("Your grandma give you a big land, so you get three wool!\n");
        player[player_number].wool += 3;
        // new add
        player[player_number].used_development_card++;
        // new add end
    }
    else if (card[index] == 7)
    {
        // 特殊事件
        int32_t stole_player = 0;

        stole_player = rand() % total_player;

        while (stole_player == player_number)
        {
            stole_player = rand() % total_player;
        }

        printf("You get a special event card!\n");
        // new add
        player[player_number].used_development_card++;
        // new add end
        if (player[player_number].brick > 0)
        {
            printf("Player %d stole 1 brick from you when you are so tired from writing Neokent's homework!\n", stole_player);
            player[player_number].brick--;
            player[stole_player].brick++;
        }
        else if (player[player_number].lumber > 0)
        {
            printf("Player %d stole 1 lumber from you when you are so tired from writing Neokent's homework!\n", stole_player);
            player[player_number].lumber--;
            player[stole_player].lumber++;
        }
        else if (player[player_number].ore > 0)
        {
            printf("Player %d stole 1 ore from you when you are so tired from writing Neokent's homework!\n", stole_player);
            player[player_number].ore--;
            player[stole_player].ore++;
        }
        else if (player[player_number].grain > 0)
        {
            printf("Player %d stole 1 grain from you when you are so tired from writing Neokent's homework!\n", stole_player);
            player[player_number].grain--;
            player[stole_player].grain++;
        }
        else if (player[player_number].wool > 0)
        {
            printf("Player %d stole 1 wool from you when you are so tired from writing Neokent's homework!\n", stole_player);
            player[player_number].wool--;
            player[stole_player].wool++;
        }
        else
        {
            printf("Player %d want to steal resource from you when you are so tired from writing Neokent's homework, but you don't have any resource can steal!\n", stole_player);
        }
    }
    else if (card[index] == 8)
    {
        // 特殊事件
        printf("You get a special event card!\n");
        printf("You win a lottery, you can get 1 more card from every resource!\n");
        // new add
        player[player_number].used_development_card++;
        // new add end
        player[player_number].brick++;
        player[player_number].lumber++;
        player[player_number].ore++;
        player[player_number].grain++;
        player[player_number].wool++;
    }
    return;
}

void print_bank_info(bankStruct *bank)
{
    // printf("\n======================================================\n\n");
    printf("Bank Information:\n");
    printf("Brick: %d\n", bank->brick);
    printf("Lumber: %d\n", bank->lumber);
    printf("Ore: %d\n", bank->ore);
    printf("Grain: %d\n", bank->grain);
    printf("Wool: %d\n", bank->wool);
    printf("Knight Card: %d\n", bank->knight_card);
    printf("Roadbuilding Card: %d\n", bank->roadbuilding_card);
    printf("Year of Plenty: %d\n", bank->year_of_plenty);
    printf("Monopoly: %d\n", bank->monopoly);
    printf("Victory Card: %d\n", bank->victory_card);
    // printf("\n======================================================\n\n");

    return;
}

// 城市7，村莊6，路5，使用發展卡4，買發展卡3，銀行交易1，玩家交易2
int32_t computer_choice(characterStruct *player, int32_t player_number, int32_t flag[7])
{
    if (player[player_number].grain >= 2 && player[player_number].ore >= 3 && flag[6] == 0)
    {
        return 7;
    }
    if (player[player_number].grain >= 1 && player[player_number].wool >= 1 && player[player_number].brick >= 1 && player[player_number].lumber >= 1 && flag[5] == 0)
    {
        return 6;
    }
    if (player[player_number].brick >= 1 && player[player_number].lumber >= 1 && flag[4] == 0)
    {
        return 5;
    }
    if (player[player_number].knight_card >= 1 || player[player_number].roadbuilding_card >= 1 ||
        player[player_number].year_of_plenty >= 1 || player[player_number].monopoly >= 1 && flag[3] == 0)
    {
        return 4;
    }
    if (player[player_number].grain >= 1 && player[player_number].wool >= 1 && player[player_number].ore >= 1 && flag[2] == 0)
    {
        return 3;
    }
    //    if( player[player_number]. ){
    //
    //    }
    if ((player[player_number].grain > 1 || player[player_number].wool > 1 ||
         player[player_number].brick > 1 || player[player_number].lumber > 1 ||
         player[player_number].ore > 1) &&
        flag[1] == 0)
    {
        return 2;
    }

    return 0; // 如果沒有足夠的以上資源
}

void computer_build(mapStruct *mapCatan, mapStruct *player_build, int32_t player_number, characterStruct *player, bankStruct *bank, int32_t type, int32_t total_player)
{
    int32_t hex = 0;
    int32_t index = 0;
    int32_t status = 0;

    printf("\n======================================================\n\n");
    map_for_choose();
    printf("======================================================\n\n");

    if (type == 1)
    {
        if (player[player_number - 1].brick == 0 || player[player_number - 1].lumber == 0)
        {
            printf("You don't havce enough resource.\n");
            return;
        }
        else if (player[player_number - 1].used_road == 15)
        {
            printf("You don't have any road can build.\n");
            return;
        }

        printf("Where do you want to build your road?\n");

        all_unbuildable(player_build);
        is_buildable(mapCatan, player_build, player_number);

        for (int32_t i = 0; i < 19; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (player_build[i].side[j] != -1)
                {
                    hex = i;
                    index = j;
                    status = 1;
                    break;
                }
            }

            if (status == 1)
            {
                break;
            }
        }

        if (status == 0)
        {
            printf("There is no place you can build road.\n");
            return;
        }

        printf("Enter the map(0~18)\n");
        printf("Player %d choose %d.\n", player_number - 1, hex);
        printf("Enter the side of the map(0~5)\n");
        printf("Player %d choose %d.\n", player_number - 1, index);

        if (player_build[hex].side[index] == -1)
        {
            printf("This side cannot build!\n");
            printf("If you want to build at other places, please choose build function again.\n");
            return;
        }
        else
        {
            printf("Build the road successly\n");
            mapCatan[hex].side[index] = player_number;
            sync_map(0, hex, index, mapCatan);
            player[player_number - 1].brick--;
            player[player_number - 1].lumber--;
            player[player_number - 1].used_road++;
            bank->brick++;
            bank->lumber++;
            // 判斷最長道路
            is_longest_road(player, total_player, player_number - 1, mapCatan);

            printf("\n");
        }
    }
    else if (type == 2)
    {
        if (player[player_number - 1].brick == 0 || player[player_number - 1].lumber == 0 || player[player_number - 1].grain == 0 || player[player_number - 1].wool == 0)
        {
            printf("you don't havce enough resource.\n");
            return;
        }
        else if (player[player_number - 1].settlement == 5)
        {
            printf("You don't have any settlement can build.\n");
            return;
        }

        printf("Where do you want to build your settlement?\n");

        all_unbuildable(player_build);
        is_buildable(mapCatan, player_build, player_number);

        for (int32_t i = 0; i < 19; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (player_build[i].corner[j] != -1)
                {
                    hex = i;
                    index = j;
                    status = 1;
                    break;
                }
            }

            if (status == 1)
            {
                break;
            }
        }

        if (status == 0)
        {
            printf("There is no place you can build settlement.\n");
            return;
        }

        printf("Enter the map(0~18)\n");
        printf("Player %d choose %d.\n", player_number - 1, hex);
        printf("Enter the corner of the map(0~5)\n");
        printf("Player %d choose %d.\n", player_number - 1, index);

        if (player_build[hex].corner[index] == -1)
        {
            printf("This corner cannot build!\n");
            printf("If you want to build at other places, please choose build function again.\n");
            return;
        }
        else
        {
            printf("Build the settlement successly\n");
            mapCatan[hex].corner[index] = player_number;

            if ((mapCatan[hex].port[index]) > 0)
            {
                player[player_number - 1].port[mapCatan[hex].port[index] - 1] = 1;
            }

            sync_map(1, hex, index, mapCatan);
            player[player_number - 1].brick--;
            player[player_number - 1].lumber--;
            player[player_number - 1].grain--;
            player[player_number - 1].wool--;
            bank->brick++;
            bank->lumber++;
            bank->grain++;
            bank->wool++;
            player[player_number - 1].victory_point++;
            player[player_number - 1].settlement++;
            // 判斷最長道路
            is_longest_road(player, total_player, player_number - 1, mapCatan);

            printf("\n");
        }
    }
    else if (type == 3)
    {
        if (player[player_number - 1].grain < 2 || player[player_number - 1].ore < 3)
        {
            printf("you don't havce enough resource.\n");
            return;
        }
        else if (player[player_number - 1].city == 4)
        {
            printf("You don't have any city can build.\n");
            return;
        }

        printf("Where do you want to build your city?\n");

        for (int32_t i = 0; i < 19; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (mapCatan[i].corner[j] == player_number)
                {
                    hex = i;
                    index = j;
                    status = 1;
                    break;
                }
            }

            if (status == 1)
            {
                break;
            }
        }

        if (status == 0)
        {
            printf("There is no place you can build city.\n");
            return;
        }

        printf("Enter the map(0~18)\n");
        printf("Player %d choose %d.\n", player_number - 1, hex);
        printf("Enter the corner of the map(0~5)\n");
        printf("Player %d choose %d.\n", player_number - 1, index);

        if (mapCatan[hex].corner[index] != player_number)
        {
            printf("You don't have settlement here so you can't build a city here!\n");
            printf("If you want to build at other places, please choose build function again.\n");
            return;
        }
        else
        {
            printf("Build the city successly\n");
            mapCatan[hex].corner[index] = 5 + player_number;
            sync_map(1, hex, index, mapCatan);
            player[player_number - 1].grain = player[player_number - 1].grain - 2;
            player[player_number - 1].ore = player[player_number - 1].ore - 3;
            bank->grain = bank->grain + 2;
            bank->ore = bank->ore + 3;
            player[player_number - 1].victory_point++;
            player[player_number - 1].city++;

            printf("\n");
        }
    }

    return;
}

void player_trade(characterStruct *player, int32_t player_number, int32_t total_player)
{
    if (player_number == 0)
    {
        // 拿出的資源、想要的資源、夠不夠資源交換
        int32_t change_type[] = {0, 0, 0, 0, 0};
        int32_t want_type[] = {0, 0, 0, 0, 0};
        int32_t can_trade[] = {0, 0, 0, 0};
        int32_t choose_num1 = 0;
        int32_t choose_num2 = 0;
        int32_t choose_player = 0;

        printf("How many card do you want to take out?: ");
        scanf("%d", &choose_num1);

        choose_card(change_type, player_number, choose_num1, player);

        if (judge_card(&(player[player_number]), change_type) == 0)
        {
            printf("You don't have enough card.\n");
            return;
        }

        printf("How many card do you want?: ");
        scanf("%d", &choose_num2);

        choose_card(want_type, player_number, choose_num2, player);
        // 判斷有沒有人可以交易
        for (int32_t i = 0; i < total_player; i++)
        {
            if (i != 0)
            {
                if (judge_card(&(player[i]), want_type) == 1)
                {
                    can_trade[i] = 1;
                }
            }
        }

        // 如果無結束交易程式
        if (can_trade[0] + can_trade[1] + can_trade[2] + can_trade[3] == 0)
        {
            printf("No player can trade with you!\n");
            return;
        }
        // 如果有印出可交易的player給玩家選
        else
        {
            for (int32_t i = 0; i < total_player; i++)
            {
                if (i != 0 && can_trade[i] == 1)
                {
                    printf("Player %d want to trade with you!\n", i);
                }
            }
            // 選出要交易的玩家

            while (1)
            {
                printf("Which player do you want to choose?: ");
                scanf("%d", &choose_player);

                if (can_trade[choose_player] == 1)
                {
                    break;
                }
                else
                {
                    printf("This player can't trade with you!\n");
                }
            }

            // 交易進行
            player[choose_player].brick += change_type[0];
            player[choose_player].lumber += change_type[1];
            player[choose_player].ore += change_type[2];
            player[choose_player].grain += change_type[3];
            player[choose_player].wool += change_type[4];
            player[0].brick -= change_type[0];
            player[0].lumber -= change_type[1];
            player[0].ore -= change_type[2];
            player[0].grain -= change_type[3];
            player[0].wool -= change_type[4];

            player[choose_player].brick -= want_type[0];
            player[choose_player].lumber -= want_type[1];
            player[choose_player].ore -= want_type[2];
            player[choose_player].grain -= want_type[3];
            player[choose_player].wool -= want_type[4];
            player[0].brick += want_type[0];
            player[0].lumber += want_type[1];
            player[0].ore += want_type[2];
            player[0].grain += want_type[3];
            player[0].wool += want_type[4];

            printf("It's deal!\n");
        }
    }
    else
    {
        // 拿出的資源、想要的資源、夠不夠資源交換
        int32_t change_type[] = {0, 0, 0, 0, 0};
        int32_t want_type[] = {0, 0, 0, 0, 0};
        int32_t can_trade[] = {0, 0, 0, 0};
        int32_t choose_num1 = 1;
        int32_t choose_num2 = 1;

        // computer 固定都是1換1
        printf("How many card do you want to take out?\n");
        printf("Player %d want to take out %d card.\n", player_number, choose_num1);

        if (player[player_number].brick > 1)
        {
            change_type[0] = 1;
            printf("Player %d want to take out 1 brick.\n", player_number);
        }
        else if (player[player_number].lumber > 1)
        {
            change_type[1] = 1;
            printf("Player %d want to take out 1 lumber.\n", player_number);
        }
        else if (player[player_number].ore > 1)
        {
            change_type[2] = 1;
            printf("Player %d want to take out 1 ore.\n", player_number);
        }
        else if (player[player_number].grain > 1)
        {
            change_type[3] = 1;
            printf("Player %d want to take out 1 grain.\n", player_number);
        }
        else if (player[player_number].wool > 1)
        {
            change_type[4] = 1;
            printf("Player %d want to take out 1 wool.\n", player_number);
        }

        printf("How many card do you want?\n");
        printf("player %d want %d card.\n", player_number, choose_num2);

        int32_t min = 20;
        int32_t min_type = 0;

        if (player[player_number].brick < min)
        {
            min = player[player_number].brick;
            min_type = 0;
        }
        if (player[player_number].lumber < min)
        {
            min = player[player_number].lumber;
            min_type = 1;
        }
        if (player[player_number].ore < min)
        {
            min = player[player_number].ore;
            min_type = 2;
        }
        if (player[player_number].grain < min)
        {
            min = player[player_number].grain;
            min_type = 3;
        }
        if (player[player_number].wool < min)
        {
            min = player[player_number].wool;
            min_type = 4;
        }

        if (min_type == 0)
        {
            want_type[0] = 1;
            printf("Player %d want 1 brick.\n", player_number);
        }
        else if (min_type == 1)
        {
            want_type[1] = 1;
            printf("Player %d want 1 lumber.\n", player_number);
        }
        else if (min_type == 2)
        {
            want_type[2] = 1;
            printf("Player %d want 1 ore.\n", player_number);
        }
        else if (min_type == 3)
        {
            want_type[3] = 1;
            printf("Player %d want 1 grain.\n", player_number);
        }
        else if (min_type == 4)
        {
            want_type[4] = 1;
            printf("Player %d want 1 wool.\n", player_number);
        }

        // 判斷有沒有人可以交易
        for (int32_t i = 0; i < total_player; i++)
        {
            if (i != player_number)
            {
                if (judge_card(&(player[i]), want_type) == 1)
                {
                    can_trade[i] = 1;
                }
            }
        }

        // 如果無結束交易程式
        if (can_trade[0] + can_trade[1] + can_trade[2] + can_trade[3] == 0)
        {
            printf("No player can trade with player %d!\n", player_number);
            return;
        }
        // 如果有印出可交易的player給玩家選
        else
        {
            for (int32_t i = 0; i < total_player; i++)
            {
                if (can_trade[i] == 1)
                {
                    printf("Player %d can trade with player %d!\n", i, player_number);
                }
            }
            // 選出要交易的玩家(以player 0為優先，讓player 0決定要不要交易)
            int32_t choose_player = 0;

            printf("Which player do you want to choose?\n");

            if (can_trade[0] == 1)
            {
                int32_t want_trade_or_not = 0;
                printf("player %d want to trade with player 0!\n", player_number);
                printf("Do player 0 want to trade?(yes:1, no:0): ");
                scanf("%d", &want_trade_or_not);

                if (want_trade_or_not == 1)
                {
                    // 交易進行
                    printf("Player %d want to trade with player %d too!", choose_player, player_number);

                    player[choose_player].brick += change_type[0];
                    player[choose_player].lumber += change_type[1];
                    player[choose_player].ore += change_type[2];
                    player[choose_player].grain += change_type[3];
                    player[choose_player].wool += change_type[4];
                    player[player_number].brick -= change_type[0];
                    player[player_number].lumber -= change_type[1];
                    player[player_number].ore -= change_type[2];
                    player[player_number].grain -= change_type[3];
                    player[player_number].wool -= change_type[4];

                    player[choose_player].brick -= want_type[0];
                    player[choose_player].lumber -= want_type[1];
                    player[choose_player].ore -= want_type[2];
                    player[choose_player].grain -= want_type[3];
                    player[choose_player].wool -= want_type[4];
                    player[player_number].brick += want_type[0];
                    player[player_number].lumber += want_type[1];
                    player[player_number].ore += want_type[2];
                    player[player_number].grain += want_type[3];
                    player[player_number].wool += want_type[4];
                    printf("It's deal!\n");
                }
            }
            else
            {
                for (int32_t i = 1; i < total_player; i++)
                {
                    if (can_trade[i] == 1)
                    {
                        choose_player = i;
                        break;
                    }
                }

                if (choose_player == 0)
                {
                    printf("No one want to trade with you.\n");
                    return;
                }

                printf("Player %d want to trade with player %d!", player_number, choose_player);
                printf("Player %d want to trade with player %d too!", choose_player, player_number);

                // 交易進行
                player[player_number].brick += want_type[0];
                player[player_number].lumber += want_type[1];
                player[player_number].ore += want_type[2];
                player[player_number].grain += want_type[3];
                player[player_number].wool += want_type[4];
                player[choose_player].brick -= want_type[0];
                player[choose_player].lumber -= want_type[1];
                player[choose_player].ore -= want_type[2];
                player[choose_player].grain -= want_type[3];
                player[choose_player].wool -= want_type[4];

                player[player_number].brick -= change_type[0];
                player[player_number].lumber -= change_type[1];
                player[player_number].ore -= change_type[2];
                player[player_number].grain -= change_type[3];
                player[player_number].wool -= change_type[4];
                player[choose_player].brick += change_type[0];
                player[choose_player].lumber += change_type[1];
                player[choose_player].ore += change_type[2];
                player[choose_player].grain += change_type[3];
                player[choose_player].wool += change_type[4];

                printf("It's deal!\n");
            }
        }
    }

    return;
}

// 深度優先搜尋 //currentVertex是頂點
void dfs(int currentVertex, int currentPath, int player_number)
{
    extern int graph[MAX_VERTICES][MAX_VERTICES];
    extern int nodeValues[MAX_VERTICES];
    extern bool visited[MAX_VERTICES];
    extern int maxPath;
    int targetValue = player_number + 1;

    // 標記當前節點已被訪問
    visited[currentVertex] = true;

    // 檢查當前節點的所有鄰接節點
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        // 如果節點 i 是當前節點的鄰接節點且尚未訪問
        if (graph[currentVertex][i] == targetValue && !visited[i] && (nodeValues[i] == 0 || nodeValues[i] == targetValue))
        {
            int edgeValue = graph[currentVertex][i]; // 獲取當前節點到鄰接節點的邊的值
            int nodeValue = nodeValues[i];           // 獲取鄰接節點的值 nodeValue
            int nextPath = currentPath + 1;          // 紀錄道路長度

            // 如果找到更大的路徑，則更新最大路徑
            if (nextPath > maxPath && (edgeValue == targetValue && (nodeValue == targetValue || nodeValue == 0)))
            {
                maxPath = nextPath;
            }
            // 遞迴搜尋下一個節點
            dfs(i, nextPath, player_number);
        }
    }

    // 還原當前節點的訪問狀態
    visited[currentVertex] = false;
}

int32_t whose_road_length(mapStruct *map, int32_t player_number)
{
    initializeGraphAndNodeValues(map);
    extern int maxPath;
    maxPath = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        dfs(i, 0, player_number);
    }
    return maxPath;
}

// map每角位須先同步再使用
void is_longest_road(characterStruct *player, int32_t total_player, int32_t player_number, mapStruct *map)
{
    // 找原最大道路,總分+2分
    int32_t oriowner = -1;
    int32_t ori_max_road = -1;
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].max_road_card == 1)
        {
            ori_max_road = player[i].road_length;
            oriowner = i;
            break;
        }
    }

    for (int32_t i = 0; i < total_player; i++)
    {
        player[i].road_length = whose_road_length(map, i); // 將玩家道路長度存進玩家結構中
        // printf("player[%d].road_length:%d\n", i, player[i].road_length);
    }

    int32_t maxowner = -1;
    int32_t max_road = -1;

    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].road_length > max_road && player[i].road_length >= 5)
        {
            max_road = player[i].road_length;
            maxowner = i;
        }
    }
    if ((maxowner == player_number) && (oriowner != player_number) && (max_road > ori_max_road))
    {
        player[player_number].victory_point += 2;
        player[player_number].max_road_card = 1;

        if (oriowner != -1)
        {
            player[oriowner].victory_point -= 2;
            player[oriowner].max_road_card = 0;
        }
    }

    return;
}

// map每角位須先同步再使用
void initializeGraphAndNodeValues(mapStruct *map_Catan)
{

    extern int graph[MAX_VERTICES][MAX_VERTICES];
    extern int nodeValues[MAX_VERTICES];
    // 設定節點值
    nodeValues[0] = map_Catan[0].corner[0] % 5;
    nodeValues[1] = map_Catan[0].corner[1] % 5;
    nodeValues[2] = map_Catan[1].corner[0] % 5;
    nodeValues[3] = map_Catan[1].corner[1] % 5;
    nodeValues[4] = map_Catan[0].corner[2] % 5;
    nodeValues[5] = map_Catan[2].corner[1] % 5;
    nodeValues[6] = map_Catan[3].corner[0] % 5;
    nodeValues[7] = map_Catan[3].corner[1] % 5;
    nodeValues[8] = map_Catan[1].corner[2] % 5;
    nodeValues[9] = map_Catan[2].corner[5] % 5;
    nodeValues[10] = map_Catan[5].corner[0] % 5;
    nodeValues[11] = map_Catan[5].corner[1] % 5;
    nodeValues[12] = map_Catan[3].corner[5] % 5;
    nodeValues[13] = map_Catan[3].corner[2] % 5;
    nodeValues[14] = map_Catan[1].corner[3] % 5;
    nodeValues[15] = map_Catan[4].corner[2] % 5;
    nodeValues[16] = map_Catan[5].corner[5] % 5;
    nodeValues[17] = map_Catan[5].corner[2] % 5;
    nodeValues[18] = map_Catan[8].corner[0] % 5;
    nodeValues[19] = map_Catan[8].corner[1] % 5;
    nodeValues[20] = map_Catan[9].corner[0] % 5;
    nodeValues[21] = map_Catan[9].corner[1] % 5;
    nodeValues[22] = map_Catan[10].corner[0] % 5;
    nodeValues[23] = map_Catan[10].corner[1] % 5;
    nodeValues[24] = map_Catan[8].corner[5] % 5;
    nodeValues[25] = map_Catan[8].corner[2] % 5;
    nodeValues[26] = map_Catan[9].corner[5] % 5;
    // nodeValues[26] = 2;
    nodeValues[27] = map_Catan[9].corner[2] % 5;
    nodeValues[28] = map_Catan[10].corner[5] % 5;
    nodeValues[29] = map_Catan[10].corner[2] % 5;
    nodeValues[30] = map_Catan[13].corner[0] % 5;
    nodeValues[31] = map_Catan[13].corner[1] % 5;
    nodeValues[32] = map_Catan[14].corner[0] % 5;
    nodeValues[33] = map_Catan[14].corner[1] % 5;
    nodeValues[34] = map_Catan[15].corner[0] % 5;
    nodeValues[35] = map_Catan[15].corner[1] % 5;
    nodeValues[36] = map_Catan[13].corner[5] % 5;
    nodeValues[37] = map_Catan[13].corner[2] % 5;
    nodeValues[38] = map_Catan[14].corner[5] % 5;
    nodeValues[39] = map_Catan[14].corner[2] % 5;
    nodeValues[40] = map_Catan[15].corner[5] % 5;
    nodeValues[41] = map_Catan[15].corner[2] % 5;
    nodeValues[42] = map_Catan[13].corner[4] % 5;
    nodeValues[43] = map_Catan[16].corner[5] % 5;
    nodeValues[44] = map_Catan[16].corner[2] % 5;
    nodeValues[45] = map_Catan[17].corner[5] % 5;
    nodeValues[46] = map_Catan[17].corner[2] % 5;
    nodeValues[47] = map_Catan[15].corner[3] % 5;
    nodeValues[48] = map_Catan[16].corner[4] % 5;
    nodeValues[49] = map_Catan[18].corner[5] % 5;
    nodeValues[50] = map_Catan[18].corner[2] % 5;
    nodeValues[51] = map_Catan[17].corner[3] % 5;
    nodeValues[52] = map_Catan[18].corner[4] % 5;
    nodeValues[53] = map_Catan[18].corner[3] % 5;

    // 設定圖形的邊的相鄰關係
    graph[0][1] = map_Catan[0].side[0] % 5;
    graph[0][3] = map_Catan[0].side[5] % 5;
    graph[1][0] = map_Catan[0].side[0] % 5;
    graph[1][4] = map_Catan[0].side[1] % 5;
    graph[2][3] = map_Catan[1].side[0] % 5;
    graph[2][7] = map_Catan[1].side[5] % 5;
    graph[3][0] = map_Catan[0].side[5] % 5;
    graph[3][2] = map_Catan[1].side[0] % 5;
    graph[3][8] = map_Catan[0].side[4] % 5;
    graph[4][1] = map_Catan[0].side[1] % 5;
    graph[4][5] = map_Catan[2].side[0] % 5;
    graph[4][9] = map_Catan[2].side[5] % 5;
    graph[5][4] = map_Catan[2].side[0] % 5;
    graph[5][10] = map_Catan[2].side[1] % 5;
    graph[6][7] = map_Catan[3].side[0] % 5;
    graph[6][12] = map_Catan[3].side[5] % 5;
    graph[7][2] = map_Catan[1].side[5] % 5;
    graph[7][6] = map_Catan[3].side[0] % 5;
    graph[7][13] = map_Catan[3].side[1] % 5;
    graph[8][3] = map_Catan[1].side[1] % 5;
    graph[8][9] = map_Catan[0].side[3] % 5;
    graph[8][14] = map_Catan[1].side[2] % 5;
    graph[9][4] = map_Catan[2].side[5] % 5;
    graph[9][8] = map_Catan[0].side[3] % 5;
    graph[9][15] = map_Catan[2].side[4] % 5;
    graph[10][5] = map_Catan[2].side[1] % 5;
    graph[10][11] = map_Catan[5].side[0] % 5;
    graph[10][16] = map_Catan[5].side[5] % 5;
    graph[11][10] = map_Catan[5].side[0] % 5;
    graph[11][17] = map_Catan[5].side[1] % 5;
    graph[12][6] = map_Catan[3].side[5] % 5;
    graph[12][18] = map_Catan[3].side[4] % 5;
    graph[13][7] = map_Catan[1].side[4] % 5;
    graph[13][14] = map_Catan[6].side[0] % 5;
    graph[13][19] = map_Catan[6].side[5] % 5;
    graph[14][8] = map_Catan[4].side[5] % 5;
    graph[14][13] = map_Catan[6].side[0] % 5;
    graph[14][20] = map_Catan[6].side[1] % 5;
    graph[15][9] = map_Catan[4].side[1] % 5;
    graph[15][16] = map_Catan[7].side[0] % 5;
    graph[15][21] = map_Catan[7].side[5] % 5;
    graph[16][10] = map_Catan[5].side[5] % 5;
    graph[16][15] = map_Catan[7].side[0] % 5;
    graph[16][22] = map_Catan[7].side[1] % 5;
    graph[17][11] = map_Catan[5].side[1] % 5;
    graph[17][23] = map_Catan[5].side[2] % 5;
    graph[18][12] = map_Catan[3].side[4] % 5;
    graph[18][19] = map_Catan[3].side[3] % 5;
    graph[18][24] = map_Catan[8].side[5] % 5;
    graph[19][13] = map_Catan[6].side[5] % 5;
    graph[19][18] = map_Catan[8].side[0] % 5;
    graph[19][25] = map_Catan[8].side[1] % 5;
    graph[20][14] = map_Catan[6].side[1] % 5;
    graph[20][21] = map_Catan[9].side[0] % 5;
    graph[20][26] = map_Catan[9].side[5] % 5;
    graph[21][15] = map_Catan[7].side[5] % 5;
    graph[21][20] = map_Catan[9].side[0] % 5;
    graph[21][27] = map_Catan[9].side[1] % 5;
    graph[22][16] = map_Catan[7].side[1] % 5;
    graph[22][23] = map_Catan[10].side[0] % 5;
    graph[22][28] = map_Catan[10].side[5] % 5;
    graph[23][17] = map_Catan[5].side[2] % 5;
    graph[23][22] = map_Catan[10].side[0] % 5;
    graph[23][29] = map_Catan[10].side[1] % 5;
    graph[24][18] = map_Catan[8].side[5] % 5;
    graph[24][30] = map_Catan[8].side[4] % 5;
    graph[25][19] = map_Catan[8].side[1] % 5;
    graph[25][26] = map_Catan[11].side[0] % 5;
    graph[25][31] = map_Catan[11].side[5] % 5;
    graph[26][20] = map_Catan[9].side[5] % 5;
    graph[26][25] = map_Catan[11].side[0] % 5;
    graph[26][32] = map_Catan[11].side[1] % 5;
    graph[27][21] = map_Catan[9].side[1] % 5;
    graph[27][28] = map_Catan[12].side[0] % 5;
    graph[27][33] = map_Catan[12].side[5] % 5;
    graph[28][22] = map_Catan[10].side[5] % 5;
    graph[28][27] = map_Catan[12].side[0] % 5;
    graph[28][34] = map_Catan[12].side[1] % 5;
    graph[29][23] = map_Catan[10].side[1] % 5;
    graph[29][35] = map_Catan[10].side[2] % 5;
    graph[30][24] = map_Catan[8].side[4] % 5;
    graph[30][36] = map_Catan[13].side[5] % 5;
    graph[30][31] = map_Catan[13].side[0] % 5;
    graph[31][25] = map_Catan[11].side[5] % 5;
    graph[31][30] = map_Catan[13].side[0] % 5;
    graph[31][37] = map_Catan[13].side[1] % 5;
    graph[32][38] = map_Catan[14].side[5] % 5;
    graph[32][33] = map_Catan[14].side[0] % 5;
    graph[32][26] = map_Catan[11].side[1] % 5;
    graph[33][39] = map_Catan[14].side[1] % 5;
    graph[33][27] = map_Catan[12].side[5] % 5;
    graph[33][32] = map_Catan[14].side[0] % 5;
    graph[34][28] = map_Catan[12].side[1] % 5;
    graph[34][40] = map_Catan[15].side[5] % 5;
    graph[34][35] = map_Catan[15].side[0] % 5;
    graph[35][34] = map_Catan[15].side[0] % 5;
    graph[35][29] = map_Catan[10].side[2] % 5;
    graph[35][41] = map_Catan[15].side[1] % 5;
    graph[36][30] = map_Catan[13].side[5] % 5;
    graph[36][42] = map_Catan[13].side[4] % 5;
    graph[37][31] = map_Catan[13].side[1] % 5;
    graph[37][38] = map_Catan[16].side[0] % 5;
    graph[37][43] = map_Catan[16].side[5] % 5;
    graph[38][32] = map_Catan[14].side[5] % 5;
    graph[38][37] = map_Catan[16].side[0] % 5;
    graph[38][44] = map_Catan[16].side[1] % 5;
    graph[39][33] = map_Catan[14].side[1] % 5;
    graph[39][40] = map_Catan[17].side[0] % 5;
    graph[39][45] = map_Catan[17].side[5] % 5;
    graph[40][39] = map_Catan[17].side[0] % 5;
    graph[40][34] = map_Catan[15].side[5] % 5;
    graph[40][46] = map_Catan[17].side[1] % 5;
    graph[41][35] = map_Catan[15].side[1] % 5;
    graph[41][47] = map_Catan[15].side[2] % 5;
    graph[42][36] = map_Catan[13].side[4] % 5;
    graph[42][43] = map_Catan[13].side[3] % 5;
    graph[43][37] = map_Catan[16].side[5] % 5;
    graph[43][42] = map_Catan[13].side[3] % 5;
    graph[43][48] = map_Catan[16].side[4] % 5;
    graph[44][38] = map_Catan[16].side[1] % 5;
    graph[44][45] = map_Catan[18].side[0] % 5;
    graph[44][49] = map_Catan[18].side[5] % 5;
    graph[45][39] = map_Catan[17].side[5] % 5;
    graph[45][44] = map_Catan[18].side[0] % 5;
    graph[45][50] = map_Catan[18].side[1] % 5;
    graph[46][40] = map_Catan[17].side[1] % 5;
    graph[46][47] = map_Catan[15].side[3] % 5;
    graph[46][51] = map_Catan[17].side[2] % 5;
    graph[47][41] = map_Catan[15].side[2] % 5;
    graph[47][46] = map_Catan[15].side[3] % 5;
    graph[48][43] = map_Catan[16].side[4] % 5;
    graph[48][49] = map_Catan[16].side[3] % 5;
    graph[49][44] = map_Catan[18].side[5] % 5;
    graph[49][48] = map_Catan[16].side[3] % 5;
    graph[49][52] = map_Catan[18].side[4] % 5;
    graph[50][45] = map_Catan[18].side[1] % 5;
    graph[50][51] = map_Catan[17].side[3] % 5;
    graph[50][53] = map_Catan[18].side[2] % 5;
    graph[51][46] = map_Catan[17].side[2] % 5;
    graph[51][50] = map_Catan[17].side[3] % 5;
    graph[52][49] = map_Catan[18].side[4] % 5;
    graph[52][53] = map_Catan[18].side[3] % 5;
    graph[53][50] = map_Catan[18].side[2] % 5;
    graph[53][52] = map_Catan[18].side[3] % 5;
    return;
}

// new function by hugo
void game_start_build(mapStruct *map_Catan, mapStruct *player1_build, mapStruct *player2_build, mapStruct *player3_build, mapStruct *player4_build, characterStruct *player1, characterStruct *player2, characterStruct *player3, characterStruct *player4, int32_t total_player, characterStruct *player, bankStruct *bank)
{
    int32_t hex = 0;
    int32_t index = 0;
    // player0 first
    print_map(map_Catan, total_player);
    printf("\n");
    printf("\n======================================================\n\n");
    sleep(1);
    map_for_choose();
    while (1)
    {
        printf("Player0 choose first. Where do you want to build your settlement?\n");
        printf("Enter the map(0~18): ");
        scanf("%d", &hex);
        printf("Enter the corner of the map(0~5): ");
        scanf("%d", &index);
        all_settlement_buildable(player1_build);
        is_buildable(map_Catan, player1_build, 1);
        if (player1_build[hex].corner[index] == -1)
        {
            printf("You can't choose here! Please choose again!\n");
        }
        else
        {
            printf("Build settlement successfully!\n");
            sleep(1);
            map_Catan[hex].corner[index] = 1;
            sync_map(1, hex, index, map_Catan);
            if (map_Catan[hex].port[index] > 0)
            {
                player1->port[map_Catan[hex].port[index] - 1] = 1;
            }
            player1->settlement++;
            player1->victory_point++;
            printf("\n");
            print_map(map_Catan, total_player);
            printf("\n");
            break;
        }
    }
    one_point_roadbuildable(player1_build, hex, index, 1);
    while (1)
    {
        printf("Player0 build a settlement. Where do you want to build your road?\n");
        printf("Enter the map(0~18): ");
        scanf("%d", &hex);
        printf("Enter the side of the map(0~5): ");
        scanf("%d", &index);
        if (player1_build[hex].side[index] == -1)
        {
            printf("You can't choose here! Please choose again!\n");
        }
        else
        {
            printf("Build road successfully!\n");
            sleep(1);
            map_Catan[hex].side[index] = 1;
            sync_map(0, hex, index, map_Catan);
            player1->used_road++;
            // 判斷最長道路
            is_longest_road(player, total_player, 0, map_Catan);
            printf("\n");
            break;
        }
    }
    print_map(map_Catan, total_player);
    printf("\n======================================================\n\n");
    sleep(1);
    // player1 first
    map_for_choose();
    printf("Player1 choose. Where do you want to build your settlement?\n");
    sleep(1);
    srand(time(NULL));
    all_settlement_buildable(player2_build);
    is_buildable(map_Catan, player2_build, 2);
    while (1)
    {
        hex = rand() % 19;
        index = rand() % 6;
        if (player2_build[hex].corner[index] == 0)
        {
            break;
        }
    }
    printf("Enter the map(0~18): %d\n", hex);
    sleep(1);
    printf("Enter the corner of the map(0~5): %d\n", index);
    printf("Build settlement successfully!\n");
    sleep(1);
    map_Catan[hex].corner[index] = 2;
    sync_map(1, hex, index, map_Catan);
    if ((map_Catan[hex].port[index]) > 0)
    {
        player2->port[map_Catan[hex].port[index] - 1] = 1;
    }
    player2->settlement++;
    player2->victory_point++;
    printf("\n");
    print_map(map_Catan, total_player);
    printf("\n");

    one_point_roadbuildable(player2_build, hex, index, 2);

    printf("Player1 build a settlement. Where do you want to build your road?\n");
    sleep(1);
    int32_t can_build_road_hex[6] = {0};   // for computer(全部電腦都共用所以只在這裡宣告)
    int32_t can_build_road_index[6] = {0}; // for computer(全部電腦都共用所以只在這裡宣告)
    int32_t tmp_counter = 0;               // for computer(全部電腦都共用所以只在這裡宣告)
    for (int32_t i = 0; i < 19; i++)
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (player2_build[i].side[j] == 0)
            {
                can_build_road_hex[tmp_counter] = i;
                can_build_road_index[tmp_counter] = j;
                tmp_counter++;
            }
        }
    }
    tmp_counter = 0;
    srand(time(NULL));
    while (1)
    {
        int32_t random = rand() % 6;
        hex = can_build_road_hex[random];
        index = can_build_road_index[random];
        if (player2_build[hex].side[index] == 0)
        {
            break;
        }
    }
    printf("Enter the map(0~18): %d\n", hex);
    printf("Enter the side of the map(0~5): %d\n", index);
    printf("Build road successfully!\n");
    map_Catan[hex].side[index] = 2;
    sync_map(0, hex, index, map_Catan);
    player2->used_road++;
    // 判斷最長道路
    is_longest_road(player, total_player, 1, map_Catan);
    printf("\n");

    print_map(map_Catan, total_player);
    printf("\n======================================================\n\n");
    sleep(1);
    // player2 first
    map_for_choose();
    printf("Player2 choose. Where do you want to build your settlement?\n");
    sleep(1);
    srand(time(NULL));
    all_settlement_buildable(player3_build);
    is_buildable(map_Catan, player3_build, 3);
    while (1)
    {
        hex = rand() % 19;
        index = rand() % 6;
        if (player3_build[hex].corner[index] == 0)
        {
            break;
        }
    }
    printf("Enter the map(0~18): %d\n", hex);
    sleep(1);
    printf("Enter the corner of the map(0~5): %d\n", index);
    printf("Build settlement successfully!\n");
    sleep(1);
    map_Catan[hex].corner[index] = 3;
    sync_map(1, hex, index, map_Catan);
    if ((map_Catan[hex].port[index]) > 0)
    {
        player3->port[map_Catan[hex].port[index] - 1] = 1;
    }
    player3->settlement++;
    player3->victory_point++;
    printf("\n");
    print_map(map_Catan, total_player);
    printf("\n");

    one_point_roadbuildable(player3_build, hex, index, 3);

    printf("Player2 build a settlement. Where do you want to build your road?\n");
    sleep(1);
    for (int32_t i = 0; i < 19; i++)
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (player3_build[i].side[j] == 0)
            {
                can_build_road_hex[tmp_counter] = i;
                can_build_road_index[tmp_counter] = j;
                tmp_counter++;
            }
        }
    }
    tmp_counter = 0;
    srand(time(NULL));
    while (1)
    {
        int32_t random = rand() % 6;
        hex = can_build_road_hex[random];
        index = can_build_road_index[random];
        if (player3_build[hex].side[index] == 0)
        {
            break;
        }
    }
    printf("Enter the map(0~18): %d\n", hex);
    sleep(1);
    printf("Enter the side of the map(0~5): %d\n", index);
    printf("Build road successfully!\n");
    sleep(1);
    map_Catan[hex].side[index] = 3;
    sync_map(0, hex, index, map_Catan);
    player3->used_road++;
    // 判斷最長道路
    is_longest_road(player, total_player, 2, map_Catan);
    printf("\n");

    print_map(map_Catan, total_player);
    printf("\n======================================================\n\n");
    sleep(1);

    mapStruct *map_give_resourse = NULL;                             // 為了在第二輪給資源用(只在這裡宣告，下面共用)
    map_give_resourse = (mapStruct *)malloc(19 * sizeof(mapStruct)); // 為了在第二輪給資源用(只在這裡宣告，下面共用)

    if (total_player == 4)
    {
        // player3 first
        map_for_choose();
        printf("Player3 choose. Where do you want to build your settlement?\n");
        sleep(1);
        srand(time(NULL));
        all_settlement_buildable(player4_build);
        is_buildable(map_Catan, player4_build, 4);
        while (1)
        {
            hex = rand() % 19;
            index = rand() % 6;
            if (player4_build[hex].corner[index] == 0)
            {
                break;
            }
        }
        printf("Enter the map(0~18): %d\n", hex);
        sleep(1);
        printf("Enter the corner of the map(0~5): %d\n", index);
        printf("Build settlement successfully!\n");
        sleep(1);
        map_Catan[hex].corner[index] = 4;
        sync_map(1, hex, index, map_Catan);
        if ((map_Catan[hex].port[index]) > 0)
        {
            player4->port[map_Catan[hex].port[index] - 1] = 1;
        }
        player4->settlement++;
        player4->victory_point++;
        printf("\n");
        print_map(map_Catan, total_player);
        printf("\n");

        one_point_roadbuildable(player4_build, hex, index, 4);

        printf("Player3 build a settlement. Where do you want to build your road?\n");
        sleep(1);
        for (int32_t i = 0; i < 19; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (player4_build[i].side[j] == 0)
                {
                    can_build_road_hex[tmp_counter] = i;
                    can_build_road_index[tmp_counter] = j;
                    tmp_counter++;
                }
            }
        }
        tmp_counter = 0;
        srand(time(NULL));
        while (1)
        {
            int32_t random = rand() % 6;
            hex = can_build_road_hex[random];
            index = can_build_road_index[random];
            if (player4_build[hex].side[index] == 0)
            {
                break;
            }
        }
        printf("Enter the map(0~18): %d\n", hex);
        sleep(1);
        printf("Enter the side of the map(0~5): %d\n", index);
        printf("Build road successfully!\n");
        sleep(1);
        map_Catan[hex].side[index] = 4;
        sync_map(0, hex, index, map_Catan);
        player4->used_road++;
        // 判斷最長道路
        is_longest_road(player, total_player, 3, map_Catan);
        printf("\n");

        print_map(map_Catan, total_player);
        printf("\n======================================================\n\n");
        sleep(1);
        // player3 second
        map_for_choose();
        printf("Player3 choose first in second round. Where do you want to build your settlement?\n");
        sleep(1);
        srand(time(NULL));
        all_settlement_buildable(player4_build);
        is_buildable(map_Catan, player4_build, 4);
        while (1)
        {
            hex = rand() % 19;
            index = rand() % 6;
            if (player4_build[hex].corner[index] == 0)
            {
                break;
            }
        }
        printf("Enter the map(0~18): %d\n", hex);
        sleep(1);
        printf("Enter the corner of the map(0~5): %d\n", index);
        printf("Build settlement successfully!\n");
        sleep(1);

        generate_map(map_give_resourse); // 為了在第二輪給資源用
        map_Catan[hex].corner[index] = 4;
        map_give_resourse[hex].corner[index] = 4; // 為了在第二輪給資源用
        sync_map(1, hex, index, map_Catan);
        sync_map(1, hex, index, map_give_resourse); // 為了在第二輪給資源用
        for (int32_t i = 0; i < 19; i++)            // 為了在第二輪給資源用
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (map_give_resourse[i].corner[j] > 0)
                {
                    if (map_Catan[i].resourse == 0)
                    {
                        player4->brick++;
                        bank->brick--;
                    }
                    else if (map_Catan[i].resourse == 1)
                    {
                        player4->lumber++;
                        bank->lumber--;
                    }
                    else if (map_Catan[i].resourse == 2)
                    {
                        player4->ore++;
                        bank->ore--;
                    }
                    else if (map_Catan[i].resourse == 3)
                    {
                        player4->grain++;
                        bank->grain--;
                    }
                    else if (map_Catan[i].resourse == 4)
                    {
                        player4->wool++;
                        bank->wool--;
                    }
                }
            }
        }
        if ((map_Catan[hex].port[index]) > 0)
        {
            player4->port[map_Catan[hex].port[index] - 1] = 1;
        }
        player4->settlement++;
        player4->victory_point++;
        printf("\n");
        print_map(map_Catan, total_player);
        printf("\n");

        one_point_roadbuildable(player4_build, hex, index, 4);

        printf("Player3 build a settlement. Where do you want to build your road?\n");
        sleep(1);
        for (int32_t i = 0; i < 19; i++)
        {
            for (int32_t j = 0; j < 6; j++)
            {
                if (player4_build[i].side[j] == 0)
                {
                    can_build_road_hex[tmp_counter] = i;
                    can_build_road_index[tmp_counter] = j;
                    tmp_counter++;
                }
            }
        }
        tmp_counter = 0;
        srand(time(NULL));
        while (1)
        {
            int32_t random = rand() % 6;
            hex = can_build_road_hex[random];
            index = can_build_road_index[random];
            if (player4_build[hex].side[index] == 0)
            {
                break;
            }
        }
        printf("Enter the map(0~18): %d\n", hex);
        sleep(1);
        printf("Enter the side of the map(0~5): %d\n", index);
        printf("Build road successfully!\n");
        sleep(1);
        map_Catan[hex].side[index] = 4;
        sync_map(0, hex, index, map_Catan);
        player4->used_road++;
        // 判斷最長道路
        is_longest_road(player, total_player, 3, map_Catan);
        printf("\n");

        print_map(map_Catan, total_player);
        printf("\n======================================================\n\n");
        sleep(1);
    }
    // player2 second
    map_for_choose();
    if (total_player == 4)
    {
        printf("Player2 choose. Where do you want to build your settlement?\n");
    }
    else if (total_player == 3)
    {
        printf("Player2 choose first in second round. Where do you want to build your settlement?\n");
    }
    sleep(1);
    srand(time(NULL));
    all_settlement_buildable(player3_build);
    is_buildable(map_Catan, player3_build, 3);
    while (1)
    {
        hex = rand() % 19;
        index = rand() % 6;
        if (player3_build[hex].corner[index] == 0)
        {
            break;
        }
    }
    printf("Enter the map(0~18): %d\n", hex);
    sleep(1);
    printf("Enter the corner of the map(0~5): %d\n", index);
    printf("Build settlement successfully!\n");
    generate_map(map_give_resourse); // 為了在第二輪給資源用
    sleep(1);
    map_Catan[hex].corner[index] = 3;
    map_give_resourse[hex].corner[index] = 3;
    sync_map(1, hex, index, map_Catan);
    sync_map(1, hex, index, map_give_resourse);
    for (int32_t i = 0; i < 19; i++) // 為了在第二輪給資源用
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (map_give_resourse[i].corner[j] > 0)
            {
                if (map_Catan[i].resourse == 0)
                {
                    player3->brick++;
                    bank->brick--;
                }
                else if (map_Catan[i].resourse == 1)
                {
                    player3->lumber++;
                    bank->lumber--;
                }
                else if (map_Catan[i].resourse == 2)
                {
                    player3->ore++;
                    bank->ore--;
                }
                else if (map_Catan[i].resourse == 3)
                {
                    player3->grain++;
                    bank->grain--;
                }
                else if (map_Catan[i].resourse == 4)
                {
                    player3->wool++;
                    bank->wool--;
                }
            }
        }
    }
    if ((map_Catan[hex].port[index]) > 0)
    {
        player3->port[map_Catan[hex].port[index] - 1] = 1;
    }
    player3->settlement++;
    player3->victory_point++;
    printf("\n");
    print_map(map_Catan, total_player);
    printf("\n");

    one_point_roadbuildable(player3_build, hex, index, 3);

    printf("Player2 build a settlement. Where do you want to build your road?\n");
    sleep(1);
    for (int32_t i = 0; i < 19; i++)
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (player3_build[i].side[j] == 0)
            {
                can_build_road_hex[tmp_counter] = i;
                can_build_road_index[tmp_counter] = j;
                tmp_counter++;
            }
        }
    }
    tmp_counter = 0;
    srand(time(NULL));
    while (1)
    {
        int32_t random = rand() % 6;
        hex = can_build_road_hex[random];
        index = can_build_road_index[random];
        if (player3_build[hex].side[index] == 0)
        {
            break;
        }
    }
    printf("Enter the map(0~18): %d\n", hex);
    sleep(1);
    printf("Enter the side of the map(0~5): %d\n", index);
    printf("Build road successfully!\n");
    sleep(1);
    map_Catan[hex].side[index] = 3;
    sync_map(0, hex, index, map_Catan);
    player3->used_road++;
    // 判斷最長道路
    is_longest_road(player, total_player, 2, map_Catan);
    printf("\n");

    print_map(map_Catan, total_player);
    printf("\n======================================================\n\n");
    sleep(1);
    // player1 second
    map_for_choose();
    printf("Player1 choose. Where do you want to build your settlement?\n");
    sleep(1);
    srand(time(NULL));
    all_settlement_buildable(player2_build);
    is_buildable(map_Catan, player2_build, 2);
    while (1)
    {
        hex = rand() % 19;
        index = rand() % 6;
        if (player2_build[hex].corner[index] == 0)
        {
            break;
        }
    }
    printf("Enter the map(0~18): %d\n", hex);
    sleep(1);
    printf("Enter the corner of the map(0~5): %d\n", index);
    printf("Build settlement successfully!\n");
    generate_map(map_give_resourse); // 為了在第二輪給資源用
    sleep(1);
    map_Catan[hex].corner[index] = 2;
    map_give_resourse[hex].corner[index] = 2;
    sync_map(1, hex, index, map_Catan);
    sync_map(1, hex, index, map_give_resourse);
    for (int32_t i = 0; i < 19; i++) // 為了在第二輪給資源用
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (map_give_resourse[i].corner[j] > 0)
            {
                if (map_Catan[i].resourse == 0)
                {
                    player2->brick++;
                    bank->brick--;
                }
                else if (map_Catan[i].resourse == 1)
                {
                    player2->lumber++;
                    bank->lumber--;
                }
                else if (map_Catan[i].resourse == 2)
                {
                    player2->ore++;
                    bank->ore--;
                }
                else if (map_Catan[i].resourse == 3)
                {
                    player2->grain++;
                    bank->grain--;
                }
                else if (map_Catan[i].resourse == 4)
                {
                    player2->wool++;
                    bank->wool--;
                }
            }
        }
    }
    if ((map_Catan[hex].port[index]) > 0)
    {
        player2->port[map_Catan[hex].port[index] - 1] = 1;
    }
    player2->settlement++;
    player2->victory_point++;
    printf("\n");
    print_map(map_Catan, total_player);
    printf("\n");

    one_point_roadbuildable(player2_build, hex, index, 2);

    printf("Player1 build a settlement. Where do you want to build your road?\n");
    sleep(1);
    for (int32_t i = 0; i < 19; i++)
    {
        for (int32_t j = 0; j < 6; j++)
        {
            if (player2_build[i].side[j] == 0)
            {
                can_build_road_hex[tmp_counter] = i;
                can_build_road_index[tmp_counter] = j;
                tmp_counter++;
            }
        }
    }
    tmp_counter = 0;
    srand(time(NULL));
    while (1)
    {
        int32_t random = rand() % 6;
        hex = can_build_road_hex[random];
        index = can_build_road_index[random];
        if (player2_build[hex].side[index] == 0)
        {
            break;
        }
    }
    printf("Enter the map(0~18): %d\n", hex);
    sleep(1);
    printf("Enter the side of the map(0~5): %d\n", index);
    printf("Build road successfully!\n");
    sleep(1);
    map_Catan[hex].side[index] = 2;
    sync_map(0, hex, index, map_Catan);
    player2->used_road++;
    // 判斷最長道路
    is_longest_road(player, total_player, 1, map_Catan);
    printf("\n");

    print_map(map_Catan, total_player);
    printf("\n======================================================\n\n");
    sleep(1);
    // player0 second
    map_for_choose();
    while (1)
    {
        printf("Player0 choose. Where do you want to build your settlement?\n");
        printf("Enter the map(0~18): ");
        scanf("%d", &hex);
        printf("Enter the corner of the map(0~5): ");
        scanf("%d", &index);
        all_settlement_buildable(player1_build);
        is_buildable(map_Catan, player1_build, 1);
        if (player1_build[hex].corner[index] == -1)
        {
            printf("You can't choose here! Please choose again!\n");
        }
        else
        {
            printf("Build settlement successfully!\n");
            generate_map(map_give_resourse); // 為了在第二輪給資源用
            sleep(1);
            map_Catan[hex].corner[index] = 1;
            map_give_resourse[hex].corner[index] = 1;
            sync_map(1, hex, index, map_Catan);
            sync_map(1, hex, index, map_give_resourse);
            for (int32_t i = 0; i < 19; i++) // 為了在第二輪給資源用
            {
                for (int32_t j = 0; j < 6; j++)
                {
                    if (map_give_resourse[i].corner[j] > 0)
                    {
                        if (map_Catan[i].resourse == 0)
                        {
                            player1->brick++;
                            bank->brick--;
                        }
                        else if (map_Catan[i].resourse == 1)
                        {
                            player1->lumber++;
                            bank->lumber--;
                        }
                        else if (map_Catan[i].resourse == 2)
                        {
                            player1->ore++;
                            bank->ore--;
                        }
                        else if (map_Catan[i].resourse == 3)
                        {
                            player1->grain++;
                            bank->grain--;
                        }
                        else if (map_Catan[i].resourse == 4)
                        {
                            player1->wool++;
                            bank->wool--;
                        }
                    }
                }
            }
            if ((map_Catan[hex].port[index]) > 0)
            {
                player1->port[map_Catan[hex].port[index] - 1] = 1;
            }
            player1->settlement++;
            player1->victory_point++;
            printf("\n");
            print_map(map_Catan, total_player);
            printf("\n");
            break;
        }
    }
    one_point_roadbuildable(player1_build, hex, index, 1);
    while (1)
    {
        printf("Player0 build a settlement. Where do you want to build your road?\n");
        printf("Enter the map(0~18): ");
        scanf("%d", &hex);
        printf("Enter the side of the map(0~5): ");
        scanf("%d", &index);
        if (player1_build[hex].side[index] == -1)
        {
            printf("You can't choose here! Please choose again!\n");
        }
        else
        {
            printf("Build road successfully!\n");
            sleep(1);
            map_Catan[hex].side[index] = 1;
            sync_map(0, hex, index, map_Catan);
            player1->used_road++;
            // 判斷最長道路
            is_longest_road(player, total_player, 0, map_Catan);
            printf("\n");
            break;
        }
    }
    print_map(map_Catan, total_player);
    printf("\n======================================================\n\n");
    sleep(1);
    free(map_give_resourse);
    return;
}
// new function by hugo end
// new function by hugo
// 用來把指定的某個角旁的三條道路改成可以建造
void one_point_roadbuildable(mapStruct *player_build, int32_t hex, int32_t index, int32_t player_number)
{
    mapStruct *map_tmp = NULL;
    map_tmp = (mapStruct *)malloc(19 * sizeof(mapStruct));
    generate_map(map_tmp);
    map_tmp[hex].corner[index] = player_number;
    sync_map(1, hex, index, map_tmp);
    all_unbuildable(player_build);
    is_buildable(map_tmp, player_build, player_number);
    free(map_tmp);
    return;
}
// new function by hugo end
// new add
void ending_info(characterStruct *player, int32_t total_player)
{
    int32_t max_used_development_card = 0;
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].used_development_card >= max_used_development_card)
        {
            max_used_development_card = player[i].used_development_card;
        }
    }
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].used_development_card == max_used_development_card)
        {
            printf("The Development Card Queen is Player %d\n", i);
        }
    }

    int32_t max_settlement = 0;
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].settlement >= max_settlement)
        {
            max_settlement = player[i].settlement;
        }
    }
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].settlement == max_settlement)
        {
            printf("Player %d Build Most Settlement\n", i);
        }
    }

    int32_t max_city = 0;
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].city >= max_city)
        {
            max_city = player[i].city;
        }
    }
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].city == max_city)
        {
            printf("Player %d Build Most City\n", i);
        }
    }

    int32_t max_road = 0;
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].max_road_card >= max_road)
        {
            max_road = player[i].max_road_card;
        }
    }
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].max_road_card == max_road)
        {
            printf("Player %d Build Longest Road\n", i);
        }
    }

    int32_t max_resource_left = 0;
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].grain + player[i].lumber + player[i].ore + player[i].brick + player[i].wool >= max_resource_left)
        {
            max_resource_left = player[i].grain + player[i].lumber + player[i].ore + player[i].brick + player[i].wool;
        }
    }
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].grain + player[i].lumber + player[i].ore + player[i].brick + player[i].wool == max_resource_left)
        {
            printf("Player %d Left most Resource\n", i);
        }
    }

    int32_t max_get_rob = 0;
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].get_rob >= max_get_rob)
        {
            max_get_rob = player[i].get_rob;
        }
    }
    for (int32_t i = 0; i < total_player; i++)
    {
        if (player[i].get_rob == max_get_rob)
        {
            printf("Player %d Get Rob Most Frequently\n", i);
        }
    }

    return;
}

// new add end