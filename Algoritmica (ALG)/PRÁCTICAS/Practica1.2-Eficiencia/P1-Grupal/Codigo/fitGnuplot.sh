#!/bin/bash

array=("burbuja" "burbujaO2" "insercion" "insercionO2" "seleccion" "seleccionO2" "mergesort" "mergesortO2" "quicksort" "quicksortO2" "heapsort" "heapsortO2" "floyd" "floydO2" "hanoi" "hanoiO2")

#Ajuste por grupo (de los 4)
for j in "${array[@]}"
do
    gnuplot -e " 

        f(x)=a0*x*x+a1*x+a2;
        g(x)=b0*x*x+b1*x+b2;
        h(x)=c0*x*x+c1*x+c2;
        j(x)=d0*x*x+d1*x+d2;

        fit f(x) 'data/Raul/salida$j.dat' via a0,a1,a2;
        fit g(x) 'data/Jose/salida$j.dat' via b0,b1,b2;
        fit h(x) 'data/Antonio/salida$j.dat' via c0,c1,c2;
        fit j(x) 'data/Pedro/salida$j.dat' via d0,d1,d2;

        set key left; set key Left; set terminal png; set output 'img/Ajustes/MIO/AjusteCuadratico/Ajuste$j.png';

        plot 
            f(x) title 'f(x)=x²+x+1', 'data/Raul/salida$j.dat' title 'Eficiencia Raul $j' with p, 
            g(x) title 'g(x)=x²+x+1', 'data/Jose/salida$j.dat' title 'Eficiencia Jose $j' with p, 
            h(x) title 'h(x)=x²+x+1', 'data/Antonio/salida$j.dat' title 'Eficiencia Antonio $j' with p,
            j(x) title 'j(x)=x²+x+1', 'data/Pedro/salida$j.dat' title 'Eficiencia Pedro $j' with p"

done

for j in "${array[@]}"
do
    gnuplot -e "

        f(x)=a0*x*(log10(x)/log10(2));
        g(x)=b0*x*(log10(x)/log10(2));
        h(x)=c0*x*(log10(x)/log10(2));
        j(x)=d0*x*(log10(x)/log10(2));

        fit f(x) 'data/Raul/salida$j.dat' via a0;
        fit g(x) 'data/Jose/salida$j.dat' via b0;
        fit h(x) 'data/Antonio/salida$j.dat' via c0;
        fit j(x) 'data/Pedro/salida$j.dat' via d0;

        set key left; set key Left; set terminal png; set output 'img/Ajustes/MIO/AjusteLogaritmico/Ajuste$j.png'; 

        plot 
            f(x) title 'f(x)=x*log2(x)', 'data/Raul/salida$j.dat' title 'Eficiencia Raul $j' with p, 
            g(x) title 'g(x)=x*log2(x)', 'data/Jose/salida$j.dat' title 'Eficiencia Jose $j' with p, 
            h(x) title 'h(x)=x*log2(x)', 'data/Antonio/salida$j.dat' title 'Eficiencia Antonio $j' with p,
            j(x) title 'j(x)=x*log2(x)', 'data/Pedro/salida$j.dat' title 'Eficiencia Pedro $j' with p"
done

for j in "${array[@]}"
do
    gnuplot -e " 

        f(x)=a0*x*x*x+a1*x*x+a2*x+a3;
        g(x)=b0*x*x*x+b1*x*x+b2*x+b3;
        h(x)=c0*x*x*x+c1*x*x+c2*x+c3;
        j(x)=d0*x*x*x+d1*x*x+d2*x+d3;

        fit f(x) 'data/Raul/salida$j.dat' via a0,a1,a2,a3;
        fit g(x) 'data/Jose/salida$j.dat' via b0,b1,b2,b3;
        fit h(x) 'data/Antonio/salida$j.dat' via c0,c1,c2,c3;
        fit j(x) 'data/Pedro/salida$j.dat' via d0,d1,d2,d3;

        set key left; set key Left; set terminal png; set output 'img/Ajustes/MIO/AjusteCubico/Ajuste$j.png';

        plot 
            f(x) title 'f(x)=x³+x²+x+1', 'data/Raul/salida$j.dat' title 'Eficiencia Raul $j' with p, 
            g(x) title 'g(x)=x³+x²+x+1', 'data/Jose/salida$j.dat' title 'Eficiencia Jose $j' with p, 
            h(x) title 'h(x)=x³+x²+x+1', 'data/Antonio/salida$j.dat' title 'Eficiencia Antonio $j' with p,
            j(x) title 'j(x)=x³+x²+x+1', 'data/Pedro/salida$j.dat' title 'Eficiencia Pedro $j' with p"
done

for j in "${array[@]}"
do
    gnuplot -e "

        f(x)=a0*2**x;
        g(x)=b0*2**x;
        h(x)=c0*2**x;
        j(x)=d0*2**x;

        fit f(x) 'data/Raul/salida$j.dat' via a0;
        fit g(x) 'data/Jose/salida$j.dat' via b0;
        fit h(x) 'data/Antonio/salida$j.dat' via c0;
        fit j(x) 'data/Pedro/salida$j.dat' via d0;

        set key left; set key Left; set terminal png; set output 'img/Ajustes/MIO/AjustePotencia/Ajuste$j.png'; 

        plot 
            f(x) title 'f(x)=2^x', 'data/Raul/salida$j.dat' title 'Eficiencia Raul $j' with p, 
            g(x) title 'g(x)=2^x', 'data/Jose/salida$j.dat' title 'Eficiencia Jose $j' with p, 
            h(x) title 'h(x)=2^x', 'data/Antonio/salida$j.dat' title 'Eficiencia Antonio $j' with p,
            j(x) title 'j(x)=2^x', 'data/Pedro/salida$j.dat' title 'Eficiencia Pedro $j' with p"
done