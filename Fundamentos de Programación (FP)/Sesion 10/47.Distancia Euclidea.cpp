#include <iostream>
#include <cmath>
#include <cctype>
using namespace std;


struct CoordenadasPunto2D{
   double abcisa;
   double ordenada;
};

double DistanciaEuclidea(CoordenadasPunto2D punto1, CoordenadasPunto2D punto2){
	double dif_abc, dif_ord;
	double distancia;
	
	dif_abc = punto1.abcisa - punto2.abcisa;
	dif_ord = punto1.ordenada - punto2.ordenada;
	
	distancia = sqrt(dif_abc*dif_abc + dif_ord*dif_ord);
	
	return distancia;	
}

int main(){
	CoordenadasPunto2D punto1, punto2;
	double dist_euclidea;
	char opc;
	bool sale;
	
	cout << "\t\t\tCALCULO DE LA DISTANCIA EUCLIDEA";
	do{
		cout << "\n\nIntroducir datos? (s/n): ";
		cin >> opc;
		sale = opc=='n';
		
		if(opc=='s' && !sale){
			cout << "\nIntrozce las coordenadas del punto1: ";
			cout << "\n\tAbcisa punto1 = ";
			cin >> punto1.abcisa;
			cout << "\n\tOrdenada punto1 = ";
			cin >> punto1.ordenada;
			cout << "\n\tAbcisa punto2 = ";
			cin >> punto2.abcisa;
			cout << "\n\tOrdenada punto2 = ";
			cin >> punto2.ordenada;
			
			dist_euclidea = DistanciaEuclidea(punto1,punto2);
			cout << "\n\t\tDistancia = " << dist_euclidea;
		}
	}while(!sale);
}
