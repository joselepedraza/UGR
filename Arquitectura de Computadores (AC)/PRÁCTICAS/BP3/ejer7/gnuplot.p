set ylabel "Tiempo (seg)"
gnuplot> set xlabel "Chunk"
gnuplot> replot
gnuplot> set title 'Comparativa Static,Dynamic,Guided - ATCGRID'                 
gnuplot> plot 'static.dat' title 'static' with lp,'dynamic.dat' title 'dynamic' with lp,'guided.dat' title 'guided' with lp

