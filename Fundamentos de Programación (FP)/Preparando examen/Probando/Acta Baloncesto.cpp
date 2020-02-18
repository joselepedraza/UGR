
#include <iostream>
using namespace std;

void Informacion(){
	cout << "Dorsales por equipo: " << endl;
	cout << "\tEquipo 1: 7-8-9-10-11" << endl;
	cout << "\tEquipo 2: 12-13-14-15-17" << endl << endl;
}

void TextoPuntuacion(){
	cout << "Introduce puntuacion anotada: ";
}

void TextoDorsal(){
	cout << "Introduce el dorsal del jugador: ";
}

void TextoDorsalInvalido(){
	cout << "Dorsal no valido ERROR" << endl;
}

void TextoPuntuacionInvalida(){
	cout << "Puntuacion no valida ERROR" << endl;
}
void Salida(){
	cout << endl <<  "Resultado: ";
}

int LeerPuntuacion(int dorsal){
	int puntuacion;
	if (dorsal > 6 && dorsal < 18 && dorsal != 16){
		do{
			TextoPuntuacion();
			cin >> puntuacion;
			if (puntuacion < 0 || puntuacion > 3){
				TextoPuntuacionInvalida();
			}
		}
		while (puntuacion < 0 || puntuacion > 3);
	}
	return puntuacion;
}

int LeerDorsal(){
	int dorsal;
	TextoDorsal();
	cin >> dorsal;
	if (dorsal < 7 || dorsal > 17 || dorsal == 16){
		if (dorsal == -1){
			Salida(); 
		}
		else{
			TextoDorsalInvalido();
		}
	}
	return dorsal;
}

void Ganador (int equipo1, int equipo2){
	if (equipo1 == equipo2){
		cout << "Empate a " << equipo1 << " puntos.";
	}
	else if(equipo1 > equipo2){
		cout << "Gana equipo 1 con " << equipo1 << " puntos.";
	}
	else{
		cout << "Gana equipo 2 con " << equipo2 << " puntos.";
	}
}

void SacarPuntuacion(){
	int dorsal, puntuacion, equipo1 = 0, equipo2 = 0;
	do{
		dorsal = LeerDorsal();
		puntuacion = LeerPuntuacion(dorsal);
		if (dorsal == 7 || dorsal == 8 || dorsal == 9 || dorsal == 10 || dorsal == 11){
			equipo1 = equipo1 + puntuacion;
		}
		else{
			equipo2 = equipo2 + puntuacion;
		}
	}
	while (dorsal != -1);
	Ganador(equipo1, equipo2);
}


int main(){
	
	Informacion();
	SacarPuntuacion();
	
}

