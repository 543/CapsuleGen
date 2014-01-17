#define min(a,b) (a<=b?a:b)

#define N 32

int main()
{
	int A[N];
	int i;
	int j;
	
	#pragma scop
	
	for (i = 0; i < N; i += 2)
	{
		for (j = i; j < min(N, i + 2); ++j)
		{
			A[j] = 0;
		}
	}
	
	#pragma endscop
	
	return 0;
}
