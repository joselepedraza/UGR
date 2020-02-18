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

long long NumHabitantesDespuesDe(long long poblacion_inicial, int anios, long long nata,long long morta,long long emig){
	long long resultado;
	double percent;
	for(int i = 1; i <= anios; i++){
		percent = (poblacion_inicial/TASA);
		poblacion_inicial = poblacion_inicial + (percent * (nata - morta + emig));
		resultado = poblacion_inicial;
	}
	return resultado;
}

int AniosHastaDoblarPob(long long poblacion_inicial, long long nata, long long morta, long long emig){
	long long pobdob;
	double percent;
	bool salida;
	int cont_anios;
	
	pobdob = poblacion_inicial*DOS;
	salida = false;
	cont_anios = 0;	
	
	for(poblacion_inicial; poblacion_inicial < pobdob || salida; poblacion_inicial += (percent * (nata - morta + emig))){
		cont_anios++;
		percent = (poblacion_inicial/TASA);
		if(poblacion_inicial>pobdob){
			salida = true;
		}
	}
	return cont_anios;
}

int main(){
	
	long long pob_ini, /*pob_fin,*/ pob_fin1;
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
	
	pob_ini = NumHabitantesDespuesDe(pob_ini,anios,nata,morta,emig);
	//pob_fin = pob_ini;	//guardo resultado pasados i años
	
	anios_hasta_doblar = AniosHastaDoblarPob(pob_ini,nata,morta,emig);
	pob_fin1 = NumHabitantesDespuesDe(pob_ini,anios_hasta_doblar,nata,morta,emig);

	/*
	while(pob_ini<pobdob){
		cont_anios++;
		pob_ini = pob_ini + (nata * (pob_ini/TASA)) - (morta * (pob_ini/TASA)) + emig * (pob_ini/TASA) ;
	}
	*/
	cout << "\n\n\tAnios que han de pasar hasta doblar la poblacion: " << anios_hasta_doblar << endl;
	cout << "\tLa poblacion estimada en " << anios << " anios, es de " << pob_ini << " habitantes." << endl;
	cout << "\tLa poblacion transcurridos " << anios_hasta_doblar << " anios es de " << pob_fin1 << " habitantes."<<endl;

}
