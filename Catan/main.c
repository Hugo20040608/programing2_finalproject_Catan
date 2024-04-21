#include "catan.h"
#include "map.h"

// 圖形的鄰接矩陣
int graph[MAX_VERTICES][MAX_VERTICES] = {0};
// 節點的值
int nodeValues[MAX_VERTICES] = {0};
// 記錄節點是否已經被訪問的陣列
bool visited[MAX_VERTICES] = {0};
// 最大路徑
int maxPath = 0;

int main()
{
    int32_t total_player = 0;
    int32_t player_number = 0;
    int32_t used_development = 0;
    int32_t card[28] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5, 5, 6, 7, 8};
    int32_t card_index = 0;

    srand(time(0));

    shuffleArray(card, 28);

    characterStruct *player;
    bankStruct *bank;

    printf("How much player: ");
    scanf("%d", &total_player);

    player = (characterStruct *)malloc(total_player * sizeof(characterStruct));
    bank = (bankStruct *)malloc(sizeof(bankStruct));

    printf("\n======================================================\n\n");
    printf("Game Start\n");

    for (int32_t i = 0; i < total_player; i++)
    {
        player_initialize(&(player[i]));
    }

    bank_initialize(bank);

    mapStruct *map_Catan = NULL;
    map_Catan = (mapStruct *)malloc(19 * sizeof(mapStruct));
    generate_map(map_Catan);
    mapStruct *player1_build = NULL;
    player1_build = (mapStruct *)malloc(19 * sizeof(mapStruct));
    mapStruct *player2_build = NULL;
    player2_build = (mapStruct *)malloc(19 * sizeof(mapStruct));
    mapStruct *player3_build = NULL;
    player3_build = (mapStruct *)malloc(19 * sizeof(mapStruct));
    mapStruct *player4_build = NULL;
    player4_build = (mapStruct *)malloc(19 * sizeof(mapStruct));

    game_start_build(map_Catan, player1_build, player2_build, player3_build, player4_build, &(player[0]), &(player[1]), &(player[2]), &(player[3]), total_player, player);

    while (1)
    {
        if (player_number == 0)
        {
            int32_t used_development = 0;
            printf("Do you want to use development card?(Y:1, N:0): ");
            scanf("%d", &used_development);

            if (used_development == 1)
            {
                if (player_number == 0)
                {
                    used_development = use_development_card(player, total_player, player_number, map_Catan, player1_build, bank);
                }
                else if (player_number == 1)
                {
                    used_development = use_development_card(player, total_player, player_number, map_Catan, player2_build, bank);
                }
                else if (player_number == 2)
                {
                    used_development = use_development_card(player, total_player, player_number, map_Catan, player3_build, bank);
                }
                else if (player_number == 3)
                {
                    used_development = use_development_card(player, total_player, player_number, map_Catan, player4_build, bank);
                }
            }

            printf("\n======================================================\n\n");
            print_map(map_Catan, total_player); // big_change
            printf("\n======================================================\n\n");

            print_player_info(player, total_player);

            roll_dice(player, total_player, player_number, map_Catan, bank);

            print_player_info(player, total_player);
            print_bank_info(bank);

            int32_t choice = -1;

            while (choice != 0)
            {
                printf("Player %d turn.\n", player_number);
                printf("0: end this round\n");
                printf("1: trade with bank\n");
                printf("2: trade with player\n");
                printf("3: buy development card\n");
                printf("4: use development card\n");
                printf("5: build\n");
                printf("Please choose your move: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    bank_trade(player, player_number, map_Catan, bank);
                    break;
                case 2:
                    player_trade(player, player_number, total_player);
                    break;
                case 3:
                    if (card_index < 28)
                    {
                        if (player[player_number].wool >= 1 && player[player_number].grain >= 1 && player[player_number].ore >= 1)
                        {
                            player[player_number].wool--;
                            player[player_number].grain--;
                            player[player_number].ore--;
                            buy_development_card(player, player_number, card_index, card, bank, total_player);
                            bank->wool++;
                            bank->grain++;
                            bank->ore++;
                            card_index = card_index + 1;
                        }
                    }
                    else
                    {
                        printf("There is no card left.\n");
                    }

                    break;
                case 4:
                    if (used_development == 0)
                    {
                        if (player_number == 0)
                        {
                            used_development = use_development_card(player, total_player, player_number, map_Catan, player1_build, bank);
                        }
                        else if (player_number == 1)
                        {
                            used_development = use_development_card(player, total_player, player_number, map_Catan, player2_build, bank);
                        }
                        else if (player_number == 2)
                        {
                            used_development = use_development_card(player, total_player, player_number, map_Catan, player3_build, bank);
                        }
                        else if (player_number == 3)
                        {
                            used_development = use_development_card(player, total_player, player_number, map_Catan, player4_build, bank);
                        }
                    }
                    else
                    {
                        printf("You already use one development card this round\n");
                    }
                    break;
                case 5:
                    if (player_number == 0)
                    {
                        build(map_Catan, player1_build, 1, player, bank, total_player);
                    }
                    else if (player_number == 1)
                    {
                        build(map_Catan, player2_build, 2, player, bank, total_player);
                    }
                    else if (player_number == 2)
                    {
                        build(map_Catan, player3_build, 3, player, bank, total_player);
                    }
                    else if (player_number == 3)
                    {
                        build(map_Catan, player4_build, 4, player, bank, total_player);
                    }
                    break;
                default:
                    break;
                }

                printf("\n======================================================\n\n");
                print_map(map_Catan, total_player); // big_change
                printf("\n======================================================\n\n");

                print_player_info(player, total_player);
                print_bank_info(bank);

                if (win(player, player_number) == 1)
                {
                    printf("player %d is winner\n", player_number);
                    ending_info(player, total_player);

                    free(player);
                    free(bank);
                    free(map_Catan);
                    free(player1_build);
                    free(player2_build);
                    free(player3_build);
                    free(player4_build);

                    return 0;
                }
            }
        }
        else
        {
            int32_t used_development = 0;
            printf("Do you want to use development card?(Y:1, N:0)\n");
            if (player[player_number].knight_card > 0 || player[player_number].roadbuilding_card > 0 || player[player_number].year_of_plenty > 0 || player[player_number].monopoly > 0)
            {
                used_development = rand() % 2;
                printf("Player %d choose %d.\n", player_number, used_development);
            }
            else
            {
                printf("Player %d choose %d.\n", player_number, used_development);
            }

            if (used_development == 1)
            {
                if (player_number == 0)
                {
                    used_development = use_development_card(player, total_player, player_number, map_Catan, player1_build, bank);
                }
                else if (player_number == 1)
                {
                    used_development = use_development_card(player, total_player, player_number, map_Catan, player2_build, bank);
                }
                else if (player_number == 2)
                {
                    used_development = use_development_card(player, total_player, player_number, map_Catan, player3_build, bank);
                }
                else if (player_number == 3)
                {
                    used_development = use_development_card(player, total_player, player_number, map_Catan, player4_build, bank);
                }
            }

            printf("\n======================================================\n\n");
            print_map(map_Catan, total_player); // big_change
            printf("\n======================================================\n\n");

            print_player_info(player, total_player);

            roll_dice(player, total_player, player_number, map_Catan, bank);

            print_player_info(player, total_player);
            print_bank_info(bank);

            int32_t choice = -1;
            int32_t flag[7] = {0};

            while (choice != 0)
            {
                printf("Player %d turn.\n", player_number);
                printf("0: end this round\n");
                printf("1: trade with bank\n");
                printf("2: trade with player\n");
                printf("3: buy development card\n");
                printf("4: use development card\n");
                printf("5: build road\n");
                printf("6: build settlement\n");
                printf("7: build city\n");
                printf("Please choose your move.\n");

                choice = computer_choice(player, player_number, flag);
                printf("The player %d choose %d.\n", player_number, choice);

                switch (choice)
                {
                case 1:
                    bank_trade(player, player_number, map_Catan, bank);
                    flag[0] = 1;
                    break;
                case 2:
                    player_trade(player, player_number, total_player);
                    flag[1] = 1;
                    break;
                case 3:
                    if (card_index < 28)
                    {
                        player[player_number].wool--;
                        player[player_number].grain--;
                        player[player_number].ore--;
                        buy_development_card(player, player_number, card_index, card, bank, total_player);
                        bank->wool++;
                        bank->grain++;
                        bank->ore++;
                        card_index = card_index + 1;
                    }
                    else
                    {
                        printf("There is no card left.\n");
                    }
                    flag[2] = 1;
                    flag[3] = 1;

                    break;
                case 4:
                    if (used_development == 0)
                    {
                        if (player_number == 0)
                        {
                            used_development = use_development_card(player, total_player, player_number, map_Catan, player1_build, bank);
                        }
                        else if (player_number == 1)
                        {
                            used_development = use_development_card(player, total_player, player_number, map_Catan, player2_build, bank);
                        }
                        else if (player_number == 2)
                        {
                            used_development = use_development_card(player, total_player, player_number, map_Catan, player3_build, bank);
                        }
                        else if (player_number == 3)
                        {
                            used_development = use_development_card(player, total_player, player_number, map_Catan, player4_build, bank);
                        }
                    }
                    else
                    {
                        printf("You already use one development card this round\n");
                    }
                    flag[3] = 1;
                    break;
                case 5:
                    if (player_number == 0)
                    {
                        computer_build(map_Catan, player1_build, 1, player, bank, 1, total_player);
                    }
                    else if (player_number == 1)
                    {
                        computer_build(map_Catan, player2_build, 2, player, bank, 1, total_player);
                    }
                    else if (player_number == 2)
                    {
                        computer_build(map_Catan, player3_build, 3, player, bank, 1, total_player);
                    }
                    else if (player_number == 3)
                    {
                        computer_build(map_Catan, player4_build, 4, player, bank, 1, total_player);
                    }
                    flag[4] = 1;
                    break;
                case 6:
                    if (player_number == 0)
                    {
                        computer_build(map_Catan, player1_build, 1, player, bank, 2, total_player);
                    }
                    else if (player_number == 1)
                    {
                        computer_build(map_Catan, player2_build, 2, player, bank, 2, total_player);
                    }
                    else if (player_number == 2)
                    {
                        computer_build(map_Catan, player3_build, 3, player, bank, 2, total_player);
                    }
                    else if (player_number == 3)
                    {
                        computer_build(map_Catan, player4_build, 4, player, bank, 2, total_player);
                    }
                    flag[5] = 1;
                    break;
                case 7:
                    if (player_number == 0)
                    {
                        computer_build(map_Catan, player1_build, 1, player, bank, 3, total_player);
                    }
                    else if (player_number == 1)
                    {
                        computer_build(map_Catan, player2_build, 2, player, bank, 3, total_player);
                    }
                    else if (player_number == 2)
                    {
                        computer_build(map_Catan, player3_build, 3, player, bank, 3, total_player);
                    }
                    else if (player_number == 3)
                    {
                        computer_build(map_Catan, player4_build, 4, player, bank, 3, total_player);
                    }
                    flag[6] = 1;
                    break;
                default:
                    break;
                }

                printf("\n======================================================\n\n");
                print_map(map_Catan, total_player); // big_change
                printf("\n======================================================\n\n");

                print_player_info(player, total_player);
                print_bank_info(bank);

                if (win(player, player_number) == 1)
                {
                    printf("player %d is winner\n", player_number);
                    ending_info(player, total_player);

                    free(player);
                    free(bank);
                    free(map_Catan);
                    free(player1_build);
                    free(player2_build);
                    free(player3_build);
                    free(player4_build);

                    return 0;
                }
            }
        }

        player_number = (player_number + 1) % total_player;
    }

    return 0;
}