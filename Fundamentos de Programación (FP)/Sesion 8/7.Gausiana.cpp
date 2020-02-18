using namespace std;
#include <cmath>
#include <cctype>
#include <iostream> 

double const MINEXP = -0.5;
double const UNO = 1.0;
double const DOS = 2.0;
double const PI = 3.141516;

	
void MenuPrincipal(){
	cout << "MENU PRINCIPAL: elige opcion(P-S)" << endl;
	cout << "\tP: Introducir valores de la funcion (esperanza y desviacion)." << endl;
	cout << "\tS: Salir del programa." << endl;
}

void MenuSecundario(){
	cout << "\nElige opcion(R-V)" << endl;
	cout << "\tR: Introducir rango de valores de abcisas." << endl;
	cout << "\tV: Volver al menu anterior (menu principal)." << endl;
}

double Gausiana(int i, double nu, double sigma){
	double resultado,frac,expon;
	
	frac = UNO /(sigma * sqrt(DOS * PI));
	expon = exp(MINEXP*(pow((i-nu)/sigma, DOS)));
	resultado = frac * expon;
	
	return resultado;	
}


int main(){
	
	double nu, sigma;
	double gausiana;
	double minimo, maximo, incremento;
	
	char op;
	
	MenuPrincipal();
	cin >> op;
	while(op!='S'){

		switch(op){
			case 'P':
				system("cls");
				//lectura de valores de esperanza y desviacion
				cout << "Introduzca el valor de la esperanza: ";
				cin >> nu;
				do{
					cout << "Introduzca el valor de la desviacion tipica: ";
					cin >> sigma;
				}while(sigma<=0);
				
				
				char op1;
				
				do{
					MenuSecundario();
					cin >> op1;
					
					if(op1=='R'){
							//lectura del rango de valores de abcisas
							cout << "Introduce el valor minimo: ";
							cin >> minimo;
	
							do{
								cout << "Introduce el valor maximo: ";
								cin >> maximo;
							}while(maximo < minimo);
	
							do{
								cout << "Introduce el valor del incremento: ";
								cin >> incremento;
							}while(incremento <= 0);
							
							
							for(double i = minimo; i <= maximo; i = i + incremento){
								gausiana = Gausiana(i,nu,sigma);
								cout << "La funcion gausiana en el intervalo introducido resulta: " << gausiana << endl;
							}
							
							op1='V';
					}
					else if(op1!='V'){
						cout << "la opcion elegida no es una opcion del menu. " << endl;
					}
					/*else{
						cout << "la opcion elegida no es una opcion del menu: " << endl;
					}*/
				}while(op1 !='V');
			break;
			default:
				if(op!='P'){
					cout << "la opcion elegida no es una opcion del menu: " << endl;
					system("pause");
					system("cls");
				}
			break;
		}
		MenuPrincipal();
		cin >> op;		
	}
	
	
system("pause");

}
