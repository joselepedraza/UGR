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

void print(bloqueLed b) {



  }
