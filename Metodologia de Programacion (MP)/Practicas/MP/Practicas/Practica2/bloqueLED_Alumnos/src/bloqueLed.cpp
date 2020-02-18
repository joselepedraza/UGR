#include <iostream>
//#include "bloqueLed.h"

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
void asignar (bloqueLed &b, const bool v []){
	int contador=7;
	for(int i = 0; i<=7; i++){
		if(v[i]){
			on(b,contador);
			contador--;
		}
		else{
			off(b,contador);
			contador--;
		}
	}
}
void volcar (bloqueLed b, bool v []){
	bool ok;
	int contador=7;
	for(int i = 0; i<=7; i++){
		ok=get(b,i);
		if(ok){
			v[contador]=true;
			contador--;
		}
		else{
			v[contador]=false;
			contador--;
		}
	}
	for(int i = 0; i<=7; i++){
		if(v[i]){
			cout << 1;
		}
		else {
			cout << 0;
		}
	}
}
//----------------------------------------------------

int main(){
    bloqueLed b;
    int posiciones[8];
    int size;
    bool v[8]={1,0,1,0,1,0,1,0};
    bool z[8];

    apagar(b);
    cout << "\nBloque apagado LEDs: ";
    print(b);
    // enciendo dos LEDs
    on(b,5); 
    on(b,7);
    cout << "\nEnciendo el 5 y el 7: ";
    print(b);
    cout << "\nAhora enciendo los LEDs 0, 1 y 2\n";
    on(b,0);
    print(b);
    on(b,1);
    print(b);
    on(b,2);
    print(b);
    cout << "\nLos LEDs encendidos estan en las posiciones: ";
    encendidos(b,posiciones, size); 
    for(int i=0; i< size; i++)
        cout << posiciones[i] << ",";

    cout << endl;  

    cout << "\nTodos encendidos: ";
    encender(b);
    print(b);

    cout << "\nTodos apagados: ";
    apagar(b);
    print(b);
    
    cout << "\nAsignar: ";
    asignar(b,v);
    print(b);
    
    cout << "\nVolcar: ";
    volcar(b,z);


    cout << "\nAhora la animacion\nEjemplo 1 \n";
    // aqui debes escribir las instrucciones para que se muestre 
    // el primer ejemplo de animacion.
	

    cout << "\n\nEjemplo 2 \n";
    // aqui debes escribir las instrucciones para que se muestre 
    // el segundo ejemplo de animacion.
	apagar(b);
	on(b,7);
	on(b,0);
	int contador = 0;
	for(int i=7;i>=0;i--){
		
		on(b,i);
        on(b,contador);
        off(b,i+1);
        off(b,contador-1);
        contador++;
		
		if(contador==4 && i==4){
		contador=5; 
		i=3;
		}
        
		print(b);
	}
	

}
