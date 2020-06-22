#!/bin/bash

array=("30" "60" "120")
for i in "${array[@]}"
do
    let size=100
    let max=2701
    let intervalo=104
    echo "" >> ./data/salida$1_$i.dat
    while (($size < $max ))
    do
        ./bin/$1 $i $size >> ./data/salida$1_$i.dat
        let size+=intervalo
    done
done
