#include <iostream>
#include <fstream>

using namespace std;



int main(){
	int max='H'-'A'+1;	
	int partidos[max];
	for(int i=0; i<max; i++){
		partidos[i]=0;
	}	
	//nombre
	int tope;
	char p;
	int n_votos;
	int indice;
	ifstream fin;
	fin.open("eleccionesA.txt");	
	fin >> tope;
	for(int i=0; i<tope; i++){
		fin >> p;
		fin >> n_votos;		
 		indice = p-'A';
		partidos[indice]+= n_votos;
	}
	fin.close();
	ofstream fout;
	fout.open("datos.txt");	
	for(int i=0; i<max; i++){
		fout <<"El partido "<< char('A'+i) << " ha obtenido "<< partidos[i] << " votos" << endl;
	}
	fout.close();
}
