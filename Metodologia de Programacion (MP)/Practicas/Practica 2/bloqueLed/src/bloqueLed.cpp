#include <iostream>
#include "bloqueLed.h"
using namespace std;

void on(bloqueLed &b, int pos) {
  bloqueLed mask;

  if ((pos >= 0) && (pos < 8)) {
    mask = 0x1 << pos;
    b = b | mask;
  }
}

void off(bloqueLed &b, int pos) {
  bloqueLed mask;

  if ((pos >= 0) && (pos < 8)) {
    mask = 0x1 << pos;
    mask = ~mask;
    b = b & mask;
  }
}

void encender(bloqueLed &b) {
  bloqueLed mask;

  mask = 0xFF;
  b = b | mask;
}


void apagar(bloqueLed &b) {
  bloqueLed mask;

  mask = 0x00;
  b = b & mask;
}

bool get(bloqueLed b, int pos) {
  bloqueLed mask;
  bool estado = false;

  if ((pos >= 0) && (pos < 8)) {
    mask = 0x1 << pos;
    b = b & mask;
    if (b > 0) {
      estado = true;
    }
  }
  return estado;
}

string bloqueLedToString(bloqueLed b) {
  string bloque;
  bool estado = false;

  for (int i = 0; i < 8; i++) {
    estado = get(b,i);
    if (estado == true) {
      bloque = bloque + "1";
    } else {
      bloque = bloque + "0";
    }
  }
  return bloque;
}

void asignar(bloqueLed &b, const bool v[]) {
  for (int i = 0; i < 8; i++) {
    if (v[i] == true) {
      on(b,i);
    } else {
      off(b,i);
    }
  }
}

void volcar(bloqueLed b, bool v[]) {
  //no usado
}

void encendidos(bloqueLed b, int posic[], int &cuantos) {
  bool estado;
  int j = 0;
  cuantos = 0;

  for (int i = 0; i < 8; i++) {
    estado = get(b,i);
    if (estado == true) {
      posic[j] = i;
      j++;
      cuantos++;
    }
  }
}

void print(bloqueLed b) {
  //no usado
}
