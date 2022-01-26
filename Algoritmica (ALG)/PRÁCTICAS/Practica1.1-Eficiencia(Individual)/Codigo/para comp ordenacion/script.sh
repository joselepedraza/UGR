#!/bin/bash

#./script.sh ejecutable liminf limsup intervalo
#./script.sh burbuja 1000 50000 2000
#el script genera un fichero .dat con los resultados y con nombre salida(loquesea).dat para que este identificado


#en este caso tomamos el mismo tamaño del problema inicial para los 6 algoritmos de ordenacion, para poder compararlos correctamente en una grafica
#                   $2          $3          $4
#   burbuja:       1000 a     63500 de     2500 en 2500
#   insercion:     1000 a     63500 de     2500 en 2500
#	seleccion:     1000 a     63500 de     2500 en 2500

#   mergesort:     1000 a  26000000 de  1000000 en 1000000
#   quicksort:     1000 a  26000000 de  1000000 en 1000000
#   heapsort:      1000 a  26000000 de  1000000 en 1000000

echo "" >> salida$1.dat
let i=$2
while (($i < $3))
do
    ./$1 $i >> salida$1.dat
    let i+=$4
done
