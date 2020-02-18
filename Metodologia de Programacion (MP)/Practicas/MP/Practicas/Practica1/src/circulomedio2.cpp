/**
   @file circulomedio.cpp
   @brief Calcula círculo con centro en medio de dos círculos y radio la mitad de la distancia
   @author MP
   @warning Módulo no definitivo (creado para ser modificado)

   Un ejemplo de ejecución es:
     Introduzca un circulo en formato radio-(x,y): 3-(0,0)
     Introduzca otro circulo: 4-(5,0)
     El círculo que pasa por los dos centros es: 2.5-(2.5,0)
**/

#include <iostream>
#include <cmath> // sqrt, M_PI
using namespace std;


class Punto {
private:
    double x; ///< coordenada x del punto
    double y; ///< coordenada y del punto

public:
    Punto(); ///< constructor. Pone a 0 las dos coordenadas
    Punto(double px, double py); ///< constructor. Inicializa un punto con dos valores x y
    double getX(); ///< Devuelve la coordenada x del punto
    double getY(); ///< Devuelve la coordenada y del punto
    void setX(double newXValue); ///< Asigna el valor newXValue a la coordenada x del punto
    void setY(double newYValue); ///< Asigna el valor newYValue a la coordenada y del punto
    void escribir(); ///<  Escribe un punto en formato (x,y)
    void leer(); ///< // Lee un punto en el formato (x,y)
};

Punto::Punto() {
    x=0;
    y=0;
}

Punto::Punto(double px, double py) {
    x=px;
    y=px;
}

double Punto::getX() {
	return x;
}

double Punto::getY() {
	return y;
}

void Punto::setX(double px) {
	x = px;
}

void Punto::setY(double py) {
	y = py;
}


void Punto::escribir() {
    // Formato de escritura del punto: (x,y)
    cout << "(" << x << "," << y << ")";
}

void Punto::leer(){
    // Formato de lectura del punto: (x,y)
    char car;
    cin >> car >> x >> car >> y >> car;
}

/**
@brief Calcula la distancia entre dos puntos
@param p1 primer punto
@param p2 segundo punto
@return la distancia entre el punto @a p1 y el punto @a p2
*/
double distancia(Punto p1, Punto p2){
    return sqrt((p1.getX()-p2.getX())*(p1.getX()-p2.getX()) +
         (p1.getY()-p2.getY())*(p1.getY()-p2.getY()));
}

/**
@brief Calcula el punto que está entre dos puntos dados con distancia mínima a ambos
@param p1 primer punto
@param p2 segundo punto
@return un punto entre el punto @a p1 y el punto @a p2 con distancia mínima a ambos
*/
Punto puntoMedio(Punto p1, Punto p2){
    Punto pMedio;
    pMedio.setX((p1.getX()+p2.getX())/2.0);
    pMedio.setY((p1.getY()+p2.getY())/2.0);
    return pMedio;
}


class Circulo {
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

Circulo::Circulo() {
	radio = 0;
}

Circulo::Circulo(Punto p, double rradio) {
	radio = rradio;
	centro = p;
}

void Circulo::set(Punto p, double rradio) {
	radio = rradio;
	centro = p;
}


Punto Circulo::getCentro()  {
	return centro;
}

double Circulo::getRadio()  {
	return radio;
}

void Circulo::escribir() {
    // Formato de escritura del círculo: radio-(x,y)
    cout << radio << "-";
    centro.escribir();
}

void Circulo::leer(){
    // Formato de lectura del círculo: radio-(x,y)
    char car;

    cin >> radio;
    cin >> car; //Leer -
    centro.leer();
}

double Circulo::area() {
    return M_PI*radio*radio;
}


/**
@brief Calcula la distancia entre dos circulos
@param c1 primer círculo
@param c2 segundo círculo
@return la distancia entre el círculo @a c1 y el círculo @a c2

La distancia entre dos círculos se define como la distancia entre los centros menos los dos radios.
Nótese que la distancia puede ser negativa si los círculos se intersecan
*/
double distancia (Circulo c1, Circulo c2){
    Punto centro1, centro2;
    double dist;

    centro1=c1.getCentro();
    centro2=c2.getCentro();
    dist=distancia(centro1,centro2)-c1.getRadio()-c2.getRadio();
    return dist;
}


/**
@brief Comprueba si un punto es interior a un círculo
@param p punto a comprobar
@param c circulo
@retval true si el punto @a p es interior al círculo @a c
@retval false en caso contrario
*/
bool interior (Punto p, Circulo c){
    if(distancia(p,c.getCentro())<=c.getRadio()) {
        return true;
    }
    else{
        return false;
    }
}


int main()
{
    Circulo c1,c2;

    do {
        cout << "Introduzca un circulo en formato radio-(x,y): ";
        c1.leer();
        cout << "Introduzca otro circulo: ";
        c2.leer();
    } while (distancia(c1.getCentro(),c2.getCentro())==0);

    Circulo res;

    res.set(puntoMedio(c1.getCentro(),c2.getCentro()),
                     distancia(c1.getCentro(),c2.getCentro())/2);
    cout << "El círculo que pasa por los dos centros es: ";
    res.escribir();
    cout << endl;
}

/* Fin: circulomedio.cpp */
 
