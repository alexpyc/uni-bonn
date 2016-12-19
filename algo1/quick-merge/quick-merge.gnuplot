#!/usr/local/bin/gnuplot -persist

set title "Die Laufzeiten von QuickSort und MergeSort"
set xlabel "n"
set ylabel "Durchschnittliche Laufzeit (Nanosekunde)"
set xrange [1:500]
set yrange [0:200000]
set key top left
plot 'data.dat' using 1:2 with lines title 'QuickSort', 'data.dat' using 1:3 with lines title 'MergeSort'
set terminal png enhanced font 'Helvetica,12'
set output 'quick-merge.png'
replot
quit
