/*La tabla para el cálculo del precio a pagar en los parkings de Madrid para el 2015 es
la siguiente:
Si permanece más de 660 minutos se paga una única tarifa de 31.55 euros
Desde el minuto 0 al 30: 0.0412 euros cada minuto
Desde el minuto 31 al 90: 0.0370 euros cada minuto
Desde el minuto 91 al 120: 0.0311 euros cada minuto
Desde el minuto 121 al 660: 0.0305 euros cada minuto
Guión de Prácticas. Fundamentos de Programación RP-II.3
RELACIÓN DE PROBLEMAS II. Estructuras de Control
Dado un tiempo de entrada (hora, minuto y segundo) y un tiempo de salida, construya
un programa que calcule la tarifa final a cobrar. Para calcular el número de minutos entre
los dos instantes de tiempo, puede utilizar la solución del ejercicio 6 de la Relación
de Problemas I.
Finalidad: Plantear una estructura condicional anidada. Dificultad Baja.*/

#include <iostream>
using namespace std;
	
int main(){
	int h_entra, min_entra, seg_entra;
	int h_sale, min_sale, seg_sale;
	int seg_inicial, seg_final, seg_dentro, min_dentro;
	const int INTERVALO1 = 30;
	const int INTERVALO2 = 90;
	const int INTERVALO3 = 120;
	const int INTERVALO4 = 660;
	const double TIEMPO1 = 0.0412;	//Desde el minuto 0 al 30: 0.0412 euros cada minuto
	const double TIEMPO2 = 0.0370;	//Desde el minuto 31 al 90: 0.0370 euros cada minuto
	const double TIEMPO3 = 0.0311;	//Desde el minuto 91 al 120: 0.0311 euros cada minuto
	const double TIEMPO4 = 0.0305;	//Desde el minuto 121 al 660: 0.0305 euros cada minuto	
	const double TARIFAUNICA = 31.55;	//A partir del minuto 660
	const int MIN = 60;
	double tarifa_final;
	
	cout << "Introduce la hora,los minutos y los segundos de entrada al parking: ";
	cin >> h_entra >> min_entra >> seg_entra;
	cout << "Introduce la hora,los minutos y los segundos de salida del parking: ";
	cin >> h_sale >> min_sale >> seg_sale;
	
	seg_inicial = (h_entra * MIN * MIN) + min_entra * MIN + seg_entra;
	seg_final = (h_sale * MIN * MIN) + (min_sale * MIN) + seg_sale;
	seg_dentro = seg_final - seg_inicial;
	min_dentro = seg_dentro / MIN; 
		
	/*min_inicial = (h_entra * MIN) + min_entra + (seg_entra / MIN);
	min_final = (h_sale * MIN) + min_sale + (seg_entra / MIN);
	min_dentro = min_final - min_inicial; 
	*/
	
	if(min_dentro <= INTERVALO1){
		if(min_dentro == 0){
			min_dentro = 1;
		}
		tarifa_final = min_dentro * TIEMPO1;
	}
	
	else if(min_dentro <= INTERVALO2){
		min_dentro = min_dentro - INTERVALO1;
		tarifa_final = min_dentro * TIEMPO2 + (INTERVALO1 * TIEMPO1);
	}
	
	else if(min_dentro <= INTERVALO3){
		min_dentro = min_dentro - INTERVALO2;
		tarifa_final = min_dentro * TIEMPO3 + ((INTERVALO2 - INTERVALO1) * TIEMPO2) + (INTERVALO1 * TIEMPO1);
	}
	
	else if(min_dentro <= INTERVALO4){
		min_dentro = min_dentro - INTERVALO3;
		tarifa_final = min_dentro * TIEMPO4 + ((INTERVALO3 - INTERVALO2) * TIEMPO3) + ((INTERVALO2 - INTERVALO1) * TIEMPO2) + (INTERVALO1 * TIEMPO1);
	}
	
	else if(min_dentro > INTERVALO4){	
		tarifa_final = TARIFAUNICA;
	}
			
	if(seg_sale < seg_entra && h_entra == h_sale && min_entra == min_sale){
		tarifa_final = -1;
	}
	
	if((seg_sale >= seg_entra) && seg_sale < MIN && seg_entra < MIN && h_entra == h_sale && min_entra == min_sale){
		tarifa_final = 0;
	}
	
	cout << "El precio a pagar es " << tarifa_final << " euros (-1 = error)." << endl;
	
}
	
