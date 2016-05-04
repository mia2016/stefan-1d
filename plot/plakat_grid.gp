set terminal png enhanced size 800, 600
set output "plakat_grense.png"

set ylabel "Posisjon [m]" offset 1
set xlabel "Tid [dager]"

set xtics 4 nomirror
set ytics nomirror

set border 3

plot "results/ultra_1/log.out" u 1:($211-$208) lc "blue" lw 2 with lines title "Kjøling",\
    "results/low_1/log.out" u 1:($211-$208) lc "red" lw 2 w lines title "Ingen kjøling"
