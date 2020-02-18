/*
Una liga de futbol desea procesar los resultados de los equipos que la componen

Para ello se debe implementar un programa que lea primero un 'codigo' de equipo (un valor entero de 5 digitos)
y posteriormente la cantidad de partidos ganandos, empatados y perdidos (como valores enteros positivos)

Se sabe que exiten 10 equipos. Para cada uno de ellos se debe mostrar la cantidad de puntos obtenidos
sabiendo que el partido ganado son 3 puntos, 1 por partido empatado y 0 por perdido

Al final del procesamiento, el programa debe informar el codigo del equipo campeon (mas puntos) y el 
codigo del equipo que desciende
*/

#include <iostream>
using namespace std;

//----------------------------------------------

void TextoCodigoEquipo(){
	cout << "Introduce el codigo del equipo: ";
}

//----------------------------------------------

void ErrorCodigoEquipo(){
	cout << "Codigo incorrecto - ERROR" << endl;
}

//----------------------------------------------

void ErrorNumeroPartidos(){
	cout << "\tNumero partidos incorrecto - ERROR" << endl;
}

//----------------------------------------------

void TextoPartidosGanados(){
	cout << "\tIntroduce cuantos partidos ha ganado: ";
}

//----------------------------------------------

void TextoPartidosEmpatados(){
	cout << "\tIntroduce cuantos partidos ha empatado: ";
}

//----------------------------------------------

void TextoPartidosPerdidos(){
	cout << "\tIntroduce cuantos partidos ha perdido: ";
}

//----------------------------------------------

void TextoPuntosEquipo(){
	cout << "\t\tLos puntos finales del equipo son: ";
}

//----------------------------------------------

int CodigoEquipo(){
	int codigo_equipo;
	do{
		TextoCodigoEquipo();
		cin >> codigo_equipo;
		if (codigo_equipo < 10000 || codigo_equipo > 99999){
			ErrorCodigoEquipo();
		}
	}
	while (codigo_equipo < 10000 || codigo_equipo > 99999);
	return codigo_equipo;
}

//----------------------------------------------

int PartidosGanados(){
	int ganados;
	do{
		TextoPartidosGanados();
		cin >> ganados;
		if (ganados < 0){
			ErrorNumeroPartidos();
		}
	}
	while (ganados < 0);
	return ganados;
}

//----------------------------------------------

int PartidosEmpatados(){
	int empatados;
	do{
		TextoPartidosEmpatados();
		cin >> empatados;
		if (empatados < 0){
			ErrorNumeroPartidos();
		}
	}
	while (empatados < 0);
	return empatados;
}

//----------------------------------------------

int PartidosPerdidos(){
	int perdidos;
	do{
		TextoPartidosPerdidos();
		cin >> perdidos;
		if (perdidos < 0){
			ErrorNumeroPartidos();
		}
	}
	while (perdidos < 0);
	return perdidos;
}

//----------------------------------------------

int Puntos(int perdidos, int empate, int ganados){
	int puntos;
	puntos = 3 * ganados + 1 * empate;
	TextoPuntosEquipo();
	return puntos;
}

//-----------------------------------------------

void Equipo(){
	

}

void Torneo(){
int equipo, puntos_aux_ganador, puntos_aux_desciende, puntos, ganador, desciende;
	
	equipo = CodigoEquipo();
	puntos_aux_ganador = Puntos(PartidosPerdidos(), PartidosEmpatados(), PartidosGanados());
	puntos_aux_desciende = puntos_aux_ganador;
	cout << puntos_aux_ganador << endl << endl;

	ganador = equipo;
	
	for (int i = 0 ; i < 2 ; i++){
		equipo = CodigoEquipo();
		puntos = Puntos(PartidosPerdidos(), PartidosEmpatados(), PartidosGanados());
		cout << puntos << endl << endl;
		
		if (puntos > puntos_aux_ganador){
			puntos_aux_ganador = puntos;
			ganador = equipo;
		}
		if (puntos < puntos_aux_desciende){
			puntos_aux_desciende = puntos;
			desciende = equipo;
		}
		
	}
	cout << "El equipo que gana la liga es: " << ganador << " con " <<  puntos_aux_ganador << endl;
	cout << "El equipo que desciende de liga es: " << desciende << " con " << puntos_aux_desciende;
	
}

//----------------------------------------------

int main(){
	Torneo();
}

