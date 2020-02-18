//Jose Luis Pedraza Román  - 80108849X - grupo E3

#include<iostream>

using namespace std;

int main(){
	//Constantes necesarias
	int const RANGO_MIN_TEL = 99;
	int const RANGO_MAX_TEL = 1000;
	int const CAMBIOHORARIO = 60;
	int const PERCENT = 100;
	int const INTER_CORTAS = 0;
	int const INTER_MEDIAS = 60;
	int const INTER_LARGAS = 300;
	int const CENTI = -1;
	
	//Entrada
	int id_llamada, tel_entrante, tel_saliente;
	double duracion = 0;
	
	int num_entrante = 0, num_saliente = 0;	//Salida
	double suma_duracion = 0; 			//Computo
	int duracion_maxima = 0;					//Computo
	double media_duracion;							//Salida
	double cont_llamadas;				//Computo
	double cont_cortas = 0, cont_medias = 0, cont_largas = 0;	//Computo
	double percent_cortas, percent_medias, percent_largas;	//Salida
	
	int segundos, minutos, minutos1, horas;	//Salida
	
	do{
		cout << "Introduce el identificador de llamada (-1 para terminar): ";
		cin >> id_llamada;
	}while((id_llamada < CENTI || id_llamada == 0) && id_llamada != CENTI);
	
	while(id_llamada != CENTI){
		do{
			cout << "Introduce el numero de telefono que recibe la llamada: ";
			cin >> tel_entrante;
		}while(tel_entrante <= RANGO_MIN_TEL || tel_entrante >= RANGO_MAX_TEL);
		
		do{
			cout << "Introduce el numero de telefono que envia la llamada: "; 
			cin >> tel_saliente;
		}while(tel_saliente <= RANGO_MIN_TEL || tel_saliente >= RANGO_MAX_TEL);
		
		do{
			cout << "Introduce la duracion de la llamada en segundos: ";
			cin >> duracion;
		}while(duracion < 0);
		
		cont_llamadas++;
		suma_duracion = suma_duracion + duracion;
		
		if(duracion > duracion_maxima){
			duracion_maxima = duracion;
			num_entrante = tel_entrante;
			num_saliente = tel_saliente;
		}
		
		if(duracion >= INTER_CORTAS && duracion < INTER_MEDIAS){
			cont_cortas++;
		}
		else if(duracion >= INTER_MEDIAS && duracion < INTER_LARGAS){
			cont_medias++;
		}
		else{
			cont_largas++;
		}
		
		do{
			cout << "Introduce el identificador de llamada (-1 para terminar): ";
			cin >> id_llamada;
		}while((id_llamada < CENTI || id_llamada == 0) && id_llamada != CENTI);
	}
	
	media_duracion = suma_duracion/cont_llamadas;	//Calculo de la media
	
	percent_cortas = (cont_cortas/cont_llamadas) * PERCENT;	//Calculo de los porcentajes
	percent_medias = (cont_medias/cont_llamadas) * PERCENT;
	percent_largas = (cont_largas/cont_llamadas) * PERCENT;
	
	segundos = duracion_maxima%CAMBIOHORARIO;		//Paso de segundos (duracion_maxima) a horas:minutos:segundos
	minutos = duracion_maxima/CAMBIOHORARIO;
	horas = minutos/CAMBIOHORARIO;
	minutos1 = minutos%CAMBIOHORARIO;
	
	//Salida
	cout << "\n\tLa llamada mas larga se ha realizado entre " << num_entrante << " y " << num_saliente << " con un total de " << horas << ":" << minutos1 << ":" << segundos << endl;
	cout << "\n\tLa media de la duracion de las llamadas de esta centralita es " << media_duracion << " segundos." << endl;
	cout << "\n\tEl porcentaje de llamadas ha sido: \n\t\tLlamadas cortas: " << percent_cortas << "\n\t\tLlamadas medias: " << percent_medias << "\n\t\tLlamadas largas: " << percent_largas << endl;

}
