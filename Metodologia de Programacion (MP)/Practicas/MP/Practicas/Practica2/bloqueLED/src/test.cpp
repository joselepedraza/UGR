#include <iostream>
#include "bloqueLed.h"

using namespace std;

int main(){
    bloqueLed b;
    int posiciones[8];
    int size;
    bool z [8]={0,0,0,1,1,1,0,1};
	bool v [8]={1,1,1,1,1,1,1,1};
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
	cout << "\nBloque Led antes de ser asignado: ";
	print(b);
	cout << "Vector asignacion: ";
	for(int i=0; i<8; i++){
		cout << z[i];
	}
	asignar(b,z);
	cout << "\nBloque Led una vez asignado: ";
	print(b);
	cout << "\nVolcar:";
	cout << "\nVector antes de volcar: ";	
	for(int i=0; i<8; i++){
		cout << v[i];
	}	
	cout << "\nVector después de volcar: ";
	volcar(b,v);
	for(int i=0; i<8; i++){
		cout << v[i];
	}
    cout << "\n\nAhora la animacion\nEjemplo 1 \n";
    // aqui debes escribir las instrucciones para que se muestre 
    // el primer ejemplo de animacion. 
    apagar(b);
    on(b,7);
    print(b);
    for(int i=6; i>=0;i--){
    	on(b,i);
    	off(b,i+1);
    	print(b);
    }

    cout << "\n\nEjemplo 2 \n";
    // aqui debes escribir las instrucciones para que se muestre 
    // el segundo ejemplo de animacion. 
	apagar(b);
    on(b,7);
    on(b,0);
    print(b);
    int contador = 1;
    for(int i=6; i>=0;i--){
    	on(b,i);
    	on(b,contador);
    	off(b,i+1);
    	off(b,contador-1);
    	contador++;
    	if(contador==i){
    		contador++;
    		i--;
    	} 
    	print(b);
    }

}
