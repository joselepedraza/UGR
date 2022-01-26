#include <stdio.h>

#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num()0
#endif

//gcc -O2 -fopenmp -o private_clause private_clause.c

int main(int argc, char const *argv[])
{
	int i, n=7;
	int a[n], suma;

	for (i = 0; i < n; ++i)
	{
		a[i]=i;
	}

	#pragma omp parallel /*private(suma)*/
	{
		suma=10;
		#pragma omp for
			for(i=0;i<n;++i){
				suma = suma + i;
				printf("thread %d, suma a[%d] = %d\n", omp_get_thread_num(),i,a[i]);
			}

		printf("\nthread %d suma = %d \n", omp_get_thread_num(), suma);
	}
	
	printf("\n suma = %d \n", suma);

	return 0;
}
