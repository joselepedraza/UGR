using namespace std;
#include <cmath>
#include <iostream>

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

double Potencia(double base, int exponente){
	double potencia;
	int exp_pos;
	
	if(base==0 && exponente==0){
		potencia = base/exponente;			// 0/0 => devuelve indeterminación
	}
	else{
		exp_pos=abs(exponente);
		potencia = 1.0;

		for (int i=1; i<=exponente; i++){
			potencia=potencia*base;
		}
	}	
	if(exponente<0){
		potencia=1/potencia; 		//Para hacer la inversa	
	}

	return potencia;
}

double Gausiana(double nu, double sigma, double abcisa){
	double const MINEXP = -0.5, UNO = 1.0, DOS = 2.0, PI = 3.141516;
	
	double resultado,frac,expon;
	
	frac = UNO /(sigma * sqrt(DOS * PI));
	expon = exp(MINEXP*(pow((abcisa-nu)/sigma, DOS)));
	resultado = frac * expon;
	
	return resultado;	
}

double AreaCDF(double nu, double sigma, double abcisa){
	const double B0 = 0.2316419, B1 = 0.319381530, B2 = -0.356563782, B3 = 1.781477937, B4 = -1.821255978, B5 = 1.330274429;
	double resultado_area, t;
	
	t=1/(1+B0 * abcisa);
	resultado_area = 1 - Gausiana(nu,sigma,abcisa)*(B1*t + B2*Potencia(t,1) + B3*Potencia(t,3) + B4*Potencia(t,4) + B5*Potencia(t,5));
	
	return resultado_area;
}

int main(){
	
	double nu, sigma;
	double gausiana;
	double minimo, maximo, incremento;
	double area_gausiana,ordenada;
	
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
								ordenada = Gausiana(nu,sigma,i);
								area_gausiana = AreaCDF(nu,sigma,i);
								cout << "\n\tf(" <<i<< ") = " << ordenada << "\n\t";
								cout << "\t\tCDF(" <<i<< ") = " << area_gausiana << endl;
							}
								
							op1='V';
					}
					else if(op1!='V'){
						cout << "la opcion elegida no es una opcion del menu. " << endl;
					}
					
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
