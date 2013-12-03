
unsigned long fibonacci(int n)
{
	if(n <= 2)
		return 1;
	else
		return fibonacci(n-1)+fibonacci(n-2);
}

unsigned long fibonacci_1(int n)
{
	unsigned long f0, f1, temp;
	int i;

	if(n <= 2)
		return 1;

	for(f0 = f1 = 1, i = 3; i <= n; i++)
	{
		temp = f0 + f1;
		f0 = f1;
		f1 = temp;
	}
	return f1;
}
