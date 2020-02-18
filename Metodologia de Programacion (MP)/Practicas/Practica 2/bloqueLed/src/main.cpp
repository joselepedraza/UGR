#include <iostream>
#include "bloqueLed.h"
using namespace std;

int main()
{
    bloqueLed b;
    int posiciones[8];
    int size;
    bool inicial[] = {0,0,0,0,0,1,0,1};

    apagar(b);
    cout << "\nBloque apagado LEDs: ";
    cout << bloqueLedToString(b) << endl;

    cout << "\nInicializo el bloque a partir de un vector de bool ";
    asignar(b,inicial);
    cout << bloqueLedToString(b)<< endl;
    cout << "\nAhora enciendo los LEDs 0, 1 y 2 con la funcion on \n";
    on(b,0);
    cout << bloqueLedToString(b)<< endl;
    on(b,1);
    cout << bloqueLedToString(b)<< endl;
    on(b,2);
    cout << bloqueLedToString(b)<< endl;

    cout << "\nLos LEDs encendidos estan en las posiciones: ";
    encendidos(b,posiciones, size);
    for(int i=0; i<size; i++)
        cout << posiciones[i] << ",";

    cout << endl;

    cout << "\nTodos encendidos: ";
    encender(b);
    cout << bloqueLedToString(b)<< endl;


    cout << "Todos apagados: ";
    apagar(b);
    cout << bloqueLedToString(b)<< endl;

    cout << "\nAhora la animacion\nEjemplo 1 \n";

    encender(b);
    cout << bloqueLedToString(b)<< endl;

    for (int i = 0; i < 8; i++) {
      if (i == 0) {
        off(b, i);
        cout << bloqueLedToString(b)<< endl;
      } else {
        on(b, i-1);
        off(b, i);
        cout << bloqueLedToString(b)<< endl;
      }
    }

    cout << "\nAhora la animacion\nEjemplo 2 \n";

    encender(b);
    cout << bloqueLedToString(b)<< endl;

    for (int i = 0; i <= 3; i++) {
        off(b, i);
        off(b, 7-i);
        cout << bloqueLedToString(b)<< endl;
    }

    for (int i = 4; i <= 7; i++) {
        on(b, i);
        on(b, 7-i);
        cout << bloqueLedToString(b)<< endl;
    }

    cout << "\n\n";
}
