
/*
 * How many games of "shesh besh" (total) there will be with 1,000,000
 * players until the winner is found?
 */

#include <stdio.h>
#include <stdlib.h>

#define AMOUNT (1000000)

size_t AmountOfGames(size_t players_num);

int main()
{
    size_t players_num = 0;

    system("clear");

    for (players_num = 1; players_num <= AMOUNT; ++players_num)
    {
        printf("%ld ==> %ld\n", players_num, AmountOfGames(players_num));
    }

    return (0);
}

size_t AmountOfGames(size_t players_num)
{
    size_t total_amount = 0;

    while (1 < players_num)
    {
        total_amount += players_num / 2;
        if (0 != players_num % 2)
        {
            ++players_num;
        }
        players_num /= 2;
    }

    return (total_amount);
}
