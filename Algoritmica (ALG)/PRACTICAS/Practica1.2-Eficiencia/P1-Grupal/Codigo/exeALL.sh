#!/bin/bash

array=("burbuja" "burbujaO2" "insercion" "insercionO2" "seleccion" "seleccionO2" "mergesort" "mergesortO2" "quicksort" "quicksortO2" "heapsort" "heapsortO2" "floyd" "floydO2" "hanoi" "hanoiO2")
for i in "${array[@]}"
do
    echo -e "Ejecutando $i"
    ./tiempos.sh $i
done
