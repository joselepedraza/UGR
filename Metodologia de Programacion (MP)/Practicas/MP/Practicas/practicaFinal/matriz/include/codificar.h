#ifndef _CODIFICAR_H_
#define	_CODIFICAR_H_
#include <iostream>
#include <cstring>
#include "byte.h"
#include "imagen.h"
#include "pgm.h"

bool ocultar(Imagen& img,char mensaje[]);
bool revelar(Imagen& img,char mensaje[], const int MAXTAM);

#endif	
