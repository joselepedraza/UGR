#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int const n_fil = 200;
int const n_colum = 200;

void multiplica(int a[n_fil][n_colum],int b[n_fil][n_colum],int c[n_fil][n_colum],int x,int y, int z){
    for(int i=0; i<x; i++){	//hacemos la multiplicacion
        for(int j=0; j<y; j++){	//fila i de a * columna j de b
            for(int h=0; h<y; h++){	//suma y añade a C
                c[i][j] += a[i][h]*b[h][j];
	    }
	}
    }
}

int main(int argc, char * argv[]){
	
	srand((int)time(0));
	
	int x,y,z;	//para hacer coincidir n_filas, con n_colum y poder realizar la multiplicacion
	int A[n_fil][n_colum], B[n_fil][n_colum], C[n_fil][n_colum];	//declaracion de matrices
	
	x=atoi(argv[1]);		//parametros
	y=atoi(argv[2]);
	z=atoi(argv[3]);
	
	
   //relleno matriz A con datos aleatorios:
    for(int i=0; i<x; ++i)
        for(int j=0; j<y; ++j)
        {
            A[i][j]=((rand() % 100) +1);
        }

    //relleno matriz B con datos aleatorios:
    for(int i=0; i<y; ++i)
        for(int j=0; j<z; ++j)
        {
            B[i][j]=((rand() % 100) +1);
        }
        
    //Inicializamos C a 0 para escribir en ella posteriormente:
	for(int i=0; i<x; ++i)
        for(int j=0; j<z; ++j)
        {
            C[i][j]=0;
        }
        
	//Calculamos el tiempo de la operacion de multiplicar las dos matrices y escribir en C:
	clock_t tini;    // Comienza
	tini=clock();           
		multiplica(A,B,C,x,y,z);        
	clock_t tfin;    // Termina
	tfin=clock();
      
	/*cout << "\nEl tiempo que tardo en realizar la multiplicacion de dos matrices (" << x <<  "x" << y << ")(" << y << "x" << z << ") es:" << "\t" << (tfin-tini)/(double)CLOCKS_PER_SEC) * 0.001 << " segundos" << " milisegundos" << endl; */

	cout << x*z << "\t" << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;

}
