#ifndef __PILA_MAX_H__
#define __PILA_MAX_H__
//COMO FUNCIONAN LAS OPCIONES PRECOMPILACION
  #define CUAL_COMPILA 2
  #if CUAL_COMPILA== 2
  	#include "pila_max_vd.h"
    typedef Pila_max_VD pila_max;
  #else
  	#include "pila_max_cola.h"
    typedef Pila_max_Cola pila_max;
  #endif
#endif
