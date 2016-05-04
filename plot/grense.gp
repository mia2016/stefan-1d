set terminal png enhanced size 900, 600
set output "grense.png"

set xtics 4

set ylabel "Dybde [m]"
set xlabel "Tid [dager]"

set xtics nomirror
set ytics nomirror

set border 3

plot "results/ultra_1/log.out" u 1:($211-$208) lc "blue" lw 2 w lines title "Kjøling",\
    "results/low_1/log.out" u 1:($211-$208) lc "red" lw 2 w lines title "Ingen kjøling"
