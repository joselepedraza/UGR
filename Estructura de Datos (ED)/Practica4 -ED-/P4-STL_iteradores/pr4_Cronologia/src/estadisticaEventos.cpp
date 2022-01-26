#include "cronologia.h"

using namespace std;

int main(int argc, char * argv[]){

	if (argc!=2){
	  cout<<"Dime el nombre del fichero con la cronologia"<<endl;
	  return 0;
	}

	ifstream f1;
	f1.open (argv[1], std::ifstream::in);

	if (!f1){
		cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
		return 0;
	}

	cronologia c1;
	f1>>c1;

	int totalAcontecimientos=0;
	int totalAnios=c1.size();
	int maximo=0;
	int max_aux;

	for(auto it=c1.begin();it!=c1.end();++it){
		totalAcontecimientos+=((it->second).getAcontecimientos()).size();
		max_aux=((it->second).getAcontecimientos()).size();
		if(maximo<max_aux){
			maximo=max_aux;
		}
	}

	cout<<"Total de anios: "<<totalAnios<<endl;
	cout<<"Total de acontecimientos: "<<totalAcontecimientos<<endl;
	cout<<"Media de acontecimientos/anio: "<<(totalAcontecimientos/totalAnios)<<endl;
	cout<<"Maximo de acontecimietos sucedidos en un anio: "<<maximo<<endl;
}
