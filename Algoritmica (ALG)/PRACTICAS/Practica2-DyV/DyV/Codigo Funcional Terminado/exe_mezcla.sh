#!/bin/bash

# Num max = 20 000 000
# Num vect = {1, 5, 10}

array=("2" "5" "10")
for i in "${array[@]}"
do
    let size=10000
    let max=20001000
    let intervalo=799600
    echo "" >> ./data/salida$1_$i.dat
    while (($size < $max ))
    do
        ./bin/$1 $size $i >> ./data/salida$1_$i.dat
        let size+=intervalo
    done
done
