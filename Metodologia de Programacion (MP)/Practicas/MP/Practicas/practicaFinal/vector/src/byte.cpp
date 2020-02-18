#include <iostream>
#include "byte.h"

using namespace std;

typedef unsigned char byte;

void on(byte &b, int pos){
	byte mask=1;
	mask = 1 << pos;
	b=mask | b;
}
void off(byte &b, int pos){
	byte mask=1;
	mask = 1 << pos;
	mask=~mask;
	b=mask & b;
}
bool get(byte b, int pos){	
	bool ok=true;
	byte mask=1;
	mask = 1 << pos;
	b=mask & b;
	if(b==0){
		ok=false;
	}
	return ok;
}
void print(byte b){
	bool ok;	
	for(int i = 7; i>=0; i--){	
		ok = get(b,i);
		if(ok){
			cout << 1;
		}else{
			cout << 0;
		}
	}
	cout << endl;
}
void encender(byte &b){
	byte mask=0;
	mask=~mask;
	b=mask | b;
}
void apagar(byte &b){
	byte mask=0;
	b=mask & b;
}
void encendidos(byte b, int posic[], int &cuantos){	
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
void asignar(byte &b, const bool v[]){
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
void volcar(byte b, bool v[]){
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

