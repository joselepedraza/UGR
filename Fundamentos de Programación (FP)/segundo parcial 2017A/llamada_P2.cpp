#include <iostream>
#include <cmath>
using namespace std;
// Ejercicio del parcial 2 sobre llamadas telefonicas

class LLamada{
private:
   static const int NOVALID = -1;
   static const int CTETIEMPO = 60;  // constante para la conversion a segundo
   long emisor;
   long receptor;
   int horaE;
   int minE;
   int segE;
   int horaF;
   int minF;
   int segF;
   // se pasa todo a segundos
   long pasoASeg(int _hora, int _min, int _seg){
      return ((_hora*CTETIEMPO)+ _min)*CTETIEMPO +_seg;
   }

public:

   LLamada() :emisor(NOVALID), receptor(NOVALID), horaE(0), minE(0),segE(0), horaF(0), minF(0),segF(0)
               {}
   LLamada(long _emisor, long _receptor, int _horaE, int _minE, int _segE, int _horaF, int _minF, int _segF)
   :emisor(_emisor), receptor(_receptor), horaE(_horaE), minE(_minE), segE(_segE ), horaF(_horaF), minF(_minF), segF(_segF){}
   
   // metodos get que devuelven cada uno de los campos miembros privados de la clase
   long getEmisor(){
      return emisor;
   }
   long getReceptor(){
      return receptor;
   }
   int getHoraE(){
      return horaE;
   }
   int getMinE(){
      return minE;
   }
   int getSegE(){
      return segE;
   }
   int getHoraF(){
      return horaF;
   }
   int getMinF(){
      return minF;
   }
   int getSegF(){
      return segF;
   }
   // calcula la duracion en segundos de la llamada
   int getDuracion(){
      return pasoASeg(horaF, minF, segF) - pasoASeg(horaE, minE, segE);
   }
   // Un unico set para asignar nuevos valores a un objeto, se le pasan todos los campos de la clase
   void setLLamada(long _emisor, long _receptor, int _horaE, int _minE, int _segE, int _horaF, int _minF, int _segF){
   	 emisor = _emisor;
	 receptor =  _receptor;
	 horaE= _horaE;
	 minE = _minE;
	 segE = _segE;
	 horaF = _horaF;
	 minF =  _minF;
	 segF =  _segF;
   }
   // comprueba si una llamada es interna segun el criterio de <= 100 en valor absoluto
   bool esInterna(){
       return fabs(emisor - receptor) >= 100;
   }
   // comprueba que esta dentro del intervalo dado por parametro
   bool enIntervalo(int _horaInf, int _minInf, int _horaSup, int _minSup){
      return (horaE >= _horaInf && ( horaE < _horaSup ||  horaE ==  _horaSup && minE <= _minSup));
   }
};


// clase lista de llamadas, una secuencia de llamadas

class Lista{
private:
   static const int CAPACIDAD=100;
   LLamada lista[CAPACIDAD];
   int util;
public:
   Lista():util(0){}
   // devuelve la longitud del vector utilizado
   int Utilizadas(){
      return util;
   }
   // aniade un objeto al final del vector
   void Aniade(LLamada otra){
   if (util < CAPACIDAD) { // si hay sitio
      lista[util]= otra;
      util++;
    }
   }
   // devuelve el componente de la posicion indicada
   // si posicion no valida devuelve objeto no valido
   LLamada Elemento(int pos){
      LLamada resultado;
      if (pos >= 0 && pos < util)
          resultado = lista[pos];
      return resultado;
   }
   // calculaDuracionTotal por acumulacion de duracion 
   // de cada llamada
   long getDuracionTotal(){
    long duracion=0;
    for(int i=0; i< util; i++)
        duracion += lista[i].getDuracion();
    return duracion;
   }
   // calcula la media de duracion como la duraciontotal / numero de llamadas
   double mediaDuracion(){
   double  media = 0;
    if (util > 0 )
	    media = getDuracionTotal()/util;
	return media;
   }
   // cuenta cuantas llamadas internas hay en la lista
   int numInterna(){
      int num=0;
      for(int i=0; i< util; i++)
      if (lista[i].esInterna())
         num++;
      return num;
   }
   // Devuelve el objeto cuya duracion es maxima
   LLamada llamadaMasDuracion(){
   int  pos_max = 0;
    for(int i=0; i< util; i++)
      if (lista[i].getDuracion() > lista[pos_max].getDuracion())
         pos_max=i;
   return lista[pos_max];
   }
   int superanMedia() {
   	int cuantos=0;
   	double media = mediaDuracion();
   	for(int i=0; i< util; i++){
   		if (lista[i].getDuracion()> media)
   		    cuantos++;
   	}
   	return cuantos;
   }
    int enIntervalo( int _horaInf, int _minInf, int _horaSup, int _minSup) {
   	int cuantos=0;
   	for(int i=0; i< util; i++){
   		if (lista[i].enIntervalo(_horaInf,  _minInf, _horaSup, _minSup))
   		    cuantos++;
   	}
   	return cuantos;
   }
};
int main(){
	
   const int FIN = -1;
   Lista llamadas;

   long emisor;
   long receptor;
   int horaE;
   int minE;
   int segE;
   int horaF;
   int minF;
   int segF;
   cin >> emisor;
   while (emisor != FIN){
         cin >> receptor >> horaE>> minE >> segE >> horaF >> minF >>  segF;
         LLamada nueva ( emisor, receptor, horaE, minE, segE, horaF, minF, segF);
         llamadas.Aniade(nueva);
         cin >> emisor;
         cout << "@@@@" << nueva.getDuracion();
   }

   if (llamadas.Utilizadas() >0){ // Ahya datos
      cout << "DURACION TOTAL" << llamadas.getDuracionTotal()<< endl;
      cout << "DURACION MEDIA" << llamadas.mediaDuracion()<< endl;
      cout << "SUPERANA LA MEDIA " << llamadas.superanMedia() << endl;
      cout << "CUANTAS INTERNAS " << llamadas.numInterna() << endl;
      cout << "LLAMADA MAS LARGA " << endl;
      LLamada masLarga(llamadas.llamadaMasDuracion());
      cout << masLarga.getDuracion()<< endl;
      cout << masLarga.getEmisor()<< endl;
      cout << masLarga.getReceptor()<< endl;
      cout << "CUANTAS en [9..10] " << llamadas.enIntervalo(9,0,10,0) << endl;

   }
   cin >> emisor;
}
 
