#include <stdio.h>

#ifdef _OPENMP
	#include <omp.h>
#endif

int main(int argc, char const *argv[])
{
	int i, n=7;
	int a[n];

	#pragma omp parallel for shared(a)
	for(i=0;i<n;++i) a[i] = i + 1;

	printf("Despues del parallel for:\n");

	for (i = 0; i < n; ++i) printf("a[%d] = %d\n",i,a[i] );
	
	return 0;
}