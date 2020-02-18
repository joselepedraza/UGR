#include <iostream>

using namespace std;

int main(){
	int const MINUTOS = 60;
	int const SEGUNDOS = 3600;
	
	int seg_ini, min_intro1, seg_intro1, h_intro1;
	int seg_fin, min_intro2, seg_intro2, h_intro2;
	int diferencia;
	
	cout << "Introduce los segundos del instante 1: ";
	cin >> seg_intro1;
	cout << "Introduce los minutos del instante 1: ";
	cin >> min_intro1;
	cout << "Introduce las horas del instante 1: ";
	cin >> h_intro1;
	
	cout << "Introduce los segundos del instante 2: ";
	cin >> seg_intro2;
	cout << "Introduce los minutos del instante 2: ";
	cin >> min_intro2;
	cout << "Introduce las horas del instante 2: ";
	cin >> h_intro2;
	
	seg_ini = seg_intro1 + min_intro1 * MINUTOS + h_intro1 * SEGUNDOS;
	seg_fin = seg_intro2 + min_intro2 * MINUTOS + h_intro2 * SEGUNDOS;
	diferencia = seg_fin - seg_ini;
	
	cout << "La diferencia es: " << diferencia << endl;
	
	
}
