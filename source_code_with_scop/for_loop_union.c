#define N 32

int main()
{
	int A[N];
	int i;
	
	#pragma scop
	
	for (i = 0; i < N; ++i)
	{
		if (i <= 42 || i >= 73)
		{
			A[i] = 0;
		}
	}
	
	#pragma endscop
	
	return 0;
}
