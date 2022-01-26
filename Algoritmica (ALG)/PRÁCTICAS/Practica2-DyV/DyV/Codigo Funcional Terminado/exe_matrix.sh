#!/bin/bash

# Num max = 20 000 000
# Num vect = {1, 5, 10}



let size=10
let max=1001
let intervalo=40
echo "" >> ./data/salida$1.dat
while (($size < $max ))
do
    ./bin/$1 $size  >> ./data/salida$1.dat
    let size+=intervalo
done
