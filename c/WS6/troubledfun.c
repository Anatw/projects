
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

