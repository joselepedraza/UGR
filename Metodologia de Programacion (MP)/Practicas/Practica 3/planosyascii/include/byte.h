#ifndef _BYTE_H_
#define	_BYTE_H_

#include <string>
using namespace std;

typedef unsigned char byte; ///< Un @c bloqueLed contiene el estado de 8 LEDs

/**
@brief enciende el LED @p pos del @c bloqueLed @p b
@param b 	el @c bloqueLed cuyo LED se quiere activar
@param pos 	el LED dentro de @p b que se quiere activar (0 m�s a la derecha)
*/
void on(byte &b, int bit);

/**
@brief apaga el LED @p pos del  @c bloqueLed @p b
@param b 	el @c bloqueLed cuyo LED se quiere desactivar
@param pos 	el LED dentro de @p b que se quiere desactivar (0 m�s a la derecha)
*/
void off(byte &b, int bit);

/**
@brief devuelve el estado del LED (encendido = true, apagado = false) en la posici�n @p pos
@param b 	el @c bloqueLed que se quiere consultar
@param pos 	el LED dentro de @ b que se quiere consultar (0 m�s a la derecha)
@retval true 	si el LED en la posici�n @p pos est� encendido
@retval false	si el LED en la posici�n @p pos est� apagado
*/
bool getbit(byte b, int bit);


/**
@brief devuelve un string conteniendo una secuencia de '0's y '1's correspondiente  al estado de cada LED
@param b el @c bloqueLed que se quiere imprimir

Por ejemplo, si en el @c bloqueLed @c b est�n encendidos los LEDs en posiciones 1 y 3 (0 m�s a la derecha), @c bloqueLedToString(b); devolver� el string @c "00001010"

*/
#endif
