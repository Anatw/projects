#include <stdlib.h>

#define ONE (1)

int main()
{
	int stock_market[] = {6, 12, 3, 5, 1, 4, 9, 2};
	int stock_market_length = (sizeof(stock_market) / sizeof(int));
	int buy = stock_market[0];
	int sell = stock_market[0];
	
	return (0);
}

/* this function will check if cell and lock for the highest and lowest points*/
/* but will make sure to choose the smaler value that appear before the higher*/
int bursa(int *buy, int *sell, int stock_market[], int stock_market_length)
{
	int *is_buy = buy;
	int *is_sell = sell;
	int profit = *sell - *buy;
	int is_profit = 0;
	int index = 1;
	
	while(index < stock_market_length)
	{
		*is_sell = *(stock_market + index);
		if(*sell > *is_sell)
		{
			sell = is_sell;
		}
		else if (*buy > *is_buy)
		{
			if(sell > is_buy)
			{
				is_buy = is_sell;
				++index;
			}
			else
			{
				++index;
			}
		}
		
	}
}
