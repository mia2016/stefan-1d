set terminal png enhanced size 1000, 1200
set output "grense.png"


set multiplot layout 2, 1

set xrange [0:9]
set yrange [0:1]


set ylabel "Dybde [m]"
set xlabel "Tid [dager]"

set title "a)" font ",16" offset -15, 0
    
plot "results/high_1/log.out" u 1:31 w lines title "Snø 100W",\
    "results/middle_1/log.out" u 1:31 w lines title "Snø 50W",\
    "results/low_1/log.out" u 1:31 w lines title "Snø 0W",\
    "results/high_1/log.out" u 1:28 w lines title "Is 100W",\
    "results/middle_1/log.out" u 1:28 w lines title "Is 50W",\
    "results/low_1/log.out" u 1:28 w lines title "Is 0W"

set title "b)" font ",16" offset -15, 0
plot "results/high_05/log.out" u 1:28 w lines title "Istykkelse",\
    "results/high_05/log.out" u 1:31 w lines title "Snøtykkelse",\
    "results/middle_05/log.out" u 1:28 w lines title "Istykkelse",\
    "results/middle_05/log.out" u 1:31 w lines title "Snøtykkelse",\
    "results/low_05/log.out" u 1:28 w lines title "Istykkelse",\
    "results/low_05/log.out" u 1:31 w lines title "Snøtykkelse"

