#include "cronologia.h"

using namespace std;

int main(int argc, char * argv[]){

	ifstream f1;
	ofstream f2;
	string key;
	bool quieroSalida=false;

	if (argc == 1){
	  cout<<"No has introducido el nombre del fichero con la cronologia !"<<endl;
	  return 0;
	  
	}else if(argc == 2){  
	  do{
			cout<<"Introduce una palabra para buscar"<<endl;
			cin>>key;
		}while(key.empty());
	}else if(argc == 3){
		key=argv[2];
	}else if(argc == 4){//Con fichero de salida
		key=argv[2];
		f2.open(argv[3]);
		if(!f2){
			cout<<"No puedo abrir el fichero "<<argv[3]<<" de la salida especificada, revisalo!"<<endl;
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
	string salida=c1.buscarEventosPalabra(key).toString();
		
	if(quieroSalida){
		f2<<salida;
		f2.close();
	}else{
		cout<<salida<<endl;
	}
	
	f1.close();
}
