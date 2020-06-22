#!/bin/bash

let size=2
let max=15
let intervalo=1
echo "" >> ./data/salida$1.dat
while (($size < $max ))
do
    ./bin/$1 $size  >> ./data/salida$1.dat
    let size+=intervalo
done
