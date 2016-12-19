#!/usr/local/bin/gnuplot -persist

set title "Die Laufzeiten von InsertionSort und MergeSort"
set xlabel "n"
set ylabel "Durchschnittliche Laufzeit (Nanosekunde)"
set xrange [1:500]
set yrange [0:600000]
set key top left
plot filename using 1:2 with lines title 'InsertionSort'
set terminal png enhanced font 'Helvetica,12'
set output 'laufzeitInsertion.png'
replot
plot filename using 1:3 with lines title 'MergeSort'
set output 'insertion-merge.png'
replot
quit
