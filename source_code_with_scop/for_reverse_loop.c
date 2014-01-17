#define N 32

int main()
{
	int A[N];
	int i;
	
	#pragma scop
	
	for (i = N; i >= 0; --i)
	{
		A[i] = 0;
	}
	
	#pragma endscop
	
	return 0;
}
