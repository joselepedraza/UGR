#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

//#define GLOBAL
#define DINAMIC
#ifdef GLOBAL
   #define MAX 33554432
#endif

//comentar para mostrar unicamente primer y ultimo componente del vector resultado v2
#define PRINTF_ALL 


int main(int argc, char **argv) {
   //Lectura valores de entrada
   if(argc < 2) {
      fprintf(stderr,"Falta num\n");
      exit(-1);
   }

   unsigned int n = atoi(argv[1]);// Máximo n= 2^32-1= 4294967295 (sizeof(unsigned int) = 4 B)
   
   int i,j;

   struct timespec ini,fin; 
   double transcurrido;
   
   //Creación e inicialización de vector y matriz
   // Creación
   #ifdef GLOBAL
      if(n > MAX){
         n=MAX;
      }
      int M[n][n];
      int v1[n];
      int v2[n];
      printf("\n\t\tGLOBAL:\n\n");
   #endif

   #ifdef DINAMIC
      int *v1,*v2;
      v1 = (int*) malloc(n*sizeof(int));
      v2 = (int*) malloc(n*sizeof(int));

      int **M;
      M = (int**) malloc(n*sizeof(int*));
      for(i=0;i<n;i++)
         M[i] = (int*)malloc(n*sizeof(int));
      printf("\n\t\tDINAMICO:\n\n");
   #endif
   
   // Inicialición
   //omp_set_num_threads(n);
   
      for(i=0;i<n;i++){
         v1[i]=i;
         v2[i]=0;
      }
      
      for(i=0;i<n;i++){
         #pragma omp parallel for
         for(j=0;j<n;j++){
            M[i][j]=v1[j]+n*i;
         }
      }
   
   //Impresión de vector y matriz iniciales
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

   //Cálculo resultado en v2 y toma de tiempos
   
      clock_gettime(CLOCK_REALTIME,&ini);
   
      
      for (i=0; i<n; i++) {
         int aux=0;
         #pragma omp parallel for reduction(+:aux)
         for (j=0; j<n; j++) {
            aux+=M[i][j]*v1[j];
         }
         #pragma omp critical
         v2[i]+=aux;
      }
      clock_gettime(CLOCK_REALTIME,&fin);
   
   transcurrido=(double) (fin.tv_sec-ini.tv_sec)+(double) ((fin.tv_nsec-ini.tv_nsec)/(1.e+9));

   //Impresión del tiempo y vector resultado
   #ifdef PRINTF_ALL
      printf("Tamaño: %d \tTiempo: %11.9f\n",n,transcurrido);
      printf("Vector resultado (M x v1):\n");
      for (i=0; i<n; i++) printf("%d ",v2[i]);
      printf("\n");
   #else
      printf("Tamaño: %d \tTiempo: %11.9f\n",n,transcurrido);
      printf("v2[0]: %d \nv2[n-1]: %d\n",v2[0],v2[n-1]);
   #endif

   //Vaciar memoria
   #ifdef DINAMIC
      for(int i=0; i<n;i++){
         free(M[i]);
      }
      free(M);
      free(v1);
      free(v2);
   #endif

return(0);
}
