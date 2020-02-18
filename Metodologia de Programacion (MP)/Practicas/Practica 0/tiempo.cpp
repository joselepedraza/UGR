#include<iostream>
using namespace std;

struct Tiempo{
int h_intro, min_intro, seg_intro;
};

int convertirASegundos(int horas, int minutos, int segundos){
	int seg_return;
	
	seg_return = segundos + minutos * 60 + horas * 3600;
	return seg_return;
}

bool esPosterior(Tiempo instante1, Tiempo instante2){
	bool esposterior = false;
	int seg_inst1, seg_inst2;
	Tiempo tiempo1;
	Tiempo tiempo2;
	seg_inst1 = convertirASegundos(tiempo1.h_intro, tiempo1.min_intro, tiempo1.seg_intro);
	seg_inst2 = convertirASegundos(tiempo2.h_intro, tiempo2.min_intro, tiempo2.seg_intro);
	
	if(seg_inst1 < seg_inst2)
		esposterior = true;
	
	
	return esposterior;
}


int main(){

Tiempo tiempo1;
Tiempo tiempo2;
int seg_intro, min_intro, h_intro;

bool posterior = false;

int seg_tiempo1, seg_tiempo2;

//entrada
do{
	cout << "Introduzca el valor de los segundos en el instante1: ";
	cin >> tiempo1.seg_intro;
}while(seg_intro < 0 && seg_intro > 59);

do{
	cout << "Introduzca el valor de los minutos en el instante1: ";
	cin >> tiempo1.min_intro;
}while(min_intro < 0 && min_intro > 59);

do{
	cout << "Introduzca el valor de las horas en el instante1: ";
	cin >> tiempo1.h_intro;
}while(h_intro < 0 && h_intro > 23);

do{	
	cout << "Introduzca el valor de los segundos en el instante2: ";
	cin >> tiempo2.seg_intro;
}while(seg_intro < 0 || seg_intro > 59);

do{
	cout << "Introduzca el valor de los minutos en el instante2: ";
	cin >> tiempo2.min_intro;
}while(min_intro < 0 || min_intro > 59);

do{
	cout << "Introduzca el valor de las horas en el instante2: ";
	cin >> tiempo2.h_intro;
}while(h_intro < 0 || h_intro > 23);

//salidas

//ESPOSTERIOR
posterior = esPosterior(tiempo1, tiempo2);

if(posterior)
	cout << "El instante2 es posterior al instante1 introducido (TRUE)" << endl;
else
	cout << "El instante1 es menor o igual al instante2 (FALSE)" << endl;

//CONVERTIRASEGUNDOS

seg_tiempo1 = convertirASegundos(tiempo1.h_intro, tiempo1.min_intro, tiempo1.seg_intro);
seg_tiempo2 = convertirASegundos(tiempo2.h_intro, tiempo2.min_intro, tiempo2.seg_intro);

cout << "El instante1 en segundos es: " << seg_tiempo1 << " segundos" << endl;
cout << "El instante2 en segundos es: " << seg_tiempo2 << " segundos" << endl;






	



}
