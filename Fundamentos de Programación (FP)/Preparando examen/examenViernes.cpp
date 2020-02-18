/*
Una estacion meteorologica registra una serie de medidas de temperatura y humedad. 
La temperatura es un valor entero entre [-20..50] y la humedad es un porcentaje (un entero entre 1 y 100). 
Construir un programa que vaya leyendo estos datos desde teclado hasta que se lea una temperatura = 100. 
Una vez terminada la lectura de datos, la estacion informa de:
.- La temperatura y humedad promedio.
.- El numero de veces que la humedad fue inferior al 33%, estuvo entre el 34% y el 66% o fue mayor que 66%.
Nota: Todas las lecturas de datos deben estar convenientemente filtradas (idealmente usando funciones).
*/

#include <iostream>
#include <string>

using namespace std;

int LeerTemperatura()
{ int valor;
	do
	 {cout << "\nIngrese temperatura [-20,50]: ";	
	  cin >> valor;
	}while(((valor < -20) || (valor > 50)) && (valor != 100));

 return valor;
}


int LeerHumedad()
{ int valor;
	do
	 {cout << "\nIngrese humedad [1,100]: ";	
	  cin >> valor;
	}while((valor < 0) || (valor > 100));

 return valor;
}



int main()
{int valores_leidos = 0;
 int suma_temp=0, suma_humedad=0;
 int cont_baja = 0, cont_media = 0, cont_alta = 0;
 int temperatura, humedad;

 temperatura = LeerTemperatura();
 
 while (temperatura != 100)
	 { humedad = LeerHumedad();
		// acumulo para el calculo de las medias
		valores_leidos++;
		suma_temp = suma_temp + temperatura;
		suma_humedad = suma_humedad + humedad;

		// proceso el valor de humedad
		if (humedad <= 33)
			cont_baja++;
		else if (humedad <= 66)	
					cont_media++;
				else
					cont_alta++;


	 temperatura = LeerTemperatura();
		
	}


// informe de resultados. Solo hago la media si se han leido valores

if (valores_leidos == 0)
	cout << "\n No se han leido valores validos" << endl;
else 
	{ cout << "\n Media de Temperaturas: " << suma_temp * 1.0 / valores_leidos;
	  cout << "\n Media de Humedades: " << suma_humedad * 1.0 / valores_leidos;
	  cout << "\n Nro de medidas con humedad baja: " << cont_baja;
	  cout << "\n Nro de medidas con humedad media: " << cont_media;
	  cout << "\n Nro de medidas con humedad alta: " << cont_alta << endl;


	}



}
