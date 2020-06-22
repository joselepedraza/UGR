/* SumaVectoresC.c
Suma de dos vectores: v3 = v1 + v2
Para compilar usar (-lrt: real time library):
gcc -fopenmp -O2 SumaVectores_parallel_for.c -o SumaVectores_parallel_for –lrt
*/
#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <omp.h>
//#define PRINTF_ALL    //comentar para quitar el printf...

int main(int argc, char** argv){


	//Leer argumento de entrada (no de componentes del vector)
	if (argc<2){
		printf("Faltan no componentes del vector\n");
		exit(-1);
	}
	unsigned int N = atoi(argv[1]); 
   
	double *v1, *v2, *v3;
	v1 = (double*) malloc(N*sizeof(double));// malloc necesita el tamaño en bytes
	v2 = (double*) malloc(N*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL
	v3 = (double*) malloc(N*sizeof(double));
	if ( (v1==NULL) || (v2==NULL) || (v3==NULL) ){
		printf("Error en la reserva de espacio para los vectores\n");
		exit(-2);
	}
   double cgt1,cgt2, ncgt;
   int i;

	//Inicializar vectores
   #pragma omp parallel for
	for(i=0; i<N; i++){
      //printf("Thread %d ejecuta iteracion %d del bucle de inicializacion\n", omp_get_thread_num(),i);
		v1[i] = N*0.1+i*0.1; 
      v2[i] = N*0.1-i*0.1; //los valores dependen de N
	}
	cgt1 = omp_get_wtime();

	//Calcular suma de vectores
   #pragma omp parallel for
	for(i=0; i<N; i++){
		v3[i] = v1[i] + v2[i];
      //printf("Thread %d ejecuta iteracion %d del bucle de calculo\n", omp_get_thread_num(),i);
   }
	cgt2 = omp_get_wtime();

	ncgt=cgt2-cgt1;

	//Imprimir resultado de la suma y el tiempo de ejecución
	#ifdef PRINTF_ALL
	printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
	for(i=0; i<N; i++)
		printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",i,i,i,v1[i],v2[i],v3[i]);
	#else
		printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n", ncgt,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]);
	#endif

    //liberar espacio reservado
	free(v1);
	free(v2);
	free(v3); 

	return 0;
}
