#!/bin/bash

array=("burbuja" "burbujaO2" "insercion" "insercionO2" "seleccion" "seleccionO2" "mergesort" "mergesortO2" "quicksort" "quicksortO2" "heapsort" "heapsortO2" "floyd" "floydO2" "hanoi" "hanoiO2")

#Graficas individuales (literalmente)
for j in "${array[@]}"
do
    gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Individuales/Raul/salida$j.png'; 
        plot 'data/Raul/salida$j.dat' title 'Eficiencia $j' with l"
    gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Individuales/Jose/salida$j.png'; 
        plot 'data/Jose/salida$j.dat' title 'Eficiencia $j' with l"
    gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Individuales/Antonio/salida$j.png'; 
        plot 'data/Antonio/salida$j.dat' title 'Eficiencia $j' with l"
    gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Individuales/Pedro/salida$j.png'; 
        plot 'data/Pedro/salida$j.dat' title 'Eficiencia $j' with l"
done

#Graficas por tipo algoritmo (de los 4)
for j in "${array[@]}"
do
    gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Grupales/TipoAlg/Comparada$j.png'; plot 
        'data/Raul/salida$j.dat' title 'Eficiencia Raul $j' with lp, 
        'data/Jose/salida$j.dat' title 'Eficiencia Jose $j' with l, 
        'data/Antonio/salida$j.dat' title 'Eficiencia Antonio $j' with lp,
        'data/Pedro/salida$j.dat' title 'Eficiencia Pedro $j' with l"
done

#Graficas por tipo eficiencia (de los 4)
gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Grupales/TipoEfi/GrupoCuadraticas.png'; plot 
    'data/Raul/salidaburbuja.dat' title 'Eficiencia Raul burbuja' with lp, 
    'data/Jose/salidaburbuja.dat' title 'Eficiencia Jose burbuja' with l, 
    'data/Antonio/salidaburbuja.dat' title 'Eficiencia Antonio burbuja' with lp, 
    'data/Pedro/salidaburbuja.dat' title 'Eficiencia Pedro burbuja' with l,

    'data/Raul/salidaseleccion.dat' title 'Eficiencia Raul seleccion' with lp, 
    'data/Jose/salidaseleccion.dat' title 'Eficiencia Jose seleccion' with l, 
    'data/Antonio/salidaseleccion.dat' title 'Eficiencia Antonio seleccion' with lp, 
    'data/Pedro/salidaseleccion.dat' title 'Eficiencia Pedro seleccion' with l,

    'data/Raul/salidainsercion.dat' title 'Eficiencia Raul insercion' with lp, 
    'data/Jose/salidainsercion.dat' title 'Eficiencia Jose insercion' with l, 
    'data/Antonio/salidainsercion.dat' title 'Eficiencia Antonio insercion' with lp, 
    'data/Pedro/salidainsercion.dat' title 'Eficiencia Pedro insercion' with l"
gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Grupales/TipoEfi/GrupoNLogaritmicas.png'; plot 
    'data/Raul/salidamergesort.dat' title 'Eficiencia Raul mergesort' with lp, 
    'data/Jose/salidamergesort.dat' title 'Eficiencia Jose mergesort' with l, 
    'data/Antonio/salidamergesort.dat' title 'Eficiencia Antonio mergesort' with lp, 
    'data/Pedro/salidamergesort.dat' title 'Eficiencia Pedro mergesort' with l,

    'data/Raul/salidaquicksort.dat' title 'Eficiencia Raul quicksort' with lp, 
    'data/Jose/salidaquicksort.dat' title 'Eficiencia Jose quicksort' with l, 
    'data/Antonio/salidaquicksort.dat' title 'Eficiencia Antonio quicksort' with lp, 
    'data/Pedro/salidaquicksort.dat' title 'Eficiencia Pedro quicksort' with l,

    'data/Raul/salidaheapsort.dat' title 'Eficiencia Raul heapsort' with lp, 
    'data/Jose/salidaheapsort.dat' title 'Eficiencia Jose heapsort' with l, 
    'data/Antonio/salidaheapsort.dat' title 'Eficiencia Antonio heapsort' with lp, 
    'data/Pedro/salidaheapsort.dat' title 'Eficiencia Pedro heapsort' with l"
gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Grupales/TipoEfi/GrupoPotencia2.png'; plot 
    'data/Raul/salidahanoi.dat' title 'Eficiencia Raul hanoi' with lp, 
    'data/Jose/salidahanoi.dat' title 'Eficiencia Jose hanoi' with l, 
    'data/Antonio/salidahanoi.dat' title 'Eficiencia Antonio hanoi' with lp, 
    'data/Pedro/salidahanoi.dat' title 'Eficiencia Pedro hanoi' with l"
gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Grupales/TipoEfi/GrupoCubica.png'; plot 
    'data/Raul/salidafloyd.dat' title 'Eficiencia Raul floyd' with lp, 
    'data/Jose/salidafloyd.dat' title 'Eficiencia Jose floyd' with l, 
    'data/Antonio/salidafloyd.dat' title 'Eficiencia Antonio floyd' with lp, 
    'data/Pedro/salidafloyd.dat' title 'Eficiencia Pedro floyd' with l"

#Graficas por grupo eficienciaO2 (de los 4)
gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Grupales/TipoEfi/GrupoCuadraticasO2.png'; plot 
    'data/Raul/salidaburbujaO2.dat' title 'Eficiencia Raul burbujaO2' with lp, 
    'data/Jose/salidaburbujaO2.dat' title 'Eficiencia Jose burbujaO2' with l, 
    'data/Antonio/salidaburbujaO2.dat' title 'Eficiencia Antonio burbujaO2' with lp, 
    'data/Pedro/salidaburbujaO2.dat' title 'Eficiencia Pedro burbujaO2' with l,

    'data/Raul/salidaseleccionO2.dat' title 'Eficiencia Raul seleccionO2' with lp, 
    'data/Jose/salidaseleccionO2.dat' title 'Eficiencia Jose seleccionO2' with l, 
    'data/Antonio/salidaseleccionO2.dat' title 'Eficiencia Antonio seleccionO2' with lp, 
    'data/Pedro/salidaseleccionO2.dat' title 'Eficiencia Pedro seleccionO2' with l,

    'data/Raul/salidainsercionO2.dat' title 'Eficiencia Raul insercionO2' with lp, 
    'data/Jose/salidainsercionO2.dat' title 'Eficiencia Jose insercionO2' with l, 
    'data/Antonio/salidainsercionO2.dat' title 'Eficiencia Antonio insercionO2' with lp, 
    'data/Pedro/salidainsercionO2.dat' title 'Eficiencia Pedro insercionO2' with l"
gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Grupales/TipoEfi/GrupoNLogaritmicasO2.png'; plot 
    'data/Raul/salidamergesortO2.dat' title 'Eficiencia Raul mergesortO2' with lp, 
    'data/Jose/salidamergesortO2.dat' title 'Eficiencia Jose mergesortO2' with l, 
    'data/Antonio/salidamergesortO2.dat' title 'Eficiencia Antonio mergesortO2' with lp, 
    'data/Pedro/salidamergesortO2.dat' title 'Eficiencia Pedro mergesortO2' with l,

    'data/Raul/salidaquicksortO2.dat' title 'Eficiencia Raul quicksortO2' with lp, 
    'data/Jose/salidaquicksortO2.dat' title 'Eficiencia Jose quicksortO2' with l, 
    'data/Antonio/salidaquicksortO2.dat' title 'Eficiencia Antonio quicksortO2' with lp, 
    'data/Pedro/salidaquicksortO2.dat' title 'Eficiencia Pedro quicksortO2' with l,

    'data/Raul/salidaheapsortO2.dat' title 'Eficiencia Raul heapsortO2' with lp, 
    'data/Jose/salidaheapsortO2.dat' title 'Eficiencia Jose heapsortO2' with l, 
    'data/Antonio/salidaheapsortO2.dat' title 'Eficiencia Antonio heapsortO2' with lp, 
    'data/Pedro/salidaheapsortO2.dat' title 'Eficiencia Pedro heapsortO2' with l"
gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Grupales/TipoEfi/GrupoPotencia2O2.png'; plot 
    'data/Raul/salidahanoiO2.dat' title 'Eficiencia Raul hanoiO2' with lp, 
    'data/Jose/salidahanoiO2.dat' title 'Eficiencia Jose hanoiO2' with l, 
    'data/Antonio/salidahanoiO2.dat' title 'Eficiencia Antonio hanoiO2' with lp, 
    'data/Pedro/salidahanoiO2.dat' title 'Eficiencia Pedro hanoiO2' with l"
gnuplot -e "set key left; set key Left; set terminal png; set output 'img/Grupales/TipoEfi/GrupoCubicaO2.png'; plot 
    'data/Raul/salidafloydO2.dat' title 'Eficiencia Raul floydO2' with lp, 
    'data/Jose/salidafloydO2.dat' title 'Eficiencia Jose floydO2' with l, 
    'data/Antonio/salidafloydO2.dat' title 'Eficiencia Antonio floydO2' with lp, 
    'data/Pedro/salidafloydO2.dat' title 'Eficiencia Pedro floydO2' with l"