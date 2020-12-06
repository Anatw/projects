#include <stdio.h>
#include <stdlib.h>

int Bursa(int arr[], int n, int *buy, int *sell)
{
	int profit = 0;
	int cur_profit = 0;
	int cand_buy = arr[0];
	int cand_sell = arr[0];
	int i = 0;
	int index_buy = 0;
	int index_sell = 0;
	
	for (i = 0; i < n; ++i)
	{
		if((arr[i] < cand_buy)) /* is current position smaller than the next? */
		{
			cand_buy = arr[i];
			index_buy = i;
		}
		
		if((arr[i] >= cand_sell))
		{
			cand_sell = arr[i];
			index_sell = i;
		}
	
		if(index_buy < index_sell) /* buy must come before sell... */
		{
			cur_profit = (arr[index_sell] - arr[index_buy]);
		}
		
		if(profit < cur_profit) /* final REAL assignments */
		{
			profit = cur_profit;
			*buy = index_buy;
			*sell = index_sell;
			printf("final %d %d %d\n", profit, *buy, *sell);
		}
	}
	return (profit);
}


int main ()
{
	int arr[7] = {6, 12, 50, 5, 1, 4, 50};
	int start;
	int end;
	
	
	printf ("maxprofit%d\n", Bursa(arr, 7, &start, &end));
	printf("finally i is:%d", start);
	printf("finally j is:%d", end);
	return(0); 
}
