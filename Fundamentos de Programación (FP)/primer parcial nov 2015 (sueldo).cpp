#include <iostream>
using namespace std;

int main(){
	int const CENTI = -1;
	int cod;
	double edad;
	double sueldo;
	
	int cod_mas_jov_mas_suel, ed_min, suel_max;
	double edad_media, sueldo_medio;
	
	int cont_trabajadores = 0;
	double suma_edad = 0, suma_sueldo = 0;
	double suel_entre_ed, suel_entre_ed_max = 0;
	
	do{
		cout << "Introduce el codigo del trabajador:(-1 para terminar) ";
   		cin >> cod;
   	}while(cod <=99 || cod >=1000);
	
	while(cod != -1){
		cout << "\nIntroduce la edad del trabajador: ";
   		cin >> edad;
   		cout << "\nIntroduce el sueldo del trabajador: ";
   		cin >> sueldo;
		
		cont_trabajadores++;
		suma_edad = suma_edad + edad;
		suma_sueldo = suma_sueldo + sueldo;
		suel_entre_ed = sueldo / edad;
		if(suel_entre_ed > suel_entre_ed_max){
			suel_entre_ed_max = suel_entre_ed;
			cod_mas_jov_mas_suel = cod;
			ed_min = edad;
			suel_max = sueldo;
		}
		
		
		do{
			cout << "Introduce el codigo del trabajador:(-1 para terminar) ";
   			cin >> cod;
   		}while((cod <=99 || cod >=1000) && cod !=-1);
	}
	
	edad_media = suma_edad/cont_trabajadores;
	sueldo_medio = suma_sueldo/cont_trabajadores;
	
	cout << "\n\tCODIGO: " << cod_mas_jov_mas_suel << endl;
	cout << "\n\tEDAD: " << ed_min << endl;
	cout << "\n\tSUELDO: " << suel_max << endl;
	cout << "\n\tEDAD MEDIA: " << edad_media << endl;
	cout << "\n\tSUELDO MEDIO: " << sueldo_medio << endl;
	
}

