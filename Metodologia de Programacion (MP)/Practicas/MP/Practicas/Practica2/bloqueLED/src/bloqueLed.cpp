#include <iostream>
#include "bloqueLed.h"

using namespace std;

typedef unsigned char bloqueLed;

void on(bloqueLed &b, int pos){
	bloqueLed mask=1;
	mask = 1 << pos;
	b=mask | b;
}
void off(bloqueLed &b, int pos){
	bloqueLed mask=1;
	mask = 1 << pos;
	mask=~mask;
	b=mask & b;
}
bool get(bloqueLed b, int pos){	
	bool ok=true;
	bloqueLed mask=1;
	mask = 1 << pos;
	b=mask & b;
	if(b==0){
		ok=false;
	}
	return ok;
}
void print(bloqueLed b){	
	for(int i = 7; i>=0; i--){	
		cout << get(b,i);
		
	}
	cout << endl;
}
void encender(bloqueLed &b){
	b=255;
}
void apagar(bloqueLed &b){
	b=0;
}
void encendidos(bloqueLed b, int posic[], int &cuantos){	
	bool ok;
	cuantos=0;
	for(int i = 0; i<=7; i++){	
        ok = get(b,i);
		if(ok){
			posic[cuantos] = i;
 			cuantos++;
		}
	}
}
void asignar(bloqueLed &b, const bool v[]){
	int contador =7;
	for(int i=0; i<8; i++){
		if(v[i]){
			on(b,contador);
			contador--;
		}else{
			off(b,contador);
			contador--;
		}
	}
}
void volcar(bloqueLed b, bool v[]){
	bool ok;
	int contador = 7;
	for(int i=0; i<=7; i++){
		ok=get(b,i);
		if(ok){
			v[contador]=true;
			contador--;
		}else{
			v[contador]=false;
			contador--;
		}
	}
}

