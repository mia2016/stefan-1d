set terminal png enhanced size 600, 800
set output "plakat_grense.png"

set multiplot layout 2, 1

set ylabel "Posisjon [m]"
set xlabel "Tid [dager]"

unset key

set xrange [0:10]
set yrange [0:1]

set xtics
set ytics

set title "a)" font ",20" offset -25,0
plot "results/high_1/log.out" u 1:28 with lines,\
    "results/high_1/log.out" u 1:31 w lines 
set title "b)" font ",20" offset -25,0
plot "results/low_1/log.out" u 1:28 with lines,\
    "results/low_1/log.out" u 1:31 with lines
