#include "cronologia.h"

using namespace std;

int main(int argc, char * argv[]){

	bool quieroSalida=false;
	
	if (argc == 2){
	  cout<<"Nos has introducido dos ficheros timeline !"<<endl;
	  return 0;
	}

	ifstream f1,f2;
	ofstream f3;
	f1.open (argv[1], std::ifstream::in);
	f2.open (argv[2], std::ifstream::in);
	
	
	if(argc==4){
		f3.open(argv[3]);//abrimos para escribir
		quieroSalida=true;
	}

	if ((!f1 && !f2) || !f3){
		cout<<"Unos de los ficheros produce error, revisalos !"<<endl;
		return 0;
	}

	cronologia mi_cronologia,c1,c2,c3;
	f1>>c1;
	f2>>c2;
	c3 = c1 + c2;
	
	
	if(quieroSalida){
		f3<<c3;
		f3.close();
	}else{
		cout<<c3;
	}
	
	f1.close();
	f2.close();
	
}
