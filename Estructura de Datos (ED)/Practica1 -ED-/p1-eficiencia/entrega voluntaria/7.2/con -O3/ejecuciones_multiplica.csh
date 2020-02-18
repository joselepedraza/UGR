#!/bin/csh
@ inicio = 0
@ fin = 200
@ incremento = 2
set ejecutable = multiplicaV103
set salida = tiempos_multiplicaV103.dat

@ i = $inicio
echo > $salida
while ( $i <= $fin )	
  echo `./{$ejecutable} $i $i $i` >> $salida
  @ i += $incremento
end
