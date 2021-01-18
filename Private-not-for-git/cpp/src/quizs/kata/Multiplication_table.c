#include <stdlib.h>
#include <stdio.h>

int **multiplication_table(int n) {
    int i = 0;
    int j = 0;
    int number = 1;
    int **result = (int **)malloc(sizeof(int *) * n);

    for (i = 0; i < n; ++i)
    {
        result[i] = (int *)malloc(sizeof(int) * n);
    }

    if (result == NULL)
    {
        printf("Result malloc failed!");
    }
  
    for (i = 0; i < n; ++i)
      {
      for (j = 0; j < n; ++j)
        {
        result[i][j] = number++;
      }
    }
  
    return result;
}

int main()
{
    int n = 4;
    int **result = multiplication_table(n);

    int i = 0;
    int j = 0;
  
    for (i = 0; i < n; ++i)
      {
      for (j = 0; j < n; ++j)
        {
            printf("%d ", result[i][j]);
        }
      }

    return 0;
}