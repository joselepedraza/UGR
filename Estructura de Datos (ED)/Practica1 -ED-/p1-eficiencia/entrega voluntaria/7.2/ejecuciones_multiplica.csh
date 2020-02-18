#!/bin/csh
@ inicio = 0
@ fin = 200
@ incremento = 2
set ejecutable = multiplicaV1
set salida = tiempos_multiplicaV1.dat

@ i = $inicio
echo > $salida
while ( $i <= $fin )	
  echo `./{$ejecutable} $i $i $i` >> $salida
  @ i += $incremento
end
