#!/bin/sh

# Ejecuciones 

echo -e "Ejecutando vmc ulysses16"
./bin/tsp_vmc data/tsp_escenarios/ulysses16.tsp > tsp_u16_vmc.dat
echo -e "Ejecutando vmc ulysses22"
./bin/tsp_vmc data/tsp_escenarios/ulysses22.tsp > tsp_u22_vmc.dat
echo -e "Ejecutando vmc att48"
./bin/tsp_vmc data/tsp_escenarios/att48.tsp > tsp_att48_vmc.dat
echo -e "Ejecutando vmc a280"
./bin/tsp_vmc data/tsp_escenarios/a280.tsp > tsp_a280_vmc.dat

echo -e "Ejecutando insercion ulysses16"
./bin/tsp_insercion data/tsp_escenarios/ulysses16.tsp > tsp_u16_ins.dat
echo -e "Ejecutando insercion ulysses22"
./bin/tsp_insercion data/tsp_escenarios/ulysses22.tsp > tsp_u22_ins.dat
echo -e "Ejecutando insercion att48"
./bin/tsp_insercion data/tsp_escenarios/att48.tsp > tsp_att48_ins.dat
echo -e "Ejecutando insercion a280"
./bin/tsp_insercion data/tsp_escenarios/a280.tsp > tsp_a280_ins.dat

echo -e "Ejecutando 2opt ulysses16 base"
./bin/tsp_2opt data/tsp_escenarios/ulysses16.tsp base > tsp_u16_2opt_base.dat
echo -e "Ejecutando 2opt ulysses16 vmc"
./bin/tsp_2opt data/tsp_escenarios/ulysses16.tsp vmc > tsp_u16_2opt_vmc.dat
echo -e "Ejecutando 2opt ulysses22 base"
./bin/tsp_2opt data/tsp_escenarios/ulysses22.tsp base > tsp_u22_2opt_base.dat
echo -e "Ejecutando 2opt ulysses22 vmc"
./bin/tsp_2opt data/tsp_escenarios/ulysses22.tsp vmc > tsp_u22_2opt_vmc.dat
echo -e "Ejecutando 2opt att48 base"
./bin/tsp_2opt data/tsp_escenarios/att48.tsp base > tsp_att48_2opt_base.dat
echo -e "Ejecutando 2opt att48 vmc"
./bin/tsp_2opt data/tsp_escenarios/att48.tsp vmc > tsp_att48_2opt_vmc.dat
echo -e "Ejecutando 2opt a280 base"
./bin/tsp_2opt data/tsp_escenarios/a280.tsp base > tsp_a280_2opt_base.dat
echo -e "Ejecutando 2opt a280 vmc"
./bin/tsp_2opt data/tsp_escenarios/a280.tsp vmc > tsp_a280_2opt_vmc.dat
echo -e "Fin del script"

# Graficar en gnuplot

# plot "tsp_u16_vmc.dat" using 2:3 title "VMC-Ulysses16" w lp
# plot "tsp_u22_vmc.dat" using 2:3 title "VMC-Ulysses22" w lp
# plot "tsp_att48_vmc.dat" using 2:3 title "VMC-att48" w lp
# plot "tsp_a280_vmc.dat" using 2:3 title "VMC-a280" w lp
# plot "tsp_u16_ins.dat" using 2:3 title "INS-Ulysses16" w lp
# plot "tsp_u22_ins.dat" using 2:3 title "INS-Ulysses22" w lp
# plot "tsp_att48_ins.dat" using 2:3 title "INS-att48" w lp
# plot "tsp_a280_ins.dat" using 2:3 title "INS-a280" w lp
# plot "tsp_u16_2opt_base.dat" using 2:3 title "2opt-Ulysses16-base" w lp
# plot "tsp_u16_2opt_vmc.dat" using 2:3 title "2opt-Ulysses16-vmc" w lp
# plot "tsp_u22_2opt_base.dat" using 2:3 title "2opt-Ulysses22-base" w lp
# plot "tsp_u22_2opt_vmc.dat" using 2:3 title "2opt-Ulysses22-vmc" w lp
# plot "tsp_att48_2opt_base.dat" using 2:3 title "2opt-att48-base" w lp
# plot "tsp_att48_2opt_vmc.dat" using 2:3 title "2opt-att48-vmc" w lp
# plot "tsp_a280_2opt_base.dat" using 2:3 title "2opt-a280-base" w lp
# plot "tsp_a280_2opt_vmc.dat" using 2:3 title "2opt-a280-vmc" w lp