#include "cronologia.h"

using namespace std;

int main(int argc, char * argv[]){

	ifstream f1;
	ofstream f2;
	int ini,fin;
	bool quieroSalida=false;

	if (argc == 1){
	  cout<<"No has introducido nada !"<<endl;
	  return 0;
	}else if(argc == 4){
		ini=atoi(argv[2]);
		fin=atoi(argv[3]);
	}else if(argc == 5){//Con fichero de salida
		ini=atoi(argv[2]);
		fin=atoi(argv[3]);
		f2.open(argv[4]);
		if(!f2){
			cout<<"No puedo abrir el fichero "<<argv[4]<<" de la salida especificada, revisalo!"<<endl;
			return 0;
		}
		quieroSalida=true;
	}
	
	f1.open (argv[1], std::ifstream::in);
	if (!f1){
		cout<<"No puedo abrir el fichero "<<argv[1]<<" de la cronologia, revisalo!"<<endl;
		return 0;
	}

	cronologia c1;
	f1>>c1;
	string salida=c1.buscarEventosRangoAnios(ini,fin).toString();
		
	if(quieroSalida){
		f2<<salida;
		f2.close();
	}else{
		cout<<salida<<endl;
	}
	
	f1.close();
}
