set terminal png enhanced size 900, 600
set output "validering.png"

set xtics 4

set ylabel "Dybde [m]"
set xlabel "Tid [dager]"

set xtics nomirror
set ytics nomirror

set border 3

plot "results/validering/dag/log.out" u 1:211 lc "blue" lw 2 w lines title "Beregnet",\
    "data_oppdal_dag.csv" u ($7/86400):($5/100.0) lc "red" lw 2 w lines title "Målt"
