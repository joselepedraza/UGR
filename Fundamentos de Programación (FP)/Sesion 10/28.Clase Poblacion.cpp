#include <iostream>
#include <iostream>
using namespace std;

double const  TASA = 1000.0;
int const CERO = 0;
int const DOS = 2;

int LeeIntRango(int min, int max){
	int nuevo;

	do{
		cout << "\tIntroduce el valor: ";
		cin >> nuevo;
	}while(nuevo < min || nuevo > max);	

	return nuevo;
}
int LeeIntMayorIgualQue(int min){
	int nuevo;
	
	do{
		cout << "\tIntroduce el valor: ";
		cin >> nuevo;	
	}while(nuevo < min);
	
	return nuevo;
}

class Poblacion{
	private:
		long long poblacion_inicial=0;	
		
	public:
		Poblacion(long long pob){
			poblacion_inicial = pob;
		}
		long long NumHabitantesDespuesDe(int anios, long long nata,long long morta,long long emig){
			double percent;
			for(int i = 1; i <= anios; i++){
				percent = (poblacion_inicial/TASA);
				poblacion_inicial = poblacion_inicial + (percent * (nata - morta + emig));
				
			}
			return poblacion_inicial;
		}
		
		int AniosHastaDoblarPob(long long pob, long long nata, long long morta, long long emig){
			long long pobdob;
			double percent;
			bool salida;
			int cont_anios;
	
			pobdob = pob*DOS;
			salida = false;
			cont_anios = 0;	
	
			for(pob; pob < pobdob || salida; pob += (percent * (nata - morta + emig))){
				cont_anios++;
				percent = (pob/TASA);
				if(pob>pobdob){
					salida = true;
				}
			}
			return cont_anios;
		}	
};

int main(){
	long long pob_ini, pob_fin1;
	long long morta, nata, emig;
	int anios,anios_hasta_doblar;
		
	cout << "Poblacion inicial. " << endl;;
	pob_ini = LeeIntMayorIgualQue(CERO);
	
	cout << "Natalidad: "<< endl;;
	nata = LeeIntRango(CERO,TASA);
	cout << "Mortalidad: "<< endl;;
	morta = LeeIntRango(CERO,TASA);
	cout << "Emigracion: "<< endl;;
	emig = LeeIntRango(CERO,TASA);
	
	cout << "Numero de anios para hacer el calculo: "<< endl;;
	anios = LeeIntMayorIgualQue(CERO);	
	
	Poblacion poblacion(pob_ini);
	
	pob_ini = poblacion.NumHabitantesDespuesDe(anios,nata,morta,emig);
	anios_hasta_doblar = poblacion.AniosHastaDoblarPob(pob_ini,nata,morta,emig);
	pob_fin1 = poblacion.NumHabitantesDespuesDe(anios_hasta_doblar,nata,morta,emig);
	
	cout << "\n\n\tAnios que han de pasar hasta doblar la poblacion: " << anios_hasta_doblar << endl;
	cout << "\tLa poblacion estimada en " << anios << " anios, es de " << pob_ini << " habitantes." << endl;
	cout << "\tLa poblacion transcurridos " << anios_hasta_doblar << " anios es de " << pob_fin1 << " habitantes."<<endl;
}
