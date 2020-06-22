#!/bin/bash

#   burbuja:       1000 a     51000 de     2000 en     2000
#   insercion:     1000 a     51000 de     2000 en     2000
#	seleccion:     1000 a     51000 de     2000 en     2000

#   mergesort   1000000 a  25100000 de  1000000 en  1000000
#   heapsort    1000000 a  25100000 de  1000000 en  1000000
#   quicksort   1000000 a  25100000 de  1000000 en  1000000

echo "" >> ./data/salida$1.dat

let size=0
let max=0
let intervalo=0

if [[ ("$1" = "burbuja") || ("$1" = "seleccion") || ("$1" = "insercion") || ("$1" = "burbujaO2") || ("$1" = "seleccionO2") || ("$1" = "insercionO2") ]]
then
    size=1000
    max=51000
    intervalo=2000
elif [[ ("$1" = "heapsort") || ("$1" = "mergesort") || ("$1" = "quicksort") || ("$1" = "heapsortO2") || ("$1" = "mergesortO2") || ("$1" = "quicksortO2") ]]
then
    size=1000000
    max=25100000
    intervalo=1000000
elif [[ ("$1" = "floyd") || ("$1" = "floydO2") ]]
then
    size=200
    max=2700
    intervalo=100
elif [[ ("$1" = "hanoi") || ("$1" = "hanoiO2") ]]
then
    size=9
    max=34
    intervalo=1
fi


while (($size < $max ))
do
    ./bin/$1 $size >> ./data/MIO/salida$1.dat
    let size+=intervalo
done
