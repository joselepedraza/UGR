#include "cronologia.h"

using namespace std;

int main(int argc, char * argv[]){

	if (argc!=2){
	  cout<<"Dime el nombre del fichero con la cronologia"<<endl;
	  return 0;
	}

	//ifstream f (argv[1]);
	ifstream f1,f2,f3;
	f1.open (argv[1], std::ifstream::in);
	f2.open ("datos/timeline_science.txt", std::ifstream::in);
	f3.open (argv[1], std::ifstream::in);
		
	if (!f1 && !f2){
		cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
		//return 0;
	}

	cronologia mi_cronologia,c1,c2,c3;
	f1>>mi_cronologia; //Cargamos en memoria la cronología.
	f2>>c3;
	f3>>c1;
	
	/**/
   	cout<<"**************** Anio especifico ****************"<<endl;
	cout<<mi_cronologia.buscarEventosAnio(1900).toString()<<endl;
	/**/

	/**/
	cout<<" **************** rango anios ****************"<<endl;
	cout<<mi_cronologia.buscarEventosRangoAnios(1900,1910).toString()<<endl;
	/**/
	
	/**/
	cout<<"**************** keyword ****************"<<endl;
	cout<<mi_cronologia.buscarEventosPalabra("Woman").toString()<<endl;
	/**/
		
	/**/
	cout<<"**************** op.igual ****************"<<endl;
	c1=mi_cronologia;
	c2=c1;
	cout<<c1.toString()<<endl;
	/**/
	
	/**/
	cout<<"**************** op.comp == ****************"<<endl;
	cout<<(c1==c2)<<endl;
	cout<<(c2==c3)<<endl;
	/**/
	
	/**/
	cout<<"**************** op. != ****************"<<endl;
	cout<<(c2!=c3)<<endl;
	cout<<(c2!=c1)<<endl;
	/**/
	
	/**/
	cout<<"**************** op. + (union) ****************"<<endl;
	c2 = c1 + c3;
	cout<<c2;
	/**/
	
	
   /* Exhibir aquí la funcionalidad programada para el TDA Cronologia / TDA FechaHistorica */ 

   // Algunas sugerencias: 
   // - Obtener los eventos acaecidos en un año dado
   // - Obtener la (sub)cronología de eventos históricos acaecidos en [anioDesde, anioHasta], donde anioDesde y anioHasta son proporcionados por el usuario
   // - Obtener la (sub)cronología de eventos históricos asociados a una palabra clave. Ejemplo: la cronología de eventos asociados a "Einstein"
   // - Operadores sobre cronologías, ejemplo: Unión de dos cronologías (la cronología resultante debería estar ordenada)
   // - Cualquier otra funcionalidad que consideréis de interés


}
