#ifndef _Circulo_H_
#define _Circulo_H_
#include "Punto.h"
class Circulo{
private:
    Punto centro; ///< Centro del círculo
    double radio; ///< radio del círculo
public:
    Circulo();///< Constructor: Pone a 0 el punto y el radio
    Circulo(Punto centro, double rradio); ///< Constructor: Inicializa el círculo con un centro y un radio
    void set(Punto centro, double rradio); ///< Asigna el centro y el radio a un circulo
    Punto getCentro(); ///< Devuelve el centro de un circulo
    double getRadio(); ///< Devuelve el radio de un circulo
    void escribir(); ///< Escribe círculo en formato radio-centro
    void leer(); ///< lee círculo en formato radio-centro
    double area(); ///< Devuelve el área de un círculo
    
};
double distancia (Circulo c1, Circulo c2);
bool interior (Punto p, Circulo c);
#endif

