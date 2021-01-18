
#include <stdio.h> /* printf */

int main()
{
    int location = 0;
    int counter = 0;
    int ok = 0;
    int game_b[10] = {0}; /* 0 = empty, 1 = X, 2 = O */
    int winner = 0;
    
    for (counter = 0; counter < 9 && winner == 0; ++counter)
    {
        if (counter % 2 == 0) /* X turn */
        {
            while (0 == ok)
            {
                printf("player X, choose next location\n");
                scanf("%d", &location);
                
                if ((location <= 0 || location > 9) || game_b[location] != 0)
                {
                    printf("X - wrong input\n");
                }
                else
                {
                    ok = 1;
                }
            }

            ok = 0;
            game_b[location] = 1;

            /* Check if winner: */
            if (counter >= 4)
            {
                if (location == 1)
                {
                    if ((game_b[2] == 1 && game_b[3] == 1) ||
                        (game_b[4] == 1 && game_b[7] == 1) ||
                        (game_b[5] == 1 && game_b[9] == 1))
                    {
                        printf("\nX has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 2)
                {
                    if ((game_b[1] == 1 && game_b[3] == 1) ||
                        (game_b[5] == 1 && game_b[8] == 1))
                    {
                        printf("\nX has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 3)
                {
                    if ((game_b[1] == 1 && game_b[2] == 1) ||
                        (game_b[5] == 1 && game_b[7] == 1) ||
                        (game_b[6] == 1 && game_b[9] == 1))
                    {
                        printf("\nX has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 4)
                {
                    if ((game_b[5] == 1 && game_b[6] == 1) ||
                        (game_b[1] == 1 && game_b[7] == 1))
                    {
                        printf("\nX has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 5)
                {
                    if ((game_b[1] == 1 && game_b[9] == 1) || 
                        (game_b[3] == 1 && game_b[7] == 1) ||
                        (game_b[2] == 1 && game_b[8] == 1) ||
                        (game_b[4] == 1 && game_b[6] == 1))
                    {
                        printf("\nX has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 6)
                {
                    if ((game_b[3] == 1 && game_b[9] == 1) ||
                        (game_b[4] == 1 && game_b[5] == 1))
                    {
                        printf("\nX has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 7)
                {
                    if ((game_b[1] == 1 && game_b[4] == 1) ||
                        (game_b[3] == 1 && game_b[5] == 1) ||
                        (game_b[8] == 1 && game_b[9] == 1))
                    {
                        printf("\nX has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 8)
                {
                    if ((game_b[2] == 1 && game_b[5] == 1) ||
                        (game_b[7] == 1 && game_b[9] == 1))
                    {
                        printf("\nX has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 9)
                {
                    if ((game_b[7] == 1 && game_b[9] == 1) ||
                        (game_b[3] == 1 && game_b[6] == 1) ||
                        (game_b[1] == 1 && game_b[5] == 1))
                    {
                        printf("\nX has won!\n");
                        winner = 1;
                    }
                }
            }
        }
        else /* O turn */
        {
            while (0 == ok)
            {
                printf("player O, choose next location\n");
                scanf("%d", &location);
                
                if ((location <= 0 || location > 9) || game_b[location] != 0)
                {
                    printf("O - wrong input\n");
                }
                else
                {
                    {
                        ok = 1;
                    }
                }
            }

            ok = 0;
            game_b[location] = 2;

            /* Check if winner: */
            if (counter >= 4)
            {
                if (location == 1)
                {
                    if ((game_b[2] == 2 && game_b[3] == 2) ||
                        (game_b[4] == 2 && game_b[7] == 2) ||
                        (game_b[5] == 2 && game_b[9] == 2))
                    {
                        printf("\nO has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 2)
                {
                    if ((game_b[1] == 2 && game_b[3] == 2) ||
                        (game_b[5] == 2 && game_b[8] == 2))
                    {
                        printf("\nO has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 3)
                {
                    if ((game_b[1] == 2 && game_b[2] == 2) ||
                        (game_b[5] == 2 && game_b[7] == 2) ||
                        (game_b[6] == 2 && game_b[9] == 2))
                    {
                        printf("\nO has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 4)
                {
                    if ((game_b[5] == 2 && game_b[6] == 2) ||
                        (game_b[1] == 2 && game_b[7] == 2))
                    {
                        printf("\nO has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 5)
                {
                    if ((game_b[1] == 2 && game_b[9] == 2) || 
                        (game_b[3] == 2 && game_b[7] == 2) ||
                        (game_b[2] == 2 && game_b[8] == 2) ||
                        (game_b[4] == 2 && game_b[6] == 2))
                    {
                        printf("\nO has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 6)
                {
                    if ((game_b[3] == 2 && game_b[9] == 2) ||
                        (game_b[4] == 2 && game_b[5] == 2))
                    {
                        printf("\nO has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 7)
                {
                    if ((game_b[1] == 2 && game_b[4] == 2) ||
                        (game_b[3] == 2 && game_b[5] == 2) ||
                        (game_b[8] == 2 && game_b[9] == 2))
                    {
                        printf("\nO has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 8)
                {
                    if ((game_b[2] == 2 && game_b[5] == 2) ||
                        (game_b[7] == 2 && game_b[9] == 2))
                    {
                        printf("\nO has won!\n");
                        winner = 1;
                    }
                }
                else if (location == 9)
                {
                    if ((game_b[7] == 2 && game_b[9] == 2) ||
                        (game_b[3] == 2 && game_b[6] == 2) ||
                        (game_b[1] == 2 && game_b[5] == 2))
                    {
                        printf("\nO has won!\n");
                        winner = 1;
                    }
                }
            }
        }
    }

    if (counter == 9)
    {
        printf("\nTie\n");
    }

    return 0;
}
