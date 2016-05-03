set terminal png enhanced size 1000, 1200
set output "grense.png"


set multiplot layout 3, 2

set key off

set xrange [0:9]
set yrange [0:1]


set ylabel "Dybde [m]"
set xlabel "Tid [dager]"

set title "a)" font ",16" offset -15, 0
plot "results/high_1/log.out" u 1:28 w lines title "Istykkelse",\
    "results/high_1/log.out" u 1:31 w lines title "Snøtykkelse"

set title "b)" font ",16" offset -15, 0
plot "results/high_05/log.out" u 1:28 w lines title "Istykkelse",\
    "results/high_05/log.out" u 1:31 w lines title "Snøtykkelse"

set title "c)" font ",16" offset -15, 0
plot "results/middle_1/log.out" u 1:28 w lines title "Istykkelse",\
    "results/middle_1/log.out" u 1:31 w lines title "Snøtykkelse"

set title "d)" font ",16" offset -15, 0
plot "results/middle_05/log.out" u 1:28 w lines title "Istykkelse",\
     "results/middle_05/log.out" u 1:31 w lines title "Snøtykkelse"

set title "e)" font ",16" offset -15, 0
plot "results/low_1/log.out" u 1:28 w lines title "Istykkelse",\
    "results/low_1/log.out" u 1:31 w lines title "Snøtykkelse"

set title "f)" font ",16" offset -15, 0
plot "results/low_05/log.out" u 1:28 w lines title "Istykkelse",\
    "results/low_05/log.out" u 1:31 w lines title "Snøtykkelse"
