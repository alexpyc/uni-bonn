#!/usr/local/bin/gnuplot -persist

set title "Die Approximationsguete von ApproxKP"
set xlabel "n"
set ylabel "Approximationsguete"
set yrange [0.5:1.5]
set key bottom right
plot 'data.txt' using 2 with lines title 'Minimal', 'data.txt' using 3 with lines title 'Maximal', 'data.txt' using 4 with lines title 'Durchschnittlich'
set terminal png enhanced font 'Helvetica,12'
set output 'approxKP.png'
replot
quit
