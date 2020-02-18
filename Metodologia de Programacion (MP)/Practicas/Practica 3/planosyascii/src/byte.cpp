#include <iostream>
#include "byte.h"
using namespace std;

void on(byte &b, int bit) {
  byte mask;

  if ((bit >= 0) && (bit < 8)) {
    mask = 0x1 << bit;
    b = b | mask;
  }
}

void off(byte &b, int bit) {
  byte mask;

  if ((bit >= 0) && (bit < 8)) {
    mask = 0x1 << bit;
    mask = ~mask;
    b = b & mask;
  }
}

void encender(byte &b) {
  byte mask;

  mask = 0xFF;
  b = b | mask;
}


void apagar(byte &b) {
  byte mask;

  mask = 0x00;
  b = b & mask;
}

bool getbit(byte b, int bit) {
  byte mask;
  bool estado = false;

  if ((bit >= 0) && (bit < 8)) {
    mask = 0x1 << bit;
    b = b & mask;
    if (b > 0) {
      estado = true;
    }
  }
  return estado;
}

string bloqueLedToString(byte b) {
  string bloque;
  bool estado = false;

  for (int i = 0; i < 8; i++) {
    estado = getbit(b,i);
    if (estado == true) {
      bloque = bloque + "1";
    } else {
      bloque = bloque + "0";
    }
  }
  return bloque;
}

void asignar(byte &b, const bool v[]) {
  for (int i = 0; i < 8; i++) {
    if (v[i] == true) {
      on(b,i);
    } else {
      off(b,i);
    }
  }
}

void volcar(byte b, bool v[]) {
  //no usado
}

void encendidos(byte b, int posic[], int &cuantos) {
  bool estado;
  int j = 0;
  cuantos = 0;

  for (int i = 0; i < 8; i++) {
    estado = getbit(b,i);
    if (estado == true) {
      posic[j] = i;
      j++;
      cuantos++;
    }
  }
}
