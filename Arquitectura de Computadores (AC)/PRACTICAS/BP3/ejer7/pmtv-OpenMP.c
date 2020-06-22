#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif

//#define TIMES
//#define PRINTF_ALL

int main(int argc, char **argv) {
  //Lectura valores de entrada
  if(argc < 2) {
    fprintf(stderr,"Falta num\n");
    exit(-1);
  }
  int n = atoi(argv[1]); 

  int i,j;
  struct timespec ini,fin; double transcurrido;

  //Creación e inicialización de vector y matriz
  // Creación
  int *v1,*v2;
  v1 = (int*) malloc(n*sizeof(double));
  v2 = (int*) malloc(n*sizeof(double));

  int **M;
  M = (int**) malloc(n*sizeof(int*));
  for(i=0;i<n;i++) 
    M[i] = (int*)malloc(n*sizeof(int));

  // Inicialización
  for(i=0;i<n;i++)
    v1[i]=i+1;

  int num=1;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(j>i) M[i][j]=0;
      else { M[i][j]=num; num++; }
    }
  }

  //Impresión de vector y matriz iniciales
  #ifndef TIMES 
    #ifdef PRINTF_ALL
      printf("Vector inicial:\n");
      for (i=0; i<n; i++) printf("%d ",v1[i]);
      printf("\n");

      printf("Matriz inicial:\n");
      for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
          if(M[i][j]<10) printf(" %d ",M[i][j]);
          else printf("%d ",M[i][j]);
        }
        printf("\n");
      }
    #endif
  #endif

  //Cálculo resultado y toma de tiempos
  clock_gettime(CLOCK_REALTIME,&ini);

  #pragma omp parallel for default(none) private(i,j) shared(n,v1,v2,M) schedule(runtime)
  for (i=0; i<n; i++) {
    v2[i]=0;
    for (j=0; j<=i; j++) {
      v2[i]+=M[i][j]*v1[j];
    }
  }

  clock_gettime(CLOCK_REALTIME,&fin);
  transcurrido=(double) (fin.tv_sec-ini.tv_sec)+(double) ((fin.tv_nsec-ini.tv_nsec)/(1.e+9));

  //Impresión del tiempo y matriz resultado
  #ifdef TIMES
    printf("%d %11.9f\n",n,transcurrido);
  #else
    #ifdef PRINTF_ALL
      printf("Tiempo: %11.9f\n",transcurrido);
      printf("Vector resultado (M x v1):\n");
      for (i=0; i<n; i++) printf("%d ",v2[i]);
      printf("\n");
    #else 
      printf("Tiempo: %11.9f\n",transcurrido);
      printf("v2[0]: %d, v2[n-1]: %d\n",v2[0],v2[n-1]);
    #endif
  #endif

  //Vaciar memoria
  free(M);
  free(v1);
  free(v2);
return(0);
}