
#include <iostream>
#include <cmath>  // NAN
using namespace std;

const double PI = 3.141593;

struct CoordenadasPunto2D{
	double abcisas;
	double ordenadas;
};

class Circunferencia{
	private:
		double radio;
		CoordenadasPunto2D centro = {NAN, NAN} ;		// para inicializar a valor nulo
		
		bool RadioCorrecto(double long_rad){
			bool es_correcto = false;
			if(long_rad>= 0){			//debe ser positivo al ser una longitud
				es_correcto=true;
			}
			return es_correcto;
		}
	public:
		Circunferencia(CoordenadasPunto2D centro_circ, double long_rad){
			if(RadioCorrecto(long_rad)){	//en otro caso se quedan con los valores por defecto
				centro = centro_circ;
				radio = long_rad;
			}
		}
		
		double LongitudCircun(){
			double long_circ = 2*PI*radio;
			return long_circ;
		}
		
		double AreaCircun(){
			double area_circ = PI*radio*radio;
			return area_circ;
		}
		
		bool ContienePunto(CoordenadasPunto2D nuevo){
			double dif_abc, dif_ord;
			bool es_contenido;
			
			dif_abc = centro.abcisas - nuevo.abcisas;
			dif_ord = centro.ordenadas - nuevo.ordenadas;
			
			es_contenido = dif_abc*dif_abc + dif_ord*dif_ord <= radio*radio;
			
			return es_contenido;
		}
};

int main(){
	double radio_cir;
	CoordenadasPunto2D centro_cir, punto_nuevo;
	double area, longitud;
	bool lo_contiene;
	
	cout << "\nIntroduce los valores para la circunferencia: ";
	cout << "\n\tRadio = ";
	cin >> radio_cir;
	
	cout << "\n\tCentro abcisa = ";
	cin >> centro_cir.abcisas;
	cout << "\n\tCentro ordenada = ";
	cin >> centro_cir.ordenadas;
	
	cout << "\nIntroduce las coordenadas del punto para comprobar si esta contenido: ";
	cout << "\n\tPunto abcisa = ";
	cin >> punto_nuevo.abcisas;
	cout << "\n\tPunto ordenada = ";
	cin >> punto_nuevo.ordenadas;
	
	Circunferencia circun(centro_cir,radio_cir);
	
	longitud = circun.LongitudCircun();
	area = circun.AreaCircun();
	lo_contiene = circun.ContienePunto(punto_nuevo);
	
	cout << "\n\t\tLongitud = " << longitud;
	cout << "\n\t\tArea = " << area;
	
	if(lo_contiene){
		cout << "\n\t\tEl punto esta contenido en la circunferencia." << endl; 
	}
	else{
		cout << "\n\t\tEl punto no esta contenido en la circunferencia." << endl;
	}		
}
