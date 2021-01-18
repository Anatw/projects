
int ispower2b(unsigned int n)
{
	unsigned int power2 = 2; /* 2^0 = 1 */
	int counter = 1;
	if (1 == n || power2 == n) /* if equal to 2^0 or 2^1 */
	{
		return (1); /* n is a power of 2 */
	}
	else if (power2 > n)
	{
		return (0);
	}
	else
	{
		power2 = power2 << counter;
		ispower2b(n); /* run this function again */
	}
}	



int setBitsNoLoop (int number)
{
	int counter = 0;
	
	/*Brian Kernighan's Algorithm */
	if(number) /* unset the first set bit */
	{
		number = number & (number - 1);
		++counter;
	}
	if
	
	return counter;
}	
	

/* great function and works great BUT has forbiddens "if's" */	
int sawpBits3And5(unsigned char character)
{
	int mask = 1;
	mask = mask << 2; /* move to 3rd bit */
	if (mask & character) /* 3 if on */
	{
		mask = mask << 2; /* move to 5th bit */
		if (mask & character) 	/* if on */
		{
			return character;
		}
		else			/* is off */
		{
			character = character | mask;
			mask = mask >> 2;
			character = character ^ mask;
		}
	}
	else			/* 3 is off */
	{
		mask = mask << 2; /* move to 5th bit */
		if (mask & character) 	/* if on */
		{
			character = character ^ mask; /* turns off 5 */
			mask = mask >> 2; /* move to 3rd bit */
			character = character & mask; /* turn on 3 */
		}
		else			/* is off */
		{
			return character;
		}
	}
	
	return character;
}
