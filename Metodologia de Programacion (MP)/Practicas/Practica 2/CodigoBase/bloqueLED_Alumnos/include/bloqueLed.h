/**
@file
@author DP
@date 16 de febrero de 2015, 19:33
@brief Funciones de manejo de bloqueLeds

*/

#ifndef _BLOQUELED_H_
#define	_BLOQUELED_H_


typedef unsigned char bloqueLed; ///< Un @c bloqueLed contiene el estado de 8 LEDs

void on(bloqueLed &b, int pos);
void off(bloqueLed &b, int pos);

bool get(bloqueLed b, int pos);

/**
@brief Muestra por la salida est�ndar una secuencia de 0s y 1s correspondiente  al estado de cada LED
@param b el @c bloqueLed que se quiere imprimir

Muestra por la salida est�ndar una secuencia de 0s y 1s correspondiente  al estado de cada LED del bloqueLed donde un cero representa que un LED est� apagado y un uno que el LED est� encendido. Se implementa utilizando la funci�n "get".

Por ejemplo, si en el @c bloqueLed @c b est�n encendidos los LEDs en posiciones 1 y 3 (0 m�s a la derecha), @c print(b); mostrar� @c 00001010

*/
void print(bloqueLed b);



void encender(bloqueLed &b);


void apagar(bloqueLed &b);


/**
@brief enciende los LEDs seg�n la configuraci�n de @p v
@param b el @c bloqueLed sobre el que se quiere actuar
@param v vector de 8 elementos que contiene la secuencia de LEDS que se quieren asignar

Asigna a @p b la configuraci�n de LEDs contenida en @p v. @p v es un vector de 8 booleanos donde @c true significa encendido y @c false significa apagado.
*/
void asignar(bloqueLed &b, const bool v[]);

/**
@brief recupera la configuraci�n de todos los LED
@param b el @c bloqueLed que se quiere consultar
@param v vector de 8 elementos que contendr� el estado de cada uno de los LEDs de @ b

Vuelca en @p v la configuraci�n de LEDs contenida en @p b. @c true significa encendido y @c false significa apagado. El tama�o de @p v debe ser 8.
*/
void volcar(bloqueLed b, bool v[]);

/**
@brief devuelve las posiciones de los LEDs encendidos
@param b el @c bloqueLed que se quiere consultar
@param posic vector de enteros (valores entre 0 a 7) que indican la posici�n de los LEDs de @p b que est�n encendidos
@param cuantos n�mero de LEDs encendidos en @p b (n�mero de elementos usados en el vector @p posic)
*/
void encendidos(bloqueLed b, int posic[], int &cuantos);

#endif
